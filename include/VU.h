/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _vsip_VU_h
#define _vsip_VU_h
void VU_mreadf_f(
    FILE*,
    vsip_mview_f*);

void VU_cmreadf_f(
    FILE*,
    vsip_cmview_f*);

void VU_vreadf_f(
    FILE*,
    vsip_vview_f*);

void VU_cvreadf_f(
    FILE*,
    vsip_cvview_f*);

void VU_mprintf_f(
    vsip_mview_f*,
    FILE*);

void VU_cmprintf_f(
    vsip_cmview_f*,
    FILE*);

void VU_vprintf_f(
    vsip_vview_f*,
    FILE*);

void VU_cvprintf_f(
    vsip_cvview_f*,
    FILE*);

void VU_mprintm_f(
    char*,
    vsip_mview_f*);

void VU_cmprintm_f(
    char*,
    vsip_cmview_f*);

void VU_vprintm_f(
    char*,
    vsip_vview_f*);

void VU_vprintm_vi(
    char*,
    vsip_vview_vi*);

void VU_vprintm_mi(
    char*,
    vsip_vview_mi*);

void VU_cvprintm_f(
    char*,
    vsip_cvview_f*);

/* double */

void VU_mreadf_d(
    FILE*,
    vsip_mview_d*);
 
void VU_cmreadf_d(
    FILE*,
    vsip_cmview_d*);
 
void VU_vreadf_d(
    FILE*,
    vsip_vview_d*);
 
void VU_cvreadf_d(
    FILE*,
    vsip_cvview_d*);

void VU_mprintf_d(
    vsip_mview_d*,
    FILE*);

void VU_cmprintf_d(
    vsip_cmview_d*,
    FILE*);

void VU_vprintf_d(
    vsip_vview_d*,
    FILE*);

void VU_cvprintf_d(
    vsip_cvview_d*,
    FILE*);

void VU_mprintm_d(
    char*,
    vsip_mview_d*);

void VU_cmprintm_d(
    char*,
    vsip_cmview_d*);
 
void VU_vprintm_d(
    char*,
    vsip_vview_d*);
 
void VU_cvprintm_d(
    char*,
    vsip_cvview_d*);


#endif /*_vsip_VU_h */

