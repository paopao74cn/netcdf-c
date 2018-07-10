/*********************************************************************
 *   Copyright 2016, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

/*
Type declarations and associated constants
are defined here.	
*/

#ifndef NCCSTYPES_H
#define NCCSTYPES_H 1

#include "ncrc.h"
#include "ncauth.h"

#define long64 long long
#define ncerror int

/* Forward */
typedef struct NCCSinfo NCCSinfo;
typedef struct NCCScurl NCCScurl;

/* This is the per-ncid data */
struct NCCSINFO {
    NC*   controller; /* Parent instance of NCD4INFO */
    int debug;
    char* rawurltext; /* as given to nccs_open */
    char* urltext;    /* as modified by nccs_open */
    NCURI* uri;      /* parse of rawuritext */
    NCCScurl* curl;
    struct {
	char* filename; /* of the substrate file */
        int nc4id; /* substrate nc4 file ncid used to hold metadata; not same as external id  */
    } substrate;
    struct {
        int  flags;
        int  debugflags;
    } controls;
    NCauth auth;
};

#endif /*NCCSTYPES_H*/
