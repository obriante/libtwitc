noinst_LIBRARIES = libtwitc.a

libtwitc_a_SOURCES = \
functions.c \
user.c \
http.c \
oauth.c \
status.c \
timeline.c \
twitter.c \
dm.c \
favorites.c


libtwitc_a_LIBADD = \
@liblogc_LIBS@

if DEBUG

AM_CFLAGS = -g3 -O0 \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@ \
	@liblogc_CFLAGS@

else

AM_CFLAGS = -O2 \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@ \
	@liblogc_CFLAGS@

endif




