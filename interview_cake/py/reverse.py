import unittest

def reverse(string):
    n = len(string)
    for i in range(0,n/2):
        tmp = string[n-i-1]
        string[n-i-1] = string[i]
        string[i] = tmp






# Tests

class Test(unittest.TestCase):

    def test_odd_length(self):
        actual =  ['h','e','l','l','o']
        reverse(actual)
        expected = ['o','l','l','e','h']
        self.assertEqual(actual, expected)

    def test_even_length(self):
        actual =  ['h','e','l','l']
        reverse(actual)
        expected = ['l','l','e','h']
        self.assertEqual(actual, expected)

    def test_length_zero(self):
        actual =  []
        reverse(actual)
        expected = []
        self.assertEqual(actual, expected)

    def test_length_one(self):
        actual =  ['h']
        reverse(actual)
        expected = ['h']
        self.assertEqual(actual, expected)

    def test_longer_string(self):
        actual =  ['h','e','l','l','o',' ','w','o','r','l','d','!']
        reverse(actual)
        expected = ['!','d','l','r','o','w',' ','o','l','l','e','h']
        self.assertEqual(actual, expected)

unittest.main(verbosity=2)
