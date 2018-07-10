/*********************************************************************
  *   Copyright 2016, UCAR/Unidata
  *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
  *********************************************************************/

/*
External functions and state variables are
defined here, including function-like #defines.
*/

#ifndef NCCS_H
#define NCCS_H 1

#include "nc4internal.h"

/**************************************************/
/* Constants */

#define RCFILEENV "CLOUDRCFILE"

/* Figure out a usable max path name max */
#ifdef PATH_MAX /* *nix* */
#define NC_MAX_PATH PATH_MAX
#else
#  ifdef MAX_PATH /*windows*/
#    define NC_MAX_PATH MAX_PATH
#  else
#    define NC_MAX_PATH 4096
#  endif
#endif

#define COUNTERTYPE unsigned long long
#define COUNTERSIZE sizeof(COUNTERTYPE)

/**************************************************/

#undef nullfree
#ifndef nullfree
#define nullfree(m) ((m)==NULL?NULL:(free(m),NULL))
#endif
#define nulldup(s) ((s)==NULL?NULL:strdup(s))

/**************************************************/
/* From csutil.c */

/**************************************************/
/* Macro defined functions */

#undef NCCHECK
#undef FAIL
#define NCCHECK(expr) if((ret=(expr))) {ret = NCCS_errorNC(ret,__LINE__,__FILE__); goto done;}else{}
#define FAIL(code,fmt,...) do{ret=NCCS_error(code,__LINE__,__FILE__,fmt , ##__VA_ARGS__); goto done;}while(0)

#define FILEIDPART(NCID) (((unsigned int) (NCID)) >> ID_SHIFT)
#define GROUPIDPART(NCID) (((unsigned int) (NCID)) & GRP_ID_MASK)
#define MAKENCID(grp,file) ((((unsigned int)(file)) << ID_SHIFT) | (grp))

/* Convert a nccs grpid to a substrate id */
#define makenc4id(ncp,id) (((id) & GRP_ID_MASK) | ((NCCS_INFO*)ncp->controller)->substrate.nc4id)
/* and the inverse */
#define makecsid(ncp,nc4id) (((nc4id) & GRP_ID_MASK) | (ncp)->ext_ncid)

#endif /*NCCS_H*/

