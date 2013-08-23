noinst_PROGRAMS=test

test_SOURCES= \
test.c

test_LDADD= \
@libtwitc_LIBS@ \
@EXTERN_DEP_LIBS@


if DEBUG

AM_CFLAGS = -g3 -O0 \
@EXTERN_DEP_CFLAGS@\
@libtwitc_CFLAGS@

else

AM_CFLAGS = -O2 \
@EXTERN_DEP_CFLAGS@\
@libtwitc_CFLAGS@

endif


TESTS = \
	test
	
EXTRA_DIST = \
	$(TESTS)

dist_noinst_SCRIPTS = \
	$(TESTS)
