/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _VI_functions_f_h
#define _VI_functions_f_h 1
vsip_vview_f* VI_vrealview_f(const vsip_cvview_f*, vsip_vview_f*);
vsip_mview_f* VI_mrealview_f(const vsip_cmview_f*, vsip_mview_f*);
vsip_vview_f* VI_vimagview_f(const vsip_cvview_f*, vsip_vview_f*);
vsip_mview_f* VI_mimagview_f(const vsip_cmview_f*, vsip_mview_f*);
vsip_cvview_f* VI_cmrowview_f(const vsip_cmview_f*,vsip_index,vsip_cvview_f*);
vsip_cvview_f* VI_cmcolview_f(const vsip_cmview_f*,vsip_index,vsip_cvview_f*);
vsip_vview_f* VI_mrowview_f(const vsip_mview_f*,vsip_index,vsip_vview_f*);
vsip_vview_f* VI_mcolview_f(const vsip_mview_f*,vsip_index,vsip_vview_f*);
vsip_mview_f* VI_mtransview_f(const vsip_mview_f*,vsip_mview_f*);
vsip_cmview_f* VI_cmtransview_f(const vsip_cmview_f*,vsip_cmview_f*);
void VI_rcvacosh_f(vsip_vview_f*,vsip_cvview_f*);
vsip_scalar_f VI_acosh_f(vsip_scalar_f);
void VI_cvcosh_f(vsip_cvview_f*,vsip_cvview_f*);
void VI_vfreqswap_f(vsip_vview_f*);
vsip_cscalar_f VI_cvjjdot_f(const vsip_cvview_f*,const vsip_cvview_f*);
#endif /* _VI_functions_f_h */
