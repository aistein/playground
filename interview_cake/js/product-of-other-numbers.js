"use strict";

function getProductsOfAllIntsExceptAtIndex(intArray) {
    // error case
    let n = intArray.length; 
    if (n <= 1) {
        throw "List is too small";
    }

    let O = intArray.slice();
    let M = intArray.slice();
    let pivot = 1;

    // corner cases
    if (n == 2) {
        O[0] = intArray[1];
        O[1] = intArray[0];
        return O;
    }
    if (n == 3) {
        O[0] = intArray[1] * intArray[2];
        O[1] = intArray[0] * intArray[2];
        O[2] = intArray[0] * intArray[1];
        return O;
    }

    // first iteration loops backwards to calculate M
    for (let i = n - 2; i >= pivot; i--) {
        M[i] = M[i] * M[i+1];
    }
    O[0] = M[pivot];

    // dynamically fill O and update M
    // left of pivot - products from A[0] downto A[i-1]
    // right of pivot - products from A[i+1] upto A[n-1]
    for (let i = pivot; i < n-1; i++) {
        M[i] = M[i-1] * intArray[i];
        O[i] = M[i-1] * M[i+1];
        pivot++;
    }
    O[n-1] = M[pivot-1];

    return O;
}


















// Tests

let desc = 'short array';
let actual = getProductsOfAllIntsExceptAtIndex([1, 2, 3]);
let expected = [6, 3, 2];
assertArrayEquals(actual, expected, desc);

desc = 'longer array',
actual = getProductsOfAllIntsExceptAtIndex([8, 2, 4, 3, 1, 5]);
expected = [120, 480, 240, 320, 960, 192];
assertArrayEquals(actual, expected, desc);

desc = 'array has one zero',
actual = getProductsOfAllIntsExceptAtIndex([6, 2, 0, 3]);
expected = [0, 0, 36, 0];
assertArrayEquals(actual, expected, desc);

desc = 'array has two zeros';
actual = getProductsOfAllIntsExceptAtIndex([4, 0, 9, 1, 0]);
expected = [0, 0, 0, 0, 0];
assertArrayEquals(actual, expected, desc);

desc = 'one negative number';
actual = getProductsOfAllIntsExceptAtIndex([-3, 8, 4]);
expected = [32, -12, -24];
assertArrayEquals(actual, expected, desc);

desc = 'all negative numbers';
actual = getProductsOfAllIntsExceptAtIndex([-7, -1, -4, -2]);
expected = [-8, -56, -14, -28];
assertArrayEquals(actual, expected, desc);

desc = 'error with empty array';
const emptyArray = () => (getProductsOfAllIntsExceptAtIndex([]));
assertThrowsError(emptyArray, desc);

desc = 'error with one number';
const oneNumber = () => (getProductsOfAllIntsExceptAtIndex([1]));
assertThrowsError(oneNumber, desc);

function assertArrayEquals(a, b, desc) {
    const arrayA = JSON.stringify(a);
    const arrayB = JSON.stringify(b);
    if (arrayA !== arrayB) {
        console.log(`${desc} ... FAIL: ${arrayA} != ${arrayB}`)
    } else {
        console.log(`${desc} ... PASS`);
    }
}

function assertThrowsError(func, desc) {
    try {
        func();
        console.log(`${desc} ... FAIL`);
    } catch (e) {
    console.log(`${desc} ... PASS`);
    }
}
