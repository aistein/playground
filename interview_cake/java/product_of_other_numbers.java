import java.util.Arrays;

public class product_of_other_numbers {

    public static int[] getProductsOfAllIntsExceptAtIndex(int[] intArray) {
        int M[] = Arrays.copyOf(intArray, intArray.length);
        int O[] = Arrays.copyOf(intArray, intArray.length);

        int n = intArray.length;
        int pivot = 1;

        // corner cases
        assert n >= 1 : "list too small.";
        if (n == 2){
            O[0] = intArray[1];
            O[1] = intArray[0];
            return O;
        }
        if (n == 2){
            O[0] = intArray[1] * intArray[2];
            O[1] = intArray[0] * intArray[2];
            O[2] = intArray[0] * intArray[1];
        }

        // first iteration, fill M backwards
        for (int i = n - 2; i >= pivot; i--){
            M[i] = intArray[i] * M[i+1];
        }
        O[0] = M[pivot];

        // dynamically fill output and update M
        // left of pivot - product from A[0] upto A[pivot-1]
        // right of pivot - product from A[n-1] downto A[pivot+1]
        for (int i = pivot; i < n-1; i++){
            M[pivot] = M[pivot-1] * intArray[i];
            O[i] = M[pivot-1] * M[pivot+1];
            pivot++;
        }
        O[n-1] = M[pivot-1];

        return O;
    } // end getProductsOfAllIntsExceptAtIndex

    public static void main(String[] args) {

        String testDescription = "smallArrayInputTest";
        int[] expected = new int[]{6, 3, 2};
        int[] actual = getProductsOfAllIntsExceptAtIndex(new int[]{1, 2, 3});
        assertEquals(expected, actual, testDescription);

        testDescription = "longArrayInputTest";
        expected = new int[]{120, 480, 240, 320, 960, 192};
        actual = getProductsOfAllIntsExceptAtIndex(new int[]{8, 2, 4, 3, 1, 5});
        assertEquals(expected, actual, testDescription);

        testDescription = "inputHasOneZeroTest";
        expected = new int[]{0, 0, 36, 0};
        actual = getProductsOfAllIntsExceptAtIndex(new int[]{6, 2, 0, 3});
        assertEquals(expected, actual, testDescription);

        testDescription = "inputHasTwoZerosTest";
        expected = new int[]{0, 0, 0, 0, 0};
        actual = getProductsOfAllIntsExceptAtIndex(new int[]{4, 0, 9, 1, 0});
        assertEquals(expected, actual, testDescription);

        testDescription = "inputHasOneNegativeNumberTest";
        expected = new int[]{32, -12, -24};
        actual = getProductsOfAllIntsExceptAtIndex(new int[]{-3, 8, 4});
        assertEquals(expected, actual, testDescription);

        testDescription = "allNegativesInputTest";
        expected = new int[]{-8, -56, -14, -28};
        actual = getProductsOfAllIntsExceptAtIndex(new int[]{-7, -1, -4, -2});
        assertEquals(expected, actual, testDescription);

        testDescription = "exceptionWithEmptyInputTest";
        assertException(new int[]{}, testDescription);

        testDescription = "exceptionWithOneNumberInputTest";
        assertException(new int[]{1}, testDescription);
    } // end main

    private static void assertEquals(int[] expected, int[] actual, String testDescription) {
        if (!Arrays.equals(expected, actual)) {
            System.err.println(testDescription + " - failed. Expected: " + Arrays.toString(expected) + ", but was: " + Arrays.toString(actual));
        } else {
            System.out.println(testDescription + " - passed.");
        }
    } // end assertEquals

    private static void assertException(int[] input, String testDescription) {
        try {
            getProductsOfAllIntsExceptAtIndex(input);
            System.err.println(testDescription + " - failed. Exception expected.");
        } catch (Exception e) {
            System.out.println(testDescription + " - passed.");
        }
    } // end assertException

} // end class product-of-other-numbers
