#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(pi-top-battery-sys, 1.1, bugs@fuhrmeister-clarke.com)
AC_CONFIG_SRCDIR([battery_simple.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h wiringPiI2C.h lxpanel/plugin.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([mkdir strcasecmp])

AC_OUTPUT
