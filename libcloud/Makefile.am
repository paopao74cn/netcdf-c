## This is a automake file, part of Unidata's netCDF package.
# Copyright 2005, see the COPYRIGHT file for more information.

# This automake file generates the Makefile to libdap2. Whatever that
# is!

# Put together AM_CPPFLAGS and AM_LDFLAGS.
include $(top_srcdir)/lib_flags.am

# We may have to add to these later.
DISTCLEANFILES =
MAINTAINERCLEANFILES =
CLEANFILES =
EXTRA_DIST = CMakeLists.txt

LDADD=

SRC= \
nccsdispatch.c \
csdebug.c

HDRS= \
nccsdispatch.h \
csdebug.h

if ENABLE_CLOUD
if USE_NETCDF4
AM_CPPFLAGS += -I$(top_srcdir)/libsrc4
endif

# Build convenience library
noinst_LTLIBRARIES = libcloud.la
libcloud_la_SOURCES = $(SRC) $(HDRS)
libcloud_la_CPPFLAGS = $(AM_CPPFLAGS)
libcloud_la_LIBADD =

endif # ENABLE_CLOUD

