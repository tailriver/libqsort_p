qsort_p
=======

A parallel quick sort routine using OpenMP.


Installation
--------
    ./configure && make


API
--------
Like `qsort` in stdlib.h. You can also use this interface in C++ and Fortran (see examples).

    void qsort_p(void* base, size_t num, size_t size, int (*compar)(const void*, const void*));

+ `base` :
    An array to sort.
    
+ `num` :
    The length of array.
    
+ `size` :
    The size of array element.
    
+ `compar` :
    A comparator.


Example and Benchmark
--------
see test directory.


Copyright and License
--------
Copyright &copy; 2014 Shinsuke Ogawa.
Distributed under the [MIT License][MIT].

[MIT]: http://www.opensource.org/licenses/mit-license.php
