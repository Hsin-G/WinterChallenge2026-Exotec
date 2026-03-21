import com.codingame.gameengine.runner.MultiplayerGameRunner;
import com.codingame.gameengine.runner.simulate.GameResult;
import java.util.Collections;
import java.util.List;

/**
 * Headless match runner for genetic training.
 * Runs a match between two bots and outputs scores and per-bot streams to stdout.
 *
 * Usage:
 *   java HeadlessRunner "command1" "command2" [seed] [leagueLevel]
 *
 * Output format (stdout):
 *   SCORES score0 score1
 *   Standard Error Stream bot1:
 *   <error output from bot 1>
 *   Standard Output Stream bot1:
 *   <output from bot 1>
 *   Standard Error Stream bot2:
 *   <error output from bot 2>
 *   Standard Output Stream bot2:
 *   <output from bot 2>
 */
public class HeadlessRunner {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: HeadlessRunner <bot1_command> <bot2_command> [seed] [leagueLevel]");
            System.exit(1);
        }

        String bot1 = args[0];
        String bot2 = args[1];
        Long seed = null;
        Integer leagueLevel = null;
        if (args.length >= 3) {
            try {
                seed = Long.parseLong(args[2]);
            } catch (NumberFormatException e) {
                System.err.println("Invalid seed: " + args[2]);
                System.exit(1);
            }
        }
        if (args.length >= 4) {
            try {
                leagueLevel = Integer.parseInt(args[3]);
            } catch (NumberFormatException e) {
                System.err.println("Invalid league level: " + args[3]);
                System.exit(1);
            }
        }

        try {
            MultiplayerGameRunner runner = new MultiplayerGameRunner();
            if (seed != null) {
                runner.setSeed(seed);
            }
            if (leagueLevel != null) {
                runner.setLeagueLevel(leagueLevel);
            }
            runner.addAgent(bot1, "Player 1");
            runner.addAgent(bot2, "Player 2");

            GameResult result = runner.simulate();

            // Extract scores from the game result
            if (result.scores != null && result.scores.size() >= 2) {
                int score0 = result.scores.getOrDefault(0, -1);
                int score1 = result.scores.getOrDefault(1, -1);
                System.out.println("SCORES " + score0 + " " + score1);
            } else {
                System.out.println("SCORES -1 -1");
            }

            // Emit per-bot stderr/stdout in structured format
            printBotStreams(result, "bot1", "0");
            printBotStreams(result, "bot2", "1");
        } catch (Exception e) {
            System.err.println("Match error: " + e.getMessage());
            e.printStackTrace(System.err);
            System.out.println("SCORES -1 -1");
        }
    }

    /**
     * Emit the stderr and stdout sections for a single bot in the structured log format.
     *
     * @param result    the GameResult from the simulation
     * @param botLabel  label used in headers, e.g. "bot1" or "bot2"
     * @param playerKey key used in the GameResult maps, e.g. "0" or "1"
     */
    private static void printBotStreams(GameResult result, String botLabel, String playerKey) {
        List<String> errors = (result.errors != null)
                ? result.errors.getOrDefault(playerKey, Collections.emptyList())
                : Collections.emptyList();
        List<String> outputs = (result.outputs != null)
                ? result.outputs.getOrDefault(playerKey, Collections.emptyList())
                : Collections.emptyList();

        System.out.println("Standard Error Stream " + botLabel + ":");
        for (String line : errors) {
            System.out.println(line);
        }
        System.out.println("Standard Output Stream " + botLabel + ":");
        for (String line : outputs) {
            System.out.println(line);
        }
    }
}
