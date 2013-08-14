dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)

AC_INIT(libtwitc, 0.1)

# prevent setting xFLAGS to default of -g -O2
if test x"$CFLAGS" = x""; then
  AC_SUBST(CFLAGS, [ ])
fi
if test x"$CXXFLAGS" = x""; then
  AC_SUBST(CXXFLAGS, [ ])
fi

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

AC_CONFIG_SUBDIRS( liblogc )
liblogc_CFLAGS="-I\$(top_srcdir)/example/logc/include"
AC_SUBST(liblogc_CFLAGS)

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
example/Makefile
)
AC_OUTPUT