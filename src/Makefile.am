lib_LIBRARIES = libtwitc.a

libtwitc_a_SOURCES = \
debug.c \
functions.c \
user.c \
http.c \
oauth.c \
status.c \
timeline.c \
twitter.c \
dm.c

libtwitc_a_LIBADD =

if DEBUG

AM_CFLAGS = -g3 -O0 \
	-DDEBUG \
	-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

AM_CXXFLAGS = -g3 -O0 \
	-DDEBUG \
	-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

else

AM_CFLAGS = -O2 \
	-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

AM_CXXFLAGS = -O2 \
	-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

endif