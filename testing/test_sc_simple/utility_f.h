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

static void VU_msub_f(
   vsip_mview_f *a,
   vsip_mview_f *b,
   vsip_mview_f *r)
{
   vsip_vview_f *arv,*brv,*rrv;
   vsip_length n = vsip_mgetcollength_f(a);
   int i;
   for(i=0; i<n; i++){
     arv=vsip_mrowview_f(a,i);
     brv=vsip_mrowview_f(b,i);
     rrv=vsip_mrowview_f(r,i);
     vsip_vsub_f(arv,brv,rrv);
     vsip_vdestroy_f(arv);
     vsip_vdestroy_f(brv);
     vsip_vdestroy_f(rrv);
   }
   return;
}   

static void VU_cmsub_f(
   vsip_cmview_f *a,
   vsip_cmview_f *b,
   vsip_cmview_f *r)
{
   vsip_cvview_f *arv,*brv,*rrv;
   vsip_length n = vsip_cmgetcollength_f(a);
   int i;
   for(i=0; i<n; i++){
     arv=vsip_cmrowview_f(a,i);
     brv=vsip_cmrowview_f(b,i);
     rrv=vsip_cmrowview_f(r,i);
     vsip_cvsub_f(arv,brv,rrv);
     vsip_cvdestroy_f(arv);
     vsip_cvdestroy_f(brv);
     vsip_cvdestroy_f(rrv);
   }
   return;
}   


static void VU_mfill_f(
   vsip_scalar_f alpha,
   vsip_mview_f *b)
{
   vsip_vview_f  *brv;
   vsip_length n = vsip_mgetcollength_f(b);
   int i;
   for(i=0; i<n; i++){
     brv = vsip_mrowview_f(b,i);
     vsip_vfill_f(alpha,brv);
     vsip_vdestroy_f(brv);
   }
   return;
}

static void VU_cmfill_f(
   vsip_cscalar_f alpha,
   vsip_cmview_f *b)
{
   vsip_cvview_f  *brv;
   vsip_length n = vsip_cmgetcollength_f(b);
   int i;
   for(i=0; i<n; i++){
     brv = vsip_cmrowview_f(b,i);
     vsip_cvfill_f(alpha,brv);
     vsip_cvdestroy_f(brv);
   }
   return;
}

static void VU_mmag_f(
   vsip_mview_f *a,
   vsip_mview_f *b)
{
   vsip_vview_f *arv;
   vsip_vview_f  *brv;
   vsip_length n = vsip_mgetcollength_f(a);
   int i;
   for(i=0; i<n; i++){
     arv = vsip_mrowview_f(a,i);
     brv = vsip_mrowview_f(b,i);
     vsip_vmag_f(arv,brv);
     vsip_vdestroy_f(arv);
     vsip_vdestroy_f(brv);
   }
   return;
}

static void VU_cmmag_f(
   vsip_cmview_f *a,
   vsip_mview_f *b)
{
   vsip_cvview_f *arv;
   vsip_vview_f  *brv;
   vsip_length n = vsip_cmgetcollength_f(a);
   int i;
   for(i=0; i<n; i++){
     arv = vsip_cmrowview_f(a,i);
     brv = vsip_mrowview_f(b,i);
     vsip_cvmag_f(arv,brv);
     vsip_cvdestroy_f(arv);
     vsip_vdestroy_f(brv);
   }
   return;
}


static void VU_mclip_f(
    vsip_mview_f *a,
    vsip_scalar_f minlim,
    vsip_scalar_f maxlim,
    vsip_scalar_f minval,
    vsip_scalar_f maxval,
    vsip_mview_f *b)
{
    vsip_vview_f *arv,*brv;
    vsip_length n = vsip_mgetcollength_f(a);
    int i;
    for(i=0; i<n; i++){
       arv = vsip_mrowview_f(a,i);
       brv = vsip_mrowview_f(b,i);
       vsip_vclip_f(arv,minlim,maxlim,minval,maxval,brv);
       vsip_vdestroy_f(arv);
       vsip_vdestroy_f(brv);
    }
    return;
}


static vsip_scalar_f VU_msumval_f(
    vsip_mview_f *a)
{
    vsip_vview_f *arv;
    vsip_length n = vsip_mgetcollength_f(a);
    int i;
    vsip_scalar_f retval = 0;
    for(i=0; i<n; i++){
      arv = vsip_mrowview_f(a,i);
      retval += vsip_vsumval_f(arv);
      vsip_vdestroy_f(arv);
    }
    return retval;
}

