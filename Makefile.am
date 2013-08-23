# DOXYGEN SUPPORT
include $(top_srcdir)/aminclude.am

SUBDIRS = src include tests

EXTRA_DIST = \
	autogen.sh \
	$(DX_CONFIG)\
	README.md

if DX_COND_doc

all: doxygen-doc

endif

MOSTLYCLEANFILES = $(DX_CLEANFILES)