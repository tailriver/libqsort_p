noinst_PROGRAMS = example benchmark fortran_mangling

AM_CPPFLAGS = -I $(top_srcdir)/include
AM_CFLAGS = -Wall -ansi -pedantic
LDADD = $(top_builddir)/lib/libqsort_p.la

example_SOURCES = example.c
benchmark_SOURCES = benchmark.c
fortran_mangling_SOURCES = fortran_mangling.f90
