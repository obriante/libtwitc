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
		 favorites.c \
		 twitcver.c \
		 twitcwin.c


libtwitc_a_LIBADD =

if DEBUG

AM_CFLAGS = -g3 -O0 \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

else

AM_CFLAGS = -O2 \
	@EXTERN_DEP_CFLAGS@\
	@libtwitc_CFLAGS@

endif




