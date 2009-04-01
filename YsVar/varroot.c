/***************************************************************************/
/**[File Name    ]varroot.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for varroot                                 **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tFEVarRoot
{
    FEVARTYPE_MEM;
    INT32       Max;
    INT32       Size;
    INT32       Len;    /* 0,No;1~Max */
    INT32       Push;   /* 0,No;1~Len */
    INT32       Pop;    /* 0,No;1~Len */
    void       *Value;
}tFEVarRoot;
#define FEVARROOT_ST_SIZE               (sizeof(tFEVarRoot))
#define FEVARROOT_MEM_MAX(v)            (((tFEVarRoot*)(v))->Max)
#define FEVARROOT_MEM_SIZE(v)           (((tFEVarRoot*)(v))->Size)
#define FEVARROOT_MEM_LEN(v)            (((tFEVarRoot*)(v))->Len)
#define FEVARROOT_MEM_PUSH(v)           (((tFEVarRoot*)(v))->Push)
#define FEVARROOT_MEM_POP(v)            (((tFEVarRoot*)(v))->Pop)
#define FEVARROOT_MEM_USERLEN(v)        (((tFEVarRoot*)(v))->Push)
#define FEVARROOT_MEM_USERCNT(v)        (((tFEVarRoot*)(v))->Pop)
#define FEVARROOT_MEM_VALUE(v)          (((tFEVarRoot*)(v))->Value)

void *FEVarRootNew()
{
    void *Var;
    tFEVarRoot *v;
    if ( NULL==(Var=malloc(FEVARROOT_ST_SIZE)) )
    {
        return NULL;
    }
    v = (tFEVarRoot *)Var;
    memset(Var,0,FEVARROOT_ST_SIZE);
    FEVarTypeInit(Var);
    FEVarTypeVVSetNot(Var);
    return Var;
}

void FEVarRootFree(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return;
    }
    FEVarVTCall(Var,FEVARTYPE_FREE_SUBFIX);
} 

void  FEVarRootShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return ;
    }
    FEVarVTCall(Var,FEVARTYPE_SHOW_SUBFIX);
}

void  FEVarRootNShow1(void *Var,INT32 T,void *Buf)
{
    char Log[BUFSIZE_512];
    char Tab[BUFSIZE_64];
    char *Type;
    INT32 L;

    memset(Tab,0,sizeof(Tab));
    FEVarToolsInitBufSpace(Tab,sizeof(Tab),T);
    Type = FEVarTypeInfoGetName(FEVarTypeVTGet(Var));

    L = 0;
    if ( FEVARTYPE_MEM_VT_ARRAY==FEVarTypeVVGet(Var) )
    {
        snprintf(Log+L,sizeof(Log)-L,"%s<Node Addr=\"%08X\" VV=\"%d\" VT=\"%d\" Type=\"%s\" "
                    "Max=\"%d\" Len=\"%d\" UserLen=\"%d\" UserCnt=\"%d\">\n" \
            ,Tab,(INT32)Var,FEVarTypeVVGet(Var),FEVarTypeVTGet(Var) \
            ,(NULL==Type)?"unknown":Type \
            ,FEVarRootGetMax(Var),FEVarRootGetLen(Var) \
            ,FEVarRootGetUserLen(Var),FEVarRootGetUserCnt(Var));
    }
    else
    {
        snprintf(Log+L,sizeof(Log)-L,"%s<Node Addr=\"%08X\" VV=\"%d\" VT=\"%d\" Type=\"%s\" "
                    "Max=\"%d\" Len=\"%d\">\n" \
            ,Tab,(INT32)Var,FEVarTypeVVGet(Var),FEVarTypeVTGet(Var) \
            ,(NULL==Type)?"unknown":Type \
            ,FEVarRootGetMax(Var),FEVarRootGetLen(Var));
    }
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);
    FEVarTypeResShow(Var,T,Buf);
    FEVarTypeKeyShow(Var,T,Buf);
}

BOOL  FEVarRootIsEmpty(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL(0>=FEVARROOT_MEM_LEN(Var));
}

BOOL  FEVarRootIsFull(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL(FEVARROOT_MEM_MAX(Var)<=FEVARROOT_MEM_LEN(Var));
}

BOOL  FEVarRootIsAdd(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL(FEVARROOT_MEM_LEN(Var)>=FEVARROOT_MEM_SIZE(Var));
}

BOOL  FEVarRootCanAdd(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL(FEVARROOT_MEM_MAX(Var)>FEVARROOT_MEM_SIZE(Var));
}

BOOL  FEVarRootSetMax(void *Var,INT32 Max)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    FEVARROOT_MEM_MAX(Var) = (0>=Max)?FEVARARRAY_UNIT_MAX:FECAL_MAX(0,Max);
    return TRUE;
}

INT32 FEVarRootGetMax(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FERTN_ERAPP_ARG;
    }
    return FEVARROOT_MEM_MAX(Var);
}

BOOL  FEVarRootSetSize(void *Var,INT32 Size)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    FEVARROOT_MEM_SIZE(Var) = FECAL_MAX(0,Size);
    return TRUE;
}

INT32 FEVarRootGetSize(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FERTN_ERAPP_ARG;
    }
    return FEVARROOT_MEM_SIZE(Var);
}

BOOL  FEVarRootSetLen(void *Var,INT32 Len)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    FEVARROOT_MEM_LEN(Var) = FECAL_MAX(0,Len);
    return TRUE;
}

BOOL  FEVarRootAddLen(void *Var,BOOL Flag)
{
    if ( Flag )
    {
        if ( FEVarRootIsFull(Var) )
        {
            return FALSE;
        }
        FEVARROOT_MEM_LEN(Var) ++;
    }
    else
    {
        if ( FEVarRootIsEmpty(Var) )
        {
            return FALSE;
        }
        FEVARROOT_MEM_LEN(Var) --;
    }
    FEVARROOT_MEM_LEN(Var) = FECAL_MAX(FEVARROOT_MEM_LEN(Var),0);
    return TRUE;
}

INT32 FEVarRootGetLen(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FERTN_ERAPP_ARG;
    }
    return FEVARROOT_MEM_LEN(Var);
}

BOOL  FEVarRootSetPushIdx(void *Var,INT32 PushIdx)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    if ( (FEVARROOT_MEM_MAX(Var)<PushIdx) || (0>PushIdx) )
    {
        return FALSE;
    }
    FEVARROOT_MEM_PUSH(Var) = PushIdx;
    return TRUE;
}

INT32 FEVarRootGetPushIdx(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FERTN_ER;
    }
    return FEVARROOT_MEM_PUSH(Var);
}

BOOL  FEVarRootSetPopIdx(void *Var,INT32 PopIdx)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    if ( (FEVARROOT_MEM_MAX(Var)<PopIdx) || (0>PopIdx) )
    {
        return FALSE;
    }
    FEVARROOT_MEM_POP(Var) = PopIdx;
    return TRUE;
}

INT32 FEVarRootGetPopIdx(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FERTN_ER;
    }
    return FEVARROOT_MEM_POP(Var);
}

BOOL  FEVarRootSetUserLen(void *Var,INT32 UserLen)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    FEVARROOT_MEM_USERLEN(Var) = UserLen;
    return TRUE;
}

BOOL  FEVarRootPlusUserLen(void *Var,BOOL Flag)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    FEVARROOT_MEM_USERLEN(Var) += ((Flag)?1:(-1));
    return TRUE;
}

INT32 FEVarRootGetUserLen(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FERTN_ER;
    }
    return FEVARROOT_MEM_USERLEN(Var);
}

BOOL  FEVarRootSetUserCnt(void *Var,INT32 UserCnt)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    FEVARROOT_MEM_USERCNT(Var) = UserCnt;
    return TRUE;
}

BOOL  FEVarRootPlusUserCnt(void *Var,BOOL Flag)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    FEVARROOT_MEM_USERCNT(Var) += ((Flag)?1:(-1));
    return TRUE;
}

INT32 FEVarRootGetUserCnt(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FERTN_ER;
    }
    return FEVARROOT_MEM_USERCNT(Var);
}

BOOL  FEVarRootSetValue(void *Var,void *Value)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    if ( NULL==Value )
    {
        FEVarTypeVVSetNull(Var);
    }
    else
    {
        FEVarTypeVVSetValue(Var);
    }
    FEVARROOT_MEM_VALUE(Var) = Value;
    return TRUE;
}

void *FEVarRootGetValue(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return NULL;
    }
    return FEVARROOT_MEM_VALUE(Var);
}

#ifdef __cplusplus
}
#endif

