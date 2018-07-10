/*********************************************************************
 *   Copyright 1993, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#include "csincludes.h"

static int nccsinitialized = 0;

static NC_Dispatch NCCS_dispatch_base;

NC_Dispatch* NCCS_dispatch_table = NULL; /* moved here from ddispatch.c */

/**************************************************/
int
NCCS_initialize(void)
{
    CURLcode cstat;
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
    cstat = curl_global_init(CURL_GLOBAL_DEFAULT);
    if(cstat != CURLE_OK)
	fprintf(stderr,"curl_global_init failed!\n");
    return THROW(NC_NOERR);
}

int
NCCS_finalize(void)
{
    curl_global_cleanup();
    return THROW(NC_NOERR);
}

/**************************************************/
/*
Following functions basically return the netcdf-4 value WRT to the nc4id.
However, it is necessary to modify the grpid(ncid) to point to the substrate.
*/

static int
NCCS_inq_base_pe(int ncid, int* pe)
{
    NC* ncp;
    int ret = NC_NOERR;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_base_pe(substrateid, pe);
    return (ret);
}

static int
NCCS_inq_format(int ncid, int* formatp)
{
    NC* ncp;
    int ret = NC_NOERR;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_format(substrateid, formatp);
    return (ret);
}

static int
NCCS_inq(int ncid, int* ndimsp, int* nvarsp, int* nattsp, int* unlimdimidp)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq(substrateid, ndimsp, nvarsp, nattsp, unlimdimidp);
    return (ret);
}

static int
NCCS_inq_type(int ncid, nc_type p2, char* p3, size_t* p4)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_type(substrateid, p2, p3, p4);
    return (ret);
}

static int
NCCS_inq_dimid(int ncid, const char* name, int* idp)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_dimid(substrateid, name, idp);
    return (ret);
}

static int
NCCS_inq_unlimdim(int ncid, int* unlimdimidp)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_unlimdim(substrateid, unlimdimidp);
    return (ret);
}

static int
NCCS_rename_dim(int ncid, int dimid, const char* name)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_rename_dim(substrateid, dimid, name);
    return (ret);
}

static int
NCCS_inq_att(int ncid, int varid, const char* name,
	    nc_type* xtypep, size_t* lenp)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_att(substrateid, varid, name, xtypep, lenp);
    return (ret);
}

static int
NCCS_inq_attid(int ncid, int varid, const char *name, int *idp)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_attid(substrateid, varid, name, idp);
    return (ret);
}

static int
NCCS_inq_attname(int ncid, int varid, int attnum, char* name)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_attname(substrateid, varid, attnum, name);
    return (ret);
}

static int
NCCS_rename_att(int ncid, int varid, const char* name, const char* newname)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_rename_att(substrateid, varid, name, newname);
    return (ret);
}

static int
NCCS_del_att(int ncid, int varid, const char* p3)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_del_att(substrateid, varid, p3);
    return (ret);
}

static int
NCCS_get_att(int ncid, int varid, const char* name, void* value, nc_type t)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = NCDISPATCH_get_att(substrateid, varid, name, value, t);
    return (ret);
}

static int
NCCS_inq_var_all(int ncid, int varid, char *name, nc_type* xtypep,
               int* ndimsp, int* dimidsp, int* nattsp,
               int* shufflep, int* deflatep, int* deflate_levelp,
               int* fletcher32p, int* contiguousp, size_t* chunksizesp,
               int* no_fill, void* fill_valuep, int* endiannessp,
	       unsigned int* idp, size_t* nparamsp, unsigned int* params
               )
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = NCDISPATCH_inq_var_all(substrateid, varid, name, xtypep,
               ndimsp, dimidsp, nattsp,
               shufflep, deflatep, deflate_levelp,
               fletcher32p, contiguousp, chunksizesp,
               no_fill, fill_valuep, endiannessp,
               idp, nparamsp, params);
    return (ret);
}

static int
NCCS_inq_varid(int ncid, const char *name, int *varidp)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_varid(substrateid,name,varidp);
    return (ret);
}

static int
NCCS_rename_var(int ncid, int varid, const char* name)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_rename_var(substrateid, varid, name);
    return (ret);
}

static int
NCCS_var_par_access(int ncid, int p2, int p3)
{
    return (NC_ENOPAR);
}

#ifdef USE_NETCDF4

static int
NCCS_inq_ncid(int ncid, const char* name, int* grp_ncid)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_ncid(substrateid, name, grp_ncid);
    return (ret);
}

static int
NCCS_show_metadata(int ncid)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_show_metadata(substrateid);
    return (ret);
}

static int
NCCS_inq_grps(int ncid, int* ngrpsp, int* grpids)
{
    NC* ncp;
    int ret;
    int substrateid;
    int ngrps;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    /* We always need to know |grpids| */
    ret = nc_inq_grps(substrateid, &ngrps, grpids);
    if(ret == NC_NOERR) {
	if(ngrpsp != NULL)
	    *ngrpsp = ngrps; /* return if caller want it */
	if(grpids != NULL) {
	    int i;
	    /* We need to convert the substrate group ids to dap4 group ids */
	    for(i=0;i<ngrps;i++)
		grpids[i] = makedap4id(ncp,grpids[i]);
	}
    }
    return (ret);
}

static int
NCCS_inq_grpname(int ncid, char* p)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_grpname(substrateid, p);
    return (ret);
}


static int
NCCS_inq_unlimdims(int ncid, int* p2, int* p3)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_unlimdims(substrateid, p2, p3);
    return (ret);
}

static int
NCCS_inq_grpname_full(int ncid, size_t* p2, char* p3)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_grpname_full(substrateid, p2, p3);
    return (ret);
}

static int
NCCS_inq_grp_parent(int ncid, int* p)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_grp_parent(substrateid, p);
    if(p != NULL)
	*p = makedap4id(ncp,*p);
    return (ret);
}

static int
NCCS_inq_grp_full_ncid(int ncid, const char* fullname, int* grpidp)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_grp_full_ncid(substrateid, fullname, grpidp);
    if(grpidp != NULL)
	*grpidp = makedap4id(ncp,*grpidp);
    return (ret);
}

static int
NCCS_inq_varids(int ncid, int* nvars, int* p)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_varids(substrateid, nvars, p);
    return (ret);
}

static int
NCCS_inq_dimids(int ncid, int* ndims, int* p3, int p4)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_dimids(substrateid, ndims, p3, p4);
    return (ret);
}

static int
NCCS_inq_typeids(int ncid, int*  ntypes, int* p)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_typeids(substrateid, ntypes, p);
    return (ret);
}

static int
NCCS_inq_type_equal(int ncid, nc_type t1, int p3, nc_type t2, int* p5)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_type_equal(substrateid, t1, p3, t2, p5);
    return (ret);
}

static int
NCCS_inq_user_type(int ncid, nc_type t, char* p3, size_t* p4, nc_type* p5,
                   size_t* p6, int* p7)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_user_type(substrateid, t, p3, p4, p5, p6, p7);
    return (ret);
}

static int
NCCS_inq_typeid(int ncid, const char* name, nc_type* t)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_typeid(substrateid, name, t);
    return (ret);
}

static int
NCCS_inq_compound_field(int ncid, nc_type xtype, int fieldid, char *name,
		      size_t *offsetp, nc_type* field_typeidp, int *ndimsp,
		      int *dim_sizesp)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_compound_field(substrateid, xtype, fieldid, name, offsetp, field_typeidp, ndimsp, dim_sizesp);
    return (ret);
}

static int
NCCS_inq_compound_fieldindex(int ncid, nc_type xtype, const char *name,
			   int *fieldidp)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_compound_fieldindex(substrateid, xtype, name, fieldidp);
    return (ret);
}

static int
NCCS_get_vlen_element(int ncid, int p2, const void* p3, size_t* p4, void* p5)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_get_vlen_element(substrateid, p2, p3, p4, p5);
    return (ret);
}

static int
NCCS_inq_enum_member(int ncid, nc_type t1, int p3, char* p4, void* p5)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_enum_member(substrateid, t1, p3, p4, p5);
    return (ret);
}

static int
NCCS_inq_enum_ident(int ncid, nc_type t1, long long p3, char* p4)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_inq_enum_ident(substrateid, t1, p3, p4);
    return (ret);
}

static int
NCCS_get_var_chunk_cache(int ncid, int p2, size_t* p3, size_t* p4, float* p5)
{
    NC* ncp;
    int ret;
    int substrateid;
    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR) return (ret);
    substrateid = makenc4id(ncp,ncid);
    ret = nc_get_var_chunk_cache(substrateid, p2, p3, p4, p5);
    return (ret);
}

#endif // USE_NETCDF4

/**************************************************/
/*
Following functions are overridden to handle 
dap4 implementation specific issues.
*/

/* Force specific format */
static int
NCCS_inq_format_extended(int ncid, int* formatp, int* modep)
{
    NC* nc;
    int ncstatus = NC_check_id(ncid, (NC**)&nc);
    if(ncstatus != NC_NOERR) return (ncstatus);
    if(modep) *modep = nc->mode;
    if(formatp) *formatp = NC_FORMATX_DAP4;
    return THROW(NC_NOERR);
}

/*
Override nc_inq_dim to handle the fact
that unlimited dimensions will not have
a proper size because the substrate has
never (not yet) been written.
*/
int
NCCS_inq_dim(int ncid, int dimid, char* name, size_t* lenp)
{
    int ret = NC_NOERR;
    NC* ncp;
    NCCSINFO* info;
    NCCSmeta* meta;
    int i;
    NCCSnode* dim = NULL;

    if((ret = NC_check_id(ncid, (NC**)&ncp)) != NC_NOERR)
	goto done;
    info = (NCCSINFO*)ncp->dispatchdata;
    meta = info->substrate.metadata;

    /* Locate the dimension specified by dimid */
    for(i=0;i<nclistlength(meta->allnodes);i++) {
	NCCSnode* n = (NCCSnode*)nclistget(meta->allnodes,i);
	if(n->sort == NCCS_DIM && n->meta.id == dimid) {
	    dim = n;
	    break;
	}
    }
    if(dim == NULL)
	{ret = NC_EBADDIM; goto done;}
    if(name)
	strncpy(name,dim->name,NC_MAX_NAME);
    if(lenp)
	*lenp = (size_t)dim->dim.size;
done:
    return (ret);
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

#ifdef USE_NETCDF4
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

#endif /*USE_NETCDF4*/

};
