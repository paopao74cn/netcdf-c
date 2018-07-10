/*********************************************************************
 *   Copyright 2016, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#ifndef _NCCSDISPATCH_H
#define _NCCSDISPATCH_H

#include <stddef.h> /* size_t, ptrdiff_t */
#include "netcdf.h"
#include "ncdispatch.h"
#include "nclog.h"
#include "ncrc.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern int
NCCS_open(const char *path, int mode,
         int basepe, size_t *chunksizehintp,
         int use_parallel, void* mpidata,
         struct NC_Dispatch* dispatch, NC* ncp);

extern int
NCCS_close(int ncid,void*);

extern int
NCCS_abort(int ncid);

extern int
NCCS_inq_dim(int ncid, int dimid, char* name, size_t* lenp);

extern int
NCCS_get_vara(int ncid, int varid,
	    const size_t *start, const size_t *edges,
            void *value,
	    nc_type memtype);

extern int
NCCS_get_vars(int ncid, int varid,
	    const size_t *start, const size_t *edges, const ptrdiff_t* strides,
            void *value,
	    nc_type memtype);

extern int
NCCS_put_vara(int ncid, int varid,
	    const size_t *start, const size_t *edges,
            void *value,
	    nc_type memtype);

extern int
NCCS_put_vars(int ncid, int varid,
	    const size_t *start, const size_t *edges, const ptrdiff_t* strides,
            void *value,
	    nc_type memtype);

extern int NCCS_initialize(void);
extern int NCCS_finalize(void);

#if defined(__cplusplus)
}
#endif

#endif /*_NCCSDISPATCH_H*/
