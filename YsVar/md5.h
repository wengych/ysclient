/***************************************************************************/
/**[File Name    ]md5.h                                                   **/
/**[File Path    ]$(APPDIR)/libsrc/fecom                                  **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(HOME)/lib                                             **/
/**[Author       ]Honggang . Wang                                         **/
/**[Copyright    ]Honggang . Wang . 2002                                  **/
/**[Date         ]2002/01/01                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for des                                     **/
/***************************************************************************/

#ifndef MCL_MD5_H
#define MCL_MD5_H
#include <fecom.h>

typedef unsigned char *MD5POINTER;
typedef unsigned short int MD5UINT2;
typedef unsigned long int MD5UINT4;

typedef struct {
  MD5UINT4 state[4];    /* state (ABCD) */
  MD5UINT4 count[2];    /* number of bits, modulo 2^64 (lsb first) */
  UCHAR buffer[64]; 	/* input buffer */
} MD5_CTX;

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif
