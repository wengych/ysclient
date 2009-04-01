/***************************************************************************/
/**[File Name    ]varlink.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for link                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif
/*
    Root
        ----Node
                ----P0(Value)
                ----P1(Child)
                ----P2(Parent)
*/

void *FEVarLinkNew(INT32 Max)
{
    void *Var;
    if ( NULL==(Var=FEVarRootNew()) )
    {
        return NULL;
    }
    FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_LINK);
    FEVarRootSetMax(Var,Max);
    FEVarRootSetSize(Var,0);
    FEVarRootSetLen(Var,0);
    return Var;
}

void *FEVarLinkNew_Key(INT32 Max,const char *Key)
{
    void *Var;
    if ( NULL==(Var=FEVarLinkNew(Max)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarLinkFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void  FEVarLinkFree(void *Var)
{
    FEVarLinkVFree(Var);
    FEVarLinkNFree(Var);
}

void  FEVarLinkNFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarLinkVFree(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return;
    }
    while( 0<FEVarLinkGetLen(Var) )
    {
        FEVarLinkDelete(Var,0);
    }
}

void  FEVarLinkShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarLinkNShow1(Var,T,Buf);
    FEVarLinkVShow(Var,T,Buf);
    FEVarTypeNShow2(Var,T,Buf);
}

void  FEVarLinkVShow(void *Var,INT32 T,void *Buf)
{
    void *Node;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    Node = FEVarRootGetValue(Var);
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

BOOL  FEVarLinkIsEmpty(void *Var)
{
    return FEVarRootIsEmpty(Var);
}
 
BOOL  FEVarLinkIsFull(void *Var)
{
    return FEVarRootIsFull(Var);
}
 

void  FEVarLinkInitPointer(void *Var)
{
    FEVarPointer4SetFlag(Var,0);
}

BOOL  FEVarLinkSetMax(void *Var,INT32 Max)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return FALSE;
    }
    if ( FEVarLinkGetLen(Var)>Max )
    {
        return FALSE;
    }
    FEVarRootSetMax(Var,Max);
    return TRUE;
}

INT32 FEVarLinkGetMax(void *Var)
{
    return FEVarRootGetMax(Var);
}

INT32 FEVarLinkGetLen(void *Var)
{
    return FEVarRootGetLen(Var);
}

BOOL  FEVarLinkIsIdxOfValue(void *Var,INT32 Idx)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL( (0<=Idx)&&(FEVarLinkGetLen(Var)>Idx) );
}

BOOL  FEVarLinkIsIdxOfRange(void *Var,INT32 Idx)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL( (0<=Idx)&&(FEVarLinkGetMax(Var)>Idx) );
}

void *FEVarLinkGetNode(void *Var,INT32 Idx)
{
    INT32 Num;
    void *V;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return NULL;
    }
    if ( !FEVarLinkIsIdxOfRange(Var,Idx) )
    {
        return NULL;
    }
    if ( Idx>=FEVarRootGetLen(Var) )
    {
        return NULL;
    }
    Num = 0;
    V = FEVarRootGetValue(Var);
    while( Num<Idx )
    {
        V = FEVarPointer4GetP1(V);
        Num ++;
    }
    return V;
}

void *FEVarLinkGet(void *Var,INT32 Idx)
{
    void *Node;
    if ( NULL==(Node=FEVarLinkGetNode(Var,Idx)) )
    {
        return NULL;
    }
    return FEVarPointer4GetP0(Node);
}

BOOL  FEVarLinkGet2(void *Var,INT32 Idx,void **V)
{
    void *Node;
    if ( NULL==V )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarLinkGetNode(Var,Idx)) )
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

BOOL  FEVarLinkAdd(void *Var,void *V)
{
    void *Node;
    void *RV;
    BOOL bRtn;
    INT32 Len;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return FALSE;
    }
    Len = FEVarLinkGetLen(Var);
    if ( !FEVarLinkIsIdxOfRange(Var,Len) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarPointer4New(FEVARLINK_NODE_P_NUM)) )
    {
        return FALSE;
    }
    FEVarLinkInitPointer(Node);
    bRtn = FALSE;
    while( 1 )
    {
        if ( !FEVarPointer4SetP0(Node,V) )
        {
            break;
        }
        if ( !FEVarPointer4SetP1(Node,NULL) )
        {
            break;
        }
        if ( !FEVarPointer4SetP2(Node,NULL) )
        {
            break;
        }
        if ( 0==FEVarLinkGetLen(Var) )
        {
            FEVarRootSetValue(Var,Node);
        }
        else if ( NULL==(RV=FEVarLinkGetNode(Var,FEVarLinkGetLen(Var)-1)) )
        {
            break;
        }
        else
        {
            FEVarPointer4SetP1(RV,Node);
            FEVarPointer4SetP2(Node,RV);
        }
        FEVarRootAddLen(Var,TRUE);
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        FEVarPointer4Free(Node);
    }
    return bRtn;
}

BOOL  FEVarLinkInsert(void *Var,INT32 Idx,void *V)
{
    void *Node;
    void *RV;
    BOOL bRtn;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return FALSE;
    }
    if ( !FEVarLinkIsIdxOfRange(Var,FEVarLinkGetLen(Var)) )
    {
        return FALSE;
    }
    if ( FEVarLinkIsEmpty(Var) )
    {
        if ( 0<Idx )
        {
            return FALSE;
        }
    }
    else
    {
        if ( !FEVarLinkIsIdxOfValue(Var,Idx) )
        {
            return FALSE;
        }
    }
    if ( NULL==(RV=FEVarLinkGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarPointer4New(FEVARLINK_NODE_P_NUM)) )
    {
        return FALSE;
    }
    FEVarLinkInitPointer(Node);
    bRtn = FALSE;
    while( 1 )
    {
        if ( !FEVarPointer4SetP0(Node,V) )
        {
            break;
        }
        if ( !FEVarPointer4SetP1(Node,NULL) )
        {
            break;
        }
        if ( !FEVarPointer4SetP2(Node,NULL) )
        {
            break;
        }
        if ( 0==Idx )
        {
            FEVarRootSetValue(Var,Node);
        }
        FEVarPointer4SetP1(Node,RV);
        FEVarPointer4SetP2(Node,FEVarPointer4GetP2(RV));
        FEVarPointer4SetP2(RV,Node);
        FEVarRootAddLen(Var,TRUE);
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        FEVarPointer4Free(Node);
    }
    return bRtn;
}

BOOL  FEVarLinkReplace(void *Var,INT32 Idx,void *V)
{
    void *Node;
    if ( !FEVarLinkIsIdxOfValue(Var,Idx) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarLinkGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  FEVarLinkReplaceValue(void *Var,INT32 Idx,void *V)
{
    void *Node;
    void *OV;
    if ( !FEVarLinkIsIdxOfValue(Var,Idx) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarLinkGetNode(Var,Idx)) )
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

BOOL  FEVarLinkDelete(void *Var,INT32 Idx)
{
    void *Node;
    if ( NULL==(Node=FEVarLinkGetNode(Var,Idx)) )
    {
        return FALSE;
    }
    return FEVarLinkDeleteNode(Var,Node);
}

BOOL  FEVarLinkDeleteNode(void *Var,void *Node)
{
    void *NP;
    void *NC;
    if ( FEVARTYPEVALUE_ISNOT(Node) )
    {
        return FALSE;
    }
    NP = FEVarPointer4GetP2(Node);
    NC = FEVarPointer4GetP1(Node);
    if ( NULL==NP )
    {
        if ( !FEVarRootSetValue(Var,NC) )
        {
            return FALSE;
        }
    }
    if ( NULL!=NP )
    {
        if ( !FEVarPointer4SetP1(NP,NC) )
        {
            return FALSE;
        }
    }
    if ( NULL!=NC )
    {
        if ( !FEVarPointer4SetP2(NC,NP) )
        {
            return FALSE;
        }
    }
    FEVarPointer4SetP1(Node,NULL);
    FEVarPointer4SetP2(Node,NULL);
    FEVarPointer4Free(Node);
    FEVarRootAddLen(Var,FALSE);
    return TRUE;
}

INT32 FEVarLinkGetIdxByKey(void *Var,const void *Key,INT32 Len)
{
    void *V;
    INT32 Idx;
    INT32 L;
    BOOL  Flag;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return FERTN_ER;
    }
    L = FEVarLinkGetLen(Var);
    Flag = FALSE;
    for ( Idx=0;Idx<L;Idx++ )
    {
        if ( NULL==(V=FEVarLinkGet(Var,Idx)) )
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
    return (Flag)?Idx:FERTN_ER;
}

void *FEVarLinkGetNodeByKey(void *Var,const void *Key,INT32 Len)
{
    void *Node;
    INT32 Idx;
    INT32 L;
    BOOL  Flag;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return NULL;
    }
    L = FEVarLinkGetLen(Var);
    Node = FEVarRootGetValue(Var);
    Flag = FALSE;
    for ( Idx=0;Idx<L;Idx++ )
    {
        if ( NULL==Node )
        {
            break;
        }
        if ( 0<Idx )
        {
            if ( NULL==(Node=FEVarPointer4GetP1(Node)) )
            {
                break;
            }
        }
        if ( FEVARTYPEVALUE_ISNOT(Node) )
        {
            continue;
        }
        if ( FEVarTypeKeyCmp(FEVarPointer4GetP0(Node),Key,Len) )
        {
            Flag = TRUE;
            break;
        }
    }
    return (Flag)?Node:NULL;
}

void *FEVarLinkGetByKey(void *Var,const void *Key,INT32 Len)
{
    void *Node;
    if ( NULL==(Node=FEVarLinkGetNodeByKey(Var,Key,Len)) )
    {
        return NULL;
    }
    return FEVarPointer4GetP0(Node);
}

BOOL  FEVarLinkGet2ByKey(void *Var,const void *Key,INT32 Len,void **V)
{
    void *Node;
    if ( NULL==V )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarLinkGetNodeByKey(Var,Key,Len)) )
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

BOOL  FEVarLinkInsertByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    void *Node;
    void *RV;
    BOOL bRtn;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return FALSE;
    }
    if ( !FEVarLinkIsIdxOfRange(Var,FEVarLinkGetLen(Var)) )
    {
        return FALSE;
    }
    if ( NULL==(RV=FEVarLinkGetNodeByKey(Var,Key,Len)) )
    {
        return FALSE;
    }
    if ( NULL==(Node=FEVarPointer4New(FEVARLINK_NODE_P_NUM)) )
    {
        return FALSE;
    }
    FEVarLinkInitPointer(Node);
    bRtn = FALSE;
    while( 1 )
    {
        if ( !FEVarPointer4SetP0(Node,V) )
        {
            break;
        }
        if ( !FEVarPointer4SetP1(Node,NULL) )
        {
            break;
        }
        if ( !FEVarPointer4SetP2(Node,NULL) )
        {
            break;
        }
        if ( NULL==FEVarPointer4GetP2(RV) )
        {
            FEVarRootSetValue(Var,Node);
        }
        FEVarPointer4SetP1(Node,RV);
        FEVarPointer4SetP2(Node,FEVarPointer4GetP2(RV));
        FEVarPointer4SetP2(RV,Node);
        FEVarRootAddLen(Var,TRUE);
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        FEVarPointer4Free(Node);
    }
    return bRtn;
}

BOOL  FEVarLinkReplaceByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    void *Node;
    if ( NULL==(Node=FEVarLinkGetNodeByKey(Var,Key,Len)) )
    {
        return FALSE;
    }
    if ( !FEVarPointer4SetP0(Node,V) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL  FEVarLinkReplaceValueByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    void *Node;
    void *OV;
    if ( NULL==(Node=FEVarLinkGetNodeByKey(Var,Key,Len)) )
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

BOOL  FEVarLinkDeleteByKey(void *Var,const void *Key,INT32 Len)
{
    void *Node;
    if ( NULL==(Node=FEVarLinkGetNodeByKey(Var,Key,Len)) )
    {
        return FALSE;
    }
    return FEVarLinkDeleteNode(Var,Node);
}

void *FEVarLinkClone(void *Var)
{
    void *N;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarLinkNew(FEVarLinkGetMax(Var))) )
    {
        return NULL;
    }
    if ( !FEVarLinkCloneValue(N,Var) )
    {
        FEVarLinkFree(N);
        N = NULL;
    }
    if ( !FEVarTypeClone(N,Var) )
    {
        FEVarLinkFree(N);
        N = NULL;
    }
    return N;
}

BOOL  FEVarLinkCloneValue(void *N,void *Var)
{
    INT32 i;
    INT32 L;
    void *V;
    BOOL bRtn;

    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_LINK) )
    {
        return FALSE;
    }
    if ( !FEVarTypeIsInit2(N,FEVARTYPE_MEM_VT_LINK) )
    {
        return FALSE;
    }
    bRtn = TRUE;
    V = NULL;
    while( 1 )
    {
        if ( !FEVarTypeClone(N,Var) )
        {
            bRtn = FALSE;
            break;
        }
        L = FEVarRootGetLen(Var);
        for ( i=0;i<L;i++ )
        {
            if ( NULL==(V=FEVarClone(FEVarLinkGet(Var,i))) )
            {
                bRtn = FALSE;
                break;
            }
            if ( !FEVarLinkAdd(N,V) )
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

