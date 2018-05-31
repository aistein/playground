import java.util.*;

public class reverse_words {
  private static void reverseCharacters(char[] word, int left, int right) {
    int n = right - left;
    for (int i = left; i < left + (n/2); i++) {
      char tmp = word[right - (i-left) - 1];
      word[right - (i-left) - 1] =  word[i];
      word[i] = tmp;
    } // end for
  } // end function reverseWord

  public static void reversePhrase(char[] phrase) {
    int n = phrase.length;
    // reverse entire phrase completely
    reverseCharacters(phrase, 0, n);
    // find each word (space-delimited) and then reverse it
    int start_idx = 0;
    for (int i = 0; i < n; i++) {
      if (phrase[i] == ' ') {
        reverseCharacters(phrase, start_idx, i);
        start_idx = i + 1; // FIXME: inherent "one-space" assumption
      } // end if
      else if (i == n-1) {
        reverseCharacters(phrase, start_idx, n);
      }
    } // end for
  } // end function reverseWord

  // tests
  public static void main(String[] args) {
      {
          final String testCase = "one word";
          final char[] expected = "vault".toCharArray();
          final char[] actual = "vault".toCharArray();
          reversePhrase(actual);
          assertEquals(testCase, expected, actual);
      }

      {
          final String testCase = "two words";
          final char[] expected = "cake thief".toCharArray();
          final char[] actual = "thief cake".toCharArray();
          reversePhrase(actual);
          assertEquals(testCase, expected, actual);
      }

      {
          final String testCase = "three words";
          final char[] expected = "get another one".toCharArray();
          final char[] actual = "one another get".toCharArray();
          reversePhrase(actual);
          assertEquals(testCase, expected, actual);
      }

      {
          final String testCase = "multiple words same length";
          final char[] expected = "the cat ate the rat".toCharArray();
          final char[] actual = "rat the ate cat the".toCharArray();
          reversePhrase(actual);
          assertEquals(testCase, expected, actual);
      }

      {
          final String testCase = "multiple words different lengths";
          final char[] expected = "chocolate bundt cake is yummy".toCharArray();
          final char[] actual = "yummy is cake bundt chocolate".toCharArray();
          reversePhrase(actual);
          assertEquals(testCase, expected, actual);
      }

      {
          final String testCase = "empty string";
          final char[] expected = "".toCharArray();
          final char[] actual = "".toCharArray();
          reversePhrase(actual);
          assertEquals(testCase, expected, actual);
      }
  }

  private static void assertEquals(String testCase, char[] expected, char[] actual) {
      if (!Arrays.equals(expected, actual)) {
          System.err.printf("%s - failed. Expected <%s> but was <%s>.\n", testCase,
                            Arrays.toString(expected), Arrays.toString(actual));
      } else {
          System.out.printf("%s - passed.\n", testCase);
      }
  } // end function assertEquals
} // end class reverse_words
