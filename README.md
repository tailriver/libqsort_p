libqsort_p
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


In Fortran:

    integer, allocatable :: array(:)
    ...
    call qsort_p(array, size(array), sizeof(array(1)), comp_int)
    ...
    contains
    integer function comp_int(a, b)
        integer, intent(in) :: a, b
        ...
        comp_int = 1 or 0 or -1
        ...
    end funtion


Example and Benchmark
--------
see test directory.


Repository
--------
[tailriver/libqsort_p.git][GitHub].


Copyright and License
--------
Copyright &copy; 2014 Shinsuke Ogawa.
Distributed under the [MIT License][MIT].


[GitHub]: https://github.com/tailriver/libqsort_p
[MIT]: http://www.opensource.org/licenses/mit-license.php
