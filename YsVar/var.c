/***************************************************************************/
/**[File Name    ]var.c                                                   **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for variant                                 **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

void  FEVarFree(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return;
    }
    FEVarVTCall(Var,FEVARTYPE_FREE_SUBFIX);
}

void  FEVarShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return;
    }
    if ( NULL!=FEVARTYPE_MEM_SHOW(Var) )
    {
        ((funcarg3non)FEVARTYPE_MEM_SHOW(Var))(Var,(void *)T,Buf);
        return;
    }
    if ( FEVarVTCall3(Var,(void *)T,Buf,FEVARTYPE_SHOW_SUBFIX) )
    {
        return;
    }
}

BOOL  FEVarPack(void *Var,void *Buf)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    if ( NULL!=FEVARTYPE_MEM_PACK(Var) )
    {
        return ((funcarg2int)FEVARTYPE_MEM_PACK(Var))(Var,Buf);
    }
    return FEVarVTCall2RtnBool(Var,Buf,FEVARTYPE_PACK_SUBFIX);
}

INT32 FEVarUnPack(void **VVar,void *Buf,INT32 P)
{
    void *F;
    void *V;
    if ( (NULL==VVar)||!FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_BIN) )
    {
        return FERTN_ERVAR_UNPACK;
    }
    if ( NULL==(V=FEVarBinGet(Buf)) )
    {
        return FERTN_ERVAR_UNPACK;
    }
    if ( NULL!=(F=FEVarFuncVTGetFunc(((BYTE*)V)[P],FEVARTYPE_UNPACK_SUBFIX)) )
    {
        return ((funcarg3int)F)(VVar,Buf,(void *)P);
    }
    return FERTN_ER;
}

BOOL  FEVarIsInit(void *Var)
{
    return FEVarTypeIsInit(Var);
}

BOOL  FEVarIsInit2(void *Var,INT32 VT)
{
    return FEVarTypeIsInit2(Var,VT);
}

INT32 FEVarGetType(void *Var)
{
    return FEVarTypeVTGet(Var);
}

void *FEVarGetRes(void *Var)
{
    return FEVarTypeResGet(Var);
}

BOOL  FEVarSetRes(void *Var,void *Res,void *Clone,void *Free,void *Show)
{
    BOOL bRtn;
    bRtn = FALSE;
    while( 1 )
    {
        if ( !FEVarTypeResSet(Var,Res) )
        {
            break;
        }
        FEVarTypeResSetClone(Var,Clone);
        FEVarTypeResSetFree(Var,Free);
        FEVarTypeResSetShow(Var,Show);
        bRtn = TRUE;
        break;
    }
    return bRtn;
}

BOOL  FEVarMoveRes(void *NVar,void *OVar)
{
    return FEVarTypeResMove(NVar,OVar);
}

INT32 FEVarGetKeyLen(void *Var)
{
    return FEVarTypeKeyGetLen(Var);
}

char *FEVarGetKey(void *Var)
{
    return (char *)FEVarTypeKeyGet(Var);
}

BOOL  FEVarCatKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarTypeKeyCat(Var,Key,Len);
}

BOOL  FEVarCpyKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarTypeKeyCpy(Var,Key,Len);
}

BOOL  FEVarReplaceKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarTypeKeyReplace(Var,Key,Len);
}

BOOL  FEVarCmpKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarTypeKeyCmp(Var,Key,Len);
}

void  FEVarDeleteKey(void *Var)
{
    FEVarTypeKeyDelete(Var);
}

BOOL  FEVarMoveKey(void *Dest,void *Src)
{
    return FEVarTypeKeyMove(Dest,Src);
}

BOOL  FEVarCloneKey(void *Dest,void *Src)
{
    return FEVarTypeKeyClone(Dest,Src);
}

void *FEVarGetFuncClone(void *Var)
{
    return FEVarTypeFuncGetClone(Var);
}

void *FEVarGetFuncFree(void *Var)
{
    return FEVarTypeFuncGetFree(Var);
}

void *FEVarGetFuncShow(void *Var)
{
    return FEVarTypeFuncGetShow(Var);
}

void *FEVarGetFuncPack(void *Var)
{
    return FEVarTypeFuncGetPack(Var);
}

BOOL  FEVarSetFunc(void *Var,void *Clone,void *Free,void *Show,void *Pack)
{
    return FEVarTypeFuncSet(Var,Clone,Free,Show,Pack);
}

BOOL  FEVarDeleteValue(void *Var)
{
    return FEVarVTCall(Var,FEVARTYPE_VFREE_SUBFIX);
}

void *FEVarClone(void *Var)
{
    return FEVarVTCallRtn(Var,FEVARTYPE_CLONE_SUBFIX);
}

BOOL  FEVarCloneValue(void *NVar,void *OVar)
{
    void *F;
    BYTE VT;
    if ( !FEVarTypeIsInit(OVar) )
    {
        return FALSE;
    }
    if ( !FEVarTypeIsInit(NVar) )
    {
        return FALSE;
    }
    VT = FEVarTypeVTGet(NVar);
    if ( NULL!=(F=FEVarFuncVTGetFunc(VT,FEVARTYPE_CLONEV_SUBFIX)) )
    {
        return (BOOL)((funcarg2int)F)(NVar,OVar);
    }
    return FALSE;
}

BOOL  FEVarVTCall(void *Var,BYTE FT)
{
    void *F;
    BYTE VT;
    BOOL bRtn;
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    bRtn = FALSE;
    VT = FEVarTypeVTGet(Var);
    if ( NULL!=(F=FEVarFuncVTGetFunc(VT,FT)) )
    {
        ((funcarg1non)F)(Var);
        bRtn = TRUE;
    }
    return bRtn;
}

void *FEVarVTCallRtn(void *Var,BYTE FT)
{
    void *F;
    BYTE VT;
    if ( !FEVarTypeIsInit(Var) )
    {
        return NULL;
    }
    VT = FEVarTypeVTGet(Var);
    if ( NULL!=(F=FEVarFuncVTGetFunc(VT,FT)) )
    {
        return ((funcarg1vp)F)(Var);
    }
    return NULL;
}

BOOL  FEVarVTCall2RtnBool(void *Var,void *Buf,BYTE FT)
{
    void *F;
    BYTE VT;
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    VT = FEVarTypeVTGet(Var);
    if ( NULL!=(F=FEVarFuncVTGetFunc(VT,FT)) )
    {
        return ((funcarg2int)F)(Var,Buf);
    }
    return FALSE;
}

BOOL  FEVarVTCall3(void *Var,void *V2,void *V3,BYTE FT)
{
    void *F;
    BYTE VT;
    BOOL bRtn;
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    bRtn = FALSE;
    VT = FEVarTypeVTGet(Var);
    if ( NULL!=(F=FEVarFuncVTGetFunc(VT,FT)) )
    {
        ((funcarg3non)F)(Var,V2,V3);
        bRtn = TRUE;
    }
    return bRtn;
}

#ifdef __cplusplus
}
#endif

