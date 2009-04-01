/***************************************************************************/
/**[File Name    ]vararray.c                                              **/
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


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

#define FEVARARRAY_INFO_POS     (0)
#define FEVARARRAY_INFO_MAX_P   (FEVARARRAY_INFO_POS)
#define FEVARARRAY_INFO_MAX_L   (INT32_SIZE)
#define FEVARARRAY_INFO_LEN_P   (FEVARARRAY_INFO_MAX_P+FEVARARRAY_INFO_MAX_L)
#define FEVARARRAY_INFO_LEN_L   (INT32_SIZE)
#define FEVARARRAY_INFO_LEN \
    (FEVARTYPE_INFO_LEN+FEVARARRAY_INFO_MAX_L+FEVARARRAY_INFO_LEN_L)
#define FEVARARRAY_VALUE_POS    (FEVARARRAY_INFO_LEN)
#define FEVARARRAY_VALUE_LEN    0

void *FEVarArrayNew(INT32 Max)
{
    void *Var;
    if ( NULL==(Var=FEVarRootNew()) )
    {
        return NULL;
    }
    FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_ARRAY);
    FEVarRootSetMax(Var,Max);
    FEVarRootSetSize(Var,0);
    FEVarRootSetLen(Var,0);
    return Var;
}

void *FEVarArrayNew_Key(INT32 Max,const char *Key)
{
    void *Var;
    if ( NULL==(Var=FEVarArrayNew(Max)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarArrayFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void *FEVarArrayNew2(INT32 Max)
{
    void *Var;
    if ( NULL==(Var=FEVarArrayNew(Max)) )
    {
        return NULL;
    }
    if ( 0>=Max )
    {
        return Var;
    }
    if ( !FEVarArrayRealloc(Var,FEVarArrayGetMax(Var)) )
    {
        FEVarArrayFree(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarArrayNew2_Key(INT32 Max,const char *Key)
{
    void *Var;
    if ( NULL==(Var=FEVarArrayNew2(Max)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarArrayFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void  FEVarArrayFree(void *Var)
{
    FEVarArrayVFree(Var);
    FEVarArrayNFree(Var);
}

void  FEVarArrayNFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarArrayVFree(void *Var)
{
    INT32 i;
    INT32 Len;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return;
    }
    Len = FEVarRootGetLen(Var);
    for ( i=Len-1;i>=0;i-- )
    {
        FEVarArrayDelete(Var,FEVarArrayGetLen(Var)-1);
    }
    free(FEVarRootGetValue(Var));
    FEVarRootSetSize(Var,0);
    FEVarRootSetValue(Var,NULL);
}

void  FEVarArrayShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarArrayNShow1(Var,T,Buf);
    FEVarArrayVShow(Var,T,Buf);
    FEVarTypeNShow2(Var,T,Buf);
}

void  FEVarArrayVShow(void *Var,INT32 T,void *Buf)
{
    INT32 Len;
    INT32 i;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    Len = FEVarRootGetLen(Var);
    for ( i=0;i<Len;i++ )
    {
        FEVarShow(FEVarArrayGet(Var,i),T+1,Buf);
    }
}

BOOL  FEVarArrayPackInfo(void *Var,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    /* Max,Len */
    if ( !FEPackFuncInt32(Buf,FEVarArrayGetMax(Var)) )
    {
        return FALSE;
    }
    return FEPackFuncInt32(Buf,FEVarArrayGetLen(Var));
}

BOOL  FEVarArrayPack(void *Var,void *Buf)
{
    BOOL bRtn;
    INT32 PL;
    INT32 L;
 
    INT32 Idx;
    INT32 Len;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    L = FEVarBinGetLen(Buf);
    bRtn = FALSE;
    while( 1 )
    {
        PL = FEVARARRAY_INFO_LEN + FEVARARRAY_VALUE_LEN;
        /* VarType */
        if ( !FEVarTypePack(Buf,Var,PL,FEVarArrayPackInfo) )
        {
            break;
        }
        Len = FEVarArrayGetLen(Var);
        for ( Idx=0;Idx<Len;Idx++ )
        {
            if ( FALSE==(bRtn=FEVarPack(FEVarArrayGet(Var,Idx),Buf)) )
            {
                break;
            }
        }
        break;
    }
    if ( !bRtn )
    {
        FEVarBinCut(Buf,L,0);
    }
 
    return bRtn;
}

INT32 FEVarArrayUnPack(void **VVar,void *Buf,INT32 P)
{
    INT32 iRtn;
    INT32 PL;
    tFEVarType VarType;
    void *V;
    INT32 VL;
    void *Var;
    void *N;
 
    INT32 Max;
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
    if ( FEVARTYPE_MEM_VT_ARRAY!=((BYTE*)V)[P] )
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
        /* Max */
        if ( !FEUnPackFuncInt32(Buf,PL+FEVARARRAY_INFO_MAX_P,&Max) )
        {
            break;
        }
        if ( !FEUnPackFuncInt32(Buf,PL+FEVARARRAY_INFO_LEN_P,&Len) )
        {
            break;
        }
        if ( NULL==(Var=FEVarArrayNew(Max)) )
        {
            break;
        }
        if ( !FEVarTypeUnPackSetType(Var,&VarType) )
        {
            break;
        }
        PL += FEVARARRAY_VALUE_POS;
        for ( Idx=0;Idx<Len;Idx++ )
        {
            if ( 0>(iRtn=FEVarUnPack(&N,Buf,PL)) )
            {
                break;
            }
            PL = iRtn;
            if ( !FEVarArrayAdd(Var,N) )
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
    FEVarArrayFree(Var);
    Var = NULL;
    return iRtn;
}

BOOL  FEVarArrayIsEmpty(void *Var)
{
    return FEVarRootIsEmpty(Var);
}

BOOL  FEVarArrayIsFull(void *Var)
{
    return FEVarRootIsFull(Var);
}

BOOL  FEVarArrayRealloc(void *Var,INT32 S)
{
    INT32 Size;
    INT32 S1;
    INT32 i;
    void *V;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    if ( (!FEVarRootIsAdd(Var))||(!FEVarRootCanAdd(Var)) )
    {
        return FALSE;
    }
    S1 = FECAL_MAX(S,FEVARARRAY_UNIT_MIN);
    Size = FEVarRootGetSize(Var);
    if ( S1+Size>=FEVarRootGetMax(Var)+FEVARARRAY_UNIT_MIN )
    {
        return FALSE;
    }
    if ( (0==Size)||(NULL==FEVarRootGetValue(Var)) )
    {
        if ( NULL==(V=malloc(FEVARP4_ST_SIZE*(Size+S1))) )
        {
            return FALSE;
        }
        memset(V,0,FEVARP4_ST_SIZE*(Size+S1));
    }
    else
    {
        if ( NULL==(V=realloc(FEVarRootGetValue(Var) \
            ,FEVARP4_ST_SIZE*(Size+S1))) )
        {
            return FALSE;
        }
        memset(((BYTE*)V)+FEVARP4_ST_SIZE*Size,0,FEVARP4_ST_SIZE*S1);
    }
    i = Size;
    Size += S1;
    for ( ;i<Size;i++ )
    {
        FEVarArrayInitPointer(((tFEVarPointer4*)V)+i);
    }
    FEVarRootSetValue(Var,V);
    FEVarRootSetSize(Var,Size);
    return TRUE;
}

void  FEVarArrayInitPointer(void *Var)
{
   FEVarPointer4Init(Var,FEVARARRAY_NODE_P_NUM);
   FEVarPointer4SetFlag(Var,0);
}

BOOL  FEVarArraySetMax(void *Var,INT32 Max)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    if ( FEVarArrayGetLen(Var)>Max )
    {
        return FALSE;
    }
    FEVarRootSetMax(Var,Max);
    return TRUE;
}

INT32 FEVarArrayGetMax(void *Var)
{
    return FEVarRootGetMax(Var);
}

INT32 FEVarArrayGetSize(void *Var)
{
    return FEVarRootGetSize(Var);
}

INT32 FEVarArrayGetLen(void *Var)
{
    return FEVarRootGetLen(Var);
}

BOOL  FEVarArraySetUserLen(void *Var,INT32 UserLen)
{
    return FEVarRootSetUserLen(Var,UserLen);
}

BOOL  FEVarArrayPlusUserLen(void *Var,BOOL Flag)
{
    return FEVarRootPlusUserLen(Var,Flag);
}

INT32 FEVarArrayGetUserLen(void *Var)
{
    return FEVarRootGetUserLen(Var);
}

BOOL  FEVarArraySetUserCnt(void *Var,INT32 UserCnt)
{
    return FEVarRootSetUserCnt(Var,UserCnt);
}

BOOL  FEVarArrayPlusUserCnt(void *Var,BOOL Flag)
{
    return FEVarRootPlusUserCnt(Var,Flag);
}

INT32 FEVarArrayGetUserCnt(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return RTNCODE_ERVAR_VT;
    }
    return FEVarRootGetUserCnt(Var);
}

BOOL  FEVarArrayIsIdxOfValue(void *Var,INT32 Idx)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL( (0<=Idx)&&(FEVarArrayGetLen(Var)>Idx) );
}

BOOL  FEVarArrayIsIdxOfRange(void *Var,INT32 Idx)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL( (0<=Idx)&&(FEVarArrayGetMax(Var)>Idx) );
}

void *FEVarArrayGetNode(void *Var,INT32 Idx)
{
    INT32 Size;
    void *V;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return NULL;
    }
    if ( !FEVarArrayIsIdxOfRange(Var,Idx) )
    {
        return NULL;
    }
    Size = FEVarRootGetSize(Var);
    if ( Idx>=Size )
    {
        if ( !FEVarArrayRealloc(Var,Idx-Size) )
        {
            return NULL;
        }
    }
    V = FEVarRootGetValue(Var);
    V = ((tFEVarPointer4*)V)+Idx;
    return V;
}

void *FEVarArrayGet(void *Var,INT32 Idx)
{
    void *Node;
    if ( NULL==(Node=FEVarArrayGetNode(Var,Idx)) )
    {
        return NULL;
    }
    return FEVarPointer4GetP0(Node);
}

BOOL  FEVarArrayGet2(void *Var,INT32 Idx,void **V)
{
    void *Node;
    if ( NULL==V )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarArrayGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    if ( FEVARTYPEVALUE_ISNOT(Node) )
    {
        return FALSE;
    }
    *V = FEVarPointer4GetP0(Node);
    return TRUE;
}

BOOL  FEVarArrayAdd(void *Var,void *V)
{
    void *Node;
    if ( NULL==(Node=FEVarArrayGetNode(Var,FEVarArrayGetLen(Var))) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    FEVarRootAddLen(Var,TRUE);
    return TRUE;
}

BOOL  FEVarArrayInsert(void *Var,INT32 Idx,void *V)
{
    void *Node;
    if ( !FEVarArrayMove(Var,Idx,1) )
    {
        return FALSE;
    }
    FEVarRootAddLen(Var,TRUE);
    if ( NULL==(Node=FEVarArrayGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  FEVarArrayReplace(void *Var,INT32 Idx,void *V)
{
    void *Node;
    if ( !FEVarArrayIsIdxOfValue(Var,Idx) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarArrayGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  FEVarArrayReplaceValue(void *Var,INT32 Idx,void *V)
{
    void *Node;
    void *OV;
    if ( !FEVarArrayIsIdxOfValue(Var,Idx) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarArrayGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    OV = FEVarPointer4GetP0(Node);
    if ( !FEVarTypeMove(V,OV) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  FEVarArrayDelete(void *Var,INT32 Idx)
{
    void *Node;
    void *V;
    if ( NULL==(Node=FEVarArrayGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    if ( FEVARTYPEVALUE_ISNOT(Node) )
    {
        return FALSE;
    }
    V = FEVarPointer4GetP0(Node);
    FEVarArrayMove(Var,Idx,-1);
    FEVarRootAddLen(Var,FALSE);
    FEVarFree(V);
    return TRUE;
}

BOOL  FEVarArrayMove(void *Var,INT32 Src,INT32 Len)
{
    INT32 i;
    void *V;
    INT32 L;
    INT32 ALen;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }
    if ( 0==Len )
    {
        return TRUE;
    }
    if ( FEVarArrayIsEmpty(Var) )
    {
        if ( 0<Src )
        {
            return FALSE;
        }
    }
    else
    {
        if ( !FEVarArrayIsIdxOfValue(Var,Src) )
        {
            return FALSE;
        }
    }
    ALen = FEVarRootGetLen(Var);
    V = FEVarRootGetValue(Var);
    if ( 0<Len )
    {
        /* Move Right */
        if ( !FEVarArrayIsIdxOfRange(Var,Src+Len) )
        {
            return FALSE;
        }
        if ( FEVarRootGetSize(Var)<ALen+Len )
        {
            if ( !FEVarArrayRealloc(Var,ALen+Len-FEVarRootGetSize(Var)) )
            {
                return FALSE;
            }
        }
        V = FEVarRootGetValue(Var);
        for ( L=ALen+Len-1,i=ALen-1;i>=Src;i--,L-- )
        {
            memcpy(((char *)V)+L*FEVARP4_ST_SIZE \
                ,((char *)V)+i*FEVARP4_ST_SIZE \
                ,FEVARP4_ST_SIZE);
        }
        for ( ;L>=Src;L-- )
        {
            FEVarArrayInitPointer(((tFEVarPointer4*)V)+L);
        }
        return TRUE;
    }
    /* Move Left */
    L = FECAL_MAX(0,Src+1+Len);
    if ( L<Src+1 )
    {
        for ( i=Src+1;i<ALen;i++,L++ )
        {
            memcpy(((char *)V)+L*FEVARP4_ST_SIZE \
                ,((char *)V)+i*FEVARP4_ST_SIZE \
                ,FEVARP4_ST_SIZE);
        }
    }
    for ( ;L<ALen;L++ )
    {
        FEVarArrayInitPointer(((tFEVarPointer4*)V)+L);
    }
    return TRUE;
}

INT32 FEVarArrayGetIdxByKey(void *Var,const void *Key,INT32 Len)
{
    void *V;
    INT32 Idx;
    INT32 L;
    BOOL Flag;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return FERTN_ER;
    }
    L = FEVarArrayGetLen(Var);
    for ( Idx=0;Idx<L;Idx++ )
    {
        if ( NULL==(V=FEVarArrayGet(Var,Idx)) )
        {
            continue;
        }
        if ( FEVARTYPEVALUE_ISNOT(V) )
        {
            continue;
        }
        if ( FEVarTypeKeyCmp(V,Key,Len) )
        {
            Flag = TRUE;
            break;
        }
    }
    return (Idx>=Len)?FERTN_ER:Idx;
}

void *FEVarArrayGetNodeByKey(void *Var,const void *Key,INT32 Len)
{
    INT32 Idx;
    if ( FERTN_ER==(Idx=FEVarArrayGetIdxByKey(Var,Key,Len)) )
    {
        return NULL;
    }
    return FEVarArrayGetNode(Var,Idx);
}

void *FEVarArrayGetByKey(void *Var,const void *Key,INT32 Len)
{
    INT32 Idx;
    if ( FERTN_ER==(Idx=FEVarArrayGetIdxByKey(Var,Key,Len)) )
    {
        return NULL;
    }
    return FEVarArrayGet(Var,Idx);
}

BOOL  FEVarArrayGet2ByKey(void *Var,const void *Key,INT32 Len,void **V)
{
    INT32 Idx;
    if ( FERTN_ER==(Idx=FEVarArrayGetIdxByKey(Var,Key,Len)) )
    {
        return FALSE;
    }
    return FEVarArrayGet2(Var,Idx,V);
}

BOOL  FEVarArrayInsertByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    INT32 Idx;
    if ( FERTN_ER==(Idx=FEVarArrayGetIdxByKey(Var,Key,Len)) )
    {
        return FALSE;
    }
    return FEVarArrayInsert(Var,Idx,V);
}

BOOL  FEVarArrayReplaceByKey(void *Var,void *V)
{
    INT32 Idx;
    if ( FERTN_ER==(Idx=FEVarArrayGetIdxByKey(Var \
        ,FEVarGetKey(V),FEVarGetKeyLen(V))) )
    {
        return FALSE;
    }
    return FEVarArrayReplace(Var,Idx,V);
}

BOOL  FEVarArrayReplaceValueByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    INT32 Idx;
    if ( FERTN_ER==(Idx=FEVarArrayGetIdxByKey(Var,Key,Len)) )
    {
        return FALSE;
    }
    return FEVarArrayReplaceValue(Var,Idx,V);
}

BOOL  FEVarArrayDeleteByKey(void *Var,const void *Key,INT32 Len)
{
    INT32 Idx;
    if ( FERTN_ER==(Idx=FEVarArrayGetIdxByKey(Var,Key,Len)) )
    {
        return FALSE;
    }
    return FEVarArrayDelete(Var,Idx);
}

void *FEVarArrayClone(void *Var)
{
    void *N;
    if ( FEVARTYPE_MEM_VT_ARRAY!=FEVarTypeVTGet(Var) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarArrayNew(FEVarArrayGetMax(Var))) )
    {
        return NULL;
    }
    if ( !FEVarArrayCloneValue(N,Var) )
    {
        FEVarArrayFree(N);
        N = NULL;
    }
    if ( !FEVarTypeClone(N,Var) )
    {
        FEVarArrayFree(N);
        N = NULL;
    }
    return N;
}

BOOL  FEVarArrayCloneValue(void *N,void *Var)
{
    INT32 i;
    INT32 L;
    INT32 S;
    void *V;
    BOOL bRtn;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return TRUE;
    }
    if ( !FEVarTypeIsInit2(N,FEVARTYPE_MEM_VT_ARRAY) )
    {
        return FALSE;
    }

    bRtn = TRUE;
    V = NULL;
    while( 1 )
    {
        S = FEVarRootGetSize(Var);
        L = FEVarRootGetLen(Var);
        S = FECAL_MAX(S,L);
        if ( !FEVarArrayRealloc(N,S) )
        {
            bRtn = FALSE;
            break;
        }
        for ( i=0;i<L;i++ )
        {
            if ( NULL==(V=FEVarClone(FEVarArrayGet(Var,i))) )
            {
                bRtn = FALSE;
                break;
            } 
            if ( !FEVarArrayAdd(N,V) )
            {
                bRtn = FALSE;
                break;
            } 
            V = NULL;
        }
        break;
    }
    FEVarFree(V);
    V = NULL;
    return bRtn;
}

#ifdef __cplusplus
}
#endif

