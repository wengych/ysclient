/***************************************************************************/
/**[File Name    ]variant.h                                               **/
/**[File Path    ]$(TOPDIR)/libsrc/fecom                                  **/
/**[Library Name ]$(LIBDIR)/libfecom.so                                   **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define head for variant                                 **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef VARIANT_H__
#define VARIANT_H__

#include <fecom.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FEVARTYPE_VER_MAJOR         1
#define FEVARTYPE_VER_SUB           0
#define FEVARARRAY_UNIT_MIN         8
#define FEVARARRAY_UNIT_MAX         0xFFFFFF /* 16777215 */
#define FEVARTYPE_FREE_SUBFIX       1
#define FEVARTYPE_NFREE_SUBFIX      2
#define FEVARTYPE_VFREE_SUBFIX      3
#define FEVARTYPE_SHOW_SUBFIX       11
#define FEVARTYPE_NSHOW1_SUBFIX     12
#define FEVARTYPE_NSHOW2_SUBFIX     13
#define FEVARTYPE_VSHOW_SUBFIX      14
#define FEVARTYPE_CLONE_SUBFIX      15
#define FEVARTYPE_CLONEV_SUBFIX     16
#define FEVARTYPE_PACK_SUBFIX       17
#define FEVARTYPE_UNPACK_SUBFIX     18

#define FEVARTYPE_MEM_VK_NOT        0
#define FEVARTYPE_MEM_VK_KEY        1
#define FEVARTYPE_MEM_VK_HASHKEY    2 

#define FEVARTYPE_MEM_VV_NOT        0
#define FEVARTYPE_MEM_VV_NULL       1
#define FEVARTYPE_MEM_VV_VALUE      2

#define FEVARTYPE_MEM_VT_NOT        VARTYPE_MEM_VT_NOT
           
#define FEVARTYPE_MEM_VT_BOOL       VARTYPE_MEM_VT_BOOL
#define FEVARTYPE_MEM_VT_BYTE       VARTYPE_MEM_VT_BYTE
#define FEVARTYPE_MEM_VT_INT16      VARTYPE_MEM_VT_INT16
#define FEVARTYPE_MEM_VT_INT32      VARTYPE_MEM_VT_INT32
#define FEVARTYPE_MEM_VT_INT64      VARTYPE_MEM_VT_INT64
#define FEVARTYPE_MEM_VT_DOUBLE     VARTYPE_MEM_VT_DOUBLE
#define FEVARTYPE_MEM_VT_BIN        VARTYPE_MEM_VT_BIN
#define FEVARTYPE_MEM_VT_STRING     VARTYPE_MEM_VT_STRING
#define FEVARTYPE_MEM_VT_OBJECT     VARTYPE_MEM_VT_OBJECT
           
#define FEVARTYPE_MEM_VT_P1         VARTYPE_MEM_VT_P1
#define FEVARTYPE_MEM_VT_P2         VARTYPE_MEM_VT_P2
#define FEVARTYPE_MEM_VT_P3         VARTYPE_MEM_VT_P3
#define FEVARTYPE_MEM_VT_P4         VARTYPE_MEM_VT_P4
           
#define FEVARTYPE_MEM_VT_ARRAY      VARTYPE_MEM_VT_ARRAY
#define FEVARTYPE_MEM_VT_FIFO       VARTYPE_MEM_VT_FIFO
#define FEVARTYPE_MEM_VT_FILO       VARTYPE_MEM_VT_FILO
#define FEVARTYPE_MEM_VT_CICLE      VARTYPE_MEM_VT_CICLE
#define FEVARTYPE_MEM_VT_HASH       VARTYPE_MEM_VT_HASH
#define FEVARTYPE_MEM_VT_LINK       VARTYPE_MEM_VT_LINK
#define FEVARTYPE_MEM_VT_TREE       VARTYPE_MEM_VT_TREE
#define FEVARTYPE_MEM_VT_XML        VARTYPE_MEM_VT_XML

#define FEVARTYPE_IS_STYPE(VT) \
    FERTN_CMPBOOL( \
    ( (FEVARTYPE_MEM_VT_BOOL==(VT)) \
    ||(FEVARTYPE_MEM_VT_BYTE==(VT))||(FEVARTYPE_MEM_VT_INT16==(VT)) \
    ||(FEVARTYPE_MEM_VT_INT32==(VT))||(FEVARTYPE_MEM_VT_INT64==(VT)) \
    ||(FEVARTYPE_MEM_VT_DOUBLE==(VT)) ) \
    )
#define FEVARTYPE_PKG_MINLEN    (INT32_SIZE+INT16_SIZE)

BOOL  FEVarVTCall(void *Var,BYTE FT);
void *FEVarVTCallRtn(void *Var,BYTE FT);
BOOL  FEVarVTCall2RtnBool(void *Var,void *Buf,BYTE FT);
BOOL  FEVarVTCall3(void *Var,void *V2,void *V3,BYTE FT);
void *FEVarFuncVTGetFunc(BYTE VT,BYTE FT);

#define FEVARTYPE_MEM_ED_BIG        'b'
#define FEVARTYPE_MEM_ED_LITTLE     'l'

#if 0
    INT32 Luck;     /* LUCK */
    BYTE VerM;      /* Current version is 1 */
    BYTE VerS;      /* Current version is 0 */
    BYTE VV;
    BYTE VT;        /* ValueType */
    BYTE ED;        /* Endianness */
    BYTE SL;        /* 1,2,4,8 */
    BYTE DP;        /* Data Precision F:F */
    BYTE VR;        
    tFEVarTypeRes Res;      /* Lock */
    void *Clone;
    void *Free;
    void *Show;
    void *Pack;
#endif
typedef struct tagFEVarTypeRes
{
    void *Res;
    void *Clone;
    void *Free;
    void *Show;
}tFEVarTypeRes;
typedef struct tagFEVarTypeKey
{
    UINT32 KH;
    INT16 KS;
    INT16 KL;
    char  *Key;
}tFEVarTypeKey;
#define FEVARTYPE_MEM \
    INT32 Luck; \
    BYTE VerM; \
    BYTE VerS; \
    BYTE VV; \
    BYTE VT; \
    BYTE ED; \
    BYTE SL; \
    BYTE DP; \
    BYTE VR; \
    tFEVarTypeRes Res; \
    tFEVarTypeKey Key; \
    void *Clone; \
    void *Free; \
    void *Show; \
    void *Pack
typedef struct tagFEVarType
{
    FEVARTYPE_MEM;   
}tFEVarType;

#define FEVARTYPE_ST_SIZE           (sizeof(tFEVarType))
#define FEVARTYPE_MEM_LUCK(v)       (((tFEVarType*)(v))->Luck)
#define FEVARTYPE_MEM_VM(v)         (((tFEVarType*)(v))->VerM)
#define FEVARTYPE_MEM_VS(v)         (((tFEVarType*)(v))->VerS)
#define FEVARTYPE_MEM_V(v)          (((tFEVarType*)(v))->VV)
#define FEVARTYPE_MEM_VT(v)         (((tFEVarType*)(v))->VT)
#define FEVARTYPE_MEM_ED(v)         (((tFEVarType*)(v))->ED)
#define FEVARTYPE_MEM_SL(v)         (((tFEVarType*)(v))->SL)
#define FEVARTYPE_MEM_DP(v)         (((tFEVarType*)(v))->DP)
#define FEVARTYPE_MEM_VR(v)         (((tFEVarType*)(v))->VR)
#define FEVARTYPE_MEM_RES(v)        ((((tFEVarType*)(v))->Res).Res)
#define FEVARTYPE_MEM_RES_CLONE(v)  ((((tFEVarType*)(v))->Res).Clone)
#define FEVARTYPE_MEM_RES_FREE(v)   ((((tFEVarType*)(v))->Res).Free)
#define FEVARTYPE_MEM_RES_SHOW(v)   ((((tFEVarType*)(v))->Res).Show)
#define FEVARTYPE_MEM_KH(v)         ((((tFEVarType*)(v))->Key).KH)
#define FEVARTYPE_MEM_KS(v)         ((((tFEVarType*)(v))->Key).KS)
#define FEVARTYPE_MEM_KL(v)         ((((tFEVarType*)(v))->Key).KL)
#define FEVARTYPE_MEM_KEY(v)        ((((tFEVarType*)(v))->Key).Key)

#define FEVARTYPE_MEM_CLONE(v)      (((tFEVarType*)(v))->Clone)
#define FEVARTYPE_MEM_FREE(v)       (((tFEVarType*)(v))->Free)
#define FEVARTYPE_MEM_SHOW(v)       (((tFEVarType*)(v))->Show)
#define FEVARTYPE_MEM_PACK(v)       (((tFEVarType*)(v))->Pack)

#define FEVARTYPE_INIT_LUCK(v) \
    FELUCK_INIT(FEVARTYPE_MEM_LUCK((v))); 
#define FEVARTYPE_INIT_NOTLUCK(v) \
    FELUCK_INIT_NOT(FEVARTYPE_MEM_LUCK((v))); 
#define FEVARTYPE_INIT_VER(v) \
    { \
        FEVARTYPE_MEM_VM((v))=FEVARTYPE_VER_MAJOR; \
        FEVARTYPE_MEM_VM((v))=FEVARTYPE_VER_SUB; \
    }

#define FEVARTYPE_MEM_VV_GET(v)     (FEVARTYPE_MEM_V(v) & 0x0F)
#define FEVARTYPE_MEM_VK_GET(v)     (((FEVARTYPE_MEM_V(v) & 0xF0)>>4) & 0x0F)
#define FEVARTYPE_MEM_VV_SET(v,vv) \
    FEVARTYPE_MEM_V(v) = \
        ((FEVARTYPE_MEM_V(v) & 0xF0) | (0x0F & (vv)))
#define FEVARTYPE_MEM_VK_SET(v,vv)  \
    FEVARTYPE_MEM_V(v) = \
        ((FEVARTYPE_MEM_V(v) & 0x0F) | (((0x0F & (vv))<<4) & 0xF0))

#define FEVARTYPE_MEM_DP_DEFAULT    0x88
/***************************************************************************/
/**  VarType                                                              **/
/***************************************************************************/
INT32 FEVarVersionTest(void *v);
void  FEVarTypeNFree(void *v);
BOOL  FEVarTypeIsInit(void *v);
BOOL  FEVarTypeMove(void *v,void *v2);
BOOL  FEVarTypeClone(void *v,void *v2);
void  FEVarTypeInit(void *v);
BOOL  FEVarTypeIsInit2(void *v,INT32 VT);
#define FEVARTYPEKEY_HAVE(v) \
    ( (FEVARTYPE_MEM_VK_KEY==FEVARTYPE_MEM_VK_GET((v))) \
        ||(FEVARTYPE_MEM_VK_HASHKEY==FEVARTYPE_MEM_VK_GET((v))) )
#define FEVARTYPEKEY_ISHASHKEY(v) \
    (FEVARTYPE_MEM_VK_HASHKEY==FEVARTYPE_MEM_VK_GET((v)))
BOOL  FEVarTypeVKIsNot(void *v);
void  FEVarTypeVKSetNot(void *v);
void  FEVarTypeVKSetKey(void *v);
void  FEVarTypeVKSetHashKey(void *v);
#define FEVARTYPEVALUE_ISNOT(v) \
    (FEVARTYPE_MEM_VV_NOT==FEVarTypeVVGet(v))
#define FEVARTYPEVALUE_ISNULL(v) \
    (FEVARTYPE_MEM_VV_NULL==FEVarTypeVVGet(v))
#define FEVARTYPEVALUE_ISSET(v) \
    (FEVARTYPE_MEM_VV_VALUE==FEVarTypeVVGet(v))
BYTE  FEVarTypeVVGet(void *v);
void  FEVarTypeVVSetNot(void *v);
void  FEVarTypeVVSetNull(void *v);
void  FEVarTypeVVSetValue(void *v);

void  FEVarTypeNShow1(void *Var,INT32 T,void *Buf);
void  FEVarTypeNShow2(void *Var,INT32 T,void *Buf);

#define FEVARTYPE_INFO_LEN      0
BOOL  FEVarTypePack(void *Buf,void *v,INT32 PL,void *PackInfo);
INT32 FEVarTypeUnPack(INT32 *PL,tFEVarType *VarType,void *Buf,INT32 P);
BOOL  FEVarTypeUnPackSetType(void *Var,tFEVarType *VarType);

BYTE  FEVarTypeVTGet(void *v);
INT32 FEVarTypeVTSet(void *v,const BYTE vt);

#define FEVARTYPEENDIAN_ISBIG(v)        \
    (FEVARTYPE_MEM_ED_BIG==FEVarTypeEDGet(v))
#define FEVARTYPEENDIAN_ISLOW(v)        \
    (FEVARTYPE_MEM_ED_LITTLE==FEVarTypeEDGet(v))
BYTE  FEVarTypeEDGet(void *v);
void  FEVarTypeEDSetBig(void *v);
void  FEVarTypeEDSetLittle(void *v);

BYTE  FEVarTypeSLGet(void *v);
void  FEVarTypeSLSet(void *v,BYTE L);
INT32 FEVarTypeDPGetInt(void *v);
INT32 FEVarTypeDPGetDec(void *v);
BOOL  FEVarTypeDPSet(void *v,INT32 Int,INT32 Dec);
BOOL  FEVarTypeDPSet2(void *v,BYTE dp);

void *FEVarTypeResGet(void *v);
void *FEVarTypeResGetFree(void *v);
void *FEVarTypeResGetShow(void *v);
BOOL  FEVarTypeResSet(void *v,void *res);
BOOL  FEVarTypeResSetClone(void *v,void *Clone);
BOOL  FEVarTypeResSetFree(void *v,void *Free);
BOOL  FEVarTypeResSetShow(void *v,void *Show);
void  FEVarTypeResDelete(void *v);
BOOL  FEVarTypeResMove(void *v,void *v2);
void  FEVarTypeResShow(void *v,INT32 T,void *Buf);
BOOL  FEVarTypeResClone(void *v,void *v2);

INT32 FEVarTypeKeyGetLen(void *v);
void *FEVarTypeKeyGet(void *v);
void  FEVarTypeKeyDelete(void *v);
void  FEVarTypeKeyDelete2(void *v);
BOOL  FEVarTypeKeySet(void *v,void *Key,INT32 KS,INT32 KL);
BOOL  FEVarTypeKeyMove(void *v,void *v2);
BOOL  FEVarTypeKeyCat(void *v,const char *Key,INT32 Len);
BOOL  FEVarTypeKeyCpy(void *v,const char *Key,INT32 Len);
BOOL  FEVarTypeKeyReplace(void *v,const char *Key,INT32 Len);
BOOL  FEVarTypeKeyCmp(void *v,const char *Key,INT32 Len);
void  FEVarTypeKeyShow(void *v,INT32 T,void *Buf);
BOOL  FEVarTypeKeyPack(void *v,void *Buf);
INT32 FEVarTypeKeyUnPack(tFEVarType *VarType,void *Buf,INT32 P);
BOOL  FEVarTypeKeyClone(void *Dest,void *Src);

void *FEVarTypeFuncGetClone(void *v);
void *FEVarTypeFuncGetFree(void *v);
void *FEVarTypeFuncGetShow(void *v);
void *FEVarTypeFuncGetPack(void *v);
BOOL  FEVarTypeFuncSet(void *v,void *Clone,void *Free,void *Show,void *Pack);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- Pointer4                                                      **/
/***************************************************************************/
typedef struct tFEVarPointer4
{
    FEVARTYPE_MEM;
    UCHAR A[8];
    void *P[4];
}tFEVarPointer4;
#define FEVARP4_ST_SIZE               (sizeof(tFEVarPointer4))
#define FEVARP4_MEM_A(v)              (((tFEVarPointer4*)(v))->A)
#define FEVARP4_MEM_V(v,IDX)          (((tFEVarPointer4*)(v))->P[IDX])
#define FEVARP4_IDX_IS(IDX)   \
    FERTN_CMPBOOL((0<=(IDX))||(4>(IDX)))
#define FEVARP4_TYPE_IS(v) \
   ( (FEVARTYPE_MEM_VT_P1==(v))||(FEVARTYPE_MEM_VT_P2==(v)) \
   ||(FEVARTYPE_MEM_VT_P3==(v))||(FEVARTYPE_MEM_VT_P4==(v)) )

void *FEVarPointer4New();
void  FEVarPointer4Free(void *Var);
void  FEVarPointer4NFree(void *Var);
void  FEVarPointer4VFree(void *Var);
BOOL  FEVarPointer4Init(void *Var,INT32 Num);
void  FEVarPointer4Show(void *Var,INT32 T,void *Buf);
#define FEVarPointer4NShow1 FEVarTypeNShow1
#define FEVarPointer4NShow2 FEVarTypeNShow2
void  FEVarPointer4VShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarPointer4IsFlag(void *Var,INT32 IDX);
BOOL  FEVarPointer4SetFlag(void *Var,INT32 IDX);
BOOL  FEVarPointer4ClearFlag(void *Var,INT32 IDX);

BOOL  FEVarPointer4SetP(void *Var,INT32 IDX,void *Value);
void *FEVarPointer4GetP(void *Var,INT32 IDX);
BOOL  FEVarPointer4SetP0(void *Var,void *Value);
void *FEVarPointer4GetP0(void *Var);
BOOL  FEVarPointer4SetP1(void *Var,void *Value);
void *FEVarPointer4GetP1(void *Var);
BOOL  FEVarPointer4SetP2(void *Var,void *Value);
void *FEVarPointer4GetP2(void *Var);
BOOL  FEVarPointer4SetP3(void *Var,void *Value);
void *FEVarPointer4GetP3(void *Var);

void *FEVarPointer4Clone(void *Var);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- SType                                                         **/
/**      SType      :  0  1  2  3  4  5  6  7                             **/
/**     VarByte     :  V                                                  **/
/**     VarInt16    :  V  V                                               **/
/**     VarInt32    :  V  V  V  V                                         **/
/**     VarInt64    :  V  V  V  V  V  V  V  V                             **/
/**     VarDouble   :  V  V  V  V  V  V  V  V                             **/
/***************************************************************************/
typedef struct tagFEVarSType
{
    FEVARTYPE_MEM;
    UCHAR   V[BUFSIZE_8];   
}tFEVarSType;
#define FEVARSTYPE_ST_SIZE           (sizeof(tFEVarSType))
#define FEVARSTYPE_MEM_V(v)          (((tFEVarSType*)(v))->V)
#define FEVARSTYPE_MEM_V_SIZE(v)     (sizeof(FEVARSTYPE_MEM_V(v)))
void *FEVarSTypeNew(BYTE VT);
void  FEVarSTypeFree(void *Var);
void  FEVarSTypeNFree(void *Var);
void  FEVarSTypeShow(void *Var,INT32 T,void *Buf);
#define FEVarSTypeNShow1   FEVarTypeNShow1
#define FEVarSTypeNShow2   FEVarTypeNShow2
void  FEVarSTypeVShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarSTypePack(void *Var,void *Buf);
INT32 FEVarSTypeUnPack(void **Var,void *Buf,INT32 P);

BOOL  FEVarSTypeInit(void *Var,BYTE VT);
BOOL  FEVarSTypeIsSType(void *Var);
void *FEVarSTypeGet(void *Var);
BOOL  FEVarSTypeSet(void *Var,void *V,INT32 LEN);
void *FEVarSTypeClone(void *Var);

BOOL  FEVarDoublePackInfo(void *Var,void *Buf);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- Bin                                                           **/
/***************************************************************************/
void  FEVarBinNFree(void *Var);
void  FEVarBinVFree(void *Var);
#define FEVarBinNShow1   FEVarTypeNShow1
#define FEVarBinNShow2   FEVarTypeNShow2
void  FEVarBinVShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarBinInit(void *Var);
BOOL  FEVarBinRealloc(void *Var,INT32 L);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- String                                                        **/
/***************************************************************************/
void  FEVarStringNFree(void *Var);
void  FEVarStringVFree(void *Var);
#define FEVarStringNShow1   FEVarTypeNShow1
#define FEVarStringNShow2   FEVarTypeNShow2
void  FEVarStringVShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarStringInit(void *Var);
BOOL  FEVarStringRealloc(void *Var,INT32 L);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- Object                                                        **/
/***************************************************************************/
#define FEVarObjectIsType(Var) \
    ( FEVARTYPE_MEM_VT_OBJECT==FEVarTypeVTGet(Var) )
void  FEVarObjectNFree(void *Var);
void  FEVarObjectVFree(void *Var);
#define FEVarObjectNShow1       FEVarTypeNShow1
#define FEVarObjectNShow2       FEVarTypeNShow2
void  FEVarObjectVShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarObjectInit(void *Var);
/***************************************************************************/
/***************************************************************************/
 
/***************************************************************************/
/**  Var -- Root                                                          **/
/***************************************************************************/
void *FEVarRootNew();
void  FEVarRootFree(void *Var);
void  FEVarRootShow(void *Var,INT32 T,void *Buf);
void  FEVarRootNShow1(void *Var,INT32 T,void *Buf);
#define FEVarRootNShow2     FEVarTypeNShow2
BOOL  FEVarRootIsEmpty(void *Var);
BOOL  FEVarRootIsFull(void *Var);
BOOL  FEVarRootIsAdd(void *Var);
BOOL  FEVarRootCanAdd(void *Var);
BOOL  FEVarRootSetMax(void *Var,INT32 Max);
INT32 FEVarRootGetMax(void *Var);
BOOL  FEVarRootSetSize(void *Var,INT32 Size);
INT32 FEVarRootGetSize(void *Var);
BOOL  FEVarRootSetLen(void *Var,INT32 Len);
BOOL  FEVarRootAddLen(void *Var,BOOL Flag);
INT32 FEVarRootGetLen(void *Var);
BOOL  FEVarRootSetPushIdx(void *Var,INT32 PushIdx);
INT32 FEVarRootGetPushIdx(void *Var);
BOOL  FEVarRootSetPopIdx(void *Var,INT32 PopIdx);
INT32 FEVarRootGetPopIdx(void *Var);
BOOL  FEVarRootSetUserLen(void *Var,INT32 UserLen);
BOOL  FEVarRootPlusUserLen(void *Var,BOOL Flag);
INT32 FEVarRootGetUserLen(void *Var);
BOOL  FEVarRootSetUserCnt(void *Var,INT32 UserCnt);
BOOL  FEVarRootPlusUserCnt(void *Var,BOOL Flag);
INT32 FEVarRootGetUserCnt(void *Var);
BOOL  FEVarRootSetValue(void *Var,void *Value);
void *FEVarRootGetValue(void *Var);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- Array                                                         **/
/***************************************************************************/
#define FEVARARRAY_NODE_P_NUM       1
void  FEVarArrayNFree(void *Var);
void  FEVarArrayVFree(void *Var);
#define FEVarArrayNShow1    FEVarRootNShow1
#define FEVarArrayNShow2    FEVarRootNShow2
void  FEVarArrayVShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarArrayPackInfo(void *Var,void *Buf);
BOOL  FEVarArrayRealloc(void *Var,INT32 S);
void  FEVarArrayInitPointer(void *Var);
void *FEVarArrayGetNode(void *Var,INT32 Idx);
BOOL  FEVarArrayMove(void *Var,INT32 Src,INT32 Len);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- Fifo                                                          **/
/***************************************************************************/
#define FEVarFifoIsType(Var) \
    ( FEVARTYPE_MEM_VT_FIFO==FEVarTypeVTGet(Var) )
#define FEVARFIFO_NODE_P_NUM        1
#define FEVARFIFO_UNIT_MIN          FEVARARRAY_UNIT_MIN
void  FEVarFifoNFree(void *Var);
void  FEVarFifoVFree(void *Var);
#define FEVarFifoNShow1    FEVarRootNShow1
#define FEVarFifoNShow2    FEVarRootNShow2
void  FEVarFifoVShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarFifoRealloc(void *Var,INT32 S);
void  FEVarFifoInitPointer(void *Var);
void *FEVarFifoGetNode(void *Var,INT32 Idx);
BOOL  FEVarFifoMove(void *Var);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- Filo                                                          **/
/***************************************************************************/
#define FEVarFiloIsType(Var) \
    ( FEVARTYPE_MEM_VT_FILO==FEVarTypeVTGet(Var) )
#define FEVARFILO_NODE_P_NUM        1
#define FEVARFILO_UNIT_MIN          FEVARARRAY_UNIT_MIN
void  FEVarFiloNFree(void *Var);
void  FEVarFiloVFree(void *Var);
#define FEVarFiloNShow1    FEVarRootNShow1
#define FEVarFiloNShow2    FEVarRootNShow2
void  FEVarFiloVShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarFiloRealloc(void *Var,INT32 S);
void  FEVarFiloInitPointer(void *Var);
void *FEVarFiloGetNode(void *Var,INT32 Idx);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- Link                                                          **/
/***************************************************************************/
#define FEVarLinkIsType(Var) \
    ( FEVARTYPE_MEM_VT_Link==FEVarTypeVTGet(Var) )
#define FEVARLINK_NODE_P_NUM        3
void  FEVarLinkNFree(void *Var);
void  FEVarLinkVFree(void *Var);
#define FEVarLinkNShow1    FEVarRootNShow1
#define FEVarLinkNShow2    FEVarRootNShow2
void  FEVarLinkVShow(void *Var,INT32 T,void *Buf);
void  FEVarLinkInitPointer(void *Var);
BOOL  FEVarLinkDeleteNode(void *Var,void *Node);
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  Var -- Hash                                                          **/
/***************************************************************************/
#define FEVARHASH_NODE_P_NUM_ARRAY  1
void *FEVarHashNewFunc(INT32 Size,void *VVar);
void  FEVarHashNFree(void *Var);
void  FEVarHashVFree(void *Var);
void  FEVarHashNShow1(void *Var,INT32 T,void *Buf);
#define FEVarHashNShow2    FEVarTypeNShow2
void  FEVarHashVShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarHashPackInfo(void *Var,void *Buf);
BOOL  FEVarHashVPack(void *Var,void *Buf);
void  FEVarHashInitPointer(void *VP);
BOOL  FEVarHashInitLink(void *VP);
void *FEVarHashGetLink(void *Var,const void *Key,INT32 Len);
BOOL  FEVarHashCloneLink(void *VP,void *VVP);
/***************************************************************************/
/***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VARIANT_H__ */ 

