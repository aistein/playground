package main

import "testing"
import "fmt"

func TestProductOfOtherNumbers(t *testing.T){
	tables := []struct {
		name string
		A []int
		O []int
		err error
	}{
		{"small vector", []int{1,2,3}, []int{6,3,2}, nil},
		{"longer vector", []int{8,2,4,3,1,5}, []int{120,480,240,320,960,192}, nil},
		{"vector has one zero", []int{6,2,0,3}, []int{0,0,36,0}, nil},
		{"vector has two zeros", []int{4,0,9,1,0}, []int{0,0,0,0,0}, nil},
		{"one negative number", []int{-3,8,4}, []int{32,-12,-24}, nil},
		{"all negative numbers", []int{-7,-1,-4,-2}, []int{-8,-56,-14,-28}, nil},
		{"error with one number", []int{1}, []int{}, fmt.Errorf("product-of-other-numbers: list of size %d is too small", 1)},
		{"error with empty slice", []int{}, []int{}, fmt.Errorf("product-of-other-numbers: list of size %d is too small", 0)},
	}

	for _, table := range tables {
		O, err := ProductOfOtherNumbers(table.A)
		if (err != nil && table.err != nil) && (err.Error() != table.err.Error()) {
			t.Errorf("Error actual: %v, Error expected: %v", err, table.err)
		}
		for i := range O {
			if O[i] != table.O[i] {
				t.Errorf("On input %v, expected %v, but got %v.", table.A, table.O, O)
			}
		}
		t.Logf("Passed Test \"%v\"", table.name)
	}
}
