package high3prod

import "testing"
import "fmt"

func TestHighestProductOf3(t *testing.T){
	tables := []struct {
		name string
		A []int
		product int
		err error
	}{
		{"short vector", []int{1,2,3,4}, 24, nil},
		{"longer vector", []int{6,1,3,5,7,8,2}, 336, nil},
		{"vector has one negative", []int{-5,4,8,2,3}, 96, nil},
		{"vector has two negatives", []int{-10,1,3,2,-10}, 300, nil},
		{"all negative numbers", []int{-5,-1,-3,-2}, -6, nil},
		{"error with one number", []int{1}, 0, fmt.Errorf("highest-product-of-3: list of size %d is too small", 1)},
		{"error with two numbers", []int{1,2}, 0, fmt.Errorf("highest-product-of-3: list of size %d is too small", 2)},
		{"error with empty slice", []int{}, 0, fmt.Errorf("highest-product-of-3: list of size %d is too small", 0)},
	}

	for _, table := range tables {
		result, err := HighestProductOf3(table.A)
		if (err != nil && table.err != nil) && (err.Error() != table.err.Error()) {
			t.Errorf("Error actual: %v, Error expected: %v", err, table.err)
		}
    if result != table.product {
			t.Errorf("Failed Test \"%v\" On input %v, expected %v, but got %v.", table.name, table.A, table.product, result)
    } else {
		  t.Logf("Passed Test \"%v\"", table.name)
    }
	}
}
