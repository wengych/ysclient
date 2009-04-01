/***************************************************************************/
/**[File Name    ]varfilo.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for filo                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

void *FEVarFiloNew(INT32 Max)
{
    void *Var;
    if ( NULL==(Var=FEVarRootNew()) )
    {
        return NULL;
    }
    FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_FILO);
    FEVarRootSetMax(Var,Max);
    FEVarRootSetSize(Var,0);
    FEVarRootSetLen(Var,0);
    return Var;
}

void *FEVarFiloNew_Key(INT32 Max,const char *Key)
{
    void *Var;
    if ( NULL==(Var=FEVarFiloNew(Max)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarFiloFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void *FEVarFiloNew2(INT32 Max)
{
    void *Var;
    if ( NULL==(Var=FEVarFiloNew(Max)) )
    {
        return NULL;
    }
    if ( 0>=Max )
    {
        return Var;
    }
    if ( !FEVarFiloRealloc(Var,FEVarFiloGetMax(Var)) )
    {
        FEVarFiloFree(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarFiloNew2_Key(INT32 Max,const char *Key)
{
    void *Var;
    if ( NULL==(Var=FEVarFiloNew2(Max)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarFiloFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void  FEVarFiloFree(void *Var)
{
    FEVarFiloVFree(Var);
    FEVarFiloNFree(Var);
}

void  FEVarFiloNFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarFiloVFree(void *Var)
{
    void *V;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FILO) )
    {
        return;
    }
    while( 0<FEVarRootGetLen(Var) )
    {
        V = NULL;
        if ( FEVarFiloPop(Var,&V) )
        {
            FEVarFree(V);
        }
    }
    free(FEVarRootGetValue(Var));
    FEVarRootSetSize(Var,0);
    FEVarRootSetValue(Var,NULL);
}

void  FEVarFiloShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FILO) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarFiloNShow1(Var,T,Buf);
    FEVarFiloVShow(Var,T,Buf);
    FEVarTypeNShow2(Var,T,Buf);
}

void  FEVarFiloVShow(void *Var,INT32 T,void *Buf)
{
    INT32 Len;
    INT32 i;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FILO) )
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
        FEVarShow(FEVarFiloGet(Var,i),T+1,Buf);
    }
}

BOOL  FEVarFiloIsEmpty(void *Var)
{
    return FEVarRootIsEmpty(Var);
}
 
BOOL  FEVarFiloIsFull(void *Var)
{
    return FEVarRootIsFull(Var);
}
 
BOOL  FEVarFiloRealloc(void *Var,INT32 S)
{
    INT32 Size;
    INT32 S1;
    INT32 i;
    void *V;
    if ( (!FEVarRootIsAdd(Var))||(!FEVarRootCanAdd(Var)) )
    {
        return FALSE;
    }
    S1 = FECAL_MAX(S,FEVARFILO_UNIT_MIN);
    Size = FEVarRootGetSize(Var);
    if ( S1+Size>=FEVarRootGetMax(Var)+FEVARFILO_UNIT_MIN )
    {
        return FALSE;
    }
    if ( (0==Size)||(NULL==FEVarRootGetValue(Var)) )
    {
        if ( NULL==(V=malloc(FEVARP4_ST_SIZE*(Size+S1))) )
        {
            return FALSE;
        }
    }
    else
    {
        if ( NULL==(V=realloc(FEVarRootGetValue(Var) \
            ,FEVARP4_ST_SIZE*(Size+S1))) )
        {
            return FALSE;
        }
    }
    i = Size;
    Size += S1;
    for ( ;i<Size;i++ )
    {
        FEVarFiloInitPointer(((tFEVarPointer4*)V)+i);
    }
    FEVarRootSetValue(Var,V);
    FEVarRootSetSize(Var,Size);
    return TRUE;
}

void  FEVarFiloInitPointer(void *Var)
{
   FEVarPointer4Init(Var,FEVARFILO_NODE_P_NUM);
   FEVarPointer4SetFlag(Var,0);
}

BOOL  FEVarFiloSetMax(void *Var,INT32 Max)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FILO) )
    {
        return FALSE;
    }
    if ( FEVarFiloGetLen(Var)>Max )
    {
        return FALSE;
    }
    FEVarRootSetMax(Var,Max);
    return TRUE;
}

INT32 FEVarFiloGetMax(void *Var)
{
    return FEVarRootGetMax(Var);
}

INT32 FEVarFiloGetLen(void *Var)
{
    return FEVarRootGetLen(Var);
}

BOOL  FEVarFiloIsIdxOfValue(void *Var,INT32 Idx)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FILO) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL( (0<=Idx)&&(FEVarFiloGetLen(Var)>Idx) );
}

BOOL  FEVarFiloIsIdxOfRange(void *Var,INT32 Idx)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FILO) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL( (0<=Idx)&&(FEVarFiloGetMax(Var)>Idx) );
}

void *FEVarFiloGetNode(void *Var,INT32 Idx)
{
    INT32 Size;
    void *V;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FILO) )
    {
        return NULL;
    }
    if ( !FEVarFiloIsIdxOfRange(Var,Idx) )
    {
        return NULL;
    }
    Size = FEVarRootGetSize(Var);
    if ( Idx>=Size )
    {
        if ( !FEVarFiloRealloc(Var,Idx-Size) )
        {
            return NULL;
        }
    }
    V = FEVarRootGetValue(Var);
    V = ((tFEVarPointer4*)V)+Idx;
    return V;
}

BOOL  FEVarFiloPush(void *Var,void *V)
{
    void *Node;
    if ( NULL==(Node=FEVarFiloGetNode(Var,FEVarRootGetLen(Var))) )
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

BOOL  FEVarFiloPop(void *Var,void **V)
{
    void *Node;
    if ( NULL==V )
    {
        return FALSE;
    }
    if ( FEVarRootIsEmpty(Var) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarFiloGetNode(Var,FEVarRootGetLen(Var)-1)) )
    {
        return FALSE;
    }
    if ( FEVARTYPEVALUE_ISNOT(Node) )
    {
        return FALSE;
    }
    *V = FEVarPointer4GetP0(Node);
    FEVarRootAddLen(Var,FALSE);
    FEVarFiloInitPointer(Node);
    return TRUE;
}

void *FEVarFiloGet(void *Var,INT32 Idx)
{
    void *Node;
    if ( NULL==(Node=FEVarFiloGetNode(Var,Idx)) )
    {
        return NULL;
    }
    return FEVarPointer4GetP0(Node);
}

BOOL  FEVarFiloGet2(void *Var,INT32 Idx,void **V)
{
    void *Node;
    if ( NULL==V )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarFiloGetNode(Var,Idx)) )
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

BOOL  FEVarFiloReplace(void *Var,INT32 Idx,void *V)
{
    void *Node;
    if ( !FEVarFiloIsIdxOfValue(Var,Idx) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarFiloGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  FEVarFiloReplaceValue(void *Var,INT32 Idx,void *V)
{
    void *Node;
    void *OV;
    if ( !FEVarFiloIsIdxOfValue(Var,Idx) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarFiloGetNode(Var,Idx)) )
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

void *FEVarFiloClone(void *Var)
{
    void *N;

    if ( FEVARTYPE_MEM_VT_FILO!=FEVarTypeVTGet(Var) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarFiloNew(FEVarFiloGetMax(Var))) )
    {
        return NULL;
    }
    if ( !FEVarFiloCloneValue(N,Var) )
    {
        FEVarFiloFree(N);
        N = NULL;
    }
    if ( !FEVarTypeClone(N,Var) )
    {
        FEVarFiloFree(N);
        N = NULL;
    }
    return N;
}

BOOL  FEVarFiloCloneValue(void *N,void *Var)
{
    INT32 i;
    INT32 S;
    INT32 L;
    void *V;
    BOOL bRtn;

    if ( !FEVarTypeIsInit2(N,FEVARTYPE_MEM_VT_FILO) )
    {
        return FALSE;
    }
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FILO) )
    {
        return TRUE;
    }
    if ( NULL==(N=FEVarFiloNew(FEVarFiloGetMax(Var))) )
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
        if ( !FEVarFiloRealloc(N,S) )
        {
            bRtn = FALSE;
            break;
        }
        for ( i=0;i<L;i++ )
        {
            if ( NULL==(V=FEVarClone(FEVarFiloGet(Var,i))) )
            {
                bRtn = FALSE;
                break;
            }
            if ( !FEVarFiloPush(N,V) )
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

