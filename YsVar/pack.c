/***************************************************************************/
/**[File Name    ]pack.c                                                  **/
/**[File Path    ]$(SRCDIR)/libsrc/fecom                                  **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(HOME)/lib                                             **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/04/28                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for pack                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <fecom.h>

#ifdef __cplusplus
extern "C"{
#endif

BOOL  FEPackFuncBool(void *Buf,BOOL v)
{
    return FEPackFuncInt32(Buf,v);
}

BOOL  FEPackFuncByte(void *Buf,BYTE v)
{
    BYTE vv;
    vv = v;
    return FEVarBinCat(Buf,&vv,BYTE_SIZE);
}

BOOL  FEPackFuncInt16(void *Buf,INT16 v)
{
    INT16 vv;
    vv = v;
    FEEndianToNet(&vv,INT16_SIZE);
    return FEVarBinCat(Buf,&vv,INT16_SIZE);
}

BOOL  FEPackFuncInt32(void *Buf,INT32 v)
{
    INT32 vv;
    vv = v;
    FEEndianToNet(&vv,INT32_SIZE);
    return FEVarBinCat(Buf,&vv,INT32_SIZE);
}

BOOL  FEPackFuncInt64(void *Buf,INT64 v)
{
    INT64 vv;
    vv = v;
    FEEndianToNet(&vv,INT64_SIZE);
    return FEVarBinCat(Buf,&vv,INT64_SIZE);
}

BOOL  FEPackFuncDouble(void *Buf,DOUBLE v,BYTE DP)
{
    DOUBLE vv;
    if ( !FEPackFuncByte(Buf,DP) )
    {
        return FALSE;
    }
    vv = v;
    FEEndianToNet(&vv,DOUBLE_SIZE);
    return FEVarBinCat(Buf,&vv,DOUBLE_SIZE);
}

BOOL  FEPackFuncString(void *Buf,char *v,INT32 L)
{
    return FEVarBinCat(Buf,v,L);
}

BOOL  FEUnPackFuncBool(void *Buf,INT32 P,BOOL *v)
{
    INT32 vv;
    if ( !FEUnPackFuncInt32(Buf,P,&vv) )
    {
        return FALSE;
    }
    *v = FERTN_CMPBOOL(0==vv);
    return TRUE;
}

BOOL  FEUnPackFuncByte(void *Buf,INT32 P,BYTE *v)
{
    BYTE *vv;
    if ( P+BYTE_SIZE>FEVarBinGetLen(Buf) )
    {
        return FALSE;
    }
    if ( NULL==(vv=(BYTE*)FEVarBinGet(Buf)) )
    {
        return FALSE;
    }
    *v = vv[P];
    return TRUE;
}

BOOL  FEUnPackFuncInt16(void *Buf,INT32 P,INT16 *v)
{
    BYTE *vv;
    if ( P+INT16_SIZE>FEVarBinGetLen(Buf) )
    {
        return FALSE;
    }
    if ( NULL==(vv=(BYTE*)FEVarBinGet(Buf)) )
    {
        return FALSE;
    }
    *v = *(INT16*)(vv+P);
    FEEndianToHost(v,INT16_SIZE);
    return TRUE;
}

BOOL  FEUnPackFuncInt32(void *Buf,INT32 P,INT32 *v)
{
    BYTE *vv;
    if ( P+INT32_SIZE>FEVarBinGetLen(Buf) )
    {
        return FALSE;
    }
    if ( NULL==(vv=(BYTE*)FEVarBinGet(Buf)) )
    {
        return FALSE;
    }
    *v = *(INT32*)(vv+P);
    FEEndianToHost(v,INT32_SIZE);
    return TRUE;
}

BOOL  FEUnPackFuncInt64(void *Buf,INT32 P,INT64 *v)
{
    BYTE *vv;
    if ( P+INT64_SIZE>FEVarBinGetLen(Buf) )
    {
        return FALSE;
    }
    if ( NULL==(vv=(BYTE*)FEVarBinGet(Buf)) )
    {
        return FALSE;
    }
    *v = *(INT64*)(vv+P);
    FEEndianToHost(v,INT64_SIZE);
    return TRUE;
}

BOOL  FEUnPackFuncDouble(void *Buf,INT32 P,DOUBLE *v,BYTE *DP)
{
    BYTE *vv;
    if ( !FEUnPackFuncByte(Buf,P,DP) )
    {
        return FALSE;
    }
    if ( P+BYTE_SIZE+DOUBLE_SIZE>FEVarBinGetLen(Buf) )
    {
        return FALSE;
    }
    if ( NULL==(vv=(BYTE*)FEVarBinGet(Buf)) )
    {
        return FALSE;
    }
    *DP = vv[P];
    *v = *(DOUBLE*)(vv+P+BYTE_SIZE);
    FEEndianToHost(v,DOUBLE_SIZE);
    return TRUE;
}

BOOL  FEUnPackFuncString(void *Buf,INT32 P,INT32 L,char *v)
{
    BYTE *vv;
    INT32 LL;
    LL = FECAL_MIN(0,L);
    if ( P+LL>FEVarBinGetLen(Buf) )
    {
        return FALSE;
    }
    if ( NULL==(vv=(BYTE*)FEVarBinGet(Buf)) )
    {
        return FALSE;
    }
    memcpy(v,vv+P,LL);
    return TRUE;
}

#ifdef __cplusplus
}
#endif

