import java.util.*;
import java.io.*;

public class SpellChecker {
    private List<String> dictionary = new ArrayList<>();

    public void loadDictionary(String dictionaryFile) throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(getClass().getResourceAsStream(dictionaryFile)))) {
            String line;
            while ((line = reader.readLine()) != null) {
                dictionary.add(line);
            }
        }
    }

    public List<String> suggestWords(String inputWord) {
        Map<String, Integer> wordDistances = new HashMap<>();

        for (String word : dictionary) {
            if (!word.equalsIgnoreCase(inputWord)) {
                int distance = calculateSequenceAlignmentDistance(inputWord, word);
                int lengthDifference = Math.abs(inputWord.length() - word.length());
                int gapPenalty = Math.max(lengthDifference, 0) * 2; 

                int totalPenalty = distance + gapPenalty;
                wordDistances.put(word, totalPenalty);
            }
        }

        List<String> suggestions = wordDistances.entrySet()
                .stream()
                .sorted(Comparator.<Map.Entry<String, Integer>>comparingInt(entry -> entry.getValue())
                        .thenComparingInt(entry -> entry.getKey().length()) 
                        .thenComparing(entry -> entry.getKey())) 
                .limit(10)
                .map(Map.Entry::getKey)
                .collect(ArrayList::new, ArrayList::add, ArrayList::addAll);

        return suggestions;
    }

    private boolean isVowel(char c) {
        return "aeiou".indexOf(c) != -1;
    }    

    private int getPenalty(char a, char b) {
        if (a == b) {
            return 0; 
        } else if (isVowel(a) && isVowel(b)) {
            return 1; 
        } else if (!isVowel(a) && !isVowel(b)) {
            return 1; 
        } else {
            return 3; 
        }
    }

   
    
    private int calculateSequenceAlignmentDistance(String word1, String word2) {
        int m = word1.length();
        int n = word2.length();

        int[][] dp = new int[m + 1][n + 1];

        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }

        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int cost = getPenalty(word1.charAt(i - 1), word2.charAt(j - 1));
                dp[i][j] = Math.min(dp[i - 1][j - 1] + cost, Math.min(dp[i - 1][j] + 2, dp[i][j - 1] + 2));
            }
        }

        return dp[m][n];
    }
}
