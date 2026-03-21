#!/usr/bin/env python3
"""
Simulation runner for WinterChallenge2026-Exotec.

Runs one or more matches between two bots using the Java HeadlessRunner
and writes a detailed result log to a file.

Usage:
    python simulate.py <bot1_command> <bot2_command> [options]

Examples:
    # Two bot binaries with config files
    python simulate.py "../bot/bot --config ../config/optimized_params.json" "../bot/bot" \\
        --matches 5 --log results.log

    # Use shorthand flags instead of inline commands
    python simulate.py \\
        --bot1 "../bot/bot --config ../config/optimized_params.json" \\
        --bot2 "../bot/bot" \\
        --matches 10 --seed 42 --league-level 3 --log results.log
"""

import argparse
import os
import random
import subprocess
import sys
import time

# ---------------------------------------------------------------------------
# Path helpers (mirror match_runner.py so this module is self-contained)
# ---------------------------------------------------------------------------
REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))


def _get_classpath():
    """Return the Java classpath for HeadlessRunner, building it if needed."""
    target_dir = os.path.join(REPO_ROOT, "target")
    cp_file = os.path.join(target_dir, ".training_cp.txt")

    if not os.path.exists(cp_file):
        ret = subprocess.run(
            [
                "mvn",
                "dependency:build-classpath",
                "-q",
                "-DincludeScope=test",
                f"-Dmdep.outputFile={cp_file}",
            ],
            cwd=REPO_ROOT,
            capture_output=True,
            text=True,
        )
        if ret.returncode != 0:
            return None

    with open(cp_file, "r") as f:
        deps = f.read().strip()

    classes = os.path.join(target_dir, "classes")
    test_classes = os.path.join(target_dir, "test-classes")
    return f"{classes}:{test_classes}:{deps}"


def run_single_match(bot1_cmd, bot2_cmd, seed=None, league_level=None, timeout=120):
    """
    Run a single match between two bots via HeadlessRunner.

    Returns:
        tuple: (score1, score2, stdout, stderr) — scores are -1 on error.
    """
    classpath = _get_classpath()
    if classpath is None:
        return -1, -1, "", "Could not build Java classpath"

    java_args = ["java", "-cp", classpath, "HeadlessRunner", bot1_cmd, bot2_cmd]
    if seed is not None:
        java_args.append(str(seed))
    if league_level is not None:
        java_args.append(str(league_level))

    try:
        result = subprocess.run(
            java_args,
            cwd=REPO_ROOT,
            capture_output=True,
            text=True,
            timeout=timeout,
        )

        for line in result.stdout.strip().split("\n"):
            if line.startswith("SCORES "):
                parts = line.split()
                if len(parts) >= 3:
                    return int(parts[1]), int(parts[2]), result.stdout, result.stderr

        return -1, -1, result.stdout, result.stderr

    except subprocess.TimeoutExpired:
        return -1, -1, "", f"Match timed out after {timeout}s"
    except Exception as exc:
        return -1, -1, "", str(exc)


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def parse_args():
    parser = argparse.ArgumentParser(
        description="Run a simulation of two bots and log the results.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )

    # Bot commands — can be given positionally or via named flags
    parser.add_argument(
        "bot1_pos",
        nargs="?",
        metavar="BOT1_CMD",
        help="Shell command to launch bot 1 (positional)",
    )
    parser.add_argument(
        "bot2_pos",
        nargs="?",
        metavar="BOT2_CMD",
        help="Shell command to launch bot 2 (positional)",
    )
    parser.add_argument(
        "--bot1",
        metavar="CMD",
        default=None,
        help="Shell command to launch bot 1 (overrides positional)",
    )
    parser.add_argument(
        "--bot2",
        metavar="CMD",
        default=None,
        help="Shell command to launch bot 2 (overrides positional)",
    )

    parser.add_argument(
        "--matches",
        type=int,
        default=1,
        help="Number of matches to simulate (default: 1)",
    )
    parser.add_argument(
        "--seed",
        type=int,
        default=None,
        help="Base random seed for reproducibility (each match uses seed+i)",
    )
    parser.add_argument(
        "--league-level",
        type=int,
        default=None,
        metavar="LEVEL",
        help="League level passed to the simulator (default: engine default)",
    )
    parser.add_argument(
        "--log",
        metavar="FILE",
        default="simulation.log",
        help="Path to the output log file (default: simulation.log)",
    )
    parser.add_argument(
        "--timeout",
        type=int,
        default=120,
        help="Seconds before a match is considered timed out (default: 120)",
    )
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="Also print simulator stdout/stderr for each match to the log",
    )
    return parser.parse_args()


# ---------------------------------------------------------------------------
# Verbose output helper
# ---------------------------------------------------------------------------

_BOT_STREAM_LABELS = [
    "Standard Error Stream bot1:",
    "Standard Output Stream bot1:",
    "Standard Error Stream bot2:",
    "Standard Output Stream bot2:",
]


def _format_bot_streams(stdout):
    """
    Parse per-bot stream sections emitted by HeadlessRunner and return a
    formatted string ready to be written to the log.

    HeadlessRunner emits blocks in the form:
        Standard Error Stream bot1:
        <lines…>
        Standard Output Stream bot1:
        <lines…>
        Standard Error Stream bot2:
        <lines…>
        Standard Output Stream bot2:
        <lines…>

    Lines before the first section header (e.g. the SCORES line) are ignored.
    """
    if not stdout:
        return ""

    sections = {label: [] for label in _BOT_STREAM_LABELS}
    current = None
    for line in stdout.rstrip("\n").split("\n"):
        if line in sections:
            current = line
        elif current is not None:
            sections[current].append(line)

    # Only emit output if at least one section header was found in the output.
    # (Sections with no content lines are still written to confirm the bot
    # produced no output/errors for that stream.)
    if current is None:
        return ""

    out = []
    for label in _BOT_STREAM_LABELS:
        out.append(f"  {label}\n")
        for line in sections[label]:
            out.append(f"  {line}\n")
    return "".join(out)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    args = parse_args()

    bot1_cmd = args.bot1 or args.bot1_pos
    bot2_cmd = args.bot2 or args.bot2_pos

    if not bot1_cmd or not bot2_cmd:
        print("ERROR: Two bot commands are required.", file=sys.stderr)
        print("  Run with --help for usage information.", file=sys.stderr)
        sys.exit(1)

    if args.matches < 1:
        print("ERROR: --matches must be >= 1.", file=sys.stderr)
        sys.exit(1)

    # Determine seeds
    if args.seed is not None:
        random.seed(args.seed)
    seeds = [
        (args.seed + i if args.seed is not None else random.randint(1, 2**31))
        for i in range(args.matches)
    ]

    log_path = os.path.abspath(args.log)
    os.makedirs(os.path.dirname(log_path) if os.path.dirname(log_path) else ".", exist_ok=True)

    wins1 = wins2 = draws = errors = 0

    with open(log_path, "w") as log:
        header = (
            "=" * 70 + "\n"
            "  SIMULATION LOG\n"
            "=" * 70 + "\n"
            f"  Bot 1: {bot1_cmd}\n"
            f"  Bot 2: {bot2_cmd}\n"
            f"  Matches:      {args.matches}\n"
            f"  Seed:         {args.seed if args.seed is not None else 'random'}\n"
            f"  League level: {args.league_level if args.league_level is not None else 'engine default'}\n"
            f"  Log file:     {log_path}\n"
            f"  Started:      {time.strftime('%Y-%m-%d %H:%M:%S')}\n"
            "=" * 70 + "\n"
        )
        log.write(header)
        print(header, end="")

        for i in range(args.matches):
            seed = seeds[i]
            match_start = time.time()

            status_line = f"\n[Match {i+1}/{args.matches}] seed={seed}"
            log.write(status_line + "\n")
            print(status_line)

            s1, s2, stdout, stderr = run_single_match(
                bot1_cmd,
                bot2_cmd,
                seed=seed,
                league_level=args.league_level,
                timeout=args.timeout,
            )

            elapsed = time.time() - match_start

            if s1 < 0 or s2 < 0:
                outcome = "ERROR"
                errors += 1
            elif s1 > s2:
                outcome = "BOT1_WIN"
                wins1 += 1
            elif s2 > s1:
                outcome = "BOT2_WIN"
                wins2 += 1
            else:
                outcome = "DRAW"
                draws += 1

            result_line = (
                f"  Result : {outcome}\n"
                f"  Score  : Bot1={s1}  Bot2={s2}\n"
                f"  Time   : {elapsed:.2f}s\n"
            )
            log.write(result_line)
            print(result_line, end="")

            if args.verbose:
                verbose_block = _format_bot_streams(stdout)
                if verbose_block:
                    log.write(verbose_block)
                    print(verbose_block, end="")

        # Summary
        summary = (
            "\n" + "=" * 70 + "\n"
            "  SUMMARY\n"
            "=" * 70 + "\n"
            f"  Total matches : {args.matches}\n"
            f"  Bot 1 wins    : {wins1}\n"
            f"  Bot 2 wins    : {wins2}\n"
            f"  Draws         : {draws}\n"
            f"  Errors        : {errors}\n"
            f"  Finished:       {time.strftime('%Y-%m-%d %H:%M:%S')}\n"
            "=" * 70 + "\n"
        )
        log.write(summary)
        print(summary, end="")

    print(f"\nLog written to: {log_path}")


if __name__ == "__main__":
    main()
