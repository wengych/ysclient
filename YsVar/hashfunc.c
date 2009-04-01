/***************************************************************************/
/**[File Name    ]hashfunc.c                                              **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for array                                   **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <fecom.h>

#ifdef __cplusplus
extern "C"{
#endif

static INT32 gaiFEHashSize[] = 
{
    17,             /* 0 */
    37,             /* 1 */
    79,             /* 2 */
    163,            /* 3 */
    331,            /* 4 */
    673,            /* 5 */
    1361,           /* 6 */
    2729,           /* 7 */
    5471,           /* 8 */
    10949,          /* 9 */
    21911,          /* 10 */
    43853,          /* 11 */
#ifndef __FE_BIG_MEMBER__
    87719           /* 12 */
#else
    87719,          /* 12 */
    175447,         /* 13 */
    350899,         /* 14 */
    701819,         /* 15 */
    1403641,        /* 16 */
    2807303,        /* 17 */
    5614657,        /* 18 */
    11229331,       /* 19 */
    22458671,       /* 20 */
    44917381,       /* 21 */
    89834777,       /* 22 */
    179669557,      /* 23 */
    359339171,      /* 24 */
    718678369,      /* 25 */
    1437356741,     /* 26 */
    2147483647      /* 27 (largest signed int prime) */
#endif
};
#define FEHASH_SIZE                 (sizeof(gaiFEHashSize)/sizeof(INT32))

INT32 FEHashCalSize(INT32 Size)
{
    int i;
    for ( i=0;i<FEHASH_SIZE;i++ )
    {
        if ( gaiFEHashSize[i]>=Size )
        {
            break;
        }
    }
    i = (FEHASH_SIZE<=i)?FEHASH_SIZE-1:i;
    return gaiFEHashSize[i];
}

INT32 FEHashCalKey(const char *key,INT32 len)
{
    INT32 h;
    UCHAR *p;
    if ( NULL==key )
    {
        return 0;
    }
    for ( h=0,p=(UCHAR *)key;*p;p++ )
    {
        h = 31*h + *p;
    }
    return abs(h);
}

INT32 FEHashGetIdx(INT32 HK,INT32 Size)
{
    return (0>=Size)?-1:HK%Size;
}

#ifdef __cplusplus
}
#endif

