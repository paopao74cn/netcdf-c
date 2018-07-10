/*********************************************************************
 *   Copyright 2016, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/
#include "csincludes.h"

int nccsdebug = 0;

#ifdef CATCH
/* Place breakpoint here to catch errors close to where they occur*/
int
csbreakpoint(int err) {return err;}

int
csthrow(int err)
{
    if(err == 0) return err;
    return csbreakpoint(err);
}
#endif
