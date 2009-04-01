/***************************************************************************/
/**[File Name    ]fecom.h                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define common for fe                                    **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef FECOM_H__
#define FECOM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef __OS_LINUX__
#include <unistd.h>
#endif
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

#include <time.h>
#ifdef __OS_LINUX__
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <dlfcn.h>
#endif

#include <errno.h>
#ifdef __OS_LINUX__
extern int errno;
#elif __OS_WIN__
extern int __errno;
#endif

#include <define.h>
#include <macro.h>
#include <rtncode.h>

#include <fedef.h>
#include <fevar.h>
#ifdef __OS_LINUX__
#include <feunit.h>
#endif

#if __OS_WIN__
/*
    指针类型强制转化,大小不完全匹配
    64位编程时,c4311的警告要处理,c412可以不处理.
*/
#pragma warning (disable: 4311 4312) 
/*  丢失数据,4244为已知类型,4267为64位类型转化 */
#pragma warning (disable: 4244 4267)
/*  安全警告 */
#pragma warning (disable: 4996)
#endif

#ifdef __cplusplus
extern "C" {
#endif

INT32 FEHashCalSize(INT32  Size);
INT32 FEHashCalKey(const char *key,INT32 len);
INT32 FEHashGetIdx(INT32 HK,INT32 Size);

/****************************************************************************/
/** des.c                                                                  **/
/****************************************************************************/
void  DESDivKeys(const UCHAR *key,
    const INT32 divnum,
    UCHAR *divdata,
    UCHAR *out_key);
INT32 DESEncrypt(const UCHAR *key,
    const INT32 divnum,
    UCHAR *divdata,
    const INT32 ilen_in,
    UCHAR *in,
    UCHAR *out);
INT32 DESDecrypt(const UCHAR *key,
    const INT32 divnum,
    UCHAR *divdata,
    const INT32 ilen_in,
    UCHAR *in,
    UCHAR *out);
INT32 DESMac(const UCHAR *key,
        const INT32 divnum,
        UCHAR *divdata,
        const INT32 ilen_in,
        UCHAR *in,
        UCHAR *mac,
        INT32 iFlag);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** md5.c                                                                  **/
/****************************************************************************/
INT32 MD5String(char *string,UCHAR digest[16]);
INT32 MD5Buffer(char *buffer,UINT32 len,UCHAR digest[16]);
INT32 MD5File(char *filename,UCHAR digest[16]);
/****************************************************************************/
/****************************************************************************/

INT32 FE2BytesUni2Gbk(char *uniStr,INT32 uniLen \
    ,char *gbStr,INT32 *GbLen,INT32 gbSize);
INT32 FE2BytesGbk2Uni(char *gbStr,INT32 gbLen \
    ,char *uniStr,INT32 *uniLen,INT32 uniSize);

INT32 FE2BytesUniToUTF8BigEndian(BYTE *Unicode,INT32 ULen \
    ,BYTE *UTF8,INT32 *PLen,INT32 Size);
INT32 FE2BytesUTF8ToUniBigEndian(BYTE *UTF8,INT32 ULen \
    ,BYTE *Unicode,INT32 *PLen,INT32 Size);
INT32 FE4BytesUniToUTF8BigEndian(BYTE *Unicode,INT32 ULen \
    ,BYTE *UTF8,INT32 *PLen,INT32 Size);
INT32 FE4BytesUTF8ToUniBigEndian(BYTE *UTF8,INT32 ULen \
    ,BYTE *Unicode,INT32 *PLen,INT32 Size);

INT32 FEGbkfilter(char *TS,char *SS);

/****************************************************************************/
/** string.c                                                               **/
/****************************************************************************/
BOOL  FECharIsSetBit(UCHAR C,INT32 Idx);
BOOL  FECharSetBit(UCHAR *C,INT32 Idx,BOOL Flag);
BOOL  FEGetEnv(char *Str,INT32 Size,const char *Key);
INT32 FEStrIsNumber(char *str,INT32 len);
INT32 FEStrIsHex(char *str,INT32 len);
char *FEStrTrimSign(char *str,char sign);
char *FEStrTrimRightSigns(char *str,char *signs);
char *FEStrTrimLeftSigns(char *str,char *signs);
char *FEStrTrimSigns(char *str,char *signs);
char *FEStrTrimChangeLine(char *str);
#define FEStrTrim(str)  FEStrTrimSigns((str),STR_TRIMLINE_SIGN)
char *FEStrToUpper(char *pcLine);
char *FEStrToLower(char *pcLine);
char *FEStrDelChar(char *pcLine,char ch);
INT32 FEStrByte2Hex(char *str,INT32 size,BYTE ch);
INT32 FEStrHex2Byte(BYTE *ch,char *str);
INT32 FEStrBytes2Hex(char *hex,INT32 size,char *bytes,INT32 len);
INT32 FEStrHex2Bytes(char *bytes,INT32 size,char *hex,INT32 len);
INT32 FEStr2Char(char *ch,char *pc,INT32 len);
void  FEStrESC(char *pcLine);
INT32 FEStrGetOneWordLen(INT32 *piWordLen \
    ,char *str,INT32 len,char *sign,INT32 signlen);
INT32 FEStrGetOneWord(INT32 *piWordLen,char *pcWord,INT32 size \
    ,char *str,INT32 len,char *sign,INT32 signlen);
INT32 FEStrFindSign(char *str,char ch);
INT32 FEStrFindLastSign(char *str,char ch);
void  FEEndianConversion(void *E,INT32 Size);
void  FEEndianToHost(void *E,INT32 Size);
void  FEEndianToNet(void *E,INT32 Size);
#define FEEndianLittle2Big(E,Size) FEEndianConversion((E),(Size))
#define FEEndianBig2Little(E,Size) FEEndianConversion((E),(Size))

char *FESetTrace(char *Buf,INT32 Size \
    ,const char *file,const INT32 line,const char *func);
#define FESETTRACE(Buf,Size) \
    FESetTrace((Buf),(Size),__FILE__,__LINE__,__func__)

INT32 FEHexToBufLine(char *Hex,INT32 Size,INT32 MaxLine \
    ,const char *Log,INT32 Len);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** file.c                                                                 **/
/****************************************************************************/
INT32 FEPathSplit(const char *Path);
INT32 FEFileTest(const char *pcFile);
INT32 FEDirTest(const char *pcDir);
INT32 FEDirTest2(const char *pcDir);
INT32 FEFileLockByName(char *pcFile);
INT32 FEFileLock(INT32 fp);
void  FEFileUnLock(INT32 fp);
void  FEFileUnLockClose(INT32 fp);
INT32 FEFileWrite(INT32 fd,const void *Log,INT32 Len);
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** log.c                                                                  **/
/****************************************************************************/
INT32 FELogListLoadFromFile(void *LogList,const char *ListFile);
void *FELogListLoadFromFile2(const char *ListFile);
void *FELogListNew();
void  FELogListFree(void *Root);
BOOL  FELogListAdd(void *Root,const char *M,const char *F,INT32 L);
BOOL  FELogListDelete(void *Root,const char *M,const char *F,INT32 L);
BOOL  FELogListSwitch(void *Dest,void *Srv);
void  FELogListShow(void *Root,INT32 T,void *Buf);

void *FELogArgsNew(char *pcDir,char *pcFile);
void  FELogArgsFree(void *Args);
INT32 FELogArgsInit(void *Args,char *pcDir,char *pcFile);
BOOL  FELogArgsSetLevel(void *Args,INT32 Level);
BOOL  FELogArgsSetLogFile(void *Args,const char *LogFile);
BOOL  FELogArgsSetNet(void *Args,const char *Ip,INT32 Port);
BOOL  FELogArgsSetModule(void *Args,const char *Module);
BOOL  FELogArgsSetFunc(void *Args,const char *Func);
BOOL  FELogArgsSetTrace(void *Args,char *file,INT32 line,const char *func);
BOOL  FELogArgsSetList(void *Args,void *List);
BOOL  FELogArgsIsWriteLog(void *Args);
void  FELogWrite(void *Args,const char *Title,const char *Log,INT32 Len);
void  FELogsWrite(void *Args,const char *Title,const char *fmt,...);
void  FETraceWrite(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FETracesWrite(void *Args,const char *Title,const char *fmt,...);
void  FEHexTraceWrite(void *Args,const char *Title,const char *Log,INT32 iLen);
INT32 FELogArgsGetEnvLevel();
void  FELogArgsCopy(void *DA,void *SA);
void  FELogArgsShow(void *Root,INT32 T,void *Buf);
void *FELogArgsClone(void *Args);

char *FELogGetNameByLevel(INT32 Level);
INT32 FELogGetLevelByName(const char *LogName);

void  FETraceAll(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FETraceDebug(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FETraceInfo(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FETraceWarn(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FETraceError(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FETraceFatal(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FETracesAll(void *Args,const char *Title,const char *fmt,...);
void  FETracesDebug(void *Args,const char *Title,const char *fmt,...);
void  FETracesInfo(void *Args,const char *Title,const char *fmt,...);
void  FETracesWarn(void *Args,const char *Title,const char *fmt,...);
void  FETracesError(void *Args,const char *Title,const char *fmt,...);
void  FETracesFatal(void *Args,const char *Title,const char *fmt,...);
void  FEHexTraceAll(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FEHexTraceDebug(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FEHexTraceInfo(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FEHexTraceWarn(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FEHexTraceError(void *Args,const char *Title,const char *Log,INT32 iLen);
void  FEHexTraceFatal(void *Args,const char *Title,const char *Log,INT32 iLen);

void  FEStdout(const char *Title,const char *fmt,...);
void  FEStderr(const char *Title,const char *fmt,...);
void  FEDebugStdout(const char *Title,const char *fmt,...);
void  FEDebugStderr(const char *Title,const char *fmt,...);
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FECOM_H__ */ 

