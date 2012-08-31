# DOXYGEN SUPPORT
include $(top_srcdir)/aminclude.am

SUBDIRS = liblogc src example

EXTRA_DIST = \
	autogen.sh \
	$(DX_CONFIG)

if DX_COND_doc

all: doxygen-doc

endif

MOSTLYCLEANFILES = $(DX_CLEANFILES)