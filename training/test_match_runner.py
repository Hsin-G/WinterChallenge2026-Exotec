import sys
from pathlib import Path
from unittest import TestCase
from unittest.mock import patch


# Ensure training modules are importable when running from repo root
TRAINING_DIR = Path(__file__).resolve().parent
if str(TRAINING_DIR) not in sys.path:
    sys.path.insert(0, str(TRAINING_DIR))

import genome  # noqa: E402
import match_runner  # noqa: E402


class MatchRunnerLeagueLevelTest(TestCase):
    def test_league_level_forwarded_to_headless_runner(self):
        """HeadlessRunner should receive the league level argument from evaluate_genome."""
        test_genome = genome.Genome.default()
        opponents = [("opp", "cmd")]
        seeds = [11, 22]
        league_level = 3

        calls = []

        def fake_run(bot1_cmd, bot2_cmd, seed=None, league_level=None, timeout=120):
            calls.append((bot1_cmd, bot2_cmd, seed, league_level, timeout))
            return (1, 0)

        with patch.object(match_runner, "run_single_match", side_effect=fake_run):
            match_runner.evaluate_genome(
                test_genome,
                opponents,
                matches_per_opponent=2,
                seeds=seeds,
                parallel=False,
                league_level=league_level,
            )

        self.assertEqual(len(calls), 2)
        self.assertTrue(all(call[3] == league_level for call in calls))
