/***************************************************************************/
/**[File Name    ]varhash.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for hash                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

#define FEVARHASH_INFO_POS     (0)
#define FEVARHASH_INFO_BASE_P   (FEVARHASH_INFO_POS)
#define FEVARHASH_INFO_BASE_L   (INT32_SIZE)
#define FEVARHASH_INFO_LEN_P   (FEVARHASH_INFO_BASE_P+FEVARHASH_INFO_BASE_L)
#define FEVARHASH_INFO_LEN_L   (INT32_SIZE)
#define FEVARHASH_INFO_LEN \
    (FEVARTYPE_INFO_LEN+FEVARHASH_INFO_BASE_L+FEVARHASH_INFO_LEN_L)
#define FEVARHASH_VALUE_POS    (FEVARHASH_INFO_LEN)
#define FEVARHASH_VALUE_LEN    0

void *FEVarHashNew(INT32 Size)
{
    void *Var;
    void *Arr;
    INT32 HS;
    INT32 i;
    BOOL Flag;
    if ( NULL==(Var=FEVarRootNew()) )
    {
        return NULL;
    }
    FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_HASH);
    HS = FEHashCalSize(Size);
    FEVarRootSetMax(Var,0);
    FEVarRootSetSize(Var,HS);
    FEVarRootSetLen(Var,0);
    if ( NULL==(Arr=malloc(FEVARP4_ST_SIZE*HS)) )
    {
        FEVarHashNFree(Var);
        return NULL;
    }
    memset(Arr,0,FEVARP4_ST_SIZE*HS);
    for ( i=0;i<HS;i++ )
    {
        FEVarHashInitPointer(((tFEVarPointer4*)Arr)+i);
    }
    FEVarRootSetValue(Var,Arr);
    Flag = TRUE;
    for ( i=0;i<HS;i++ )
    {
        if ( !FEVarHashInitLink(((tFEVarPointer4*)Arr)+i) )
        {
            Flag = FALSE;
            break;
        }
    }
    if ( !Flag )
    {
        FEVarRootFree(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarHashNew_Key(INT32 Max,const char *Key)
{
    void *Var;
    if ( NULL==(Var=FEVarHashNew(Max)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarHashFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void  FEVarHashFree(void *Var)
{
    FEVarHashVFree(Var);
    FEVarHashNFree(Var);
}

void  FEVarHashNFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarHashVFree(void *Var)
{
    INT32 i;
    INT32 HS;
    void *Arr;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_HASH) )
    {
        return;
    }
    if ( NULL!=(Arr=FEVarRootGetValue(Var)) )
    {
        HS = FEVarRootGetSize(Var);
        for ( i=0;i<HS;i++ )
        {
            FEVarPointer4VFree(((tFEVarPointer4*)Arr)+i);
        }
        free(Arr);
    }
    FEVarRootSetSize(Var,0);
    FEVarRootSetValue(Var,NULL);
}

void  FEVarHashShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_HASH) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarHashNShow1(Var,T,Buf);
    FEVarHashVShow(Var,T,Buf);
    FEVarTypeNShow2(Var,T,Buf);
}

void  FEVarHashNShow1(void *Var,INT32 T,void *Buf)
{
    char Log[BUFSIZE_512];
    char Tab[BUFSIZE_64];
    char *Type;
    INT32 L;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_HASH) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    memset(Tab,0,sizeof(Tab));
    FEVarToolsInitBufSpace(Tab,sizeof(Tab),T);
    Type = FEVarTypeInfoGetName(FEVarTypeVTGet(Var));

    L = 0;
    sprintf(Log+L,"%s<Node Addr=\"%08X\" VV=\"%d\" VT=\"%d\" Type=\"%s\" "
                "Base=\"%d\" Len=\"%d\">\n" \
        ,Tab,(INT32)Var,FEVarTypeVVGet(Var),FEVarTypeVTGet(Var) \
        ,(NULL==Type)?"unknown":Type \
        ,FEVarRootGetSize(Var),FEVarRootGetLen(Var));
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);
    FEVarTypeResShow(Var,T,Buf);
    FEVarTypeKeyShow(Var,T,Buf);
}

void  FEVarHashVShow(void *Var,INT32 T,void *Buf)
{
    INT32 i;
    INT32 HS;
    void *Arr;
    void *Link;
    void *Node;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_HASH) )
    {
        return;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    HS = FEVarRootGetSize(Var);
    Arr = FEVarRootGetValue(Var);
    for ( i=0;i<HS;i++ )
    {
        Link = FEVarPointer4GetP0(((tFEVarPointer4*)Arr)+i);
        if ( !FEVarTypeIsInit2(Link,FEVARTYPE_MEM_VT_LINK) )
        {
            continue;
        }
        Node = FEVarRootGetValue(Link);
        while( NULL!=Node )
        {
            if ( !FEVarTypeIsInit(Node) )
            {
                break;
            }
            FEVarShow(FEVarPointer4GetP0(Node),T+1,Buf);
            Node = FEVarPointer4GetP1(Node);
        }
    }
}

BOOL  FEVarHashPackInfo(void *Var,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_HASH) )
    {
        return FALSE;
    }
    /* Base,Len */
    if ( !FEPackFuncInt32(Buf,FEVarRootGetSize(Var)) )
    {
        return FALSE;
    }
    return FEPackFuncInt32(Buf,FEVarHashGetLen(Var));
}
 
BOOL  FEVarHashVPack(void *Var,void *Buf)
{
    INT32 i;
    INT32 HS;
    void *Arr;
    void *Link;
    void *Node;
    BOOL bRtn;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_HASH) )
    {
        return FALSE;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    HS = FEVarRootGetSize(Var);
    Arr = FEVarRootGetValue(Var);
    bRtn = TRUE;
    for ( i=0;i<HS;i++ )
    {
        Link = FEVarPointer4GetP0(((tFEVarPointer4*)Arr)+i);
        if ( !FEVarTypeIsInit2(Link,FEVARTYPE_MEM_VT_LINK) )
        {
            continue;
        }
        Node = FEVarRootGetValue(Link);
        while( NULL!=Node )
        {
            if ( !FEVarTypeIsInit(Node) )
            {
                bRtn = FALSE;
                break;
            }
            FEVarPack(FEVarPointer4GetP0(Node),Buf);
            Node = FEVarPointer4GetP1(Node);
        }
        if ( !bRtn )
        {
            break;
        }
    }
    return bRtn;
}

BOOL  FEVarHashPack(void *Var,void *Buf)
{
    BOOL bRtn;
    INT32 PL;
    INT32 L;
 
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_HASH) )
    {
        return FALSE;
    }
    L = FEVarBinGetLen(Buf);
    bRtn = FALSE;
    while( 1 )
    {
        PL = FEVARHASH_INFO_LEN + FEVARHASH_VALUE_LEN;
        /* VarType */
        if ( !FEVarTypePack(Buf,Var,PL,FEVarHashPackInfo) )
        {
            break;
        }
        if ( FALSE==(bRtn=FEVarHashVPack(Var,Buf)) )
        {
            break;
        }
        break;
    }
    if ( !bRtn )
    {
        FEVarBinCut(Buf,L,0);
    }
 
    return bRtn;
}

INT32 FEVarHashUnPack(void **VVar,void *Buf,INT32 P)
{
    INT32 iRtn;
    INT32 PL;
    tFEVarType VarType;
    void *V;
    INT32 VL;
    void *Var;
    void *N;
 
    INT32 Size;
    INT32 Len;
    INT32 Idx;
 
    iRtn = RTNCODE_ERVAR_UNPACK;
    if ( NULL==VVar )
    {
        return iRtn;
    }
    if ( NULL==(V=FEVarBinGet(Buf)) )
    {
        return iRtn;
    }
    if ( FEVARTYPE_MEM_VT_HASH!=((BYTE*)V)[P] )
    {
        return iRtn;
    }
    if ( FERTN_OK>(iRtn=FEVarTypeUnPack(&PL,&VarType,Buf,P+BYTE_SIZE)) )
    {
        return iRtn;
    }
    VL = PL;
    PL = iRtn;
 
    *VVar = NULL;
    Var = NULL;
    N = NULL;
    iRtn = FERTN_ERVAR_UNPACK;
    while( 1 )
    {
        /* Size */
        if ( !FEUnPackFuncInt32(Buf,PL+FEVARHASH_INFO_BASE_P,&Size) )
        {
            break;
        }
        if ( !FEUnPackFuncInt32(Buf,PL+FEVARHASH_INFO_LEN_P,&Len) )
        {
            break;
        }
        if ( NULL==(Var=FEVarHashNew(Size)) )
        {
            break;
        }
        if ( !FEVarTypeUnPackSetType(Var,&VarType) )
        {
            break;
        }
        PL += FEVARHASH_VALUE_POS;
        for ( Idx=0;Idx<Len;Idx++ )
        {
            if ( 0>(iRtn=FEVarUnPack(&N,Buf,PL)) )
            {
                break;
            }
            PL = iRtn;
            if ( !FEVarHashAdd(Var,N) )
            {
                break;
            }
            N = NULL;
        }
        if ( Idx<Len )
        {
            iRtn = FERTN_ERVAR_UNPACK;
            break;
        }
        iRtn = FERTN_OK;
        break;
    }
    if ( FERTN_OK==iRtn )
    {
        iRtn = PL;
        *VVar = Var;
        Var = NULL;
    }
    FEVarFree(N);
    N = NULL;
    FEVarHashFree(Var);
    Var = NULL;
    return iRtn;
}

void  FEVarHashInitPointer(void *VP)
{
    if ( NULL==VP )
    {
        return ;
    }
    FEVarPointer4Init(VP,FEVARHASH_NODE_P_NUM_ARRAY);
    FEVarPointer4SetFlag(VP,0);
}

BOOL  FEVarHashInitLink(void *VP)
{
    void *Link;
    if ( NULL==VP )
    {
        return FALSE;
    }
    if ( NULL==(Link=FEVarLinkNew(0)) )
    {
        return FALSE;
    }
    return FEVarPointer4SetP0(VP,Link);
}

BOOL  FEVarHashIsEmpty(void *Var)
{
    return FEVarRootIsEmpty(Var);
}

INT32 FEVarHashGetLen(void *Var)
{
    return FEVarRootGetLen(Var);
}

void *FEVarHashGetLink(void *Var,const void *Key,INT32 Len)
{
    void *Arr;
    INT32 KH;
    INT32 Idx;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_HASH)||(NULL==Key) )
    {
        return NULL;
    }
    if ( 0==strlen(Key) )
    {
        return NULL;
    }
    KH = FEHashCalKey(Key,Len);
    Idx = FEHashGetIdx(KH,FEVarRootGetSize(Var));
    if ( NULL==(Arr=FEVarRootGetValue(Var)) )
    {
        return NULL;
    }
    return FEVarPointer4GetP0(((tFEVarPointer4*)Arr)+Idx);
}

void *FEVarHashGetNode(void *Var,const void *Key,INT32 Len)
{
    void *Link;
    if ( NULL==(Link=FEVarHashGetLink(Var,Key,Len)) )
    {
        return FALSE;
    }
    return FEVarLinkGetNodeByKey(Link,Key,Len);
}

void *FEVarHashGet(void *Var,const void *Key,INT32 Len)
{
    void *Link;
    if ( NULL==(Link=FEVarHashGetLink(Var,Key,Len)) )
    {
        return NULL;
    }
    return FEVarLinkGetByKey(Link,Key,Len);
}

BOOL  FEVarHashGet2(void *Var,const void *Key,INT32 Len,void **V)
{
    void *Link;
    if ( NULL==(Link=FEVarHashGetLink(Var,Key,Len)) )
    {
        return FALSE;
    }
    return FEVarLinkGet2ByKey(Link,Key,Len,V);
}

BOOL  FEVarHashAdd(void *Var,void *V)
{
    void *Link;
    if ( NULL==FEVarGetKey(V) )
    {
        return FALSE;
    }
    if ( NULL==(Link=FEVarHashGetLink(Var,FEVarGetKey(V),FEVarGetKeyLen(V))) )
    {
        return FALSE;
    }
    if ( !FEVarLinkAdd(Link,V) )
    {
        return FALSE;
    }
    FEVarTypeVKSetHashKey(V);
    FEVarRootAddLen(Var,TRUE);
    return TRUE;
}

BOOL  FEVarHashReplace(void *Var,void *V)
{
    void *Link;
    if ( NULL==(Link=FEVarHashGetLink(Var,FEVarGetKey(V),FEVarGetKeyLen(V))) )
    {
        return FALSE;
    }
    return FEVarLinkReplaceByKey(Link,FEVarGetKey(V),FEVarGetKeyLen(V),V);
}

BOOL  FEVarHashReplaceValue(void *Var,const void *Key,INT32 Len,void *V)
{
    void *Link;
    if ( NULL==(Link=FEVarHashGetLink(Var,Key,Len)) )
    {
        return FALSE;
    }
    return FEVarLinkReplaceValueByKey(Link,Key,Len,V);
}

BOOL  FEVarHashDelete(void *Var,const void *Key,INT32 Len)
{
    void *Link;
    if ( NULL==(Link=FEVarHashGetLink(Var,Key,Len)) )
    {
        return FALSE;
    }
    if ( !FEVarLinkDeleteByKey(Link,Key,Len) )
    {
        return FALSE;
    }
    FEVarRootAddLen(Var,FALSE);
    return TRUE;
}

BOOL  FEVarHashCloneLink(void *VP,void *VVP)
{
    void *Link;
    if ( NULL==VP )
    {
        return FALSE;
    }
    if ( NULL==(Link=FEVarLinkClone(VVP)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(VP,Link) )
    {
        FEVarLinkFree(Link);
    }
    return TRUE;
}

void *FEVarHashClone(void *Var)
{
    void *NVar;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_HASH) )
    {
        return NULL;
    }
    if ( NULL==(NVar=FEVarHashNew(FEVarRootGetSize(Var))) )
    {
        return NULL;
    }
    if ( !FEVarHashCloneValue(NVar,Var) )
    {
        FEVarHashFree(NVar);
        NVar = NULL;
    }
    if ( !FEVarTypeClone(NVar,Var) )
    {
        FEVarHashFree(NVar);
        NVar = NULL;
    }
    return NVar;
}

BOOL  FEVarHashCloneValue(void *NVar,void *OVar)
{
    void *N;
    void *OArr;
    void *OLink;
    INT32 HS;
    INT32 LL;
    INT32 i;
    INT32 j;
    BOOL bRtn;

    if ( !FEVarTypeIsInit2(NVar,FEVARTYPE_MEM_VT_HASH) )
    {
        return FALSE;
    }
    if ( !FEVarTypeIsInit2(OVar,FEVARTYPE_MEM_VT_HASH) )
    {
        return TRUE;
    }

    OArr = FEVarRootGetValue(OVar);
    HS = FEVarRootGetSize(OVar);
    bRtn = TRUE;
    for ( i=0;i<HS;i++ )
    {
        if ( NULL==(OLink=FEVarPointer4GetP0(((tFEVarPointer4*)OArr)+i)) )
        {
            bRtn = FALSE;
            break;
        }
        LL = FEVarLinkGetLen(OLink);
        N = NULL;
        for ( j=0;j<LL;j++ )
        {
            if ( NULL==(N=FEVarClone(FEVarLinkGet(OLink,j))) )
            {
                bRtn = FALSE;
                break;
            }
            if ( !FEVarHashAdd(NVar,N) )
            {
                bRtn = FALSE;
                break;
            }
            N = NULL;
        }
        if ( !bRtn )
        {
            break;
        }
    }
    FEVarFree(N);
    N = NULL;
    return bRtn;
}

#ifdef __cplusplus
}
#endif

