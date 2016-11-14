/*  Created RJudd October 17, 1998 */
/*  SPAWARSYSCEN D881 */
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
/* $Id: vsip_lud_destroy_f.c,v 1.1 1999/12/02 17:23:36 judd Exp judd $ */
/*  This program is the work of a US Government Employee */
/*  done as part of his official duties */

#include<vsip_ludattributes_f.h>

int (vsip_lud_destroy_f)( 
           vsip_lu_f* lud) {
    if(lud == NULL) return 0;
    if(lud->P != NULL) free(lud->P);
    free((void*) lud);
    return 0;
}
