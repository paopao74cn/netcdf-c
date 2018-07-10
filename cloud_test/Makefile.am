## This is a automake file, part of Unidata's netCDF package.
# Copyright 2011, see the COPYRIGHT file for more information.

# This file builds and runs Cloud Storage tests.

# Put together AM_CPPFLAGS and AM_LDFLAGS.
include $(top_srcdir)/lib_flags.am

#TEST_EXTENSIONS = .sh

#LOG_DRIVER = $(SHELL) $(top_srcdir)/test-driver-verbose

LDADD = ${top_builddir}/liblib/libnetcdf.la
AM_CPPFLAGS += -I$(top_srcdir)/libcloud -I$(top_srcdir)/libsrc4

# Set up the tests; do the .sh first, then .c
check_PROGRAMS =
TESTS =

if ENABLE_CLOUD

# WARNING: these are unit tests, so they will not
# appear in CMakeLists.txt
check_PROGRAMS +=
TESTS +=

if BUILD_UTILITIES
# These rely on ncdump
TESTS +=
endif

# Note which tests depend on other tests. Necessary for make -j check.
#test_raw.log: test_parse.log

endif #ENABLE_CLOUD

EXTRA_DIST = CMakeLists.txt

CLEANFILES = *.exe
# This should only be left behind if using parallel io
CLEANFILES += tmp_*

clean-local: clean-local-check

.PHONY: clean-local-check

clean-local-check:
	-rm -rf results
