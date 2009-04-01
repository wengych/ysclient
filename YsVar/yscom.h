/***************************************************************************/
/**[File Name    ]yscom.h                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define common of pthread for YsPay                      **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef YSCOM_H__
#define YSCOM_H__

#include <fecom.h>
#include <ysdef.h>
#include <ysrtn.h>
#include <ysmacro.h>
#include <ysvar.h>

#if __OS_LINUX__
#include <pthread.h>
#include <ysunit.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

/****************************************************************************/
/** Pkg func                                                               **/
/****************************************************************************/
BOOL  YSPkgDataToStruct(void *PkgStruct,INT32 PkgSize,void *Pkg,INT32 PkgLen);
INT32 YSPkgStructToData(void *Pkg,INT32 PkgSize,void *PkgStruct);
BOOL  YSPkgStructInit(void *PkgStruct,BOOL ReqT,const char *Type \
    ,INT32 PkgSum,INT32 PkgNum,INT32 DSum,INT32 DLen,void *Data \
    ,INT32 RtnLen,void *Rtn,INT32 MsgLen,void *Msg);
#define YSPkgStructInitReq(PkgStruct,Type,DSum,Data) \
    YSPkgStructInit((PkgStruct),TRUE,(Type) \
        ,1,1,(DSum),(DSum),(Data),0,NULL,0,NULL)
#define YSPkgStructInitResp(PkgStruct,Type,DSum,Data,RL,R,ML,M) \
    YSPkgStructInit((PkgStruct),FALSE,(Type) \
        ,1,1,(DSum),(DSum),(Data),(RL),(R),(ML),(M))
void  YSPkgHeadStructShow(void *PkgStruct,INT32 T,void *Buf);

BOOL  YSPkgTcpRead(INT32 Sock,void *Pkg,void *Head);
BOOL  YSPkgTcpWrite(INT32 Sock,void *Head);
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FECOM_H__ */ 

