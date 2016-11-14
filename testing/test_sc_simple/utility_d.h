/* Created by RJudd */
/* SPAWARSYSCEN D857 */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/

static void VU_msub_d(
   vsip_mview_d *a,
   vsip_mview_d *b,
   vsip_mview_d *r)
{
   vsip_vview_d *arv,*brv,*rrv;
   vsip_length n = vsip_mgetcollength_d(a);
   int i;
   for(i=0; i<n; i++){
     arv=vsip_mrowview_d(a,i);
     brv=vsip_mrowview_d(b,i);
     rrv=vsip_mrowview_d(r,i);
     vsip_vsub_d(arv,brv,rrv);
     vsip_vdestroy_d(arv);
     vsip_vdestroy_d(brv);
     vsip_vdestroy_d(rrv);
   }
   return;
}   

static void VU_cmsub_d(
   vsip_cmview_d *a,
   vsip_cmview_d *b,
   vsip_cmview_d *r)
{
   vsip_cvview_d *arv,*brv,*rrv;
   vsip_length n = vsip_cmgetcollength_d(a);
   int i;
   for(i=0; i<n; i++){
     arv=vsip_cmrowview_d(a,i);
     brv=vsip_cmrowview_d(b,i);
     rrv=vsip_cmrowview_d(r,i);
     vsip_cvsub_d(arv,brv,rrv);
     vsip_cvdestroy_d(arv);
     vsip_cvdestroy_d(brv);
     vsip_cvdestroy_d(rrv);
   }
   return;
}   


static void VU_mfill_d(
   vsip_scalar_d alpha,
   vsip_mview_d *b)
{
   vsip_vview_d  *brv;
   vsip_length n = vsip_mgetcollength_d(b);
   int i;
   for(i=0; i<n; i++){
     brv = vsip_mrowview_d(b,i);
     vsip_vfill_d(alpha,brv);
     vsip_vdestroy_d(brv);
   }
   return;
}

static void VU_cmfill_d(
   vsip_cscalar_d alpha,
   vsip_cmview_d *b)
{
   vsip_cvview_d  *brv;
   vsip_length n = vsip_cmgetcollength_d(b);
   int i;
   for(i=0; i<n; i++){
     brv = vsip_cmrowview_d(b,i);
     vsip_cvfill_d(alpha,brv);
     vsip_cvdestroy_d(brv);
   }
   return;
}

static void VU_mmag_d(
   vsip_mview_d *a,
   vsip_mview_d *b)
{
   vsip_vview_d *arv;
   vsip_vview_d  *brv;
   vsip_length n = vsip_mgetcollength_d(a);
   int i;
   for(i=0; i<n; i++){
     arv = vsip_mrowview_d(a,i);
     brv = vsip_mrowview_d(b,i);
     vsip_vmag_d(arv,brv);
     vsip_vdestroy_d(arv);
     vsip_vdestroy_d(brv);
   }
   return;
}

static void VU_cmmag_d(
   vsip_cmview_d *a,
   vsip_mview_d *b)
{
   vsip_cvview_d *arv;
   vsip_vview_d  *brv;
   vsip_length n = vsip_cmgetcollength_d(a);
   int i;
   for(i=0; i<n; i++){
     arv = vsip_cmrowview_d(a,i);
     brv = vsip_mrowview_d(b,i);
     vsip_cvmag_d(arv,brv);
     vsip_cvdestroy_d(arv);
     vsip_vdestroy_d(brv);
   }
   return;
}


static void VU_mclip_d(
    vsip_mview_d *a,
    vsip_scalar_d minlim,
    vsip_scalar_d maxlim,
    vsip_scalar_d minval,
    vsip_scalar_d maxval,
    vsip_mview_d *b)
{
    vsip_vview_d *arv,*brv;
    vsip_length n = vsip_mgetcollength_d(a);
    int i;
    for(i=0; i<n; i++){
       arv = vsip_mrowview_d(a,i);
       brv = vsip_mrowview_d(b,i);
       vsip_vclip_d(arv,minlim,maxlim,minval,maxval,brv);
       vsip_vdestroy_d(arv);
       vsip_vdestroy_d(brv);
    }
    return;
}


static vsip_scalar_d VU_msumval_d(
    vsip_mview_d *a)
{
    vsip_vview_d *arv;
    vsip_length n = vsip_mgetcollength_d(a);
    int i;
    vsip_scalar_d retval = 0;
    for(i=0; i<n; i++){
      arv = vsip_mrowview_d(a,i);
      retval += vsip_vsumval_d(arv);
      vsip_vdestroy_d(arv);
    }
    return retval;
}

