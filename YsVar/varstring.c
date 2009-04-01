/***************************************************************************/
/**[File Name    ]varstring.c                                             **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for var string                              **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tagFEVarString
{
    FEVARTYPE_MEM;
    INT32   S;
    INT32   L;
    UCHAR   C;
    UCHAR   R[3];
    char   *V;
}tFEVarString;
#define FEVARSTRING_ST_SIZE           (sizeof(tFEVarString))
#define FEVARSTRING_MEM_S(v)          (((tFEVarString*)(v))->S)
#define FEVARSTRING_MEM_L(v)          (((tFEVarString*)(v))->L)
#define FEVARSTRING_MEM_C(v)          (((tFEVarString*)(v))->C)
#define FEVARSTRING_MEM_R(v)          (((tFEVarString*)(v))->R)
#define FEVARSTRING_MEM_V(v)          (((tFEVarString*)(v))->V)

#define FEVARSTRING_INFO_POS        (0)
#define FEVARSTRING_INFO_LEN        (FEVARTYPE_INFO_LEN)
#define FEVARSTRING_VALUE_POS       (FEVARSTRING_INFO_LEN)

void *FEVarStringNew()
{
    void *Var;
    tFEVarString *t;
    if ( NULL==(Var=malloc(FEVARSTRING_ST_SIZE)) )
    {
        return NULL;
    }
    t = (tFEVarString *)Var;
    memset(Var,0,FEVARSTRING_ST_SIZE);
    FEVarTypeInit(Var);
    FEVarStringInit(Var);
    return Var;
}

void *FEVarStringNew2(INT32 Size)
{
    void *Var;
    if ( NULL==(Var=FEVarStringNew()) )
    {
        return NULL;
    }
    if ( !FEVarStringRealloc(Var,Size) )
    {
        FEVarStringFree(Var);
        Var = NULL;
    }
    return Var;
}

void  FEVarStringFree(void *Var)
{
    FEVarStringVFree(Var);
    FEVarStringNFree(Var);
}

void  FEVarStringNFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarStringVFree(void *Var)
{
    FEVarStringClear(Var);
}

void  FEVarStringDelete(void *Var)
{
    FEVarStringClear(Var);
}

void  FEVarStringShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarStringNShow1(Var,T,Buf);
    FEVarStringVShow(Var,T,Buf);
    FEVarStringNShow2(Var,T,Buf);
}

void  FEVarStringVShow(void *Var,INT32 T,void *Buf)
{
    char Log[BUFSIZE_128];
    char Tab[BUFSIZE_64];
    INT32 L;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return;
    }
    if ( !FEVARTYPEVALUE_ISSET(Var) )
    {
        return;
    }
    memset(Tab,0,sizeof(Tab));
    FEVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    L = 0;

    sprintf(Log+L,"%s<Value Len=\"%d\">",Tab,FEVARSTRING_MEM_L(Var));
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);

    FEVarStringCat(Buf,FEVARSTRING_MEM_V(Var),FEVARSTRING_MEM_L(Var));

    L = 0;
    sprintf(Log+L,"</Value>\n");
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);
}

BOOL  FEVarStringPack(void *Var,void *Buf)
{
    BOOL bRtn;
    INT32 PL;
    INT32 L;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return FALSE;
    }
    L = FEVarBinGetLen(Buf);
    bRtn = FALSE;
    while( 1 )
    {
        PL = FEVARSTRING_INFO_LEN+FEVARSTRING_MEM_L(Var);
        /* VarType */
        if ( !FEVarTypePack(Buf,Var,PL,NULL) )
        {
            break;
        }
        if ( !FEVarBinCat(Buf,FEVARSTRING_MEM_V(Var),FEVARSTRING_MEM_L(Var)) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    if ( !bRtn )
    {
        FEVarBinCut(Buf,L,0);
    }

    return bRtn;
}

INT32 FEVarStringUnPack(void **VVar,void *Buf,INT32 P)
{
    INT32 iRtn;
    INT32 PL;
    tFEVarType VarType;
    void *V;
    INT32 VL;
    void *Var;

    iRtn = RTNCODE_ERVAR_UNPACK;
    if ( NULL==VVar )
    {
        return iRtn;
    }
    if ( NULL==(V=FEVarBinGet(Buf)) )
    {
        return iRtn;
    }
    if ( FEVARTYPE_MEM_VT_STRING!=((BYTE*)V)[P] )
    {
        return iRtn;
    }
    if ( FERTN_OK>(iRtn=FEVarTypeUnPack(&PL,&VarType,Buf,P+1)) )
    {
        return iRtn;
    }
    VL = PL;
    PL = iRtn;
    
    *VVar = NULL;
    Var = NULL;
    iRtn = FERTN_ERVAR_UNPACK;
    while( 1 )
    {
        PL += FEVARSTRING_VALUE_POS;
        if ( NULL==(Var=FEVarStringSave(((BYTE*)V)+PL,VL)) )
        {
            break;
        }
        PL += VL;
        if ( !FEVarTypeUnPackSetType(Var,&VarType) )
        {
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
    FEVarStringFree(Var);
    Var = NULL;
    return iRtn;
}

BOOL  FEVarStringInit(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    FEVARSTRING_MEM_S(Var) = 0;
    FEVARSTRING_MEM_L(Var) = 0;
    FEVARSTRING_MEM_C(Var) = FECHARSET_UTF8;
    FEVARSTRING_MEM_V(Var) = NULL;
    FEVarTypeVVSetValue(Var);
    FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_STRING);
    FEVarTypeEDSetBig(Var);
    return TRUE;
}

BOOL  FEVarStringClear(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return FALSE;
    }
    if ( (0<FEVARSTRING_MEM_S(Var))&&(NULL!=FEVARSTRING_MEM_V(Var)) )
    {
        free(FEVARSTRING_MEM_V(Var));
        FEVARSTRING_MEM_V(Var) = NULL;
    }
    FEVarStringInit(Var);
    return TRUE;
}

void  FEVarStringReset(void *Var)
{
    FEVarStringCut(Var,0,0);
}

void  FEVarStringCut(void *Var,INT32 S,INT32 L)
{
    INT32 SS;
    INT32 EE;
    INT32 LL;
    INT32 i;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    SS = FECAL_MIN(0,S);
    if ( (SS<FEVARSTRING_MEM_L(Var))&&(NULL!=FEVARSTRING_MEM_V(Var)) )
    {
        LL = FECAL_MIN(0,L);
        EE = SS+LL;
        if ( (0<L)&&(EE<FEVARSTRING_MEM_L(Var)) )
        {
            for ( i=EE;i<FEVARSTRING_MEM_L(Var);i++ )
            {
                FEVARSTRING_MEM_V(Var)[SS] = FEVARSTRING_MEM_V(Var)[i];
                SS ++;
            }
        }
        memset(FEVARSTRING_MEM_V(Var)+SS,0,FEVARSTRING_MEM_L(Var)-SS);
        FEVARSTRING_MEM_L(Var) = SS;
    }
}

INT32 FEVarStringGetSize(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return FERTN_ER;
    }
    return FEVARSTRING_MEM_S(Var);
}

BOOL  FEVarStringSetLen(void *Var,INT32 Len)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return FALSE;
    }
    FEVARSTRING_MEM_L(Var) = FECAL_MAX(Len,0);
    FEVARSTRING_MEM_L(Var) = FECAL_MIN(Len,FEVARSTRING_MEM_S(Var)-1);
    return TRUE;
}

INT32 FEVarStringGetLen(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return FERTN_ER;
    }
    return FEVARSTRING_MEM_L(Var);
}

void *FEVarStringGet(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return NULL;
    }
    return FEVARSTRING_MEM_V(Var);
}

BOOL  FEVarStringGet2(void *Var,void *V,INT32 *L,INT32 S)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return FALSE;
    }
    if ( (NULL==V)||(NULL==L)||(S-1<FEVARSTRING_MEM_L(Var)) )
    {
        return FALSE;
    }
    memset(V,0,S);
    if ( FEVARTYPEVALUE_ISSET(Var) )
    {
        memcpy(V,FEVARSTRING_MEM_V(Var),FEVARSTRING_MEM_L(Var));
        *L = FEVARSTRING_MEM_L(Var);
    }
    else
    {
        *L = 0;
    }
    return TRUE;
}

 
BOOL  FEVarStringMalloc(void *Var,INT32 L)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return FALSE;
    }
    if ( 0>=L )
    {
        return TRUE;
    }
    if ( FEVARSTRING_MEM_L(Var)+L<FEVARSTRING_MEM_S(Var) )
    {
        return TRUE;
    }
    return FEVarStringRealloc(Var \
        ,L+FEVARSTRING_MEM_L(Var)-FEVARSTRING_MEM_S(Var));
}

BOOL  FEVarStringRealloc(void *Var,INT32 L)
{
    void *v;
    INT32 vs;
    INT32 pos;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return FALSE;
    }
    if ( 0>=L )
    {
        return TRUE;
    }
    pos = FEVARSTRING_MEM_L(Var);
    vs = L;
    v = FEVARSTRING_MEM_V(Var);
    if ( NULL==v )
    {
        vs ++;
        if ( NULL==(v=malloc(vs)) )
        {
            return FALSE;
        }
    }
    else
    {
        vs += FEVARSTRING_MEM_S(Var);
        if ( NULL==(v=realloc(v,vs)) )
        {
            return FALSE;
        }
    }
    memset(((UCHAR*)v)+pos,0,vs-pos);
    FEVARSTRING_MEM_S(Var) = vs;
    FEVARSTRING_MEM_V(Var) = v;

    return TRUE;
}

BOOL  FEVarStringCat(void *Var,void *V,INT32 L)
{
    INT32 pos;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return FALSE;
    }
    if ( (NULL==V)||(0>=L) )
    {
        return TRUE;
    }
    if ( !FEVarStringRealloc(Var,L) )
    {
        return FALSE;
    }
    pos = FEVARSTRING_MEM_L(Var);
    FEVARSTRING_MEM_L(Var) += L;
    memcpy(FEVARSTRING_MEM_V(Var)+pos,V,L);
    FEVarTypeVVSetValue(Var);
    return TRUE;
}

BOOL  FEVarStringCpy(void *Var,void *V,INT32 L)
{
    FEVarStringDelete(Var);
    return FEVarStringCat(Var,V,L);
}

BOOL  FEVarStringCatUni(void *Var,void *V,INT32 L)
{
    BOOL bRtn;
    void *v;
    INT32 vl;
    INT32 vs;
    if ( (NULL==V)||(0==L) )
    {
        return FEVarStringCat(Var,NULL,0);
    }
    vs = 3*L+1;
    if ( NULL==(v=malloc(vs)) )
    {
        return FALSE;
    }
    memset(v,0,vs);
    bRtn = FALSE;
    while( 1 )
    {
        if ( FERTN_OK!=FE2BytesUniToUTF8BigEndian(V,L,v,&vl,vs) )
        {
            break;
        }
        if ( !FEVarStringCat(Var,v,vl) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    free(v);
    return bRtn;
}

BOOL  FEVarStringCpyUni(void *Var,void *V,INT32 Len)
{
    FEVarStringDelete(Var);
    return FEVarStringCatUni(Var,V,Len);
}

BOOL  FEVarStringCatGbk(void *Var,void *V,INT32 L)
{
    BOOL bRtn;
    void *v;
    INT32 vl;
    INT32 vs;
    if ( (NULL==V)||(0==L) )
    {
        return FEVarStringCat(Var,NULL,0);
    }
    vs = 3*L+1;
    if ( NULL==(v=malloc(vs)) )
    {
        return FALSE;
    }
    memset(v,0,vs);
    bRtn = FALSE;
    while( 1 )
    {
        if ( FERTN_OK!=FE2BytesGbk2Uni(V,L,v,&vl,vs) )
        {
            break;
        }
        if ( !FEVarStringCatUni(Var,v,vl) )
        {
            break;
        }
        bRtn = TRUE;
        break;
    }
    free(v);
    return bRtn;
}

BOOL  FEVarStringCpyGbk(void *Var,void *V,INT32 L)
{
    FEVarStringDelete(Var);
    return FEVarStringCatGbk(Var,V,L);
}

void *FEVarStringSave(void *V,INT32 L)
{
    void *Var;
    if ( NULL==(Var=FEVarStringNew()) )
    {
        return NULL;
    }
    if ( !FEVarStringCat(Var,V,L) )
    {
        FEVarStringFree(Var);
        return NULL;
    }
    return Var;
}
 
void *FEVarStringSave2(const char *Key,void *V,INT32 L)
{
    void *Var;
    if ( NULL==(Var=FEVarStringSave(V,L)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarStringFree(Var);
            Var = NULL;
        }   
    }   
    return Var;
}

void *FEVarStringClone(void *Var)
{
    void *N;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_STRING) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarStringSave(FEVarStringGet(Var),FEVarStringGetLen(Var))) )
    {
        return NULL;
    }
    if ( !FEVarTypeClone(N,Var) )
    {
        FEVarStringFree(N);
        N = NULL;
    }
    return N;
}

#ifdef __cplusplus
}
#endif

