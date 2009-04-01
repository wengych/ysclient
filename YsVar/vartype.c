/***************************************************************************/
/**[File Name    ]vartype.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for variant type                            **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

INT32 FEVarVersionTest(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FERTN_ERAPP_ARG;
    }
    if ( FEVARTYPE_VER_MAJOR<FEVARTYPE_MEM_VM(v) )
    {
        return FERTN_OK2;
    }
    if ( FEVARTYPE_VER_MAJOR==FEVARTYPE_MEM_VM(v) )
    {
        if ( FEVARTYPE_VER_SUB==FEVARTYPE_MEM_VS(v) )
        {
            return FERTN_OK1;
        }
        else if ( FEVARTYPE_VER_SUB<FEVARTYPE_MEM_VS(v) )
        {
            return FERTN_OK2;
        }
    }
    return FERTN_OK;
}

void  FEVarTypeNFree(void *v)
{
    tFEVarType *b;
    if ( !FEVarTypeIsInit(v) )
    {
        return;
    }
    if ( FEVARTYPEKEY_ISHASHKEY(v) )
    {
        FEVarTypeVKSetKey(v);
    }
    FEVarTypeResDelete(v);
    FEVarTypeKeyDelete2(v);
    FEVARTYPE_INIT_NOTLUCK(v);
    b = (tFEVarType*)v;
    
    free(v);
}

BOOL  FEVarTypeIsInit(void *v)
{
    if ( NULL==v )
    {
        return FALSE;
    }
    return FELUCK_ISINIT(FEVARTYPE_MEM_LUCK(v));
}

BOOL  FEVarTypeIsInit2(void *v,INT32 VT)
{
    if ( NULL==v )
    {
        return FALSE;
    }
    if ( !FELUCK_ISINIT(FEVARTYPE_MEM_LUCK(v)) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL(VT==FEVARTYPE_MEM_VT(v));
}

BOOL  FEVarTypeMove(void *v,void *v2)
{
    if ( !FEVarTypeKeyMove(v,v2) )
    {
        return FALSE;
    }
    return FEVarTypeResMove(v,v2);
}

BOOL  FEVarTypeClone(void *v,void *v2)
{
    if ( !FEVarTypeKeyClone(v,v2) )
    {
        return FALSE;
    }
    if ( !FEVarTypeResClone(v,v2) )
    {
        FEVarTypeKeyDelete2(v);
        return FALSE;
    }
    FEVARTYPE_MEM_CLONE(v) = FEVARTYPE_MEM_CLONE(v2);
    FEVARTYPE_MEM_FREE(v) = FEVARTYPE_MEM_FREE(v2);
    FEVARTYPE_MEM_SHOW(v) = FEVARTYPE_MEM_SHOW(v2);
    FEVARTYPE_MEM_PACK(v) = FEVARTYPE_MEM_PACK(v2);
    return TRUE;
}

void  FEVarTypeInit(void *v)
{
    if ( NULL==v )
    {
        return ;
    }
    memset(v,0,FEVARTYPE_ST_SIZE);
    FEVARTYPE_INIT_VER(v);
    FEVARTYPE_MEM_VK_SET(v,FEVARTYPE_MEM_VK_NOT);
    FEVARTYPE_MEM_VV_SET(v,FEVARTYPE_MEM_VV_NOT);
    FEVARTYPE_MEM_VT(v) = FEVARTYPE_MEM_VT_NOT;
    FEVARTYPE_MEM_ED(v) = FEVARTYPE_MEM_ED_BIG;
    FEVARTYPE_MEM_DP(v) = FEVARTYPE_MEM_DP_DEFAULT;
    FEVARTYPE_MEM_RES(v) = NULL;
    FEVARTYPE_MEM_RES_CLONE(v) = NULL;
    FEVARTYPE_MEM_RES_FREE(v) = NULL;
    FEVARTYPE_MEM_RES_SHOW(v) = NULL;
    FEVARTYPE_MEM_KH(v) = 0;
    FEVARTYPE_MEM_KS(v) = 0;
    FEVARTYPE_MEM_KL(v) = 0;
    FEVARTYPE_MEM_KEY(v) = NULL;
    FEVARTYPE_MEM_CLONE(v) = NULL;
    FEVARTYPE_MEM_FREE(v) = NULL;
    FEVARTYPE_MEM_SHOW(v) = NULL;
    FEVARTYPE_MEM_PACK(v) = NULL;
    FEVARTYPE_INIT_LUCK(v);
    FEVarTypeEDSetBig(v);
}

BOOL  FEVarTypeVKIsNot(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return TRUE;
    }
    return FERTN_CMPBOOL(FEVARTYPE_MEM_VK_NOT==FEVARTYPE_MEM_VK_GET(v));
}

void  FEVarTypeVKSetNot(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    FEVARTYPE_MEM_VK_SET(v,FEVARTYPE_MEM_VK_NOT);
    FEVARTYPE_MEM_KS(v) = 0;
    FEVARTYPE_MEM_KL(v) = 0;
}

void  FEVarTypeVKSetKey(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    FEVARTYPE_MEM_VK_SET(v,FEVARTYPE_MEM_VK_KEY);
}

void  FEVarTypeVKSetHashKey(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    FEVARTYPE_MEM_VK_SET(v,FEVARTYPE_MEM_VK_HASHKEY);
}

BYTE  FEVarTypeVVGet(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FEVARTYPE_MEM_VV_NOT;
    }
    return FEVARTYPE_MEM_VV_GET(v);
}

void  FEVarTypeVVSetNot(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    FEVARTYPE_MEM_VV_SET(v,FEVARTYPE_MEM_VV_NOT);
}

void  FEVarTypeVVSetNull(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    FEVARTYPE_MEM_VV_SET(v,FEVARTYPE_MEM_VV_NULL);
}

void  FEVarTypeVVSetValue(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    FEVARTYPE_MEM_VV_SET(v,FEVARTYPE_MEM_VV_VALUE);
}

void  FEVarTypeNShow1(void *Var,INT32 T,void *Buf)
{
    char Log[BUFSIZE_512];
    char Tab[BUFSIZE_64];
    char *Type;
    INT32 L;
    if ( !FEVarTypeIsInit(Var) )
    {
        return;
    }
    memset(Tab,0,sizeof(Tab));
    FEVarToolsInitBufSpace(Tab,sizeof(Tab),T);
    Type = FEVarTypeInfoGetName(FEVarTypeVTGet(Var));

    L = 0;
    sprintf(Log+L,"%s<Node Addr=\"%08X\" VV=\"%d\" VT=\"%d\" Type=\"%s\">\n" \
        ,Tab,(INT32)Var,FEVarTypeVVGet(Var),FEVarTypeVTGet(Var) \
        ,(NULL==Type)?"unknown":Type);
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);
    FEVarTypeResShow(Var,T,Buf);
    FEVarTypeKeyShow(Var,T,Buf);
    if ( FEVARTYPEVALUE_ISNOT(Var) )
    {
        sprintf(Log,"%s <NotValue/>\n",Tab);
        L = strlen(Log);
        FEVarStringCat(Buf,Log,L);
    }
    else if ( FEVARTYPEVALUE_ISNULL(Var) )
    {
        sprintf(Log,"%s <NullValue/>\n",Tab);
        L = strlen(Log);
        FEVarStringCat(Buf,Log,L);
    }
}

void  FEVarTypeNShow2(void *Var,INT32 T,void *Buf)
{
    char Log[BUFSIZE_256];
    char Tab[BUFSIZE_64];
    INT32 L;

    if ( !FEVarTypeIsInit(Var) )
    {
        return;
    }

    memset(Tab,0,sizeof(Tab));
    FEVarToolsInitBufSpace(Tab,sizeof(Tab),T);
 
    L = 0;
    sprintf(Log+L,"%s</Node>\n",Tab);
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);
}

BOOL  FEVarTypePack(void *Buf,void *v,INT32 PL,void *PackInfo)
{
    INT32 L;
    if ( !FEVarTypeIsInit(v) )
    {
        return FALSE;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    L = INT32_SIZE+INT16_SIZE+FEVARTYPE_MEM_KL(v)+PL;
    if ( !FEVarBinMalloc(Buf,L+BYTE_SIZE) )
    {
        return FALSE;
    }
    if ( !FEPackFuncByte(Buf,FEVARTYPE_MEM_VT(v)) )
    {
        return FALSE;
    }
    /* PL = Len(Info)+Len(Data) */
    if ( !FEPackFuncInt32(Buf,L) )
    {
        return FALSE;
    }
    if ( !FEVarTypeKeyPack(v,Buf) )
    {
        return FALSE;
    }
    if ( NULL!=PackInfo )
    {
        if ( FALSE==((funcarg2int)PackInfo)(v,Buf) )
        {
            return FALSE;
        }
    }
    return TRUE;
}

INT32 FEVarTypeUnPack(INT32 *PL,tFEVarType *VarType,void *Buf,INT32 P)
{
    INT32 LL;
    INT32 iRtn;
    
    if ( (NULL==PL)||(NULL==VarType)||(NULL==Buf) )
    {
        return FERTN_ERAPP_ARG;
    }
    if ( !FEUnPackFuncInt32(Buf,P,&LL) )
    {
        return FERTN_ERVAR_UNPACK;
    }
    memset(VarType,0,FEVARTYPE_ST_SIZE);
    if ( 0>=(iRtn=FEVarTypeKeyUnPack(VarType,Buf,P+INT32_SIZE)) )
    {
        return FERTN_ERVAR_UNPACK;
    }
    *PL = LL-INT32_SIZE-INT16_SIZE-FEVARTYPE_MEM_KL(VarType);
    return iRtn;
}

BOOL  FEVarTypeUnPackSetType(void *Var,tFEVarType *VarType)
{
    if ( !FEVarTypeIsInit(Var)||(NULL==VarType) )
    {
        return FALSE;
    }
    if ( 0<FEVARTYPE_MEM_KL(VarType) )
    {
        if ( !FEVarTypeKeyCpy(Var,FEVARTYPE_MEM_KEY(VarType) \
            ,FEVARTYPE_MEM_KL(VarType)) )
        {
            return FALSE;
        }
    }
    return TRUE;
}

BYTE  FEVarTypeVTGet(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return 0;
    }
    return FEVARTYPE_MEM_VT(v);
}

INT32 FEVarTypeVTSet(void *v,const BYTE vt)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FERTN_ERAPP_ARG;
    }
    FEVARTYPE_MEM_VT(v) = vt;
    return FERTN_OK;
}

BYTE  FEVarTypeEDGet(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return 0;
    }
    return FEVARTYPE_MEM_ED(v);
}

void  FEVarTypeEDSetBig(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    FEVARTYPE_MEM_ED(v) = FEVARTYPE_MEM_ED_BIG;
}

void  FEVarTypeEDSetLittle(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    FEVARTYPE_MEM_ED(v) = FEVARTYPE_MEM_ED_LITTLE;
}

BYTE  FEVarTypeSLGet(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return 0;
    }
    return FEVARTYPE_MEM_SL(v);
}

void  FEVarTypeSLSet(void *v,BYTE L)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    FEVARTYPE_MEM_SL(v) = FECAL_MAX(0,L);
}

INT32 FEVarTypeDPGetInt(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return 0;
    }
    return ((FEVARTYPE_MEM_DP(v)>>4)&0x0F);
}

INT32 FEVarTypeDPGetDec(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return 0;
    }
    return (FEVARTYPE_MEM_DP(v)&0x0F);
}

BOOL  FEVarTypeDPSet(void *v,INT32 Int,INT32 Dec)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FALSE;
    }
    FEVARTYPE_MEM_DP(v) = (((FECAL_MAX(0,Int)%16)<<4)&0xF0) \
        | ((FECAL_MAX(0,Dec)%16)&0x0F);
    return TRUE;
}

BOOL  FEVarTypeDPSet2(void *v,BYTE dp)
{
    INT32 Int;
    INT32 Dec;
    Int = ((dp>>4)&0x0F);
    Dec = (dp&0x0F);
    return FEVarTypeDPSet(v,Int,Dec);
}

void *FEVarTypeResGet(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return NULL;
    }
    return FEVARTYPE_MEM_RES(v);
}

void *FEVarTypeResGetFree(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return NULL;
    }
    return FEVARTYPE_MEM_RES_FREE(v);
}

void *FEVarTypeResGetShow(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return NULL;
    }
    return FEVARTYPE_MEM_RES_SHOW(v);
}

BOOL  FEVarTypeResSet(void *v,void *Res)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FALSE;
    }
    FEVARTYPE_MEM_RES(v) = Res;
    return TRUE;
}

BOOL  FEVarTypeResSetClone(void *v,void *Clone)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FALSE;
    }
    FEVARTYPE_MEM_RES_CLONE(v) = Clone;
    return TRUE;
}

BOOL  FEVarTypeResSetFree(void *v,void *Free)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FALSE;
    }
    FEVARTYPE_MEM_RES_FREE(v) = Free;
    return TRUE;
}

BOOL  FEVarTypeResSetShow(void *v,void *Show)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FALSE;
    }
    FEVARTYPE_MEM_RES_SHOW(v) = Show;
    return TRUE;
}

void  FEVarTypeResDelete(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return ;
    }
    if ( (NULL!=FEVARTYPE_MEM_RES(v))&&(NULL!=FEVARTYPE_MEM_RES_FREE(v)) )
    {
        ((funcarg1non)(FEVARTYPE_MEM_RES_FREE(v)))(FEVARTYPE_MEM_RES(v));
        FEVARTYPE_MEM_RES(v) = NULL;
        FEVARTYPE_MEM_RES_FREE(v) = NULL;
        FEVARTYPE_MEM_RES_SHOW(v) = NULL;
    }
}

BOOL  FEVarTypeResMove(void *v,void *v2)
{
    if ( !FEVarTypeIsInit(v) || !FEVarTypeIsInit(v2) )
    {
        return FALSE;
    }
    FEVarTypeResDelete(v);
    FEVARTYPE_MEM_RES(v) = FEVARTYPE_MEM_RES(v2);
    FEVARTYPE_MEM_RES_FREE(v) = FEVARTYPE_MEM_RES_FREE(v2);
    FEVARTYPE_MEM_RES_SHOW(v) = FEVARTYPE_MEM_RES_SHOW(v2);
    FEVARTYPE_MEM_RES(v2) = NULL;
    FEVARTYPE_MEM_RES_FREE(v2) = NULL;
    FEVARTYPE_MEM_RES_SHOW(v2) = NULL;
    return TRUE;
}

void  FEVarTypeResShow(void *v,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return;
    }
    if ( (NULL!=FEVARTYPE_MEM_RES(v))&&(NULL!=FEVARTYPE_MEM_RES_SHOW(v)) )
    {
        ((funcarg3non)(FEVARTYPE_MEM_RES_SHOW(v))) \
            (FEVARTYPE_MEM_RES(v),(void *)T,Buf);
    }
}

BOOL  FEVarTypeResClone(void *v,void *v2)
{
    if ( !FEVarTypeIsInit(v) || !FEVarTypeIsInit(v2) )
    {
        return FALSE;
    }
    if ( (NULL!=FEVARTYPE_MEM_RES(v2))&&(NULL!=FEVARTYPE_MEM_RES_CLONE(v2)) )
    {
        FEVARTYPE_MEM_RES(v) = (((funcarg1vp)(FEVARTYPE_MEM_RES_CLONE(v2)))) 
            (FEVARTYPE_MEM_RES(v2));
    }
    if ( NULL!=FEVARTYPE_MEM_RES(v) )
    {
        FEVARTYPE_MEM_RES_FREE(v) = FEVARTYPE_MEM_RES_FREE(v2);
        FEVARTYPE_MEM_RES_SHOW(v) = FEVARTYPE_MEM_RES_SHOW(v2);
    }
    return TRUE;
}

INT32 FEVarTypeKeyGetLen(void *v)
{
    if ( FEVarTypeVKIsNot(v) )
    {
        return 0;
    }
    return FEVARTYPE_MEM_KL(v);
}

void *FEVarTypeKeyGet(void *v)
{
    if ( FEVarTypeVKIsNot(v) )
    {
        return 0;
    }
    return FEVARTYPE_MEM_KEY(v);
}

void  FEVarTypeKeyDelete(void *v)
{
    if ( FEVarTypeVKIsNot(v) )
    {
        return;
    }
    if ( FEVARTYPEKEY_ISHASHKEY(v) )
    {
        return ;
    }
    if ( NULL!=FEVARTYPE_MEM_KEY(v) )
    {
        free(FEVARTYPE_MEM_KEY(v));
    }
    FEVARTYPE_MEM_KS(v) = 0;
    FEVARTYPE_MEM_KL(v) = 0;
    FEVARTYPE_MEM_KEY(v) = NULL;
    FEVarTypeVKSetNot(v);
}

void  FEVarTypeKeyDelete2(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return;
    }
    if ( FEVARTYPEKEY_ISHASHKEY(v) )
    {
        FEVarTypeVKSetKey(v);
    }
    FEVarTypeKeyDelete(v);
}

BOOL  FEVarTypeKeySet(void *v,void *Key,INT32 KS,INT32 KL)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FALSE;
    }
    if ( (NULL==Key)||(0>=KS)||(0>=KL)||(KS<KL) )
    {
        FEVARTYPE_MEM_KS(v) = 0;
        FEVARTYPE_MEM_KL(v) = 0;
        FEVARTYPE_MEM_KEY(v) = NULL;
        FEVarTypeVKSetNot(v);
    }
    else
    {
        FEVARTYPE_MEM_KS(v) = KS;
        FEVARTYPE_MEM_KL(v) = KL;
        FEVARTYPE_MEM_KEY(v) = Key;
        FEVarTypeVKSetKey(v);
    }
    return TRUE;
}

BOOL  FEVarTypeKeyMove(void *v,void *v2)
{
    if ( !FEVarTypeIsInit(v) || !FEVarTypeIsInit(v2) )
    {
        return FALSE;
    }
    if ( !FEVARTYPEKEY_HAVE(v2) )
    {
        return TRUE;
    }
    FEVarTypeKeyDelete(v);
    if ( !FEVarTypeKeySet(v \
        ,FEVARTYPE_MEM_KEY(v2) \
        ,FEVARTYPE_MEM_KS(v2) \
        ,FEVARTYPE_MEM_KL(v2)) )
    {
        return FALSE;
    }
    FEVarTypeKeySet(v2,NULL,0,0);
    return TRUE;
}

BOOL  FEVarTypeKeyCat(void *v,const char *Key,INT32 Len)
{
    INT32 KS;
    INT32 KL;
    INT32 Pos;
    INT32 L;
    void *K;
    if ( !FEVarTypeIsInit(v)||(NULL==Key)||(0>=Len) )
    {
        return FALSE;
    }
    if ( FEVARTYPEKEY_ISHASHKEY(v) )
    {
        return FALSE;
    }
    if ( 0==strlen(Key) )
    {
        return FALSE;
    }
    L = FECAL_MAX(1,FEVARTYPE_MEM_KS(v));
    KL = FECAL_MAX(0,FEVARTYPE_MEM_KL(v));
    K = FEVARTYPE_MEM_KEY(v);
    Pos = FECAL_MAX(0,KL);
    KS = L+Len;
    if ( (NULL==K)||(0>=KS) )
    {
        if ( NULL==(K=malloc(KS)) )
        {
            return FALSE;
        }
    }
    else
    {
        if ( NULL==(K=realloc(K,KS)) )
        {
            return FALSE;
        }
    }
    memset(((BYTE*)K)+Pos,0,KS-KL);
    memcpy(((BYTE*)K)+Pos,Key,Len);
    if ( !FEVarTypeKeySet(v,K,KS,KL+Len) )
    {
        return FALSE;
    }
    FEVARTYPE_MEM_KH(v) = FEHashCalKey(K,KL+Len);
    return TRUE;
}

BOOL  FEVarTypeKeyCpy(void *v,const char *Key,INT32 Len)
{
    if ( !FEVarTypeIsInit(v)||(NULL==Key)||(0>=Len) )
    {
        return FALSE;
    }
    if ( FEVARTYPEKEY_ISHASHKEY(v) )
    {
        return FALSE;
    }
    if ( 0==strlen(Key) )
    {
        return FALSE;
    }
    FEVarTypeKeyDelete(v);
    return FEVarTypeKeyCat(v,Key,Len);
}

BOOL  FEVarTypeKeyReplace(void *v,const char *Key,INT32 Len)
{
    INT32 L;
    INT32 KL;
    if ( !FEVarTypeIsInit(v)||(NULL==Key)||(0>=Len) )
    {
        return FALSE;
    }
    if ( !FEVARTYPEKEY_ISHASHKEY(v) )
    {
        return FALSE;
    }
    L = FECAL_MAX(1,FEVARTYPE_MEM_KS(v));
    KL = FECAL_MAX(0,FEVARTYPE_MEM_KL(v));
    if ( L<Len )
    {
        return FEVarTypeKeyCpy(v,Key,Len);
    }
    memset(FEVARTYPE_MEM_KEY(v),0,L);
    memcpy(FEVARTYPE_MEM_KEY(v),Key,Len);
    FEVARTYPE_MEM_KL(v) = Len;
    FEVARTYPE_MEM_KH(v) = FEHashCalKey(FEVARTYPE_MEM_KEY(v),Len);
    return TRUE;
}

BOOL  FEVarTypeKeyCmp(void *v,const char *Key,INT32 Len)
{
    if ( FEVarTypeVKIsNot(v) )
    {
        return FALSE;
    }
    if ( FEVARTYPE_MEM_KL(v)!=Len )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL(0==memcmp(FEVARTYPE_MEM_KEY(v),Key,Len));
}

void  FEVarTypeKeyShow(void *v,INT32 T,void *Buf)
{
    char Log[BUFSIZE_256];
    char Tab[BUFSIZE_64];
    INT32 L;
 
    if ( FEVarTypeVKIsNot(v) )
    {
        return;
    }
 
    memset(Tab,0,sizeof(Tab));
    FEVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    L = 0;
    snprintf(Log+L,sizeof(Log),"%s<Key VK=\"%d\" HK=\"%d\" Len=\"%d\">" \
        ,Tab,FEVARTYPE_MEM_VK_GET(v),FEVARTYPE_MEM_KH(v),FEVarTypeKeyGetLen(v));
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);

    FEVarStringCat(Buf,FEVarTypeKeyGet(v),FEVarTypeKeyGetLen(v));

    L = 0;
    snprintf(Log+L,sizeof(Log),"</Key>\n");
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);
}

BOOL  FEVarTypeKeyPack(void *v,void *Buf)
{
    if ( !FEVarTypeIsInit(v) || !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    if ( !FEPackFuncInt16(Buf,FEVARTYPE_MEM_KL(v)) )
    {
        return FALSE;
    }
    if ( !FEVarTypeVKIsNot(v) )
    {
        if ( !FEPackFuncString(Buf,FEVARTYPE_MEM_KEY(v),FEVARTYPE_MEM_KL(v)) )
        {
            return FALSE;
        }
    }
    return TRUE;
}

INT32 FEVarTypeKeyUnPack(tFEVarType *VarType,void *Buf,INT32 P)
{
    void *V;
    if ( !FEUnPackFuncInt16(Buf,P,&(FEVARTYPE_MEM_KL(VarType))) )
    {
        return FERTN_ERVAR_UNPACK;
    }
    if ( NULL==(V=FEVarBinGet(Buf)) )
    {
        return FERTN_ERVAR_UNPACK;
    }
    FEVARTYPE_MEM_KEY(VarType) = ((char *)V)+P+INT16_SIZE;
    return P+INT16_SIZE+FEVARTYPE_MEM_KL(VarType);
}

BOOL  FEVarTypeKeyClone(void *Dest,void *Src)
{
    if ( !FEVarTypeIsInit(Dest) || !FEVarTypeIsInit(Src) )
    {
        return FALSE;
    }
    if ( FEVarTypeVKIsNot(Src) )
    {
        return TRUE;
    }
    return FEVarTypeKeyCpy(Dest,FEVarTypeKeyGet(Src),FEVarTypeKeyGetLen(Src));
}

void *FEVarTypeFuncGetClone(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return NULL;
    }
    return FEVARTYPE_MEM_CLONE(v);
}

void *FEVarTypeFuncGetFree(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return NULL;
    }
    return FEVARTYPE_MEM_FREE(v);
}

void *FEVarTypeFuncGetShow(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return NULL;
    }
    return FEVARTYPE_MEM_SHOW(v);
}

void *FEVarTypeFuncGetPack(void *v)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return NULL;
    }
    return FEVARTYPE_MEM_PACK(v);
}

BOOL  FEVarTypeFuncSet(void *v,void *Clone,void *Free,void *Show,void *Pack)
{
    if ( !FEVarTypeIsInit(v) )
    {
        return FALSE;
    }
    FEVARTYPE_MEM_CLONE(v) = Clone;
    FEVARTYPE_MEM_FREE(v) = Free;
    FEVARTYPE_MEM_SHOW(v) = Show;
    FEVARTYPE_MEM_PACK(v) = Pack;
    return TRUE;
}

#ifdef __cplusplus
}
#endif

