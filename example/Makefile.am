noinst_PROGRAMS=test

AUTOMAKE_OPTIONS = subdir-objects

test_SOURCES= \
logc/src/logc.c \
test.c

test_LDADD= \
@libtwitc_LIBS@ \
@EXTERN_DEP_LIBS@


if DEBUG

AM_CFLAGS = -g3 -O0 \
@EXTERN_DEP_CFLAGS@\
@liblogc_CFLAGS@\
@libtwitc_CFLAGS@

else

AM_CFLAGS = -O2 \
@EXTERN_DEP_CFLAGS@\
@liblogc_CFLAGS@\
@libtwitc_CFLAGS@

endif
