#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libqsort_p], [1.0.1], [shinsuke@tailriver.net])
AC_CONFIG_SRCDIR([lib/qsort_p.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
LT_INIT([disable-shared])
AC_PROG_CXX
AC_PROG_FC
AC_FC_WRAPPERS

AC_LANG_PUSH([C])
AX_OPENMP
AC_LANG_POP([C])
AC_LANG_PUSH([C++])
AX_OPENMP
AC_LANG_POP([C++])
AC_LANG_PUSH([Fortran])
AX_OPENMP
AC_LANG_POP([Fortran])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

CFLAGS="$CFLAGS $OPENMP_CFLAGS"
CXXFLAGS="$CFLAGS $OPENMP_CXXFLAGS"
FCFLAGS="$FCFLAGS $OPENMP_FCFLAGS"

AC_CONFIG_FILES([Makefile include/Makefile lib/Makefile test/Makefile])
AC_OUTPUT
