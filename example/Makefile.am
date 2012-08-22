noinst_PROGRAMS=test

test_SOURCES= \
test.c

test_LDADD= \
@EXTERN_DEP_LIBS@ \
@libtwitc_LIBS@

if DEBUG

AM_CXXFLAGS = -g3 -O0 \
-DDEBUG \
-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
@EXTERN_DEP_CFLAGS@\
@libtwitc_CFLAGS@


AM_CFLAGS = -g3 -O0 \
-DDEBUG \
-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
@EXTERN_DEP_CFLAGS@\
@libtwitc_CFLAGS@

else

AM_CXXFLAGS = -O2 \
-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
@EXTERN_DEP_CFLAGS@\
@libtwitc_CFLAGS@



AM_CFLAGS = -O2 \
-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
@EXTERN_DEP_CFLAGS@\
@libtwitc_CFLAGS@

endif