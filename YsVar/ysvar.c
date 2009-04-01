/***************************************************************************/
/**[File Name    ]ysvar.c                                                 **/
/**[File Path    ]$(SRCDIR)/libsrc/yscom                                  **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(HOME)/lib                                             **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/04/28                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for var                                     **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <ysvar.h>

#ifdef __cplusplus
extern "C"{
#endif

BYTE  YSVarTypeInfoGetVT(const char *Name)
{
    return FEVarTypeInfoGetVT(Name);
}

char *YSVarTypeInfoGetName(const BYTE VT)
{
    return FEVarTypeInfoGetName(VT);
}

BOOL  YSVarTypeInfoIs(const BYTE VT)
{
    return FEVarTypeInfoIs(VT);
}

BOOL  YSVarTypeInfoIsName(const char *Name)
{
    return FEVarTypeInfoIsName(Name);
}

void  YSVarFree(void *Var)
{
    FEVarFree(Var);
}

void  YSVarShow(void *Var,INT32 T,void *Buf)
{
    FEVarShow(Var,T,Buf);
}

BOOL  YSVarPack(void *Var,void *Buf)
{
    return FEVarPack(Var,Buf);
}

INT32 YSVarUnPack(void **VVar,void *Buf,INT32 P)
{
    return FEVarUnPack(VVar,Buf,P);
}

BOOL  YSVarIsInit(void *Var)
{
    return FEVarIsInit(Var);
}

BOOL  YSVarIsInit2(void *Var,INT32 VT)
{
    return FEVarIsInit2(Var,VT);
}

INT32 YSVarGetType(void *Var)
{
    return FEVarGetType(Var);
}

void *YSVarGetRes(void *Var)
{
    return FEVarGetRes(Var);
}

BOOL  YSVarSetRes(void *Var,void *Res,void *Clone,void *Free,void *Show)
{
    return FEVarSetRes(Var,Res,Clone,Free,Show);
}

BOOL  YSVarMoveRes(void *NVar,void *OVar)
{
    return FEVarMoveRes(NVar,OVar);
}

INT32  YSVarGetKeyLen(void *Var)
{
    return FEVarGetKeyLen(Var);
}

char *YSVarGetKey(void *Var)
{
    return FEVarGetKey(Var);
}

BOOL  YSVarCatKey(void *Var,const char *Key)
{
    if ( NULL==Key )
    {
        return TRUE;
    }
    return FEVarCatKey(Var,Key,strlen(Key));
}

BOOL  YSVarCpyKey(void *Var,const char *Key)
{
    if ( NULL==Key )
    {
        FEVarDeleteKey(Var);
        return TRUE;
    }
    return FEVarCpyKey(Var,Key,strlen(Key));
}

BOOL  YSVarReplaceKey(void *Var,const char *Key)
{
    if ( NULL==Key )
    {
        FEVarDeleteKey(Var);
        return TRUE;
    }
    return FEVarReplaceKey(Var,Key,strlen(Key));
}

BOOL  YSVarCmpKey(void *Var,const char *Key)
{
    if ( NULL==Key )
    {
        return FALSE;
    }
    return FEVarCmpKey(Var,Key,strlen(Key));
}

void  YSVarDeleteKey(void *Var)
{
    FEVarDeleteKey(Var);
}

BOOL  YSVarMoveKey(void *NVar,void *OVar)
{
    return FEVarMoveKey(NVar,OVar);
}

BOOL  YSVarCloneKey(void *NVar,void *OVar)
{
    return FEVarCloneKey(NVar,OVar);
}

void *YSVarGetFuncClone(void *Var)
{
    return FEVarGetFuncClone(Var);
}
 
void *YSVarGetFuncFree(void *Var)
{
    return FEVarGetFuncFree(Var);
}
 
void *YSVarGetFuncShow(void *Var)
{
    return FEVarGetFuncShow(Var);
}
 
void *YSVarGetFuncPack(void *Var)
{
    return FEVarGetFuncPack(Var);
}
 
BOOL  YSVarSetFunc(void *Var,void *Clone,void *Free,void *Show,void *Pack)
{
    return FEVarSetFunc(Var,Clone,Free,Show,Pack);
}
 
void *YSVarClone(void *Var)
{
    return FEVarClone(Var);
}

BOOL  YSVarCloneValue(void *NVar,void *OVar)
{
    return FEVarCloneValue(NVar,OVar);
}

BOOL  YSVarDeleteValue(void *Var)
{
    return FEVarDeleteValue(Var);
}

void *YSVarBoolNew()
{
    return FEVarBoolNew();
}

void  YSVarBoolFree(void *Var)
{
    FEVarBoolFree(Var);
}

BOOL  YSVarBoolGet(void *Var,BOOL *V)
{
    return FEVarBoolGet(Var,V);
}

BOOL  YSVarBoolSet(void *Var,BOOL V)
{
    return FEVarBoolSet(Var,V);
}

void *YSVarBoolSave(BOOL V)
{
    return FEVarBoolSave(V);
}

void *YSVarBoolSave2(const char *Key,BOOL V)
{
    return FEVarBoolSave2(Key,V);
}

void *YSVarBoolClone(void *Var)
{
    return FEVarBoolClone(Var);
}

void *YSVarByteNew()
{
    return FEVarByteNew();
}

void  YSVarByteFree(void *Var)
{
    FEVarByteFree(Var);
}

BOOL  YSVarByteGet(void *Var,BYTE *V)
{
    return FEVarByteGet(Var,V);
}

BOOL  YSVarByteSet(void *Var,BYTE V)
{
    return FEVarByteSet(Var,V);
}

void *YSVarByteSave(BYTE V)
{
    return FEVarByteSave(V);
}

void *YSVarByteSave2(const char *Key,BYTE V)
{
    return FEVarByteSave2(Key,V);
}

void *YSVarByteClone(void *Var)
{
    return FEVarByteClone(Var);
}

void *YSVarInt16New()
{
    return FEVarInt16New();
}

void  YSVarInt16Free(void *Var)
{
    FEVarInt16Free(Var);
}

BOOL  YSVarInt16Get(void *Var,INT16 *V)
{
    return FEVarInt16Get(Var,V);
}

BOOL  YSVarInt16Set(void *Var,INT16 V)
{
    return FEVarInt16Set(Var,V);
}

void *YSVarInt16Save(INT16 V)
{
    return FEVarInt16Save(V);
}

void *YSVarInt16Save2(const char *Key,INT16 V)
{
    return FEVarInt16Save2(Key,V);
}

void *YSVarInt16Clone(void *Var)
{
    return FEVarInt16Clone(Var);
}

void *YSVarInt32New()
{
    return FEVarInt32New();
}

void  YSVarInt32Free(void *Var)
{
    FEVarInt32Free(Var);
}

BOOL  YSVarInt32Get(void *Var,INT32 *V)
{
    return FEVarInt32Get(Var,V);
}

BOOL  YSVarInt32Set(void *Var,INT32 V)
{
    return FEVarInt32Set(Var,V);
}

void *YSVarInt32Save(INT32 V)
{
    return FEVarInt32Save(V);
}

void *YSVarInt32Save2(const char *Key,INT32 V)
{
    return FEVarInt32Save2(Key,V);
}

void *YSVarInt32Clone(void *Var)
{
    return FEVarInt32Clone(Var);
}

void *YSVarInt64New()
{
    return FEVarInt64New();
}

void  YSVarInt64Free(void *Var)
{
    FEVarInt64Free(Var);
}

BOOL  YSVarInt64Get(void *Var,INT64 *V)
{
    return FEVarInt64Get(Var,V);
}

BOOL  YSVarInt64Set(void *Var,INT64 V)
{
    return FEVarInt64Set(Var,V);
}

void *YSVarInt64Save(INT64 V)
{
    return FEVarInt64Save(V);
}

void *YSVarInt64Save2(const char *Key,INT64 V)
{
    return FEVarInt64Save2(Key,V);
}

void *YSVarInt64Clone(void *Var)
{
    return FEVarInt64Clone(Var);
}

void *YSVarDoubleNew()
{
    return FEVarDoubleNew();
}

void  YSVarDoubleFree(void *Var)
{
    FEVarDoubleFree(Var);
}

BOOL  YSVarDoubleGet(void *Var,DOUBLE *V)
{
    return FEVarDoubleGet(Var,V);
}

BOOL  YSVarDoubleSet(void *Var,DOUBLE V)
{
    return FEVarDoubleSet(Var,V);
}

void *YSVarDoubleSave(DOUBLE V)
{
    return FEVarDoubleSave(V);
}

void *YSVarDoubleSave2(const char *Key,DOUBLE V)
{
    return FEVarDoubleSave2(Key,V);
}

void *YSVarDoubleClone(void *Var)
{
    return FEVarDoubleClone(Var);
}

void *YSVarBinNew()
{
    return FEVarBinNew();
}

void *YSVarBinNew2(INT32 Size)
{
    return FEVarBinNew2(Size);
}

void  YSVarBinFree(void *Var)
{
    FEVarBinFree(Var);
}

void  YSVarBinShow(void *Var,INT32 T,void *Buf)
{
    FEVarBinShow(Var,T,Buf);
}

BOOL  YSVarBinPack(void *Var,void *Buf)
{
    return FEVarBinPack(Var,Buf);
}

INT32 YSVarBinUnPack(void **VVar,void *Buf,INT32 P)
{
    return FEVarBinUnPack(VVar,Buf,P);
}

void  YSVarBinDelete(void *Var)
{
    FEVarBinDelete(Var);
}

BOOL  YSVarBinClear(void *Var)
{
    return FEVarBinClear(Var);
}

void  YSVarBinReset(void *Var)
{
    FEVarBinReset(Var);
}

void  YSVarBinCut(void *Var,INT32 S,INT32 L)
{
    FEVarBinCut(Var,S,L);
}

INT32 YSVarBinGetSize(void *Var)
{
    return FEVarBinGetSize(Var);
}

BOOL  YSVarBinSetLen(void *Var,INT32 L)
{
    return FEVarBinSetLen(Var,L);
}

INT32 YSVarBinGetLen(void *Var)
{
    return FEVarBinGetLen(Var);
}

void *YSVarBinGet(void *Var)
{
    return FEVarBinGet(Var);
}

BOOL  YSVarBinGet2(void *Var,void *V,INT32 *L,INT32 S)
{
    return FEVarBinGet2(Var,V,L,S);
}

BOOL  YSVarBinMalloc(void *Var,INT32 L)
{
    return FEVarBinMalloc(Var,L);
}

BOOL  YSVarBinCat(void *Var,void *V,INT32 L)
{
    return FEVarBinCat(Var,V,L);
}

BOOL  YSVarBinCpy(void *Var,void *V,INT32 L)
{
    return FEVarBinCpy(Var,V,L);
}

void *YSVarBinSave(void *V,INT32 L)
{
    return FEVarBinSave(V,L);
}

void *YSVarBinSave2(const char *Key,void *V,INT32 L)
{
    return FEVarBinSave2(Key,V,L);
}

void *YSVarBinClone(void *Var)
{
    return FEVarBinClone(Var);
}

void *YSVarStringNew()
{
    return FEVarStringNew();
}

void *YSVarStringNew2(INT32 Size)
{
    return FEVarStringNew2(Size);
}

void  YSVarStringFree(void *Var)
{
    FEVarStringFree(Var);
}

void  YSVarStringShow(void *Var,INT32 T,void *Buf)
{
    FEVarStringShow(Var,T,Buf);
}

BOOL  YSVarStringPack(void *Var,void *Buf)
{
    return FEVarStringPack(Var,Buf);
}

INT32 YSVarStringUnPack(void **VVar,void *Buf,INT32 P)
{
    return FEVarStringUnPack(VVar,Buf,P);
}

void  YSVarStringDelete(void *Var)
{
    FEVarStringDelete(Var);
}

BOOL  YSVarStringClear(void *Var)
{
    return FEVarStringClear(Var);
}

void  YSVarStringReset(void *Var)
{
    FEVarStringReset(Var);
}

void  YSVarStringCut(void *Var,INT32 S,INT32 L)
{
    FEVarStringCut(Var,S,L);
}

INT32 YSVarStringGetSize(void *Var)
{
    return FEVarStringGetSize(Var);
}

BOOL  YSVarStringSetLen(void *Var,INT32 L)
{
    return FEVarStringSetLen(Var,L);
}

INT32 YSVarStringGetLen(void *Var)
{
    return FEVarStringGetLen(Var);
}

void *YSVarStringGet(void *Var)
{
    return FEVarStringGet(Var);
}

BOOL  YSVarStringGet2(void *Var,void *V,INT32 *L,INT32 S)
{
    return FEVarStringGet2(Var,V,L,S);
}

BOOL  YSVarStringMalloc(void *Var,INT32 L)
{
    return FEVarStringMalloc(Var,L);
}

BOOL  YSVarStringCat(void *Var,void *V,INT32 L)
{
    return FEVarStringCat(Var,V,L);
}

BOOL  YSVarStringCpy(void *Var,void *V,INT32 L)
{
    return FEVarStringCpy(Var,V,L);
}

void *YSVarStringSave(void *V,INT32 L)
{
    return FEVarStringSave(V,L);
}

void *YSVarStringSave2(const char *Key,void *V,INT32 L)
{
    return FEVarStringSave2(Key,V,L);
}

void *YSVarStringClone(void *Var)
{
    return FEVarStringClone(Var);
}

void *YSVarObjectNew()
{
    return FEVarObjectNew();
}

void  YSVarObjectFree(void *Var)
{
    FEVarObjectFree(Var);
}

void  YSVarObjectShow(void *Var,INT32 T,void *Buf)
{
    FEVarObjectShow(Var,T,Buf);
}

void *YSVarObjectGet(void *Var)
{
    return FEVarObjectGet(Var);
}

BOOL  YSVarObjectGet2(void *Var,void **V)
{
    return FEVarObjectGet2(Var,V);
}

void *YSVarObjectGetVClone(void *Var)
{
    return FEVarObjectGetVClone(Var);
}

void *YSVarObjectGetVFree(void *Var)
{
    return FEVarObjectGetVFree(Var);
}

void *YSVarObjectGetVShow(void *Var)
{
    return FEVarObjectGetVShow(Var);
}

void *YSVarObjectGetVPack(void *Var)
{
    return FEVarObjectGetVPack(Var);
}

BOOL  YSVarObjectSet(void *Var,void *V)
{
    return FEVarObjectSet(Var,V);
}

BOOL  YSVarObjectSetFuncVClone(void *Var,void *Clone)
{
    return FEVarObjectSetFuncVClone(Var,Clone);
}

BOOL  YSVarObjectSetFuncVFree(void *Var,void *Free)
{
    return FEVarObjectSetFuncVFree(Var,Free);
}

BOOL  YSVarObjectSetFuncVShow(void *Var,void *Show)
{
    return FEVarObjectSetFuncVShow(Var,Show);
}

BOOL  YSVarObjectSetFuncVPack(void *Var,void *Pack)
{
    return FEVarObjectSetFuncVPack(Var,Pack);
}

void *YSVarObjectSave(void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    return FEVarObjectSave(V,Clone,Free,Show,Pack);
}

void *YSVarObjectSave2(const char *Key \
    ,void *V,void *Clone,void *Free,void *Show,void *Pack)
{
    return FEVarObjectSave2(Key,V,Clone,Free,Show,Pack);
}

void *YSVarObjectClone(void *Var)
{
    return FEVarObjectClone(Var);
}

void *YSVarArrayNew(INT32 Max)
{
    return FEVarArrayNew(Max);
}

void *YSVarArrayNew_Key(INT32 Max,const char *Key)
{
    return FEVarArrayNew_Key(Max,Key);
}

void *YSVarArrayNew2(INT32 Max)
{
    return FEVarArrayNew2(Max);
}

void *YSVarArrayNew2_Key(INT32 Max,const char *Key)
{
    return FEVarArrayNew2_Key(Max,Key);
}

void  YSVarArrayFree(void *Var)
{
    FEVarArrayFree(Var);
}

void  YSVarArrayShow(void *Var,INT32 T,void *Buf)
{
    FEVarArrayShow(Var,T,Buf);
}

BOOL  YSVarArrayPack(void *Var,void *Buf)
{
    return FEVarArrayPack(Var,Buf);
}

INT32 YSVarArrayUnPack(void **VVar,void *Buf,INT32 P)
{
    return FEVarArrayUnPack(VVar,Buf,P);
}

BOOL  YSVarArrayIsEmpty(void *Var)
{
    return FEVarArrayIsEmpty(Var);
}

BOOL  YSVarArrayIsFull(void *Var)
{
    return FEVarArrayIsFull(Var);
}

BOOL  YSVarArraySetMax(void *Var,INT32 Max)
{
    return FEVarArraySetMax(Var,Max);
}

INT32 YSVarArrayGetMax(void *Var)
{
    return FEVarArrayGetMax(Var);
}

INT32 YSVarArrayGetSize(void *Var)
{
    return FEVarArrayGetSize(Var);
}

INT32 YSVarArrayGetLen(void *Var)
{
    return FEVarArrayGetLen(Var);
}

BOOL  YSVarArraySetUserLen(void *Var,INT32 UserLen)
{
    return FEVarArraySetUserLen(Var,UserLen);
}

BOOL  YSVarArrayPlusUserLen(void *Var,BOOL Flag)
{
    return FEVarArraySetUserLen(Var,Flag);
}

INT32  YSVarArrayGetUserLen(void *Var)
{
    return FEVarArrayGetUserLen(Var);
}

BOOL  YSVarArraySetUserCnt(void *Var,INT32 UserCnt)
{
    return FEVarArraySetUserCnt(Var,UserCnt);
}

BOOL  YSVarArrayPlusUserCnt(void *Var,BOOL Flag)
{
    return FEVarArraySetUserCnt(Var,Flag);
}

INT32  YSVarArrayGetUserCnt(void *Var)
{
    return FEVarArrayGetUserCnt(Var);
}

BOOL  YSVarArrayIsIdxOfValue(void *Var,INT32 Idx)
{
    return FEVarArrayIsIdxOfValue(Var,Idx);
}

BOOL  YSVarArrayIsIdxOfRange(void *Var,INT32 Idx)
{
    return FEVarArrayIsIdxOfRange(Var,Idx);
}

BOOL  YSVarArrayAdd(void *Var,void *V)
{
    return FEVarArrayAdd(Var,V);
}

BOOL  YSVarArrayInsert(void *Var,INT32 Idx,void *V)
{
    return FEVarArrayInsert(Var,Idx,V);
}

BOOL  YSVarArrayReplace(void *Var,INT32 Idx,void *V)
{
    return FEVarArrayReplace(Var,Idx,V);
}

BOOL  YSVarArrayReplaceValue(void *Var,INT32 Idx,void *V)
{
    return FEVarArrayReplaceValue(Var,Idx,V);
}

BOOL  YSVarArrayDelete(void *Var,INT32 Idx)
{
    return FEVarArrayDelete(Var,Idx);
}


void *YSVarArrayGet(void *Var,INT32 Idx)
{
    return FEVarArrayGet(Var,Idx);
}

BOOL  YSVarArrayGet2(void *Var,INT32 Idx,void **V)
{
    return FEVarArrayGet2(Var,Idx,V);
}

INT32 YSVarArrayGetIdxByKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarArrayGetIdxByKey(Var,Key,Len);
}

void *YSVarArrayGetNodeByKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarArrayGetNodeByKey(Var,Key,Len);
}

void *YSVarArrayGetByKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarArrayGetByKey(Var,Key,Len);
}

BOOL  YSVarArrayGet2ByKey(void *Var,const void *Key,INT32 Len,void **V)
{
    return FEVarArrayGet2ByKey(Var,Key,Len,V);
}

BOOL  YSVarArrayInsertByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    return FEVarArrayInsertByKey(Var,Key,Len,V);
}

BOOL  YSVarArrayReplaceByKey(void *Var,void *V)
{
    return FEVarArrayReplaceByKey(Var,V);
}

BOOL  YSVarArrayReplaceValueByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    return FEVarArrayReplaceValueByKey(Var,Key,Len,V);
}

BOOL  YSVarArrayDeleteByKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarArrayDeleteByKey(Var,Key,Len);
}

void *YSVarArrayClone(void *Var)
{
    return FEVarArrayClone(Var);
}

BOOL  YSVarArrayCloneValue(void *N,void *Var)
{
    return FEVarArrayCloneValue(N,Var);
}

void *YSVarFifoNew(INT32 Max)
{
    return FEVarFifoNew(Max);
}

void *YSVarFifoNew_Key(INT32 Max,const char *Key)
{
    return FEVarFifoNew_Key(Max,Key);
}

void *YSVarFifoNew2(INT32 Max)
{
    return FEVarFifoNew2(Max);
}

void *YSVarFifoNew2_Key(INT32 Max,const char *Key)
{
    return FEVarFifoNew2_Key(Max,Key);
}

void  YSVarFifoFree(void *Var)
{
    FEVarFifoFree(Var);
}

void  YSVarFifoShow(void *Var,INT32 T,void *Buf)
{
    FEVarFifoShow(Var,T,Buf);
}

BOOL  YSVarFifoIsEmpty(void *Var)
{
    return FEVarFifoIsEmpty(Var);
}

BOOL  YSVarFifoIsFull(void *Var)
{
    return FEVarFifoIsFull(Var);
}

BOOL  YSVarFifoSetMax(void *Var,INT32 Max)
{
    return FEVarFifoSetMax(Var,Max);
}

INT32 YSVarFifoGetMax(void *Var)
{
    return FEVarFifoGetMax(Var);
}

INT32 YSVarFifoGetLen(void *Var)
{
    return FEVarFifoGetLen(Var);
}

BOOL  YSVarFifoIsIdxOfValue(void *Var,INT32 Idx)
{
    return FEVarFifoIsIdxOfValue(Var,Idx);
}

BOOL  YSVarFifoIsIdxOfRange(void *Var,INT32 Idx)
{
    return FEVarFifoIsIdxOfRange(Var,Idx);
}

BOOL  YSVarFifoPush(void *Var,void *V)
{
    return FEVarFifoPush(Var,V);
}

BOOL  YSVarFifoPop(void *Var,void **V)
{
    return FEVarFifoPop(Var,V);
}

void *YSVarFifoGet(void *Var,INT32 Idx)
{
    return FEVarFifoGet(Var,Idx);
}

BOOL  YSVarFifoGet2(void *Var,INT32 Idx,void **V)
{
    return FEVarFifoGet2(Var,Idx,V);
}

BOOL  YSVarFifoReplace(void *Var,INT32 Idx,void *V)
{
    return FEVarFifoReplace(Var,Idx,V);
}

BOOL  YSVarFifoReplaceValue(void *Var,INT32 Idx,void *V)
{
    return FEVarFifoReplaceValue(Var,Idx,V);
}

void *YSVarFifoClone(void *Var)
{
    return FEVarFifoClone(Var);
}

BOOL  YSVarFifoCloneValue(void *N,void *Var)
{
    return FEVarFifoCloneValue(N,Var);
}

void *YSVarFiloNew(INT32 Max)
{
    return FEVarFiloNew(Max);
}

void *YSVarFiloNew_Key(INT32 Max,const char *Key)
{
    return FEVarFiloNew_Key(Max,Key);
}

void *YSVarFiloNew2(INT32 Max)
{
    return FEVarFiloNew2(Max);
}

void *YSVarFiloNew2_Key(INT32 Max,const char *Key)
{
    return FEVarFiloNew2_Key(Max,Key);
}

void  YSVarFiloFree(void *Var)
{
    FEVarFiloFree(Var);
}

void  YSVarFiloShow(void *Var,INT32 T,void *Buf)
{
    FEVarFiloShow(Var,T,Buf);
}

BOOL  YSVarFiloIsEmpty(void *Var)
{
    return FEVarFiloIsEmpty(Var);
}

BOOL  YSVarFiloIsFull(void *Var)
{
    return FEVarFiloIsFull(Var);
}

BOOL  YSVarFiloSetMax(void *Var,INT32 Max)
{
    return FEVarFiloSetMax(Var,Max);
}

INT32 YSVarFiloGetMax(void *Var)
{
    return FEVarFiloGetMax(Var);
}

INT32 YSVarFiloGetLen(void *Var)
{
    return FEVarFiloGetLen(Var);
}

BOOL  YSVarFiloIsIdxOfValue(void *Var,INT32 Idx)
{
    return FEVarFiloIsIdxOfValue(Var,Idx);
}

BOOL  YSVarFiloIsIdxOfRange(void *Var,INT32 Idx)
{
    return FEVarFiloIsIdxOfRange(Var,Idx);
}

BOOL  YSVarFiloPush(void *Var,void *V)
{
    return FEVarFiloPush(Var,V);
}

BOOL  YSVarFiloPop(void *Var,void **V)
{
    return FEVarFiloPop(Var,V);
}

void *YSVarFiloGet(void *Var,INT32 Idx)
{
    return FEVarFiloGet(Var,Idx);
}

BOOL  YSVarFiloGet2(void *Var,INT32 Idx,void **V)
{
    return FEVarFiloGet2(Var,Idx,V);
}

BOOL  YSVarFiloReplace(void *Var,INT32 Idx,void *V)
{
    return FEVarFiloReplace(Var,Idx,V);
}

BOOL  YSVarFiloReplaceValue(void *Var,INT32 Idx,void *V)
{
    return FEVarFiloReplaceValue(Var,Idx,V);
}

void *YSVarFiloClone(void *Var)
{
    return FEVarFiloClone(Var);
}

BOOL  YSVarFiloCloneValue(void *N,void *Var)
{
    return FEVarFiloCloneValue(N,Var);
}

void *YSVarLinkNew(INT32 Max)
{
    return FEVarLinkNew(Max);
}

void *YSVarLinkNew_Key(INT32 Max,const char *Key)
{
    return FEVarLinkNew_Key(Max,Key);
}

void  YSVarLinkFree(void *Var)
{
    FEVarLinkFree(Var);
}

void  YSVarLinkShow(void *Var,INT32 T,void *Buf)
{
    FEVarLinkShow(Var,T,Buf);
}

BOOL  YSVarLinkIsEmpty(void *Var)
{
    return FEVarLinkIsEmpty(Var);
}

BOOL  YSVarLinkIsFull(void *Var)
{
    return FEVarLinkIsFull(Var);
}

BOOL  YSVarLinkSetMax(void *Var,INT32 Max)
{
    return FEVarLinkSetMax(Var,Max);
}

INT32 YSVarLinkGetMax(void *Var)
{
    return FEVarLinkGetMax(Var);
}

INT32 YSVarLinkGetLen(void *Var)
{
    return FEVarLinkGetLen(Var);
}

BOOL  YSVarLinkIsIdxOfValue(void *Var,INT32 Idx)
{
    return FEVarLinkIsIdxOfValue(Var,Idx);
}

BOOL  YSVarLinkIsIdxOfRange(void *Var,INT32 Idx)
{
    return FEVarLinkIsIdxOfRange(Var,Idx);
}

void *YSVarLinkGetNode(void *Var,INT32 Idx)
{
    return FEVarLinkGetNode(Var,Idx);
}

void *YSVarLinkGet(void *Var,INT32 Idx)
{
    return FEVarLinkGet(Var,Idx);
}

BOOL  YSVarLinkGet2(void *Var,INT32 Idx,void **V)
{
    return FEVarLinkGet2(Var,Idx,V);
}

BOOL  YSVarLinkAdd(void *Var,void *V)
{
    return FEVarLinkAdd(Var,V);
}

BOOL  YSVarLinkInsert(void *Var,INT32 Idx,void *V)
{
    return FEVarLinkInsert(Var,Idx,V);
}

BOOL  YSVarLinkReplace(void *Var,INT32 Idx,void *V)
{
    return FEVarLinkReplace(Var,Idx,V);
}

BOOL  YSVarLinkReplaceValue(void *Var,INT32 Idx,void *V)
{
    return FEVarLinkReplaceValue(Var,Idx,V);
}

BOOL  YSVarLinkDelete(void *Var,INT32 Idx)
{
    return FEVarLinkDelete(Var,Idx);
}

INT32 YSVarLinkGetIdxByKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarLinkGetIdxByKey(Var,Key,Len);
}

void *YSVarLinkGetNodeByKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarLinkGetNodeByKey(Var,Key,Len);
}

void *YSVarLinkGetByKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarLinkGetByKey(Var,Key,Len);
}

BOOL  YSVarLinkGet2ByKey(void *Var,const void *Key,INT32 Len,void **V)
{
    return FEVarLinkGet2ByKey(Var,Key,Len,V);
}

BOOL  YSVarLinkInsertByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    return FEVarLinkInsertByKey(Var,Key,Len,V);
}

BOOL  YSVarLinkReplaceByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    return FEVarLinkReplaceByKey(Var,Key,Len,V);
}

BOOL  YSVarLinkReplaceValueByKey(void *Var,const void *Key,INT32 Len,void *V)
{
    return FEVarLinkReplaceValueByKey(Var,Key,Len,V);
}

BOOL  YSVarLinkDeleteByKey(void *Var,const void *Key,INT32 Len)
{
    return FEVarLinkDeleteByKey(Var,Key,Len);
}

void *YSVarLinkClone(void *Var)
{
    return FEVarLinkClone(Var);
}

BOOL  YSVarLinkCloneValue(void *N,void *Var)
{
    return FEVarLinkCloneValue(N,Var);
}

void *YSVarHashNew(INT32 Max)
{
    return FEVarHashNew(Max);
}

void *YSVarHashNew_Key(INT32 Max,const char *Key)
{
    return FEVarHashNew_Key(Max,Key);
}

void  YSVarHashFree(void *Var)
{
    FEVarHashFree(Var);
}

void  YSVarHashShow(void *Var,INT32 T,void *Buf)
{
    FEVarHashShow(Var,T,Buf);
}

BOOL  YSVarHashPack(void *Var,void *Buf)
{
    return FEVarHashPack(Var,Buf);
}

INT32 YSVarHashUnPack(void **VVar,void *Buf,INT32 P)
{
    return FEVarHashUnPack(VVar,Buf,P);
}

BOOL  YSVarHashIsEmpty(void *Var)
{
    return FEVarHashIsEmpty(Var);
}

INT32 YSVarHashGetLen(void *Var)
{
    return FEVarHashGetLen(Var);
}

void *YSVarHashGetNode(void *Var,const char *Key)
{
    if ( NULL==Key )
    {
        return NULL;
    }
    return FEVarHashGetNode(Var,Key,strlen(Key));
}

void *YSVarHashGet(void *Var,const char *Key)
{
    if ( NULL==Key )
    {
        return NULL;
    }
    return FEVarHashGet(Var,Key,strlen(Key));
}

BOOL  YSVarHashGet2(void *Var,const char *Key,void **V)
{
    if ( NULL==Key )
    {
        return FALSE;
    }
    return FEVarHashGet2(Var,Key,strlen(Key),V);
}

BOOL  YSVarHashAdd(void *Var,void *V)
{
    return FEVarHashAdd(Var,V);
}

BOOL  YSVarHashReplace(void *Var,void *V)
{
    return FEVarHashReplace(Var,V);
}

BOOL  YSVarHashReplaceValue(void *Var,const char *Key,void *V)
{
    if ( NULL==Key )
    {
        return FALSE;
    }
    return FEVarHashReplaceValue(Var,Key,strlen(Key),V);
}

BOOL  YSVarHashDelete(void *Var,const char *Key)
{
    return FEVarHashDelete(Var,Key,strlen(Key));
}

void *YSVarHashClone(void *Var)
{
    return FEVarHashClone(Var);
}

BOOL  YSVarHashCloneValue(void *N,void *Var)
{
    return FEVarHashCloneValue(N,Var);
}

#ifdef __cplusplus
}
#endif

