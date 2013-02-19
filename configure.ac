#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([KiwiOS], [0.1.0], [admin@kokabsolu.com])
AC_CONFIG_SRCDIR([src/lib/stdio.c])
AC_CONFIG_HEADERS([include/config.h])

# Options
AC_ARG_ENABLE([gcc-warnings],
    [AS_HELP_STRING([--enable-gcc-warnings],
      [Enable -Wall gcc flag.])]
)
AS_IF([test "x$enable_gcc_warnings" != xno],
        [
            AC_SUBST([CFLAGS_WALL], "-Wall")
        ],
        [
            AC_SUBST([CFLAGS_WALL], "")
        ]
)
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
      [Enable debugging.])]
)
AS_IF([test "x$enable_debug" != xno],
      	[
      		AC_SUBST([CFLAGS_DEBUG], "-g")
      	],
      	[
      		AC_SUBST([CFLAGS_DEBUG], "-O3")
      	]
)

echo "Additionnals compilation flags: $CFLAGS_WALL $CFLAGS_DEBUG"

AC_ARG_VAR([KEYMAP], [Define used keymap.])
keymap=${KEYMAP:-FR_FR}
keymap=${keymap^^}
AC_DEFINE_UNQUOTED([KEYMAP], [_KEYMAP_${keymap}_], [Define used keymap.])

# Checks for programs.
AC_PROG_CC([gcc cc])
AC_PATH_PROGS([LD], [ld], [:])
AC_PATH_PROGS([RM], [rm], [:])
AC_PATH_PROGS([AS], [nasm], [:])
AC_PATH_PROGS([GRUB_MKRESCUE], [grub-mkrescue], [:])
AC_PATH_PROGS([QEMU], [qemu qemu-system-i386], [:])

# Checks for compiler options.
AC_C_INLINE
AC_C_CONST
AC_C_VOLATILE

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_TYPE([__builtin_va_list], [AC_DEFINE([HAVE___BUILTIN_VA_LIST], [1])])

# Checks for library functions.
AC_CHECK_FUNCS([__builtin_va_start __builtin_va_arg __builtin_va_end __builtin_va_copy])

echo "Creating target dirs..."
mkdir -p target
mkdir -p target/bin

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
