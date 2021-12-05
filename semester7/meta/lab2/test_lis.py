from lis import c_longest_increasing_subsequence


def test_c_lis():
    assert c_longest_increasing_subsequence([1, 2, 3, 4]) == [1, 2, 3, 4]
    assert len(c_longest_increasing_subsequence([1, 2, 1, 2, 3])) == 4
    assert c_longest_increasing_subsequence([1, 2, 1, 2, 3, -100, -10, -1, 0, 1, 2]) == [-100, -10, -1, 0, 1, 2]
    assert c_longest_increasing_subsequence([1, 2, 1, 2, 3, -100, 1, 2, 2, 10, 11]) == [1, 1, 1, 2, 2, 10, 11]


def test_c_lis_empty_list():
    assert c_longest_increasing_subsequence([]) == []


def test_one_item_for_desc_seq():
    assert len(c_longest_increasing_subsequence([5, 4, 3, 2, 1])) == 1