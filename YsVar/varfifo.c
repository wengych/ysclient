/***************************************************************************/
/**[File Name    ]varfifo.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for fifo                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

void *FEVarFifoNew(INT32 Max)
{
    void *Var;
    if ( NULL==(Var=FEVarRootNew()) )
    {
        return NULL;
    }
    FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_FIFO);
    FEVarRootSetMax(Var,Max);
    FEVarRootSetSize(Var,0);
    FEVarRootSetLen(Var,0);
    FEVarRootSetPushIdx(Var,0);
    FEVarRootSetPopIdx(Var,0);
    return Var;
}

void *FEVarFifoNew_Key(INT32 Max,const char *Key)
{
    void *Var;
    if ( NULL==(Var=FEVarFifoNew(Max)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarFifoFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void *FEVarFifoNew2(INT32 Max)
{
    void *Var;
    if ( NULL==(Var=FEVarFifoNew(Max)) )
    {
        return NULL;
    }
    if ( 0>=Max )
    {
        return Var;
    }
    if ( !FEVarFifoRealloc(Var,FEVarFifoGetMax(Var)) )
    {
        FEVarFifoFree(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarFifoNew2_Key(INT32 Max,const char *Key)
{
    void *Var;
    if ( NULL==(Var=FEVarFifoNew2(Max)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarFifoFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void  FEVarFifoFree(void *Var)
{
    FEVarFifoVFree(Var);
    FEVarFifoNFree(Var);
}

void  FEVarFifoNFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarFifoVFree(void *Var)
{
    void *V;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return;
    }
    while( 0<FEVarRootGetLen(Var) )
    {
        V = NULL;
        if ( FEVarFifoPop(Var,&V) )
        {
            FEVarFree(V);
        }
    }
    free(FEVarRootGetValue(Var));
    FEVarRootSetSize(Var,0);
    FEVarRootSetValue(Var,NULL);
}

void  FEVarFifoShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarFifoNShow1(Var,T,Buf);
    FEVarFifoVShow(Var,T,Buf);
    FEVarTypeNShow2(Var,T,Buf);
}

void  FEVarFifoVShow(void *Var,INT32 T,void *Buf)
{
    INT32 Len;
    INT32 i;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
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
        FEVarShow(FEVarFifoGet(Var,i),T+1,Buf);
    }
}

BOOL  FEVarFifoIsEmpty(void *Var)
{
    return FEVarRootIsEmpty(Var);
}
 
BOOL  FEVarFifoIsFull(void *Var)
{
    return FEVarRootIsFull(Var);
}
 
BOOL  FEVarFifoRealloc(void *Var,INT32 S)
{
    INT32 PushIdx;
    INT32 PopIdx;
    INT32 Size;
    INT32 S1;
    INT32 i;
    void *V;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return FALSE;
    }
    S1 = FECAL_MAX(S,1);

    /* Move Left */
    PushIdx = FEVarRootGetPushIdx(Var);
    Size = FEVarRootGetSize(Var);
    if ( PushIdx+S1<Size )
    {
        return TRUE;
    }

    S1 = FECAL_MAX(S,FEVARFIFO_UNIT_MIN);
    PopIdx = FEVarRootGetPopIdx(Var);
    if ( S1<=PopIdx )
    {
        if ( !FEVarFifoMove(Var) )
        {
            return FALSE;
        }
        PopIdx = FEVarRootGetPopIdx(Var);
        PushIdx = FEVarRootGetPushIdx(Var);
        return TRUE;
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
        FEVarFifoInitPointer(((tFEVarPointer4*)V)+i);
    }
    FEVarRootSetValue(Var,V);
    FEVarRootSetSize(Var,Size);
    return TRUE;
}

void  FEVarFifoInitPointer(void *Var)
{
   FEVarPointer4Init(Var,FEVARFIFO_NODE_P_NUM);
   FEVarPointer4SetFlag(Var,0);
}

BOOL  FEVarFifoSetMax(void *Var,INT32 Max)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return FALSE;
    }
    if ( FEVarFifoGetLen(Var)>Max )
    {
        return FALSE;
    }
    FEVarRootSetMax(Var,Max);
    return TRUE;
}

INT32 FEVarFifoGetMax(void *Var)
{
    return FEVarRootGetMax(Var);
}

INT32 FEVarFifoGetLen(void *Var)
{
    return FEVarRootGetLen(Var);
}

BOOL  FEVarFifoIsIdxOfValue(void *Var,INT32 Idx)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return FALSE;
    }
    if ( 0==FEVarFifoGetLen(Var) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL( (FEVarRootGetPushIdx(Var)>Idx) \
        && (FEVarRootGetPopIdx(Var)<=Idx) );
}

BOOL  FEVarFifoIsIdxOfRange(void *Var,INT32 Idx)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL( (0<=Idx)&&(FEVarFifoGetMax(Var)>Idx) );
}

void *FEVarFifoGetNode(void *Var,INT32 Idx)
{
    INT32 Size;
    void *V;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return NULL;
    }
    if ( !FEVarFifoIsIdxOfRange(Var,Idx) )
    {
        return NULL;
    }
    Size = FEVarRootGetSize(Var);
    if ( Idx>=Size )
    {
        if ( !FEVarFifoRealloc(Var,Idx-Size) )
        {
            return NULL;
        }
    }
    V = FEVarRootGetValue(Var);
    V = ((tFEVarPointer4*)V)+Idx;
    return V;
}

BOOL  FEVarFifoPush(void *Var,void *V)
{
    void *Node;
    INT32 PopIdx;
    INT32 PushIdx;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return FALSE;
    }
    PopIdx = FEVarRootGetPopIdx(Var);
    PushIdx = FEVarRootGetPushIdx(Var);
    if ( FEVarRootGetMax(Var)<=PushIdx )
    {
        if ( !FEVarFifoMove(Var) )
        {
            return FALSE;
        }
        PopIdx = FEVarRootGetPopIdx(Var);
        PushIdx = FEVarRootGetPushIdx(Var);
    }
    if ( NULL==(Node=FEVarFifoGetNode(Var,PushIdx)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    FEVarRootAddLen(Var,TRUE);
    FEVarRootSetPushIdx(Var,FEVarRootGetPushIdx(Var)+1);
    return TRUE;
}

BOOL  FEVarFifoPop(void *Var,void **V)
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
    if ( NULL==(Node=FEVarFifoGetNode(Var,FEVarRootGetPopIdx(Var))) )
    {
        return FALSE;
    }
    if ( FEVARTYPEVALUE_ISNOT(Node) )
    {
        return FALSE;
    }
    *V = FEVarPointer4GetP0(Node);
    FEVarRootAddLen(Var,FALSE);
    FEVarRootSetPopIdx(Var,FEVarRootGetPopIdx(Var)+1);
    FEVarFifoInitPointer(Node);
    return TRUE;
}

void *FEVarFifoGet(void *Var,INT32 Idx)
{
    void *Node;
    if ( NULL==(Node=FEVarFifoGetNode(Var,FEVarRootGetPopIdx(Var)+Idx)) )
    {
        return NULL;
    }
    return FEVarPointer4GetP0(Node);
}

BOOL  FEVarFifoGet2(void *Var,INT32 Idx,void **V)
{
    void *Node;
    if ( NULL==V )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarFifoGetNode(Var,FEVarRootGetPopIdx(Var)+Idx)) )
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

BOOL  FEVarFifoReplace(void *Var,INT32 Idx,void *V)
{
    void *Node;
    if ( !FEVarFifoIsIdxOfValue(Var,Idx) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarFifoGetNode(Var,FEVarRootGetPopIdx(Var)+Idx)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  FEVarFifoReplaceValue(void *Var,INT32 Idx,void *V)
{
    void *Node;
    void *OV;
    if ( !FEVarFifoIsIdxOfValue(Var,Idx) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarFifoGetNode(Var,FEVarRootGetPopIdx(Var)+Idx)) )
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

BOOL  FEVarFifoMove(void *Var)
{
    INT32 i;
    INT32 j;
    void *V;
    INT32 PopIdx;
    INT32 PushIdx;
    INT32 Len;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return FALSE;
    }
    Len = FEVarRootGetLen(Var);
    if ( 0==Len )
    {
        FEVarRootSetPopIdx(Var,0);
        FEVarRootSetPushIdx(Var,0);
        return TRUE;
    }
    if ( FEVarRootGetMax(Var)==Len )
    {
        return FALSE;
    }
    PopIdx = FEVarRootGetPopIdx(Var);
    PushIdx = FEVarRootGetPushIdx(Var);
    V = FEVarRootGetValue(Var);
    for ( i=PopIdx,j=0;i<PushIdx;i++,j++ )
    {
        memcpy(((char *)V)+j*FEVARP4_ST_SIZE \
            ,((char *)V)+i*FEVARP4_ST_SIZE \
            ,FEVARP4_ST_SIZE);
    }
    for ( ;j<PushIdx;j++ )
    {
        FEVarFifoInitPointer(((tFEVarPointer4*)V)+j);
    }
    FEVarRootSetPopIdx(Var,0);
    FEVarRootSetPushIdx(Var,PushIdx-PopIdx);
    return TRUE;
}

void *FEVarFifoClone(void *Var)
{
    void *N;
    if ( FEVARTYPE_MEM_VT_FIFO!=FEVarTypeVTGet(Var) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarFifoNew(FEVarFifoGetMax(Var))) )
    {
        return NULL;
    }
    if ( !FEVarFifoCloneValue(N,Var) )
    {
        FEVarFifoFree(N);
        N = NULL;
    }
    if ( !FEVarTypeClone(N,Var) )
    {
        FEVarFifoFree(N);
        N = NULL;
    }
    return N;
}

BOOL  FEVarFifoCloneValue(void *N,void *Var)
{
    INT32 i;
    INT32 S;
    INT32 L;
    void *V;
    BOOL bRtn;

    if ( !FEVarTypeIsInit2(N,FEVARTYPE_MEM_VT_FIFO) )
    {
        return FALSE;
    }
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_FIFO) )
    {
        return TRUE;
    }
    bRtn = TRUE;
    V = NULL;
    while( 1 )
    {
        S = FEVarRootGetSize(Var);
        L = FEVarRootGetLen(Var);
        S = FECAL_MAX(S,L);
        if ( !FEVarFifoRealloc(N,S) )
        {
            bRtn = FALSE;
            break;
        }
        for ( i=0;i<L;i++ )
        {
            if ( NULL==(V=FEVarClone(FEVarFifoGet(Var,i))) )
            {
                bRtn = FALSE;
                break;
            }
            if ( !FEVarFifoPush(N,V) )
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

