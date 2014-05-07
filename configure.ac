#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libqsort_p], [0.1], [shinsuke@tailriver.net])
AC_CONFIG_SRCDIR([lib/qsort_p.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CC
AC_PROG_FC
LT_INIT

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile lib/Makefile test/Makefile])
AC_OUTPUT