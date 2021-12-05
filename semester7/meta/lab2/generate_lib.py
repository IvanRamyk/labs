from cffi import FFI
ffibuilder = FFI()

ffibuilder.cdef("int* longest_increasing_subsequence(int arr[], int n);")

ffibuilder.set_source("_longest_increasing_subsequence",  # name of the output C extension
"""
    #include "longest_increasing_subsequence.h"
""",
    sources=['longest_increasing_subsequence.c'],   # includes pi.c as additional sources
    libraries=['m'])    # on Unix, link with the math library

if __name__ == "__main__":
    ffibuilder.compile(verbose=True)