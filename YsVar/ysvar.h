/***************************************************************************/
/**[File Name    ]ysvar.h                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define common for ysvar                                 **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef YSVAR_H__
#define YSVAR_H__

#include <fecom.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/** var --byte,int16,int32,int64,double,bin,string                         **/
/****************************************************************************/
#define YSVarToolsInitBuf FEVarToolsInitBuf
#define YSVarToolsInitBufSpace(Buf,Size,Len) \
    FEVarToolsInitBufSpace((Buf),(Size),(Len))
 
BYTE  YSVarTypeInfoGetVT(const char *Name);
char *YSVarTypeInfoGetName(const BYTE VT);
BOOL  YSVarTypeInfoIs(const BYTE VT);
BOOL  YSVarTypeInfoIsName(const char *Name);

void  YSVarFree(void *Var);
void  YSVarShow(void *Var,INT32 T,void *Buf);
BOOL  YSVarPack(void *Var,void *Buf);
INT32 YSVarUnPack(void **VVar,void *Buf,INT32 P);
BOOL  YSVarIsInit(void *Var);
BOOL  YSVarIsInit2(void *Var,INT32 VT);
INT32 YSVarGetType(void *Var);

void *YSVarGetRes(void *Var);
BOOL  YSVarSetRes(void *Var,void *Res,void *Clone,void *Free,void *Show);
BOOL  YSVarMoveRes(void *NVar,void *OVar);

INT32 YSVarGetKeyLen(void *Var);
char *YSVarGetKey(void *Var);
BOOL  YSVarCatKey(void *Var,const char *Key);
BOOL  YSVarCpyKey(void *Var,const char *Key);
BOOL  YSVarReplaceKey(void *Var,const char *Key);
BOOL  YSVarCmpKey(void *Var,const char *Key);
void  YSVarDeleteKey(void *Var);
BOOL  YSVarMoveKey(void *Dest,void *Src);
BOOL  YSVarCloneKey(void *Dest,void *Src);

void *YSVarGetFuncClone(void *v);
void *YSVarGetFuncFree(void *v);
void *YSVarGetFuncShow(void *v);
void *YSVarGetFuncPack(void *v);
BOOL  YSVarSetFunc(void *v,void *Clone,void *Free,void *Show,void *Pack);

void *YSVarClone(void *Var);
BOOL  YSVarCloneValue(void *NVar,void *OVar);
BOOL  YSVarDeleteValue(void *Var);
 
void *YSVarBoolNew();
void  YSVarBoolFree(void *Var);
BOOL  YSVarBoolGet(void *Var,BOOL *V);
BOOL  YSVarBoolSet(void *Var,BOOL V);
void *YSVarBoolSave(BOOL V);
void *YSVarBoolSave2(const char *Key,BOOL V);
void *YSVarBoolClone(void *Var);
 
void *YSVarByteNew();
void  YSVarByteFree(void *Var);
BOOL  YSVarByteGet(void *Var,BYTE *V);
BOOL  YSVarByteSet(void *Var,BYTE V);
void *YSVarByteSave(BYTE V);
void *YSVarByteSave2(const char *Key,BYTE V);
void *YSVarByteClone(void *Var);
 
void *YSVarInt16New();
void  YSVarInt16Free(void *Var);
BOOL  YSVarInt16Get(void *Var,INT16 *V);
BOOL  YSVarInt16Set(void *Var,INT16 V);
void *YSVarInt16Save(INT16 V);
void *YSVarInt16Save2(const char *Key,INT16 V);
void *YSVarInt16Clone(void *Var);
 
void *YSVarInt32New();
void  YSVarInt32Free(void *Var);
BOOL  YSVarInt32Get(void *Var,INT32 *V);
BOOL  YSVarInt32Set(void *Var,INT32 V);
void *YSVarInt32Save(INT32 V);
void *YSVarInt32Save2(const char *Key,INT32 V);
void *YSVarInt32Clone(void *Var);
 
void *YSVarInt64New();
void  YSVarInt64Free(void *Var);
BOOL  YSVarInt64Get(void *Var,INT64 *V);
BOOL  YSVarInt64Set(void *Var,INT64 V);
void *YSVarInt64Save(INT64 V);
void *YSVarInt64Save2(const char *Key,INT64 V);
void *YSVarInt64Clone(void *Var);
 
void *YSVarDoubleNew();
void  YSVarDoubleFree(void *Var);
BOOL  YSVarDoubleGet(void *Var,DOUBLE *V);
BOOL  YSVarDoubleSet(void *Var,DOUBLE V);
INT32 YSVarDoubleGetDPInt(void *Var);
INT32 YSVarDoubleGetDPDec(void *Var);
BOOL  YSVarDoubleSetDP(void *Var,INT32 Int,INT32 Dec);
void *YSVarDoubleSave(DOUBLE V);
void *YSVarDoubleSave2(const char *Key,DOUBLE V);
void *YSVarDoubleClone(void *Var);

void *YSVarBinNew();
void *YSVarBinNew2(INT32 Size);
void  YSVarBinFree(void *Var);
void  YSVarBinShow(void *Var,INT32 T,void *Buf);
BOOL  YSVarBinPack(void *Var,void *Buf);
INT32 YSVarBinUnPack(void **VVar,void *Buf,INT32 P);
void  YSVarBinDelete(void *Var);
BOOL  YSVarBinClear(void *Var);
void  YSVarBinReset(void *Var);
void  YSVarBinCut(void *Var,INT32 S,INT32 L);
INT32 YSVarBinGetSize(void *Var);
BOOL  YSVarBinSetLen(void *Var,INT32 Len);
INT32 YSVarBinGetLen(void *Var);
void *YSVarBinGet(void *Var);
BOOL  YSVarBinGet2(void *Var,void *V,INT32 *L,INT32 S);
BOOL  YSVarBinMalloc(void *Var,INT32 L);
BOOL  YSVarBinCat(void *Var,void *V,INT32 L);
BOOL  YSVarBinCpy(void *Var,void *V,INT32 L);
void *YSVarBinSave(void *V,INT32 L);
void *YSVarBinSave2(const char *Key,void *V,INT32 L);
void *YSVarBinClone(void *Var);

void *YSVarStringNew();
void *YSVarStringNew2(INT32 Size);
void  YSVarStringFree(void *Var);
void  YSVarStringShow(void *Var,INT32 T,void *Buf);
BOOL  YSVarStringPack(void *Var,void *Buf);
INT32 YSVarStringUnPack(void **VVar,void *Buf,INT32 P);
void  YSVarStringDelete(void *Var);
BOOL  YSVarStringClear(void *Var);
void  YSVarStringReset(void *Var);
void  YSVarStringCut(void *Var,INT32 S,INT32 L);
INT32 YSVarStringGetSize(void *Var);
BOOL  YSVarStringSetLen(void *Var,INT32 Len);
INT32 YSVarStringGetLen(void *Var);
void *YSVarStringGet(void *Var);
BOOL  YSVarStringGet2(void *Var,void *V,INT32 *L,INT32 S);
BOOL  YSVarStringMalloc(void *Var,INT32 L);
BOOL  YSVarStringCat(void *Var,void *V,INT32 L);
BOOL  YSVarStringCpy(void *Var,void *V,INT32 L);
void *YSVarStringSave(void *V,INT32 L);
void *YSVarStringSave2(const char *Key,void *V,INT32 L);
void *YSVarStringClone(void *Var);

void *YSVarObjectNew();
void  YSVarObjectFree(void *Var);
void  YSVarObjectShow(void *Var,INT32 T,void *Buf);
void *YSVarObjectGet(void *Var);
BOOL  YSVarObjectGet2(void *Var,void **V);
void *YSVarObjectGetVClone(void *Var);
void *YSVarObjectGetVFree(void *Var);
void *YSVarObjectGetVShow(void *Var);
void *YSVarObjectGetVPack(void *Var);
BOOL  YSVarObjectSet(void *Var,void *V);
BOOL  YSVarObjectSetFuncVClone(void *Var,void *VNew);
BOOL  YSVarObjectSetFuncVFree(void *Var,void *VFree);
BOOL  YSVarObjectSetFuncVShow(void *Var,void *VShow);
BOOL  YSVarObjectSetFuncVPack(void *Var,void *VPack);
void *YSVarObjectSave(void *V,void *Clone,void *Free,void *Show,void *Pack);
void *YSVarObjectSave2(const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack);
void *YSVarObjectClone(void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- array                                                           **/
/****************************************************************************/
void *YSVarArrayNew(INT32 Max);
void *YSVarArrayNew_Key(INT32 Max,const char *Key);
void *YSVarArrayNew2(INT32 Max);
void *YSVarArrayNew2_Key(INT32 Max,const char *Key);
void  YSVarArrayFree(void *Var);
void  YSVarArrayShow(void *Var,INT32 T,void *Buf);
BOOL  YSVarArrayPack(void *Var,void *Buf);
INT32 YSVarArrayUnPack(void **VVar,void *Buf,INT32 P);
BOOL  YSVarArrayIsEmpty(void *Var);
BOOL  YSVarArrayIsFull(void *Var);
BOOL  YSVarArraySetMax(void *Var,INT32 Max);
INT32 YSVarArrayGetMax(void *Var);
INT32 YSVarArrayGetSize(void *Var);
INT32 YSVarArrayGetLen(void *Var);
BOOL  YSVarArraySetUserLen(void *Var,INT32 UserLen);
BOOL  YSVarArrayPlusUserLen(void *Var,BOOL Flag);
INT32 YSVarArrayGetUserLen(void *Var);
BOOL  YSVarArraySetUserCnt(void *Var,INT32 UserCnt);
BOOL  YSVarArrayPlusUserCnt(void *Var,BOOL Flag);
INT32 YSVarArrayGetUserCnt(void *Var);
BOOL  YSVarArrayIsIdxOfValue(void *Var,INT32 Idx);
BOOL  YSVarArrayIsIdxOfRange(void *Var,INT32 Idx);
BOOL  YSVarArrayAdd(void *Var,void *V);
BOOL  YSVarArrayInsert(void *Var,INT32 Idx,void *V);
BOOL  YSVarArrayReplace(void *Var,INT32 Idx,void *V);
BOOL  YSVarArrayReplaceValue(void *Var,INT32 Idx,void *V);
BOOL  YSVarArrayDelete(void *Var,INT32 Idx);
void *YSVarArrayGet(void *Var,INT32 Idx);
BOOL  YSVarArrayGet2(void *Var,INT32 Idx,void **V);

INT32 YSVarArrayGetIdxByKey(void *Var,const void *Key,INT32 Len);
void *YSVarArrayGetByKey(void *Var,const void *Key,INT32 Len);
BOOL  YSVarArrayGet2ByKey(void *Var,const void *Key,INT32 Len,void **V);
BOOL  YSVarArrayInsertByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  YSVarArrayReplaceByKey(void *Var,void *V);
BOOL  YSVarArrayReplaceValueByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  YSVarArrayDeleteByKey(void *Var,const void *Key,INT32 Len);

void *YSVarArrayClone(void *Var);
BOOL  YSVarArrayCloneValue(void *N,void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- FIFO                                                            **/
/****************************************************************************/
void *YSVarFifoNew(INT32 Max);
void *YSVarFifoNew_Key(INT32 Max,const char *Key);
void *YSVarFifoNew2(INT32 Max);
void *YSVarFifoNew2_Key(INT32 Max,const char *Key);
void  YSVarFifoFree(void *Var);
void  YSVarFifoShow(void *Var,INT32 T,void *Buf);
BOOL  YSVarFifoIsEmpty(void *Var);
BOOL  YSVarFifoIsFull(void *Var);
BOOL  YSVarFifoSetMax(void *Var,INT32 Max);
INT32 YSVarFifoGetMax(void *Var);
INT32 YSVarFifoGetLen(void *Var);
BOOL  YSVarFifoIsIdxOfValue(void *Var,INT32 Idx);
BOOL  YSVarFifoIsIdxOfRange(void *Var,INT32 Idx);
BOOL  YSVarFifoPush(void *Var,void *V);
BOOL  YSVarFifoPop(void *Var,void **V);
void *YSVarFifoGet(void *Var,INT32 Idx);
BOOL  YSVarFifoGet2(void *Var,INT32 Idx,void **V);
BOOL  YSVarFifoReplace(void *Var,INT32 Idx,void *V);
BOOL  YSVarFifoReplaceValue(void *Var,INT32 Idx,void *V);
void *YSVarFifoClone(void *Var);
BOOL  YSVarFifoCloneValue(void *N,void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- FILO                                                            **/
/****************************************************************************/
void *YSVarFiloNew(INT32 Max);
void *YSVarFiloNew_Key(INT32 Max,const char *Key);
void *YSVarFiloNew2(INT32 Max);
void *YSVarFiloNew2_Key(INT32 Max,const char *Key);
void  YSVarFiloFree(void *Var);
void  YSVarFiloShow(void *Var,INT32 T,void *Buf);
BOOL  YSVarFiloIsEmpty(void *Var);
BOOL  YSVarFiloIsFull(void *Var);
BOOL  YSVarFiloSetMax(void *Var,INT32 Max);
INT32 YSVarFiloGetMax(void *Var);
INT32 YSVarFiloGetLen(void *Var);
BOOL  YSVarFiloIsIdxOfValue(void *Var,INT32 Idx);
BOOL  YSVarFiloIsIdxOfRange(void *Var,INT32 Idx);
BOOL  YSVarFiloPush(void *Var,void *V);
BOOL  YSVarFiloPop(void *Var,void **V);
void *YSVarFiloGet(void *Var,INT32 Idx);
BOOL  YSVarFiloGet2(void *Var,INT32 Idx,void **V);
BOOL  YSVarFiloReplace(void *Var,INT32 Idx,void *V);
BOOL  YSVarFiloReplaceValue(void *Var,INT32 Idx,void *V);

void *YSVarFiloClone(void *Var);
BOOL  YSVarFiloCloneValue(void *N,void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- link                                                            **/
/****************************************************************************/
void *YSVarLinkNew(INT32 Max);
void *YSVarLinkNew_Key(INT32 Max,const char *Key);
void  YSVarLinkFree(void *Var);
void  YSVarLinkShow(void *Var,INT32 T,void *Buf);
BOOL  YSVarLinkIsEmpty(void *Var);
BOOL  YSVarLinkIsFull(void *Var);
INT32 YSVarLinkSetMax(void *Var,INT32 Max);
INT32 YSVarLinkGetMax(void *Var);
INT32 YSVarLinkGetLen(void *Var);
BOOL  YSVarLinkIsIdxOfValue(void *Var,INT32 Idx);
BOOL  YSVarLinkIsIdxOfRange(void *Var,INT32 Idx);
void *YSVarLinkGet(void *Var,INT32 Idx);
BOOL  YSVarLinkGet2(void *Var,INT32 Idx,void **V);
BOOL  YSVarLinkAdd(void *Var,void *V);
BOOL  YSVarLinkInsert(void *Var,INT32 Idx,void *V);
BOOL  YSVarLinkReplace(void *Var,INT32 Idx,void *V);
BOOL  YSVarLinkReplaceValue(void *Var,INT32 Idx,void *V);
BOOL  YSVarLinkDelete(void *Var,INT32 Idx);

INT32 YSVarLinkGetIdxByKey(void *Var,const void *Key,INT32 Len);
void *YSVarLinkGetByKey(void *Var,const void *Key,INT32 Len);
BOOL  YSVarLinkGet2ByKey(void *Var,const void *Key,INT32 Len,void **V);
BOOL  YSVarLinkInsertByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  YSVarLinkReplaceByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  YSVarLinkReplaceValueByKey(void *Var,const void *Key,INT32 Len,void *V);
BOOL  YSVarLinkDeleteByKey(void *Var,const void *Key,INT32 Len);

void *YSVarLinkClone(void *Var);
BOOL  YSVarLinkCloneValue(void *N,void *Var);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** var -- hash                                                            **/
/****************************************************************************/
void *YSVarHashNew(INT32 Size);
void *YSVarHashNew_Key(INT32 Max,const char *Key);
void  YSVarHashFree(void *Var);
void  YSVarHashShow(void *Var,INT32 T,void *Buf);
BOOL  YSVarHashPack(void *Var,void *Buf);
INT32 YSVarHashUnPack(void **VVar,void *Buf,INT32 P);
BOOL  YSVarHashIsEmpty(void *Var);
INT32 YSVarHashGetLen(void *Var);
void *YSVarHashGet(void *Var,const char *Key);
BOOL  YSVarHashGet2(void *Var,const char *Key,void **V);
BOOL  YSVarHashAdd(void *Var,void *V);
BOOL  YSVarHashReplace(void *Var,void *V);
BOOL  YSVarHashReplaceValue(void *Var,const char *Key,void *V);
BOOL  YSVarHashDelete(void *Var,const char *Key);
void *YSVarHashClone(void *Var);
BOOL  YSVarHashCloneValue(void *NVar,void *OVar);
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef YSVAR_H__ */ 

