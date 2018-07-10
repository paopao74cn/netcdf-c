/*********************************************************************
 *   Copyright 2016, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#ifndef CSINCLUDES_H
#define CSINCLUDES_H 1

#include "config.h"
#if defined(_WIN32) || defined(_WIN64)
#include <crtdbg.h>
#include <direct.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <curl/curl.h>

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef HAVE_GETRLIMIT
#  ifdef HAVE_SYS_RESOURCE_H
#    include <sys/time.h>
#  endif
#  ifdef HAVE_SYS_RESOURCE_H
#    include <sys/resource.h>
#  endif
#endif

#include "netcdf.h"
#include "nc.h"
#include "ncrc.h"
#include "ncbytes.h"
#include "nclist.h"
#include "ncuri.h"
#include "nclog.h"
#include "ncdap.h"

#include "csutil.h"

#include "nccstypes.h"
#include "nccs.h"

#include "csdebug.h"

#endif /*CSINCLUDES_H*/


