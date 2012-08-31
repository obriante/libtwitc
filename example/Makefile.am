noinst_PROGRAMS=test

test_SOURCES= \
test.c

test_LDADD= \
@libtwitc_LIBS@ \
@liblogc_LIBS@ \
@EXTERN_DEP_LIBS@


if DEBUG

AM_CFLAGS = -g3 -O0 \
-DDEBUG \
-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
@EXTERN_DEP_CFLAGS@\
@liblogc_CFLAGS@ \
@libtwitc_CFLAGS@

else

AM_CFLAGS = -O2 \
-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
@EXTERN_DEP_CFLAGS@\
@liblogc_CFLAGS@ \
@libtwitc_CFLAGS@

endif
