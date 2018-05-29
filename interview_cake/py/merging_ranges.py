import unittest


def merge_ranges(meetings):

    # Merge meeting ranges
    n = len(meetings)

    assert n >= 1, "list not long enough"

    # first, sort the meetings list
    meetings = sorted(meetings, key = lambda x: x[0])

    # now just iterate once merge
    merged_mtgs = []
    a = meetings.pop(0)
    for mtg in meetings:
        a_st, a_fin = a
        b_st, b_fin = mtg
        if (a_st <= b_st and a_fin >= b_fin):
            # mtg is contained in a, so fughet-about-it
            continue
        elif a_fin >= b_st:
            # merge a and mtg
            a = (a_st, b_fin)
        else:
            # a and mtg are disjoint, so push a and replace it
            merged_mtgs.append(a)
            a = mtg

    # don't forget the last one!
    merged_mtgs.append(a)

    return merged_mtgs


















# Tests

class Test(unittest.TestCase):

    def test_meetings_overlap(self):
        actual = merge_ranges([(1, 3), (2, 4)])
        expected = [(1, 4)]
        self.assertEqual(actual, expected)

    def test_meetings_touch(self):
        actual = merge_ranges([(5, 6), (6, 8)])
        expected = [(5, 8)]
        self.assertEqual(actual, expected)

    def test_meeting_contains_other_meeting(self):
        actual = merge_ranges([(1, 8), (2, 5)])
        expected = [(1, 8)]
        self.assertEqual(actual, expected)

    def test_meetings_stay_separate(self):
        actual = merge_ranges([(1, 3), (4, 8)])
        expected = [(1, 3), (4, 8)]
        self.assertEqual(actual, expected)

    def test_multiple_merged_meetings(self):
        actual = merge_ranges([(1, 4), (2, 5), (5, 8)])
        expected = [(1, 8)]
        self.assertEqual(actual, expected)

    def test_meetings_not_sorted(self):
        actual = merge_ranges([(5, 8), (1, 4), (6, 8)])
        expected = [(1, 4), (5, 8)]
        self.assertEqual(actual, expected)

    def test_sample_input(self):
        actual = merge_ranges([(0, 1), (3, 5), (4, 8), (10, 12), (9, 10)])
        expected = [(0, 1), (3, 8), (9, 12)]
        self.assertEqual(actual, expected)


unittest.main(verbosity=2)
