/***************************************************************************/
/**[File Name    ]varobject.c                                             **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for var object                              **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tagFEVarObject
{
    FEVARTYPE_MEM;
    void    *V;
    void    *VClone;
    void    *VFree;
    void    *VShow;
    void    *VPack;
}tFEVarObject;
#define FEVAROBJECT_ST_SIZE             (sizeof(tFEVarObject))
#define FEVAROBJECT_MEM_V(v)            (((tFEVarObject*)(v))->V)
#define FEVAROBJECT_MEM_VCLONE(v)       (((tFEVarObject*)(v))->VClone)
#define FEVAROBJECT_MEM_VFREE(v)        (((tFEVarObject*)(v))->VFree)
#define FEVAROBJECT_MEM_VSHOW(v)        (((tFEVarObject*)(v))->VShow)
#define FEVAROBJECT_MEM_VPACK(v)        (((tFEVarObject*)(v))->VPack)

void *FEVarObjectNew()
{
    void *Var;
	tFEVarObject *t;
    if ( NULL==(Var=malloc(FEVAROBJECT_ST_SIZE)) )
    {
        return NULL;
    }
    t = (tFEVarObject *)Var;
    memset(Var,0,FEVAROBJECT_ST_SIZE);
    FEVarTypeInit(Var);
    FEVarObjectInit(Var);
    return Var;
}

void  FEVarObjectFree(void *Var)
{
    FEVarObjectVFree(Var);
    FEVarObjectNFree(Var);
}

void  FEVarObjectNFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarObjectVFree(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return;
    }
    if ( NULL!=FEVAROBJECT_MEM_VFREE(Var) )
    {
        ((funcarg1non)(FEVAROBJECT_MEM_VFREE(Var)))(FEVAROBJECT_MEM_V(Var));
    }
    else if ( NULL!=FEVAROBJECT_MEM_V(Var) )
    {
        FEVarFree(FEVAROBJECT_MEM_V(Var));
    }
    FEVarObjectInit(Var);
}

void  FEVarObjectShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarObjectNShow1(Var,T,Buf);
    FEVarObjectVShow(Var,T,Buf);
    FEVarObjectNShow2(Var,T,Buf);
}
 
void  FEVarObjectVShow(void *Var,INT32 T,void *Buf)
{
    char Log[BUFSIZE_128];
    char Tab[BUFSIZE_64];
    char *Tmp;
    INT32 L;
    INT32 P;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    if ( !FEVARTYPEVALUE_ISSET(Var) )
    {
        return;
    }
    memset(Tab,0,sizeof(Tab));
    FEVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    L = 0;
    memset(Log,0,sizeof(Log));
 
    sprintf(Log+L,"%s<Value>\n",Tab);
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);

    if ( NULL!=FEVAROBJECT_MEM_VSHOW(Var) )
    {
        ((funcarg3non)(FEVAROBJECT_MEM_VSHOW(Var))) \
            (FEVAROBJECT_MEM_V(Var),(void *)(T+1),Buf);
    }
    else if ( NULL!=FEVAROBJECT_MEM_V(Var) )
    {
        FEVarShow(FEVAROBJECT_MEM_V(Var),T+1,Buf);
    }
    P = FEVarStringGetLen(Buf);
    Tmp = (char *)FEVarStringGet(Buf);
    L = 0;
    memset(Log,0,sizeof(Log));
    if ( NULL!=Tmp )
    {
        if ( '\n'==Tmp[P-1] )
        {
            sprintf(Log+L,"%s</Value>\n",Tab);
            L += strlen(Log+L);
        }
    }
    if ( 0==L )
    {
        sprintf(Log+L,"\n%s</Value>\n",Tab);
        L += strlen(Log+L);
    }
    FEVarStringCat(Buf,Log,L);
}

BOOL  FEVarObjectInit(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_OBJECT);
    FEVAROBJECT_MEM_V(Var) = NULL;
    FEVAROBJECT_MEM_VCLONE(Var) = NULL;
    FEVAROBJECT_MEM_VFREE(Var) = NULL;
    FEVAROBJECT_MEM_VSHOW(Var) = NULL;
    FEVAROBJECT_MEM_VPACK(Var) = NULL;
    return TRUE;
}

void *FEVarObjectGet(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return NULL;
    }
    return FEVAROBJECT_MEM_V(Var);
}

BOOL  FEVarObjectGet2(void *Var,void **V)
{
    if ( (!FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT))||(NULL==V) )
    {
        return FALSE;
    }
    *V = FEVAROBJECT_MEM_V(Var);
    return TRUE;
}

void *FEVarObjectGetVClone(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return NULL;
    }
    return FEVAROBJECT_MEM_VCLONE(Var);
}

void *FEVarObjectGetVFree(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return NULL;
    }
    return FEVAROBJECT_MEM_VFREE(Var);
}

void *FEVarObjectGetVShow(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return NULL;
    }
    return FEVAROBJECT_MEM_VSHOW(Var);
}

void *FEVarObjectGetVPack(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return NULL;
    }
    return FEVAROBJECT_MEM_VPACK(Var);
}

BOOL  FEVarObjectSet(void *Var,void *V )
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return FALSE;
    }
    FEVAROBJECT_MEM_V(Var) = V;
    if ( NULL==V )
    {
        FEVarTypeVVSetNull(Var);
    }
    else
    {
        FEVarTypeVVSetValue(Var);
    }
    return TRUE;
}

BOOL  FEVarObjectSetFuncVClone(void *Var,void *VClone)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return FALSE;
    }
    FEVAROBJECT_MEM_VCLONE(Var) = VClone;
    return TRUE;
}

BOOL  FEVarObjectSetFuncVFree(void *Var,void *VFree)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return FALSE;
    }
    FEVAROBJECT_MEM_VFREE(Var) = VFree;
    return TRUE;
}

BOOL  FEVarObjectSetFuncVShow(void *Var,void *VShow)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return FALSE;
    }
    FEVAROBJECT_MEM_VSHOW(Var) = VShow;
    return TRUE;
}

BOOL  FEVarObjectSetFuncVPack(void *Var,void *VPack)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return FALSE;
    }
    FEVAROBJECT_MEM_VPACK(Var) = VPack;
    return TRUE;
}

void *FEVarObjectSave(void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    void *Var;
    if ( NULL==(Var=FEVarObjectNew()) )
    {
        return NULL;
    }
    FEVarObjectSet(Var,V);
    FEVAROBJECT_MEM_VCLONE(Var) = Clone;
    FEVAROBJECT_MEM_VFREE(Var) = Free;
    FEVAROBJECT_MEM_VSHOW(Var) = Show;
    FEVAROBJECT_MEM_VPACK(Var) = Pack;
    return Var;
}

void *FEVarObjectSave2(const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    void *Var;
    if ( NULL==Key )
    {
        return NULL;
    }
    if ( NULL==(Var=FEVarObjectSave(V,Clone,Free,Show,Pack)) )
    {
        return NULL;
    }
    if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
    {
        FEVarObjectFree(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarObjectClone(void *Var)
{
    void *N;
    void *V;
    BOOL Flag;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_OBJECT) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarObjectNew()) )
    {
        return NULL;
    }
    Flag = FALSE;
    if ( NULL!=FEVAROBJECT_MEM_VCLONE(Var) )
    {
        if ( NULL!=(V= \
        ((funcarg1vp)(FEVAROBJECT_MEM_VCLONE(Var)))(FEVarObjectGet(Var))) )
        {
            Flag = TRUE;
        }
    }
    else if ( NULL!=(V=FEVarClone(FEVarObjectGet(Var))) )
    {
        Flag = TRUE;
    }
    if ( Flag )
    {
        FEVarObjectSet(N,V);
        FEVAROBJECT_MEM_VCLONE(N) = FEVAROBJECT_MEM_VCLONE(Var);
        FEVAROBJECT_MEM_VFREE(N) = FEVAROBJECT_MEM_VFREE(Var);
        FEVAROBJECT_MEM_VSHOW(N) = FEVAROBJECT_MEM_VSHOW(Var);
        FEVAROBJECT_MEM_VPACK(N) = FEVAROBJECT_MEM_VPACK(Var);
        if ( !FEVarTypeClone(N,Var) )
        {
            FEVarObjectFree(N);
            N = NULL;
        }
    }
    else
    {
        FEVarObjectFree(N);
        N = NULL;
    }
    return N;
}

#ifdef __cplusplus
}
#endif

