noinst_PROGRAMS=test

test_SOURCES= \
test.c

test_LDADD= \
@EXTERN_DEP_LIBS@ \
@libtwitc_LIBS@

if DEBUG

AM_CPPFLAGS = \
	-DDEBUG \
	-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

else

AM_CPPFLAGS = \
	-DDEBUG \
	-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

endif