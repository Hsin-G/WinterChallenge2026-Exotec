# Simulation Tool

Run one-off matches between any two bots using the Java HeadlessRunner and
record a detailed log of every match result.

All simulation tools live in the `simulation/` folder.

## Prerequisites

The same prerequisites as the training system are required:

| Requirement | Notes |
|---|---|
| **Java 17** | Runs the game engine / referee |
| **Maven** | Builds the Java referee (`mvn test-compile`) |
| **g++** (C++17) | Compiles the C++ bot |
| **Python 3.8+** | Runs the simulation script |

Make sure the bot binary and the Java referee are compiled before running a
simulation:

```bash
# 1. Build the C++ bot
cd bot && make

# 2. Build the Java referee (only needed once)
cd ..
mvn test-compile -q -DskipTests
```

## Usage

```
python simulation/simulate.py BOT1_CMD BOT2_CMD [options]
```

Or use named flags instead of positional arguments:

```
python simulation/simulate.py --bot1 BOT1_CMD --bot2 BOT2_CMD [options]
```

### Options

| Flag | Default | Description |
|---|---|---|
| `--matches N` | `1` | Number of matches to run |
| `--seed S` | random | Base random seed; match *i* uses seed `S+i` |
| `--league-level L` | engine default | League level forwarded to the simulator |
| `--log FILE` | `simulation.log` | Path to the output log file |
| `--timeout S` | `120` | Seconds before a match is considered timed out |
| `--verbose` | off | Also write simulator stdout/stderr to the log |

## Examples

### Quickstart — one match, default log

```bash
python simulation/simulate.py \
    "../bot/bot --config config/optimized_params.json" \
    "../bot/bot"
```

### Five matches with a fixed seed

```bash
python simulation/simulate.py \
    --bot1 "./bot/bot --config config/optimized_params.json" \
    --bot2 "./bot/bot" \
    --matches 5 \
    --seed 42 \
    --log simulation/results.log
```

### Ten matches at league level 3, verbose output

```bash
python simulation/simulate.py \
    --bot1 "./bot/bot --config config/optimized_params.json" \
    --bot2 "./bot/boss1" \
    --matches 10 \
    --seed 100 \
    --league-level 3 \
    --log simulation/vs_boss1.log \
    --verbose
```

### Compare two different config files

```bash
python simulation/simulate.py \
    --bot1 "./bot/bot --config config/optimized_params.json" \
    --bot2 "./bot/bot --config config/other_params.json" \
    --matches 20 \
    --seed 0 \
    --log simulation/config_comparison.log
```

## Log File Format

The log file is plain text and contains:

1. **Header** — both bot commands, match count, seed, league level, and start
   time.
2. **Per-match block** — match number, seed used, outcome
   (`BOT1_WIN` / `BOT2_WIN` / `DRAW` / `ERROR`), raw scores, and elapsed
   time.  When `--verbose` is set, the simulator's stdout/stderr is also
   included.
3. **Summary** — total matches, wins per bot, draws, and error count.

Example output:

```
======================================================================
  SIMULATION LOG
======================================================================
  Bot 1: ./bot/bot --config config/optimized_params.json
  Bot 2: ./bot/bot
  Matches:      5
  Seed:         42
  League level: engine default
  Log file:     /path/to/simulation/results.log
  Started:      2026-03-21 08:10:00
======================================================================

[Match 1/5] seed=42
  Result : BOT1_WIN
  Score  : Bot1=3  Bot2=1
  Time   : 4.32s

[Match 2/5] seed=43
  Result : DRAW
  Score  : Bot1=2  Bot2=2
  Time   : 3.91s

...

======================================================================
  SUMMARY
======================================================================
  Total matches : 5
  Bot 1 wins    : 3
  Bot 2 wins    : 1
  Draws         : 1
  Errors        : 0
  Finished:       2026-03-21 08:10:25
======================================================================
```
