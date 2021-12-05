from _longest_increasing_subsequence.lib import longest_increasing_subsequence


def c_array_to_list(lis):
    length = lis[0]
    return [lis[i + 1] for i in range(length)]


def c_longest_increasing_subsequence(sequence):
    return c_array_to_list(longest_increasing_subsequence(sequence, len(sequence)))
