/***************************************************************************/
/**[File Name    ]ysmacro.h                                               **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define macro                                            **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef YSMACRO_H__
#define YSMACRO_H__

#include <macro.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __DEBUG__
#define YSDEBUG_STEP \
    fprintf(stderr,"%s,%d %s\n",__FILE__,__LINE__,__func__)
#define YSDEBUG_PSTEP \
    fprintf(stderr,"%s,%d %s --%d\n" \
        ,__FILE__,__LINE__,__func__,(INT32)pthread_self())
#endif

#define YSDEBUG_TRACE(Buf) \
    sprintf(Buf,"%s,%d %s",__FILE__,__LINE__,__func__)
#define YSDEBUG_TRACES  __FILE__,__LINE__,__func__
#define YSSETTRACE(Buf,Size) \
    FESetTrace((Buf),(Size),__FILE__,__LINE__,__func__)


#define YSCAL_MIN(N1,N2)            CALCULATE_MIN(N1,N2) 
#define YSCAL_MAX(N1,N2)            CALCULATE_MAX(N1,N2)

#define YSLUCK_NUM                  LUCK_NUM
#define YSLUCK_INIT(v)              ((v)=YSLUCK_NUM)
#define YSLUCK_INIT_NOT(v)          ((v)=0)
#define YSLUCK_ISINIT(v)            (YSRTN_CMPBOOL(YSLUCK_NUM==(v)))

/****************************************************************************/
/** Var Array                                                              **/
/****************************************************************************/
#define YSARRAYSIZE_MIN             ARRAYSIZE_MIN
#define YSARRAYSIZE_MAX             ARRAYSIZE_MAX
#define YSARRAYSIZE_GETMIN(Size)   (YSCAL_MIN(0,(Size)))
#define YSARRAYSIZE_GETMAX(Max) \
    ((0==YSCAL_MAX(0,(Max))) \
    ?YSARRAYSIZE_MAX \
    :YSCAL_MIN(YSCAL_MIN(1,(Max)),YSARRAYSIZE_MAX))
#define YSARRAYSIZE_GETSIZE(Max,Size) \
    (YSCAL_MIN(YSARRAYSIZE_GETMAX((Max)),YSCAL_MAX(1,(Size))))
#define YSARRAYSIZE_ISREALLOC(Max,Size) \
    YSRTN_CMP(YSARRAYSIZE_GETMAX((Max))>=YSCAL_MAX(0,(Size)))
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Endian                                                                 **/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef YSMACRO_H__ */ 

