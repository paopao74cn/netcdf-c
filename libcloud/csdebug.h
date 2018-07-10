/*********************************************************************
 *   Copyright 2016, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/
#ifndef CSDEBUG_H
#define CSDEBUG_H

#include <assert.h>
#include <stdarg.h>

#undef CSDEBUG /* general debug */

extern int nccsdebug;

#ifndef CATCH
#define CATCH /* Warning: significant performance impact */
#endif

#ifndef THROW
/* Place breakpoint on dapbreakpoint to catch errors close to where they occur*/
#define THROW(e) csthrow(e)
#define THROWCHK(e) (void)csthrow(e)
extern int csbreakpoint(int err);
extern int csthrow(int err);
#else
#define THROW(e) (e)
#define THROWCHK(e)
#endif

#define LOG0(level,msg) nclog(level,msg)
#define LOG1(level,msg,a1) nclog(level,msg,a1)
#define LOG2(level,msg,a1,a2) nclog(level,msg,a1,a2)

#endif /*CSDEBUG_H*/

