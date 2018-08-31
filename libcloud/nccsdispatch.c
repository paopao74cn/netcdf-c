/*********************************************************************
 *   Copyright 1993, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#include "csincludes.h"
#include "csdispatch.h"

static int nccsinitialized = 0;

static NC_Dispatch NCCS_dispatch_base;
NC_Dispatch* NCCS_dispatch_table = NULL; /* moved here from ddispatch.c */

/**************************************************/
int
NCCS_initialize(void)
{
    NCCS_dispatch_table = &NCCS_dispatch_base;
    nccsinitialized = 1;
    ncloginit();
#ifdef CLOUDDEBUG
    /* force logging to go to stderr */
    nclogclose();
    if(nclogopen(NULL))
        ncsetlogging(1); /* turn it on */
#endif
    /* Load rc file */
    NC_rcload();    
    return THROW(NC_NOERR);
}

int
NCCS_finalize(void)
{
    return THROW(NC_NOERR);
}

/**************************************************/

static NC_Dispatch NCCS_dispatch_base = {

NC_FORMATX_CLOUD,

NCCS_create,
NCCS_open,

NCCS_redef,
NCCS__enddef,
NCCS_sync,
NCCS_abort,
NCCS_close,
NCCS_set_fill,
NCCS_inq_base_pe,
NCCS_set_base_pe,
NCCS_inq_format,
NCCS_inq_format_extended,

NCCS_inq,
NCCS_inq_type,

NCCS_def_dim,
NCCS_inq_dimid,
NCCS_inq_dim,
NCCS_inq_unlimdim,
NCCS_rename_dim,

NCCS_inq_att,
NCCS_inq_attid,
NCCS_inq_attname,
NCCS_rename_att,
NCCS_del_att,
NCCS_get_att,
NCCS_put_att,

NCCS_def_var,
NCCS_inq_varid,
NCCS_rename_var,
NCCS_get_vara,
NCCS_put_vara,
NCCS_get_vars,
NCCS_put_vars,
NCDEFAULT_get_varm,
NCDEFAULT_put_varm,

NCCS_inq_var_all,

NCCS_var_par_access,
NCCS_def_var_fill,

NCCS_show_metadata,
NCCS_inq_unlimdims,
NCCS_inq_ncid,
NCCS_inq_grps,
NCCS_inq_grpname,
NCCS_inq_grpname_full,
NCCS_inq_grp_parent,
NCCS_inq_grp_full_ncid,
NCCS_inq_varids,
NCCS_inq_dimids,
NCCS_inq_typeids,
NCCS_inq_type_equal,
NCCS_def_grp,
NCCS_rename_grp,
NCCS_inq_user_type,
NCCS_inq_typeid,

NCCS_def_compound,
NCCS_insert_compound,
NCCS_insert_array_compound,
NCCS_inq_compound_field,
NCCS_inq_compound_fieldindex,
NCCS_def_vlen,
NCCS_put_vlen_element,
NCCS_get_vlen_element,
NCCS_def_enum,
NCCS_insert_enum,
NCCS_inq_enum_member,
NCCS_inq_enum_ident,
NCCS_def_opaque,
NCCS_def_var_deflate,
NCCS_def_var_fletcher32,
NCCS_def_var_chunking,
NCCS_def_var_endian,
NCCS_def_var_filter,
NCCS_set_var_chunk_cache,
NCCS_get_var_chunk_cache,

};
