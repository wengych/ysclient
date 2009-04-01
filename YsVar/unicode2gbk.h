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

/** ����Դ��targetValue������ֵ��������d1��d2 **/
UINT32 to(const UINT32 targetValue, int type);
INT32 indexOf(const UINT32 targetValue, DataPair *pItems);
#if 0
/** ������ת���ɳ���Ϊ4��16�����ַ��������Ȳ�����0���� **/
char *intToHex(UINT32 value, int TotalLen);

/** ��һ��Unicode���ַ�ת����GB�� **/
UINT32 ch2GB(const UINT32 targetValue);
/** ��Unicode��ת����GB�� **/
char *str2GB(const char *unicodeStr);

/** ��һ��GB���ַ�ת����Unicode�� **/
UINT32 ch2Uni(const UINT32 targetValue);	
/** ��GB���ַ���ת����Unicode�룬ԭ�ַ������Ⱥ�Ŀ���ַ���������ͬ **/
char *str2Uni(const char *gbStr);
/** ��GB���ַ���ת����Unicode�룬%ת����%25������ı�׼ASCII���ַ�������ת���������˫�ֽ�ת����%uXXXX�ĸ�ʽ**/
char *str2FmtUni(const char *gbStr);	

#endif

#ifdef __cplusplus
}
#endif
#endif
