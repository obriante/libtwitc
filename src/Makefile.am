lib_LIBRARIES = libtwitc.a

AM_CFLAGS = \
@EXTERN_DEP_LIBS@

libtwitc_a_SOURCES = \
debug.c \
functions.c \
user.c \
oauth.c \
http.c \
timeline.c \
twitter.c

libtwitc_a_LIBADD =

if DEBUG

AM_CPPFLAGS = \
	-DDEBUG \
	-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

else

AM_CPPFLAGS = \
	-DPROG_DIR=\""$(prefix)/share/@PACKAGE@"\" \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

endif