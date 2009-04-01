/***************************************************************************/
/**[File Name    ]varpointer.c                                            **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for varpointer[1..4]                        **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

void *FEVarPointer4New(INT32 Num)
{
    void *Var;
    tFEVarPointer4 *v;
    if ( NULL==(Var=malloc(FEVARP4_ST_SIZE)) )
    {
        return NULL;
    }
    v = (tFEVarPointer4*)Var;
    memset(Var,0,FEVARP4_ST_SIZE);
    FEVarPointer4Init(Var,Num);
    return Var;
}

void FEVarPointer4Free(void *Var)
{   
    FEVarPointer4VFree(Var);
    FEVarPointer4NFree(Var);
}

void  FEVarPointer4NFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarPointer4VFree(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return;
    }
    if ( FEVarPointer4IsFlag(Var,3) )
    {
        FEVarFree(FEVarPointer4GetP3(Var));
    }
    if ( FEVarPointer4IsFlag(Var,2) )
    {
        FEVarFree(FEVarPointer4GetP2(Var));
    }
    if ( FEVarPointer4IsFlag(Var,1) )
    {
        FEVarFree(FEVarPointer4GetP1(Var));
    }
    if ( FEVarPointer4IsFlag(Var,0) )
    {
        FEVarFree(FEVarPointer4GetP0(Var));
    }
    FEVarPointer4Init(Var,FEVarTypeIsInit(Var));
}

BOOL  FEVarPointer4Init(void *Var,INT32 Num)
{
    if ( NULL==Var )
    {
        return FALSE;
    }
    FEVarTypeInit(Var);
    FEVarTypeVVSetNot(Var);
    switch( Num )
    {
        case 1:
            FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_P1);
            break;
        case 2:
            FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_P2);
            break;
        case 3:
            FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_P3);
            break;
        case 4:
        default:
            FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_P4);
            break;
    }
    FEVARP4_MEM_V(Var,0) = NULL;
    FEVARP4_MEM_V(Var,1) = NULL;
    FEVARP4_MEM_V(Var,2) = NULL;
    FEVARP4_MEM_V(Var,3) = NULL;
    return TRUE;
}

void  FEVarPointer4Show(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarPointer4NShow1(Var,T,Buf);
    FEVarPointer4VShow(Var,T,Buf);
    FEVarPointer4NShow2(Var,T,Buf);
}

void  FEVarPointer4VShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    switch( FEVarTypeVTGet(Var) )
    {
        case FEVARTYPE_MEM_VT_P4:
            FEVarShow(FEVarPointer4GetP3(Var),T+1,Buf);
        case FEVARTYPE_MEM_VT_P3:
            FEVarShow(FEVarPointer4GetP2(Var),T+1,Buf);
        case FEVARTYPE_MEM_VT_P2:
            FEVarShow(FEVarPointer4GetP1(Var),T+1,Buf);
        case FEVARTYPE_MEM_VT_P1:
            FEVarShow(FEVarPointer4GetP0(Var),T+1,Buf);
            break;
        default:
            break;
    }
}
 
BOOL  FEVarPointer4IsFlag(void *Var,INT32 IDX)
{
#if 0
    INT32 Idx;
    UCHAR T;
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    if ( !FEVARP4_IDX_IS(IDX) )
    {
        return TRUE;
    }
    Idx = IDX/8;
    T = 0x01 << (IDX%8);
    return FERTN_CMPBOOL(0!=((FEVARP4_MEM_A(Var)[Idx]) & T));
#else
    return FECharIsSetBit((FEVARP4_MEM_A(Var))[IDX/8],IDX%8);
#endif
}

BOOL  FEVarPointer4SetFlag(void *Var,INT32 IDX)
{
#if 0
    INT32 Idx;
    UCHAR T;
    if ( !FEVarTypeIsInit(Var) || !FEVARP4_IDX_IS(IDX) )
    {
        return FALSE;
    }
    Idx = IDX/8;
    T = 0x01 << (IDX%8);
    FEVARP4_MEM_A(Var)[Idx] = ((FEVARP4_MEM_A(Var)[Idx]) | T);
    return TRUE;
#else
    if ( !FEVarTypeIsInit(Var) || !FEVARP4_IDX_IS(IDX) )
    {
        return FALSE;
    }
    return FECharSetBit(&(FEVARP4_MEM_A(Var)[IDX/8]),(IDX%8),TRUE);
#endif
}

BOOL  FEVarPointer4ClearFlag(void *Var,INT32 IDX)
{
#if 0
    INT32 Idx;
    UCHAR T;
    if ( !FEVarTypeIsInit(Var) || !FEVARP4_IDX_IS(IDX) )
    {
        return FALSE;
    }
    Idx = IDX/8;
    T = 0x01 << (IDX%8);
    T = T ^ 0xFF;
    FEVARP4_MEM_A(Var)[Idx] = ((FEVARP4_MEM_A(Var)[Idx]) & T);
    return TRUE;
#else
    if ( !FEVarTypeIsInit(Var) || !FEVARP4_IDX_IS(IDX) )
    {
        return FALSE;
    }
    return FECharSetBit(&(FEVARP4_MEM_A(Var)[IDX/8]),(IDX%8),FALSE);
#endif
}

BOOL  FEVarPointer4SetP(void *Var,INT32 IDX,void *Value)
{
    if ( !FEVarTypeIsInit(Var) || !FEVARP4_IDX_IS(IDX) )
    {
        return FALSE;
    }
    if ( FEVarPointer4IsFlag(Var,IDX) )
    {
        FEVarFree(FEVarPointer4GetP(Var,IDX));
        FEVARP4_MEM_V(Var,IDX) = NULL;
    }
    FEVARP4_MEM_V(Var,IDX) = Value;
    if ( (NULL==FEVARP4_MEM_V(Var,0)) \
        &&(NULL==FEVARP4_MEM_V(Var,1)) \
        &&(NULL==FEVARP4_MEM_V(Var,2)) \
        &&(NULL==FEVARP4_MEM_V(Var,3)) )
    {
        FEVarTypeVVSetNot(Var);
    }
    else
    {
        FEVarTypeVVSetValue(Var);
    }
    return TRUE;
}

void *FEVarPointer4GetP(void *Var,INT32 IDX)
{
    if ( !FEVarTypeIsInit(Var) || !FEVARP4_IDX_IS(IDX) )
    {
        return NULL;
    }
    return FEVARP4_MEM_V(Var,IDX);
}

BOOL  FEVarPointer4SetP0(void *Var,void *Value)
{
    return FEVarPointer4SetP(Var,0,Value);
}

void *FEVarPointer4GetP0(void *Var)
{
    return FEVarPointer4GetP(Var,0);
}

BOOL  FEVarPointer4SetP1(void *Var,void *Value)
{
    return FEVarPointer4SetP(Var,1,Value);
}

void *FEVarPointer4GetP1(void *Var)
{
    return FEVarPointer4GetP(Var,1);
}

BOOL  FEVarPointer4SetP2(void *Var,void *Value)
{
    return FEVarPointer4SetP(Var,2,Value);
}

void *FEVarPointer4GetP2(void *Var)
{
    return FEVarPointer4GetP(Var,2);
}

BOOL  FEVarPointer4SetP3(void *Var,void *Value)
{
    return FEVarPointer4SetP(Var,3,Value);
}

void *FEVarPointer4GetP3(void *Var)
{
    return FEVarPointer4GetP(Var,3);
}

void *FEVarPointer4Clone(void *Var)
{
    INT32 i;
    BOOL Flag;
    void *N;
    void *V;
    if ( !FEVarTypeIsInit(Var) )
    {
        return NULL;
    }
    if ( !FEVARP4_TYPE_IS(FEVarTypeVTGet(Var)) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarPointer4New(FEVarTypeVTGet(Var))) )
    {
        return NULL;
    }
    Flag = TRUE;
    V = NULL;
    for ( i=0;i<4;i++ )
    {
        if ( FEVarPointer4IsFlag(Var,i) )
        {
            if ( NULL==(V=FEVarClone(FEVarPointer4GetP(Var,i))) )
            {
                Flag = FALSE;
                break;
            }
            if ( !FEVarPointer4SetP(N,i,V) )
            {
                Flag = FALSE;
                break;
            }
        }
    }
    if ( Flag )
    {
        if ( !FEVarTypeClone(N,Var) )
        {
            Flag = FALSE;
        }
    }
    if ( !Flag )
    {
        FEVarFree(V);
        V = NULL;
        FEVarPointer4Free(N);
        N = NULL;
    }
    return N;
}

#ifdef __cplusplus
}
#endif

