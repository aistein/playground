package high3prod

import "fmt"

// Max function for integers
func Max(A int, B int) int {
  if (A > B) {
    return A
  }
  return B
}

// Min function for integers
func Min(A int, B int) int {
  if (A < B) {
    return A
  }
  return B
}

// HighestProductOf3 - takes int array A and returns the highest Product
//   of 3 distinct numbers from A.  We are guaranteed to have at least 3
func HighestProductOf3(A []int) (int, error) {
  n := len(A)

  // error case
  if (n < 3) {
    return 0, fmt.Errorf("highest-product-of-3: list of size %d is too small", n)
  }

  // corner case
  if n == 3 {
    return A[0] * A[1] * A[2], nil
  }

  // general case
  highestProductOf3 := A[0] * A[1] * A[2]
  highestProductOf2 := Max(Max(A[0]*A[1], A[0]*A[2]), A[1]*A[2])
  highest := Max(Max(A[0], A[1]), A[2])
  lowestProductOf2 := Min(Min(A[0]*A[1], A[0]*A[2]), A[1]*A[2])
  lowest := Min(Min(A[0], A[1]), A[2])

  for i := 3; i < n; i++ {
      if A[i] < 0 {
        highestProductOf3 = Max(highestProductOf3, A[i] * lowestProductOf2)
        highestProductOf2 = Max(highestProductOf2, A[i] * lowest)
        lowestProductOf2 = Min(lowestProductOf2, A[i] * highest)
        highest = Max(highest, A[i])
        lowest = Min(lowest, A[i])
      } else {
        highestProductOf3 = Max(highestProductOf3, A[i] * highestProductOf2)
        highestProductOf2 = Max(highestProductOf2, A[i] * highest)
        lowestProductOf2 = Min(lowestProductOf2, A[i] * lowest)
        highest = Max(highest, A[i])
        lowest = Min(lowest, A[i])
      }
  }

  return highestProductOf3, nil
}

func main() {
  slice := []int{6,1,3,5,7,8,2}
	prod, err := HighestProductOf3(slice)
	if err != nil {
		fmt.Println(err)
	}
    fmt.Println(prod)
}
