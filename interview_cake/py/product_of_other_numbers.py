import unittest

def get_products_of_all_ints_except_at_index(int_list):
	M = list(int_list)
	O = list(int_list)
	n = len(int_list)
	pivot = 1

	# corner cases
	assert n >= 1, "list not long enough"
	if n == 2:
		O[0] = int_list[1]
		O[1] = int_list[0]
		return O
	if n == 3:
		O[0] = int_list[1] * int_list[2]
		O[1] = int_list[0] * int_list[2]
		O[2] = int_list[0] * int_list[1]
		return O

	# first iteration fills M backwards
	for i in range(n-2, pivot-1, -1):
		M[i] = int_list[i] * M[i + 1]
	O[0] = M[pivot]

	# fill output dynamically
	# left of pivot - product from A[0] upto A[pivot-1]
	# right of pivot - product from A[n-1] downto A[pivot+1]
	for i in range(pivot, n-1, 1):
		M[pivot] = M[pivot-1] * int_list[i]
		O[i] = M[pivot-1] * M[pivot+1]
		pivot = pivot + 1
	O[n-1] = M[pivot-1]
	return O




# Tests

class Test(unittest.TestCase):

	def test_small_list(self):
		actual = get_products_of_all_ints_except_at_index([1, 2, 3])
		expected = [6, 3, 2]
		self.assertEqual(actual, expected)

	def test_longer_list(self):
		actual = get_products_of_all_ints_except_at_index([8, 2, 4, 3, 1, 5])
		expected = [120, 480, 240, 320, 960, 192]
		self.assertEqual(actual, expected)

	def test_list_has_one_zero(self):
		actual = get_products_of_all_ints_except_at_index([6, 2, 0, 3])
		expected = [0, 0, 36, 0]
		self.assertEqual(actual, expected)

	def test_list_has_two_zeros(self):
		actual = get_products_of_all_ints_except_at_index([4, 0, 9, 1, 0])
		expected = [0, 0, 0, 0, 0]
		self.assertEqual(actual, expected)

	def test_one_negative_number(self):
		actual = get_products_of_all_ints_except_at_index([-3, 8, 4])
		expected = [32, -12, -24]
		self.assertEqual(actual, expected)

	def test_all_negative_numbers(self):
		actual = get_products_of_all_ints_except_at_index([-7, -1, -4, -2])
		expected = [-8, -56, -14, -28]
		self.assertEqual(actual, expected)

	def test_error_with_empty_list(self):
		with self.assertRaises(Exception):
			get_products_of_all_ints_except_at_index([])

	def test_error_with_one_number(self):
		with self.assertRaises(Exception):
			get_products_of_all_ints_except_at_index([1])

unittest.main(verbosity=2)
