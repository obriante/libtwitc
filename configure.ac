dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)

AC_INIT([libtwitc], [0.2], [orazio.briante@hotmail.it])

# prevent setting xFLAGS to default of -g -O2
if test x"$CFLAGS" = x""; then
  AC_SUBST(CFLAGS, [ ])
fi
if test x"$CXXFLAGS" = x""; then
  AC_SUBST(CXXFLAGS, [ ])
fi

AC_CANONICAL_SYSTEM

TWITC_MAJOR_VERSION=$(echo $PACKAGE_VERSION | cut -d. -f1)
TWITC_MINOR_VERSION=$(echo $PACKAGE_VERSION | cut -d. -f2)
TWITC_MICRO_VERSION=$(echo $PACKAGE_VERSION | cut -d. -f3)
TWITC_EXTRA_VERSION=$(echo $PACKAGE_VERSION | cut -d. -f4)

TWITC_VERSION=$TWITC_MAJOR_VERSION.$TWITC_MINOR_VERSION.$TWITC_MICRO_VERSION${SNAPSHOT:+.$SNAPSHOT}

AC_SUBST(TWITC_MAJOR_VERSION)
AC_SUBST(TWITC_MINOR_VERSION)
AC_SUBST(TWITC_MICRO_VERSION)
AC_SUBST(LT_VERSION)
AC_SUBST(TWITC_VERSION)



AC_PROG_CC
AC_PROG_CXX
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([no])])

dnl Initialize automake
AM_INIT_AUTOMAKE()

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 

dnl Doxygen
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(ON)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN([$PACKAGE_NAME],[twitc.doxyfile],[doc])

PKG_CHECK_MODULES(EXTERN_DEP, [libcurl libxml-2.0 oauth json])

AC_CONFIG_SUBDIRS( libtwitc )
	libtwitc_CFLAGS="-I\$(top_srcdir)/include"
	libtwitc_LIBS="\$(top_builddir)/src/libtwitc.a"
AC_SUBST(libtwitc_CFLAGS)
AC_SUBST(libtwitc_LIBS)

dnl DEBUG
AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug], [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac], [debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

AC_PROG_RANLIB

AC_CONFIG_FILES(
Makefile
src/Makefile
include/Makefile
include/twitc/Makefile
tests/Makefile
)
AC_OUTPUT