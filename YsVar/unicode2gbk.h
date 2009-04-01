#ifndef MCL_GBUNICODE_H
#define MCL_GBUNICODE_H

#define _GB_UNI_ITEM_COUNT	7445	

#ifdef __cplusplus
extern "C" {
#endif

#include <fecom.h>

typedef struct{
	UINT32 d1;
	UINT32 d2;
}	DataPair;

/** 返回源码targetValue编码后的值，即根据d1求d2 **/
UINT32 to(const UINT32 targetValue, int type);
INT32 indexOf(const UINT32 targetValue, DataPair *pItems);
#if 0
/** 把整数转换成长度为4的16进制字符串，长度不够用0补齐 **/
char *intToHex(UINT32 value, int TotalLen);

/** 把一个Unicode码字符转换成GB码 **/
UINT32 ch2GB(const UINT32 targetValue);
/** 把Unicode码转换成GB码 **/
char *str2GB(const char *unicodeStr);

/** 把一个GB码字符转换成Unicode码 **/
UINT32 ch2Uni(const UINT32 targetValue);	
/** 把GB码字符串转换成Unicode码，原字符串长度和目标字符串长度相同 **/
char *str2Uni(const char *gbStr);
/** 把GB码字符串转换成Unicode码，%转换成%25，其余的标准ASCII码字符不进行转换，其余的双字节转换成%uXXXX的格式**/
char *str2FmtUni(const char *gbStr);	

#endif

#ifdef __cplusplus
}
#endif
#endif
