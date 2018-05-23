package prodother

import "fmt"

// ProductOfOtherNumbers takes the slice A and returns a slice O
//  for which each element at index i of O corresponds to the product of
//  all elements in A except the one at index i.
func ProductOfOtherNumbers(A []int) ([]int, error) {

	n := len(A)
	pivot := 1

	// Error case
	if n <= 1 {
		return []int{}, fmt.Errorf("product-of-other-numbers: list of size %d is too small", n)
	}

	O := make([]int, n)
	M := make([]int, n)
	copy(O, A)
	copy(M, A)

	// Corner cases
	if n == 2 {
		O[0] = A[1]
		O[1] = A[0]
		return O, nil
	}
	if n == 3 {
		O[0] = A[1]*A[2]
		O[1] = A[0]*A[2]
		O[2] = A[0]*A[1]
		return O, nil
	}

	// first iteration fills M backwards
	for i := n - 2; i >= pivot; i-- {
		M[i] = A[i] * M[i+1]
	}
	O[0] = M[pivot];

	// now dynamically fill output and update M
	// left of pivot - product from A[0] upto A[pivot-1]
	// right of pivot - product from A[n-1] downto A[pivot+1]
	for i := pivot; i < n-1; i++ {
		M[pivot] = M[pivot-1] * A[i]
		O[i] = M[pivot-1] * M[pivot+1]
		pivot++
	}
	O[n-1] = M[pivot-1]

    return O, nil
}

func main() {
	slice := []int{1,2,3,4,5,6}
	prod, err := ProductOfOtherNumbers(slice)
	if err != nil {
		fmt.Println(err)
	}
    fmt.Println(prod)
}
