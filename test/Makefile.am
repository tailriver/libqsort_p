noinst_PROGRAMS = verify example example_cxx example_fortran benchmark

AM_CPPFLAGS = -I $(top_srcdir)/include
AM_CFLAGS = -Wall -ansi -pedantic
AM_CXXFLAGS = -Wall -ansi -pedantic
LDADD = $(top_builddir)/lib/libqsort_p.la

verify_SOURCES = verify.c
example_SOURCES = example.c
example_cxx_SOURCES = example_cxx.cpp
example_fortran_SOURCES = example_fortran.f90
benchmark_SOURCES = benchmark.c

EXTRA_DIST = benchmark.plt
