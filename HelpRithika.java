import java.util.*;

public class RitikaTask {

    private static int[] canFormWithDeletions(String sub, String mainStr, int maxDeletions) {
        int i = 0, j = 0, deletionsUsed = 0;
        while (i < mainStr.length() && j < sub.length()) {
            if (mainStr.charAt(i) == sub.charAt(j)) {
                i++;
                j++;
            } else {
                deletionsUsed++;
                if (deletionsUsed > maxDeletions) {
                    return new int[] {i, deletionsUsed};
                }
                i++;
            }
        }
        return new int[] {i, deletionsUsed};
    }

    private static boolean canMatchCharacter(char c, List<String> substrings) {
        for (String sub : substrings) {
            if (sub.indexOf(c) >= 0) {
                return true;
            }
        }
        return false;
    }

    public static String solveRitikaTask(List<String> substrings, String mainStr, int k) {
        int n = mainStr.length();
        int deletionsUsed = 0;
        StringBuilder formedString = new StringBuilder();
        boolean isAnyMatch = false;

        for (int i = 0; i < n; i++) {
            if (!canMatchCharacter(mainStr.charAt(i), substrings)) {
                return "Impossible";
            }
        }

        for (int i = 0; i < n;) {
            boolean matched = false;
            for (String sub : substrings) {
                int[] result = canFormWithDeletions(sub, mainStr.substring(i), k - deletionsUsed);
                int newIndex = result[0];
                int usedDeletions = result[1];

                if (newIndex > 0) {
                    matched = true;
                    isAnyMatch = true;
                    formedString.append(mainStr.substring(i, i + newIndex));
                    i += newIndex;
                    deletionsUsed += usedDeletions;
                    break;
                }
            }
            if (!matched) {
                break;
            }
        }

        if (formedString.length() == n) {
            if (deletionsUsed <= k) {
                return "Possible";
            } else {
                return formedString.toString().trim();
            }
        } else if (isAnyMatch) {
            return "Nothing";
        } else if (deletionsUsed > k) {
            return formedString.toString().trim();
        } else {
            return formedString.toString().trim();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int N = scanner.nextInt();
        scanner.nextLine();
        List<String> substrings = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            substrings.add(scanner.nextLine());
        }

        String mainStr = scanner.nextLine();
        int K = scanner.nextInt();

        String result = solveRitikaTask(substrings, mainStr, K);
        System.out.print(result);

        scanner.close();
    }
}
