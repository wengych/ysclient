/***************************************************************************/
/**[File Name    ]varbin.c                                                **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for var bin                                 **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tagFEVarBin
{
    FEVARTYPE_MEM;
    INT32   Size;
    INT32   Len;
    void   *V;
}tFEVarBin;
#define FEVARBIN_ST_SIZE           (sizeof(tFEVarBin))
#define FEVARBIN_MEM_S(v)          (((tFEVarBin*)(v))->Size)
#define FEVARBIN_MEM_L(v)          (((tFEVarBin*)(v))->Len)
#define FEVARBIN_MEM_V(v)          (((tFEVarBin*)(v))->V)

#define FEVARBIN_INFO_POS           (0)
#define FEVARBIN_INFO_LEN           (FEVARTYPE_INFO_LEN)
#define FEVARBIN_VALUE_POS          (FEVARBIN_INFO_LEN)

void *FEVarBinNew()
{
    void *Var;
	tFEVarBin *t;
    if ( NULL==(Var=malloc(FEVARBIN_ST_SIZE)) )
    {
        return NULL;
    }
    t = (tFEVarBin *)Var;
    memset(Var,0,FEVARBIN_ST_SIZE);
    FEVarTypeInit(Var);
    FEVarBinInit(Var);
    return Var;
}
 
void *FEVarBinNew2(INT32 Size)
{
    void *Var;
    if ( NULL==(Var=FEVarBinNew()) )
    {
        return NULL;
    }
    if ( !FEVarBinRealloc(Var,Size) )
    {
        FEVarBinFree(Var);
        Var = NULL;
    }
    return Var;
}

void  FEVarBinFree(void *Var)
{
    FEVarBinVFree(Var);
    FEVarBinNFree(Var);
}

void  FEVarBinNFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarBinVFree(void *Var)
{
    FEVarBinClear(Var);
}

void  FEVarBinDelete(void *Var)
{
    FEVarBinClear(Var);
}

void  FEVarBinShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return ;
    }
    if ( !FEVarTypeIsInit2(Buf,FEVARTYPE_MEM_VT_STRING) )
    {
        return ;
    }
    FEVarBinNShow1(Var,T,Buf);
    FEVarBinVShow(Var,T,Buf);
    FEVarBinNShow2(Var,T,Buf);
}

void  FEVarBinVShow(void *Var,INT32 T,void *Buf)
{
    char Log[BUFSIZE_128];
    char Tab[BUFSIZE_64];
    INT32 L;
    INT32 i;
    INT32 LL;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
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

    sprintf(Log+L,"%s<Value Len=\"%d\">\n",Tab,FEVARBIN_MEM_L(Var));
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);

    for ( i=0;i<FEVARBIN_MEM_L(Var);i+=MAXHEXLOGLINE )
    {
        LL = FEVARBIN_MEM_L(Var)-i;
        memset(Log,0,sizeof(Log));
        FEHexToBufLine(Log,sizeof(Log),MAXHEXLOGLINE \
            ,((char*)FEVARBIN_MEM_V(Var))+i,LL);
        L = strlen(Log);
        strcpy(Log+L,"\n");
        L++;
        FEVarStringCat(Buf,Log,L);
    }

    L = 0;
    sprintf(Log+L,"%s</Value>\n",Tab);
    L += strlen(Log+L);

    sprintf(Log+L,"%s<NHex>\n",Tab);
    L += strlen(Log+L);

    for ( i=0;i<FEVARBIN_MEM_L(Var);i++ )
    {
        if ( (sizeof(Log)<L+3)||(70<=L) )
        {
            FEVarStringCat(Buf,Log,L);
            memset(Log,0,sizeof(Log));
            L = 0;
        }
        sprintf(Log+L,"%02X",((UCHAR*)FEVARBIN_MEM_V(Var))[i]);
        L += strlen(Log+L);
        if ( 70<=L )
        {
            L = strlen(Log);
            strcpy(Log+L,"\n");
            L++;
        }
    }
    if ( 0<L )
    {
        FEVarStringCat(Buf,Log,L);
    }
    L = 0;
    sprintf(Log+L,"\n%s</NHex>\n",Tab);
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);
}

BOOL  FEVarBinPack(void *Var,void *Buf)
{
    BOOL bRtn;
    INT32 PL;
    INT32 L;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    L = FEVarBinGetLen(Buf);
    bRtn = FALSE;
    while( 1 )
    {
        PL = FEVARBIN_INFO_LEN+FEVARBIN_MEM_L(Var);
        /* VarType */
        if ( !FEVarTypePack(Buf,Var,PL,NULL) )
        {
            break;
        }
        if ( !FEVarBinCat(Buf,FEVARBIN_MEM_V(Var),FEVARBIN_MEM_L(Var)) )
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

INT32 FEVarBinUnPack(void **VVar,void *Buf,INT32 P)
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
    if ( FEVARTYPE_MEM_VT_BIN!=((BYTE*)V)[P] )
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
    iRtn = RTNCODE_ERVAR_UNPACK;
    while( 1 )
    {
        PL += FEVARBIN_VALUE_POS;
        if ( NULL==(Var=FEVarBinSave(((BYTE*)V)+PL,VL)) )
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
    FEVarBinFree(Var);
    Var = NULL;
    return iRtn;
}

BOOL  FEVarBinInit(void *Var)
{
    if ( NULL==Var )
    {
        return FALSE;
    }
    FEVARBIN_MEM_S(Var) = 0;
    FEVARBIN_MEM_L(Var) = 0;
    FEVARBIN_MEM_V(Var) = NULL;
    FEVarTypeVVSetValue(Var);
    FEVarTypeVTSet(Var,FEVARTYPE_MEM_VT_BIN);
    FEVarTypeEDSetBig(Var);
    return TRUE;
}

BOOL  FEVarBinClear(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    if ( (0<=FEVARBIN_MEM_S(Var))&&(NULL!=FEVARBIN_MEM_V(Var)) )
    {
        free(FEVARBIN_MEM_V(Var));
    }
    FEVarBinInit(Var);
    return TRUE;
}

void  FEVarBinReset(void *Var)
{
    FEVarBinCut(Var,0,0);
}

void  FEVarBinCut(void *Var,INT32 S,INT32 L)
{
    INT32 SS;
    INT32 EE;
    INT32 LL;
    INT32 i;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return ;
    }
    SS = FECAL_MIN(0,S);
    if ( (SS<FEVARBIN_MEM_L(Var))&&(NULL!=FEVARBIN_MEM_V(Var)) )
    {
        LL = FECAL_MIN(0,L);
        EE = SS+LL;
        if ( (0<L)&&(EE<FEVARBIN_MEM_L(Var)) )
        {
            for ( i=EE;i<FEVARBIN_MEM_L(Var);i++ )
            {
                ((char *)FEVARBIN_MEM_V(Var))[SS] \
                    = ((char *)FEVARBIN_MEM_V(Var))[i];
                SS ++;
            }
        }
        memset(((BYTE*)FEVARBIN_MEM_V(Var))+SS,0,FEVARBIN_MEM_L(Var)-SS);
        FEVARBIN_MEM_L(Var) = SS;
    }
}

INT32 FEVarBinGetSize(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return FERTN_ER;
    }
    return FEVARBIN_MEM_S(Var);
}
 
BOOL  FEVarBinSetLen(void *Var,INT32 Len)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    FEVARBIN_MEM_L(Var) = FECAL_MAX(Len,0);
    FEVARBIN_MEM_L(Var) = FECAL_MIN(Len,FEVARBIN_MEM_S(Var)-1);
    return TRUE;
}

INT32 FEVarBinGetLen(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return FERTN_ER;
    }
    return FEVARBIN_MEM_L(Var);
}

void *FEVarBinGet(void *Var)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return NULL;
    }
    return FEVARBIN_MEM_V(Var);
}

BOOL  FEVarBinGet2(void *Var,void *V,INT32 *L,INT32 S)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    if ( (NULL==V)||(NULL==L)||(S-1<FEVARBIN_MEM_L(Var)) )
    {
        return FALSE;
    }
    memset(V,0,S);
    if ( FEVARTYPEVALUE_ISSET(Var) )
    {
        memcpy(V,FEVARBIN_MEM_V(Var),FEVARBIN_MEM_L(Var));
        *L = FEVARBIN_MEM_L(Var);
    }
    else
    {
        *L = 0;
    }
    return TRUE;
}

BOOL  FEVarBinMalloc(void *Var,INT32 L)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    if ( 0>=L )
    {
        return TRUE;
    }
    if ( FEVARBIN_MEM_L(Var)+L<FEVARBIN_MEM_S(Var) )
    {
        return TRUE;
    }
    return FEVarBinRealloc(Var,L+FEVARBIN_MEM_L(Var)-FEVARBIN_MEM_S(Var));
}

BOOL  FEVarBinRealloc(void *Var,INT32 L)
{
    void *v;
    INT32 vs;
    INT32 pos;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    if ( 0>=L )
    {
        return TRUE;
    }
    pos = FEVARBIN_MEM_L(Var);
    vs = L;
    if ( NULL==FEVARBIN_MEM_V(Var) )
    {
        vs ++;
        if ( NULL==(v=malloc(vs)) )
        {
            return FALSE;
        }
    }
    else
    {
        vs += FEVARBIN_MEM_S(Var);
        if ( NULL==(v=realloc(FEVARBIN_MEM_V(Var),vs)) )
        {
            return FALSE;
        }
    }
    memset(((BYTE*)v)+pos,0,vs-pos);
    FEVARBIN_MEM_S(Var) = vs;
    FEVARBIN_MEM_V(Var) = v;

    return TRUE;
}

BOOL  FEVarBinCat(void *Var,void *V,INT32 L)
{
    INT32 pos;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return FALSE;
    }
    if ( (NULL==V)||(0>=L) )
    {
        return TRUE;
    }
    if ( !FEVarBinRealloc(Var,L) )
    {
        return FALSE;
    }
    pos = FEVARBIN_MEM_L(Var);
    FEVARBIN_MEM_L(Var) += L;
    memcpy(((BYTE*)FEVARBIN_MEM_V(Var))+pos,V,L);
    FEVarTypeVVSetValue(Var);
    return TRUE;
}

BOOL  FEVarBinCpy(void *Var,void *V,INT32 L)
{
    FEVarBinDelete(Var);
    return FEVarBinCat(Var,V,L);
}

void *FEVarBinSave(void *V,INT32 L)
{
    void *Var;
    if ( NULL==(Var=FEVarBinNew()) )
    {
        return NULL;
    }
    if ( !FEVarBinCat(Var,V,L) )
    {
        FEVarBinFree(Var);
        return NULL;
    }
    return Var;
}

void *FEVarBinSave2(const char *Key,void *V,INT32 L)
{
    void *Var;
    if ( NULL==(Var=FEVarBinSave(V,L)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarBinFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void *FEVarBinClone(void *Var)
{
    void *N;
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_BIN) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarBinSave(FEVarBinGet(Var),FEVarBinGetLen(Var))) )
    {
        return NULL;
    }
    if ( !FEVarTypeClone(N,Var) )
    {
        FEVarBinFree(N);
        N = NULL;
    }
    return N;
}

#ifdef __cplusplus
}
#endif

