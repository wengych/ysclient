/***************************************************************************/
/**[File Name    ]varstype.c                                              **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for var stype                               **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

#define FEVARSTYPE_INFO_POS         (0)
#define FEVARSTYPE_INFO_LEN         (FEVARTYPE_INFO_LEN)
#define FEVARSTYPE_VALUE_POS        (FEVARSTYPE_INFO_LEN)

#define FEVARDOUBLE_INFO_POS        (0)
#define FEVARDOUBLE_INFO_LEN        (FEVARTYPE_INFO_LEN+BYTE_SIZE)
#define FEVARDOUBLE_VALUE_POS       (FEVARDOUBLE_INFO_LEN)

void *FEVarSTypeNew(BYTE VT)
{
    void *Var;
    tFEVarSType *v;
    if ( NULL==(Var=malloc(FEVARSTYPE_ST_SIZE)) )
    {
        return NULL;
    }
    v = (tFEVarSType*)Var;
    memset(Var,0,FEVARSTYPE_ST_SIZE);
    FEVarTypeInit(Var);
    FEVarSTypeInit(Var,VT);
    return Var;
}

void  FEVarSTypeFree(void *Var)
{
    FEVarSTypeNFree(Var);
}

void  FEVarSTypeNFree(void *Var)
{
    FEVarTypeNFree(Var);
}

void  FEVarSTypeShow(void *Var,INT32 T,void *Buf)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return ;
    }
    if ( !FEVarSTypeIsSType(Var) )
    {
        return;
    }
    FEVarSTypeNShow1(Var,T,Buf);
    FEVarSTypeVShow(Var,T,Buf);
    FEVarSTypeNShow2(Var,T,Buf);
}

void  FEVarSTypeVShow(void *Var,INT32 T,void *Buf)
{
    char Log[BUFSIZE_256];
    UCHAR Tmp[BUFSIZE_32];
    UCHAR Tmp2[BUFSIZE_32];
    char Tab[BUFSIZE_64];
    INT32 Len;
    INT32 L;
    INT32 i;
    if ( !FEVarSTypeIsSType(Var) )
    {
        return;
    }
    if ( !FEVARTYPEVALUE_ISSET(Var) )
    {
        return;
    }
    memset(Tab,0,sizeof(Tab));
    FEVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    memset(Tmp,0,sizeof(Tmp));
    memcpy(Tmp,FEVARSTYPE_MEM_V(Var),FEVARSTYPE_MEM_V_SIZE(Var));

    L = 0;

    if ( FEVARTYPE_MEM_VT_DOUBLE==FEVarTypeVTGet(Var) )
    {
        sprintf(Log+L,"%s<Value Size=\"%d Prec=\"%d.%d\" \">" \
            ,Tab,FEVarTypeSLGet(Var) \
            ,FEVarTypeDPGetInt(Var),FEVarTypeDPGetDec(Var));
    }
    else
    {
        sprintf(Log+L,"%s<Value Size=\"%d\">",Tab,FEVarTypeSLGet(Var));
    }
    L += strlen(Log+L);
    Len = FEVarTypeSLGet(Var);
    switch ( FEVarTypeVTGet(Var) )
    {
        case FEVARTYPE_MEM_VT_BOOL:
            sprintf(Log+L,"%d",FERTN_CMPBOOL(FEVARSTYPE_MEM_V(Var)));
            break;
        case FEVARTYPE_MEM_VT_BYTE:
            if ( (0x20<FEVARSTYPE_MEM_V(Var)[0]) \
                &&(0x80>FEVARSTYPE_MEM_V(Var)[0]) )
            {
                sprintf(Log+L,"%c",FEVARSTYPE_MEM_V(Var)[0]);
            }
            else
            {
                sprintf(Log+L,"0x%02X",FEVARSTYPE_MEM_V(Var)[0]);
            }
            break;
        case FEVARTYPE_MEM_VT_INT16:
            sprintf(Log+L,"%d",*(INT16*)(Tmp));
            break;
        case FEVARTYPE_MEM_VT_INT32:
            sprintf(Log+L,"%d",*(INT32*)(Tmp));
            break;
        case FEVARTYPE_MEM_VT_INT64:
            sprintf(Log+L,"%lld",*(INT64*)(Tmp));
            break;
        case FEVARTYPE_MEM_VT_DOUBLE:
            memset(Tmp2,0,sizeof(Tmp2));
            snprintf(Tmp2+1,sizeof(Tmp2)-1,"%d.%d" \
                ,FEVarDoubleGetDPInt(Var),FEVarDoubleGetDPDec(Var));
            Tmp2[0] = '%';
            Tmp2[strlen(Tmp2)] = 'F';
            sprintf(Log+L,Tmp2,*(DOUBLE*)(Tmp));
            break;
        default:
            sprintf(Log+L,"%s <ErrMsg>not sample type</ErrMsg>\n%s",Tab,Tab);
            Len = FEVARSTYPE_MEM_V_SIZE(Var);
            break;
    }
    L += strlen(Log+L);

    sprintf(Log+L,"</Value>\n");
    L += strlen(Log+L);

    sprintf(Log+L,"%s<HHex Size=\"%d\">",Tab,FEVarTypeSLGet(Var));
    L += strlen(Log+L);
    for ( i=0;i<Len;i++ )
    {
        sprintf(Log+L,"%02X ",(FEVARSTYPE_MEM_V(Var))[i]);
        L += 3;
    }
    sprintf(Log+L,"</HHex>\n");
    L += strlen(Log+L);

    if ( 1<Len )
    {
        FEEndianToNet(Tmp,Len);
    }
    sprintf(Log+L,"%s<NHex Size=\"%d\">",Tab,FEVarTypeSLGet(Var));
    L += strlen(Log+L);
    for ( i=0;i<Len;i++ )
    {
        sprintf(Log+L,"%02X ",Tmp[i]);
        L += 3;
    }
    sprintf(Log+L,"</NHex>\n");
    L += strlen(Log+L);
    FEVarStringCat(Buf,Log,L);
}

BOOL  FEVarSTypePack(void *Var,void *Buf)
{
    BOOL bRtn;
    INT32 PL;
    INT32 L;
    void *PackInfo;
    UCHAR V[BUFSIZE_64];
    if ( !FEVarSTypeIsSType(Var) )
    {
        return FALSE;
    }
    L = FEVarBinGetLen(Buf);
    bRtn = FALSE;
    while( 1 )
    {
        PL = FEVARSTYPE_INFO_LEN;
        PackInfo = NULL;
        if ( FEVARTYPE_MEM_VT_DOUBLE==FEVARTYPE_MEM_VT(Var) )
        {
            PL = FEVARDOUBLE_INFO_LEN;
            /* VarType */
            PackInfo = FEVarDoublePackInfo;
        }
        PL += FEVARTYPE_MEM_SL(Var);
        if ( !FEVarTypePack(Buf,Var,PL,PackInfo) )
        {
            break;
        }
        memset(V,0,sizeof(V));
        memcpy(V,FEVARSTYPE_MEM_V(Var),FEVARTYPE_MEM_SL(Var));
        FEEndianToNet(V,FEVARTYPE_MEM_SL(Var));
        if ( !FEVarBinCat(Buf,V,FEVARTYPE_MEM_SL(Var)) )
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

INT32 FEVarSTypeUnPack(void **VVar,void *Buf,INT32 P)
{
    INT32 iRtn;
    INT32 PL;
    tFEVarType VarType;
    void *V;
    INT32 VL;
    void *Var;
    UCHAR VV[BUFSIZE_64];

    iRtn = RTNCODE_ERVAR_UNPACK;
    if ( NULL==VVar )
    {
        return iRtn;
    }
    if ( NULL==(V=FEVarBinGet(Buf)) )
    {
        return iRtn;
    }
    if ( !FEVARTYPE_IS_STYPE(((BYTE*)V)[P]) )
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
    iRtn = RTNCODE_ERVAR_UNPACK;
    while( 1 )
    {
        if ( NULL==(Var=FEVarSTypeNew(((BYTE*)V)[P])) )
        {
            break;
        }
        if ( !FEVarTypeUnPackSetType(Var,&VarType) )
        {
            break;
        }
        if ( FEVARTYPE_MEM_VT_DOUBLE==((BYTE*)V)[P] )
        {
            if ( !FEVarTypeDPSet2(Var,((BYTE*)V)[PL]) )
            {
                break;
            }
            PL += FEVARDOUBLE_VALUE_POS;
        }
        else
        {
            PL += FEVARSTYPE_VALUE_POS;
        }
        memset(VV,0,sizeof(VV));
        memcpy(VV,((BYTE*)V)+PL,FEVARTYPE_MEM_SL(Var));
        FEEndianToHost(VV,FEVARTYPE_MEM_SL(Var));
        if ( !FEVarSTypeSet(Var,VV,FEVARTYPE_MEM_SL(Var)) )
        {
            break;
        }
        PL += FEVARTYPE_MEM_SL(Var);
        iRtn = FERTN_OK;
        break;
    }
    if ( FERTN_OK==iRtn )
    {
        iRtn = PL; 
        *VVar = Var;
        Var = NULL;
    }
    FEVarSTypeFree(Var);
    Var = NULL;
    return iRtn;
}


BOOL  FEVarSTypeInit(void *Var,BYTE VT)
{
    INT32 SL;
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    if ( !FEVARTYPE_IS_STYPE(VT) )
    {
        return FALSE;
    }
    FEVarTypeVVSetValue(Var);
    FEVarTypeVTSet(Var,VT);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    FEVarTypeEDSetLittle(Var);
#else
    FEVarTypeEDSetBig(Var);
#endif
    switch ( VT )
    {
        case FEVARTYPE_MEM_VT_BOOL:
            SL = BOOL_SIZE;
            break;
        case FEVARTYPE_MEM_VT_BYTE:
            SL = BYTE_SIZE;
            break;
        case FEVARTYPE_MEM_VT_INT16:
            SL = INT16_SIZE;
            break;
        case FEVARTYPE_MEM_VT_INT32:
            SL = INT32_SIZE;
            break;
        case FEVARTYPE_MEM_VT_INT64:
            SL = INT64_SIZE;
            break;
        case FEVARTYPE_MEM_VT_DOUBLE:
            SL = DOUBLE_SIZE;
            break;
        default:
            break;
    }
    if ( 0==SL )
    {
        return FALSE;
    }
    FEVarTypeSLSet(Var,SL);
    memset(FEVARSTYPE_MEM_V(Var),0,FEVARSTYPE_MEM_V_SIZE(Var));
    return TRUE;
}

BOOL  FEVarSTypeIsSType(void *Var)
{
    if ( !FEVarTypeIsInit(Var) )
    {
        return FALSE;
    }
    return FEVARTYPE_IS_STYPE(FEVarTypeVTGet(Var));
}

void *FEVarSTypeGet(void *Var)
{
    if ( !FEVarSTypeIsSType(Var) )
    {
        return NULL;
    }
    return FEVARSTYPE_MEM_V(Var);
}

BOOL  FEVarSTypeSet(void *Var,void *V,INT32 Len)
{
    if ( !FEVarSTypeIsSType(Var)||(0>Len) )
    {
        return FALSE;
    }
    memset(FEVARSTYPE_MEM_V(Var),0,FEVARSTYPE_MEM_V_SIZE(Var));
    if ( NULL==V )
    {
        FEVarTypeVVSetNull(Var);
        FEVarTypeSLSet(Var,0);
    }
    else
    {
        FEVarTypeVVSetValue(Var);
        memcpy(FEVARSTYPE_MEM_V(Var),V,Len);
        FEVarTypeSLSet(Var,Len);
    }
    return TRUE;
}

void *FEVarSTypeClone(void *Var)
{
    void *N;

    if ( !FEVarSTypeIsSType(Var) )
    {
        return NULL;
    }
    if ( NULL==(N=FEVarSTypeNew(FEVarTypeVTGet(Var))) )
    {
        return NULL;
    }
    if ( !FEVarSTypeSet(N,FEVARSTYPE_MEM_V(Var),FEVarTypeSLGet(Var)) )
    {
        FEVarSTypeFree(N);
        return NULL;
    }
    if ( FEVARTYPE_MEM_VT_DOUBLE==FEVarTypeVTGet(Var) )
    {
        if ( !FEVarTypeDPSet(N,FEVarTypeDPGetInt(Var),FEVarTypeDPGetDec(Var)) )
        {
            FEVarSTypeFree(N);
            return NULL;
        }
    }
    if ( !FEVarTypeClone(N,Var) )
    {
        FEVarBinFree(N);
        N = NULL;
    }
    return N;
}

void *FEVarBoolNew()
{
    return FEVarSTypeNew(FEVARTYPE_MEM_VT_BOOL);
}

void  FEVarBoolFree(void *Var)
{
    FEVarSTypeFree(Var);
}

BOOL  FEVarBoolGet(void *Var,BOOL *V)
{
    void *v;
    if ( NULL==(v=FEVarSTypeGet(Var)) )
    {
        return FALSE;
    }
    (*V) = *((BOOL*)v);
    return TRUE;
}

BOOL  FEVarBoolSet(void *Var,BOOL V)
{
    return FEVarSTypeSet(Var,&V,BOOL_SIZE);
}

void *FEVarBoolSave(BOOL V)
{
    void *Var;
    if ( NULL==(Var=FEVarBoolNew()) )
    {
        return NULL;
    }
    if ( !FEVarBoolSet(Var,V) )
    {
        FEVarBoolFree(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarBoolSave2(const char *Key,BOOL V)
{
    void *Var;
    if ( NULL==(Var=FEVarBoolSave(V)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarBoolFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void *FEVarBoolClone(void *Var)
{
    return FEVarSTypeClone(Var);
}

void *FEVarByteNew()
{
    return FEVarSTypeNew(FEVARTYPE_MEM_VT_BYTE);
}

void  FEVarByteFree(void *Var)
{
    FEVarSTypeFree(Var);
}

BOOL  FEVarByteGet(void *Var,BYTE *V)
{
    void *v;
    if ( NULL==(v=FEVarSTypeGet(Var)) )
    {
        return FALSE;
    }
    (*V) = ((BYTE*)v)[0];
    return TRUE;
}

BOOL  FEVarByteSet(void *Var,BYTE V)
{
    return FEVarSTypeSet(Var,&V,BYTE_SIZE);
}

void *FEVarByteSave(BYTE V)
{
    void *Var;
    if ( NULL==(Var=FEVarByteNew()) )
    {
        return NULL;
    }
    if ( !FEVarByteSet(Var,V) )
    {
        FEVarByteFree(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarByteSave2(const char *Key,BYTE V)
{
    void *Var;
    if ( NULL==(Var=FEVarByteSave(V)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarBoolFree(Var);
            Var = NULL;
        }   
    }
    return Var;
}   

void *FEVarByteClone(void *Var)
{
    return FEVarSTypeClone(Var);
}

void *FEVarInt16New()
{
    return FEVarSTypeNew(FEVARTYPE_MEM_VT_INT16);
}

void  FEVarInt16Free(void *Var)
{
    FEVarSTypeFree(Var);
}

BOOL  FEVarInt16Get(void *Var,INT16 *V)
{
    void *v;
    if ( NULL==(v=FEVarSTypeGet(Var)) )
    {
        return FALSE;
    }
    (*V) = *(INT16*)v;
    return TRUE;
}

BOOL  FEVarInt16Set(void *Var,INT16 V)
{
    return FEVarSTypeSet(Var,&V,INT16_SIZE);
}

void *FEVarInt16Save(INT16 V)
{
    void *Var;
    if ( NULL==(Var=FEVarInt16New()) )
    {
        return NULL;
    }
    if ( !FEVarInt16Set(Var,V) )
    {
        FEVarInt16Free(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarInt16Save2(const char *Key,INT16 V)
{
    void *Var;
    if ( NULL==(Var=FEVarInt16Save(V)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarBoolFree(Var);
            Var = NULL;
        }   
    }
    return Var;
}   

void *FEVarInt16Clone(void *Var)
{
    return FEVarSTypeClone(Var);
}

void *FEVarInt32New()
{
    return FEVarSTypeNew(FEVARTYPE_MEM_VT_INT32);
}

void  FEVarInt32Free(void *Var)
{
    FEVarSTypeFree(Var);
}

BOOL  FEVarInt32Get(void *Var,INT32 *V)
{
    void *v;
    if ( NULL==(v=FEVarSTypeGet(Var)) )
    {
        return FALSE;
    }
    (*V) = *(INT32*)v;
    return TRUE;
}

BOOL  FEVarInt32Set(void *Var,INT32 V)
{
    return FEVarSTypeSet(Var,&V,INT32_SIZE);
}

void *FEVarInt32Save(INT32 V)
{
    void *Var;
    if ( NULL==(Var=FEVarInt32New()) )
    {
        return NULL;
    }
    if ( !FEVarInt32Set(Var,V) )
    {
        FEVarInt32Free(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarInt32Save2(const char *Key,BOOL V)
{
    void *Var;
    if ( NULL==(Var=FEVarInt32Save(V)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarBoolFree(Var);
            Var = NULL;
        }   
    }
    return Var;
}   

void *FEVarInt32Clone(void *Var)
{
    return FEVarSTypeClone(Var);
}

void *FEVarInt64New()
{
    return FEVarSTypeNew(FEVARTYPE_MEM_VT_INT64);
}

void  FEVarInt64Free(void *Var)
{
    FEVarSTypeFree(Var);
}

BOOL  FEVarInt64Get(void *Var,INT64 *V)
{
    void *v;
    if ( NULL==(v=FEVarSTypeGet(Var)) )
    {
        return FALSE;
    }
    (*V) = *(INT64*)v;
    return TRUE;
}

BOOL  FEVarInt64Set(void *Var,INT64 V)
{
    return FEVarSTypeSet(Var,&V,INT64_SIZE);
}

void *FEVarInt64Save(INT64 V)
{
    void *Var;
    if ( NULL==(Var=FEVarInt64New()) )
    {
        return NULL;
    }
    if ( !FEVarInt64Set(Var,V) )
    {
        FEVarInt64Free(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarInt64Save2(const char *Key,INT64 V)
{
    void *Var;
    if ( NULL==(Var=FEVarInt64Save(V)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarBoolFree(Var);
            Var = NULL;
        }
    }
    return Var;
}

void *FEVarInt64Clone(void *Var)
{
    return FEVarSTypeClone(Var);
}

void *FEVarDoubleNew()
{
    return FEVarSTypeNew(FEVARTYPE_MEM_VT_DOUBLE);
}

void  FEVarDoubleFree(void *Var)
{
    FEVarSTypeFree(Var);
}

BOOL  FEVarDoublePackInfo(void *Var,void *Buf)
{
    if ( !FEVarTypeIsInit2(Var,FEVARTYPE_MEM_VT_DOUBLE) )
    {
        return FALSE;
    }
    return FEPackFuncByte(Buf,FEVARTYPE_MEM_DP(Var));
}

BOOL  FEVarDoubleGet(void *Var,DOUBLE *V)
{
    void *v;
    if ( NULL==(v=FEVarSTypeGet(Var)) )
    {
        return FALSE;
    }
    (*V) = *(DOUBLE*)v;
    return TRUE;
}

BOOL  FEVarDoubleSet(void *Var,DOUBLE V)
{
    return FEVarSTypeSet(Var,&V,DOUBLE_SIZE);
}

INT32 FEVarDoubleGetDPInt(void *Var)
{
    return FEVarTypeDPGetInt(Var);
}

INT32 FEVarDoubleGetDPDec(void *Var)
{
    return FEVarTypeDPGetDec(Var);
}

BOOL  FEVarDoubleSetDP(void *Var,INT32 Int,INT32 Dec)
{
    return FEVarTypeDPSet(Var,Int,Dec);
}

BOOL  FEVarDoubleSetDP2(void *Var,BYTE DP)
{
    return FEVarTypeDPSet2(Var,DP);
}

void *FEVarDoubleSave(DOUBLE V)
{
    void *Var;
    if ( NULL==(Var=FEVarDoubleNew()) )
    {
        return NULL;
    }
    if ( !FEVarDoubleSet(Var,V) )
    {
        FEVarDoubleFree(Var);
        Var = NULL;
    }
    return Var;
}

void *FEVarDoubleSave2(const char *Key,DOUBLE V)
{
    void *Var;
    if ( NULL==(Var=FEVarDoubleSave(V)) )
    {
        return NULL;
    }
    if ( NULL!=Key )
    {
        if ( !FEVarTypeKeyCpy(Var,Key,strlen(Key)) )
        {
            FEVarDoubleFree(Var);
            Var = NULL;
        }
    }
    return Var;
}
 
void *FEVarDoubleClone(void *Var)
{
    return FEVarSTypeClone(Var);
}

#ifdef __cplusplus
}
#endif

