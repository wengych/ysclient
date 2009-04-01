/***************************************************************************/
/**[File Name    ]fevar.h                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define common for fevar                                 **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef FEVAR_H__
#define FEVAR_H__

#include <fecom.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/** var --byte,int16,int32,int64,double,bin,string                         **/
/****************************************************************************/
void  FEVarToolsInitBuf(char *Buf,INT32 Size,INT32 Len,UCHAR ch);
#define FEVarToolsInitBufSpace(Buf,Size,Len) \
    FEVarToolsInitBuf((Buf),(Size),(Len),CHAR_SPACE)
 
BYTE  FEVarTypeInfoGetVT(const char *Name);
char *FEVarTypeInfoGetName(const BYTE VT);
BOOL  FEVarTypeInfoIs(const BYTE VT);
BOOL  FEVarTypeInfoIsName(const char *Name);

void  FEVarFree(void *Var);
void  FEVarShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarPack(void *Var,void *Buf);
INT32 FEVarUnPack(void **VVar,void *Buf,INT32 P);
BOOL  FEVarIsInit(void *Var);
BOOL  FEVarIsInit2(void *v,INT32 VT);
INT32 FEVarGetType(void *Var);

void *FEVarGetRes(void *Var);
BOOL  FEVarSetRes(void *Var,void *Res,void *Clone,void *Free,void *Show);
BOOL  FEVarMoveRes(void *NVar,void *OVar);

INT32 FEVarGetKeyLen(void *Var);
char *FEVarGetKey(void *Var);
BOOL  FEVarCatKey(void *Var,const void *Key,INT32 Len);
BOOL  FEVarCpyKey(void *Var,const void *Key,INT32 Len);
BOOL  FEVarReplaceKey(void *Var,const void *Key,INT32 Len);
BOOL  FEVarCmpKey(void *Var,const void *Key,INT32 Len);
void  FEVarDeleteKey(void *Var);
BOOL  FEVarMoveKey(void *Dest,void *Src);
BOOL  FEVarCloneKey(void *Dest,void *Src);

void *FEVarGetFuncClone(void *v);
void *FEVarGetFuncFree(void *v);
void *FEVarGetFuncShow(void *v);
void *FEVarGetFuncPack(void *v);
BOOL  FEVarSetFunc(void *v,void *Clone,void *Free,void *Show,void *Pack);

void *FEVarClone(void *Var);
BOOL  FEVarCloneValue(void *NVar,void *OVar);
BOOL  FEVarDeleteValue(void *Var);
 
void *FEVarBoolNew();
void  FEVarBoolFree(void *Var);
BOOL  FEVarBoolGet(void *Var,BOOL *V);
BOOL  FEVarBoolSet(void *Var,BOOL V);
void *FEVarBoolSave(BOOL V);
void *FEVarBoolSave2(const char *Key,BOOL V);
void *FEVarBoolClone(void *Var);
 
void *FEVarByteNew();
void  FEVarByteFree(void *Var);
BOOL  FEVarByteGet(void *Var,BYTE *V);
BOOL  FEVarByteSet(void *Var,BYTE V);
void *FEVarByteSave(BYTE V);
void *FEVarByteSave2(const char *Key,BYTE V);
void *FEVarByteClone(void *Var);
 
void *FEVarInt16New();
void  FEVarInt16Free(void *Var);
BOOL  FEVarInt16Get(void *Var,INT16 *V);
BOOL  FEVarInt16Set(void *Var,INT16 V);
void *FEVarInt16Save(INT16 V);
void *FEVarInt16Save2(const char *Key,INT16 V);
void *FEVarInt16Clone(void *Var);
 
void *FEVarInt32New();
void  FEVarInt32Free(void *Var);
BOOL  FEVarInt32Get(void *Var,INT32 *V);
BOOL  FEVarInt32Set(void *Var,INT32 V);
void *FEVarInt32Save(INT32 V);
void *FEVarInt32Save2(const char *Key,INT32 V);
void *FEVarInt32Clone(void *Var);
 
void *FEVarInt64New();
void  FEVarInt64Free(void *Var);
BOOL  FEVarInt64Get(void *Var,INT64 *V);
BOOL  FEVarInt64Set(void *Var,INT64 V);
void *FEVarInt64Save(INT64 V);
void *FEVarInt64Save2(const char *Key,INT64 V);
void *FEVarInt64Clone(void *Var);
 
void *FEVarDoubleNew();
void  FEVarDoubleFree(void *Var);
BOOL  FEVarDoubleGet(void *Var,DOUBLE *V);
BOOL  FEVarDoubleSet(void *Var,DOUBLE V);
INT32 FEVarDoubleGetDPInt(void *Var);
INT32 FEVarDoubleGetDPDec(void *Var);
BOOL  FEVarDoubleSetDP(void *Var,INT32 Int,INT32 Dec);
BOOL  FEVarDoubleSetDP2(void *Var,BYTE DP);
void *FEVarDoubleSave(DOUBLE V);
void *FEVarDoubleSave2(const char *Key,DOUBLE V);
void *FEVarDoubleClone(void *Var);

void *FEVarBinNew();
void *FEVarBinNew2(INT32 Size);
void  FEVarBinFree(void *Var);
void  FEVarBinShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarBinPack(void *Var,void *Buf);
INT32 FEVarBinUnPack(void **VVar,void *Buf,INT32 P);
void  FEVarBinDelete(void *Var);
BOOL  FEVarBinClear(void *Var);
void  FEVarBinReset(void *Var);
void  FEVarBinCut(void *Var,INT32 S,INT32 L);
INT32 FEVarBinGetSize(void *Var);
BOOL  FEVarBinSetLen(void *Var,INT32 Len);
INT32 FEVarBinGetLen(void *Var);
void *FEVarBinGet(void *Var);
BOOL  FEVarBinGet2(void *Var,void *V,INT32 *L,INT32 S);
BOOL  FEVarBinMalloc(void *Var,INT32 L);
BOOL  FEVarBinCat(void *Var,void *V,INT32 L);
BOOL  FEVarBinCpy(void *Var,void *V,INT32 L);
void *FEVarBinSave(void *V,INT32 L);
void *FEVarBinSave2(const char *Key,void *V,INT32 L);
void *FEVarBinClone(void *Var);

void *FEVarStringNew();
void *FEVarStringNew2(INT32 Size);
void  FEVarStringFree(void *Var);
void  FEVarStringShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarStringPack(void *Var,void *Buf);
INT32 FEVarStringUnPack(void **VVar,void *Buf,INT32 P);
void  FEVarStringDelete(void *Var);
BOOL  FEVarStringClear(void *Var);
void  FEVarStringReset(void *Var);
void  FEVarStringCut(void *Var,INT32 S,INT32 L);
INT32 FEVarStringGetSize(void *Var);
BOOL  FEVarStringSetLen(void *Var,INT32 Len);
INT32 FEVarStringGetLen(void *Var);
void *FEVarStringGet(void *Var);
BOOL  FEVarStringGet2(void *Var,void *V,INT32 *L,INT32 S);
BOOL  FEVarStringMalloc(void *Var,INT32 L);
BOOL  FEVarStringCat(void *Var,void *V,INT32 L);
BOOL  FEVarStringCpy(void *Var,void *V,INT32 L);
#define FEVarStringCatUTF8 FEVarStringCat
#define FEVarStringCpyUTF8 FEVarStringCpy
BOOL  FEVarStringCatUni(void *Var,void *V,INT32 L);
BOOL  FEVarStringCpyUni(void *Var,void *V,INT32 L);
BOOL  FEVarStringCatGbk(void *Var,void *V,INT32 L);
BOOL  FEVarStringCpyGbk(void *Var,void *V,INT32 L);
void *FEVarStringSave(void *V,INT32 L);
void *FEVarStringSave2(const char *Key,void *V,INT32 L);
void *FEVarStringClone(void *Var);

void *FEVarObjectNew();
void  FEVarObjectFree(void *Var);
void  FEVarObjectShow(void *Var,INT32 T,void *Buf);
void *FEVarObjectGet(void *Var);
BOOL  FEVarObjectGet2(void *Var,void **V);
void *FEVarObjectGetVClone(void *Var);
void *FEVarObjectGetVFree(void *Var);
void *FEVarObjectGetVShow(void *Var);
void *FEVarObjectGetVPack(void *Var);
BOOL  FEVarObjectSet(void *Var,void *V);
BOOL  FEVarObjectSetFuncVClone(void *Var,void *VNew);
BOOL  FEVarObjectSetFuncVFree(void *Var,void *VFree);
BOOL  FEVarObjectSetFuncVShow(void *Var,void *VShow);
BOOL  FEVarObjectSetFuncVPack(void *Var,void *VPack);
void *FEVarObjectSave(void *V,void *Clone,void *Free,void *Show,void *Pack);
void *FEVarObjectSave2(const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack);
void *FEVarObjectClone(void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- array                                                           **/
/****************************************************************************/
void *FEVarArrayNew(INT32 Max);
void *FEVarArrayNew_Key(INT32 Max,const char *Key);
void *FEVarArrayNew2(INT32 Max);
void *FEVarArrayNew2_Key(INT32 Max,const char *Key);
void  FEVarArrayFree(void *Var);
void  FEVarArrayShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarArrayPack(void *Var,void *Buf);
INT32 FEVarArrayUnPack(void **VVar,void *Buf,INT32 P);
BOOL  FEVarArrayIsEmpty(void *Var);
BOOL  FEVarArrayIsFull(void *Var);
BOOL  FEVarArraySetMax(void *Var,INT32 Max);
INT32 FEVarArrayGetMax(void *Var);
INT32 FEVarArrayGetSize(void *Var);
INT32 FEVarArrayGetLen(void *Var);
BOOL  FEVarArraySetUserLen(void *Var,INT32 UserLen);
BOOL  FEVarArrayPlusUserLen(void *Var,BOOL Flag);
INT32 FEVarArrayGetUserLen(void *Var);
BOOL  FEVarArraySetUserCnt(void *Var,INT32 UserCnt);
BOOL  FEVarArrayPlusUserCnt(void *Var,BOOL Flag);
INT32 FEVarArrayGetUserCnt(void *Var);
BOOL  FEVarArrayIsIdxOfValue(void *Var,INT32 Idx);
BOOL  FEVarArrayIsIdxOfRange(void *Var,INT32 Idx);
BOOL  FEVarArrayAdd(void *Var,void *V);
BOOL  FEVarArrayInsert(void *Var,INT32 Idx,void *V);
BOOL  FEVarArrayReplace(void *Var,INT32 Idx,void *V);
BOOL  FEVarArrayReplaceValue(void *Var,INT32 Idx,void *V);
BOOL  FEVarArrayDelete(void *Var,INT32 Idx);
void *FEVarArrayGet(void *Var,INT32 Idx);
BOOL  FEVarArrayGet2(void *Var,INT32 Idx,void **V);

INT32 FEVarArrayGetIdxByKey(void *Var,const void *Key,INT32 Len);
void *FEVarArrayGetNodeByKey(void *Var,const void *Key,INT32 Len);
void *FEVarArrayGetByKey(void *Var,const void *Key,INT32 Len);
BOOL  FEVarArrayGet2ByKey(void *Var,const void *Key,INT32 Len,void **V);
BOOL  FEVarArrayInsertByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  FEVarArrayReplaceByKey(void *Var,void *V);
BOOL  FEVarArrayReplaceValueByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  FEVarArrayDeleteByKey(void *Var,const void *Key,INT32 Len);

void *FEVarArrayClone(void *Var);
BOOL  FEVarArrayCloneValue(void *N,void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- FIFO                                                            **/
/****************************************************************************/
void *FEVarFifoNew(INT32 Max);
void *FEVarFifoNew_Key(INT32 Max,const char *Key);
void *FEVarFifoNew2(INT32 Max);
void *FEVarFifoNew2_Key(INT32 Max,const char *Key);
void  FEVarFifoFree(void *Var);
void  FEVarFifoShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarFifoIsEmpty(void *Var);
BOOL  FEVarFifoIsFull(void *Var);
BOOL  FEVarFifoSetMax(void *Var,INT32 Max);
INT32 FEVarFifoGetMax(void *Var);
INT32 FEVarFifoGetLen(void *Var);
BOOL  FEVarFifoIsIdxOfValue(void *Var,INT32 Idx);
BOOL  FEVarFifoIsIdxOfRange(void *Var,INT32 Idx);
BOOL  FEVarFifoPush(void *Var,void *V);
BOOL  FEVarFifoPop(void *Var,void **V);
void *FEVarFifoGet(void *Var,INT32 Idx);
BOOL  FEVarFifoGet2(void *Var,INT32 Idx,void **V);
BOOL  FEVarFifoReplace(void *Var,INT32 Idx,void *V);
BOOL  FEVarFifoReplaceValue(void *Var,INT32 Idx,void *V);

void *FEVarFifoClone(void *Var);
BOOL  FEVarFifoCloneValue(void *N,void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- FILO                                                            **/
/****************************************************************************/
void *FEVarFiloNew(INT32 Max);
void *FEVarFiloNew_Key(INT32 Max,const char *Key);
void *FEVarFiloNew2(INT32 Max);
void *FEVarFiloNew2_Key(INT32 Max,const char *Key);
void  FEVarFiloFree(void *Var);
void  FEVarFiloShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarFiloIsEmpty(void *Var);
BOOL  FEVarFiloIsFull(void *Var);
BOOL  FEVarFiloSetMax(void *Var,INT32 Max);
INT32 FEVarFiloGetMax(void *Var);
INT32 FEVarFiloGetLen(void *Var);
BOOL  FEVarFiloIsIdxOfValue(void *Var,INT32 Idx);
BOOL  FEVarFiloIsIdxOfRange(void *Var,INT32 Idx);
BOOL  FEVarFiloPush(void *Var,void *V);
BOOL  FEVarFiloPop(void *Var,void **V);
void *FEVarFiloGet(void *Var,INT32 Idx);
BOOL  FEVarFiloGet2(void *Var,INT32 Idx,void **V);
BOOL  FEVarFiloReplace(void *Var,INT32 Idx,void *V);
BOOL  FEVarFiloReplaceValue(void *Var,INT32 Idx,void *V);

void *FEVarFiloClone(void *Var);
BOOL  FEVarFiloCloneValue(void *N,void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- link                                                            **/
/****************************************************************************/
void *FEVarLinkNew(INT32 Max);
void *FEVarLinkNew_Key(INT32 Max,const char *Key);
void  FEVarLinkFree(void *Var);
void  FEVarLinkShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarLinkIsEmpty(void *Var);
BOOL  FEVarLinkIsFull(void *Var);
INT32 FEVarLinkSetMax(void *Var,INT32 Max);
INT32 FEVarLinkGetMax(void *Var);
INT32 FEVarLinkGetLen(void *Var);
BOOL  FEVarLinkIsIdxOfValue(void *Var,INT32 Idx);
BOOL  FEVarLinkIsIdxOfRange(void *Var,INT32 Idx);
void *FEVarLinkGetNode(void *Var,INT32 Idx);
void *FEVarLinkGet(void *Var,INT32 Idx);
BOOL  FEVarLinkGet2(void *Var,INT32 Idx,void **V);
BOOL  FEVarLinkAdd(void *Var,void *V);
BOOL  FEVarLinkInsert(void *Var,INT32 Idx,void *V);
BOOL  FEVarLinkReplace(void *Var,INT32 Idx,void *V);
BOOL  FEVarLinkReplaceValue(void *Var,INT32 Idx,void *V);
BOOL  FEVarLinkDelete(void *Var,INT32 Idx);

INT32 FEVarLinkGetIdxByKey(void *Var,const void *Key,INT32 Len);
void *FEVarLinkGetNodeByKey(void *Var,const void *Key,INT32 Len);
void *FEVarLinkGetByKey(void *Var,const void *Key,INT32 Len);
BOOL  FEVarLinkGet2ByKey(void *Var,const void *Key,INT32 Len,void **V);
BOOL  FEVarLinkInsertByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  FEVarLinkReplaceByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  FEVarLinkReplaceValueByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  FEVarLinkDeleteByKey(void *Var,const void *Key,INT32 Len);

void *FEVarLinkClone(void *Var);
BOOL  FEVarLinkCloneValue(void *N,void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- hash                                                            **/
/****************************************************************************/
void *FEVarHashNew(INT32 Size);
void *FEVarHashNew_Key(INT32 Size,const char *Key);
void  FEVarHashFree(void *Var);
void  FEVarHashShow(void *Var,INT32 T,void *Buf);
BOOL  FEVarHashPack(void *Var,void *Buf);
INT32 FEVarHashUnPack(void **VVar,void *Buf,INT32 P);
BOOL  FEVarHashIsEmpty(void *Var);
INT32 FEVarHashGetLen(void *Var);
void *FEVarHashGetNode(void *Var,const void *Key,INT32 Len);
void *FEVarHashGet(void *Var,const void *Key,INT32 Len);
BOOL  FEVarHashGet2(void *Var,const void *Key,INT32 Len,void **V);
BOOL  FEVarHashAdd(void *Var,void *V);
BOOL  FEVarHashReplace(void *Var,void *V);
BOOL  FEVarHashReplaceValue(void *Var,const void *Key,INT32 Len,void *V);
BOOL  FEVarHashDelete(void *Var,const void *Key,INT32 Len);
void *FEVarHashClone(void *Var);
BOOL  FEVarHashCloneValue(void *NVar,void *OVar);
/****************************************************************************/
/****************************************************************************/

BOOL  FEPackFuncBool(void *Buf,BOOL v);
BOOL  FEPackFuncByte(void *Buf,BYTE v);
BOOL  FEPackFuncInt16(void *Buf,INT16 v);
BOOL  FEPackFuncInt32(void *Buf,INT32 v);
BOOL  FEPackFuncInt64(void *Buf,INT64 v);
BOOL  FEPackFuncDouble(void *Buf,DOUBLE v,BYTE DP);
BOOL  FEPackFuncString(void *Buf,char *v,INT32 L);

BOOL  FEUnPackFuncBool(void *Buf,INT32 P,BOOL *v);
BOOL  FEUnPackFuncByte(void *Buf,INT32 P,BYTE *v);
BOOL  FEUnPackFuncInt16(void *Buf,INT32 P,INT16 *v);
BOOL  FEUnPackFuncInt32(void *Buf,INT32 P,INT32 *v);
BOOL  FEUnPackFuncInt64(void *Buf,INT32 P,INT64 *v);
BOOL  FEUnPackFuncDouble(void *Buf,INT32 P,DOUBLE *v,BYTE *DP);
BOOL  FEUnPackFuncString(void *Buf,INT32 P,INT32 L,char *v);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FEVAR_H__ */ 

