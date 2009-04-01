/***************************************************************************/
/**[File Name    ]unicode2utf8.c                                          **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for conversion between unicode and utf8     **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <fecom.h>

#ifdef __cplusplus
extern "C"{
#endif

#define FEUNICODE_2BYTES        2
#define FEUNICODE_4BYTES        4
#define FEUNICODE2UTF8_BUFSIZE_TOSMALL(L1,L2,S) \
    if ( (L1)+(L2)>=(S) ) \
    { \
        return FERTN_ERAPP_SIZE; \
    }

INT32 FEUniToUTF8BigEndian(BYTE *Unicode,INT32 ULen \
    ,BYTE *UTF8,INT32 *PLen,INT32 Size)
{
    INT32 iRtn;
    INT32 UPos;
    INT32 Len;

    if ( (NULL==Unicode)||(NULL==UTF8)||(NULL==PLen) )
    {
        return FERTN_ERAPP_ARG;
    }
    iRtn = FERTN_OK;
    *PLen = 0;
    UPos = 0;
    Len = 0;
    if ( FEUNICODE_4BYTES==ULen )
    {
        if ( 0x00!=(UCHAR)(Unicode[UPos]) )
        {
            /* 00200000 - 03FFFFFF  : (00FFFFFF - 03FFFFFF) */
            /*      111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
            if ( 0x04>(UCHAR)(Unicode[UPos]) )
            {
                FEUNICODE2UTF8_BUFSIZE_TOSMALL(Len,5,Size);
                UTF8[Len]   = (Unicode[UPos]&0x03)|0xF8;
                UTF8[Len+1] = ((Unicode[UPos+1]&0xFC)>>2)|0x80;
                Len += 2;
            }
            /* 04000000 - 7FFFFFFF  : */
            /*      1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
            else if ( 0x80>(UCHAR)(Unicode[UPos]) )
            {
                FEUNICODE2UTF8_BUFSIZE_TOSMALL(Len,6,Size);
                UTF8[Len]   = ((Unicode[UPos]&0x40)>>6)|0xFC;
                UTF8[Len+1] = (Unicode[UPos]&0x3F)|0x80;
                UTF8[Len+2] = ((Unicode[UPos+1]&0xFC)>>2)|0x80;
                Len += 3;
            }
            else
            {
                return FERTN_ERSYS_UNICODENOT;
            }
        }
        else if ( 0x00!=(UCHAR)(Unicode[UPos+1]) )
        {
            /* 00010000 - 001FFFFF  : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
            if ( 0x20>(UCHAR)(Unicode[UPos+1]) )
            {
                FEUNICODE2UTF8_BUFSIZE_TOSMALL(Len,4,Size);
                UTF8[Len] = ((Unicode[UPos+1]&0x1C)>>2)|0xF0;
                Len ++;
            }
            /* 00200000 - 03FFFFFF  : (00200000 - 00FFFFFF) */
            /*      111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
            else
            {
                FEUNICODE2UTF8_BUFSIZE_TOSMALL(Len,5,Size);
                UTF8[Len]   = (Unicode[UPos]&0x03)|0xF8;
                UTF8[Len+1] = ((Unicode[UPos+1]&0xFC)>>2)|0x80;
                Len += 2;
            }
        }
        UPos = 2;
    }
    /* 00000000 - 0000007F      : 0xxxxxxx */
    if ( (0x00==(UCHAR)(Unicode[UPos]))&&(0x80>(UCHAR)(Unicode[UPos+1])) )
    {
        FEUNICODE2UTF8_BUFSIZE_TOSMALL(Len,1,Size);
        UTF8[Len] = (Unicode[UPos+1])&0x7F;
        Len ++;
    }
    /* 00000080 - 000007FF      : 110xxxxx 10xxxxxx */
    else if ( 0x08>(UCHAR)(Unicode[UPos]) )
    {
        FEUNICODE2UTF8_BUFSIZE_TOSMALL(Len,2,Size);
        UTF8[Len] = ((Unicode[UPos]&0x07)<<2) \
            |((Unicode[UPos+1]&0xC0)>>6)|0xC0;
        UTF8[Len+1] = (Unicode[UPos+1]&0x3F)|0x80;
        Len += 2;
    }
    /* 00000800 - 0000FFFF      : 1110xxxx 10xxxxxx 10xxxxxx */
    else
    {
        FEUNICODE2UTF8_BUFSIZE_TOSMALL(Len,3,Size);
        if ( 0<UPos )
        {
            UTF8[Len] = (Unicode[UPos-1]&0x03)|((Unicode[UPos]&0xF0)>>4)|0x80;
        }
        else
        {
            UTF8[Len] = ((Unicode[UPos]&0xF0)>>4)|0xE0;
        }
        UTF8[Len+1] = ((Unicode[UPos]&0x0F)<<2) \
            |((Unicode[UPos+1]&0xC0)>>6)|0x80;
        UTF8[Len+2] = (Unicode[UPos+1]&0x3F)|0x80;
        Len += 3;
    }
    UPos += 2;
    *PLen = Len;
    return iRtn;
}

INT32 FEUTF8ToUniBigEndian(BYTE *UTF8,INT32 *PLen \
    ,BYTE *Unicode,INT32 ULen,INT32 Size)
{
    INT32 iRtn;
    INT32 UPos;
    INT32 Len;
    INT32 UTF8Len;

    if ( (NULL==UTF8)||(NULL==Unicode)||(NULL==PLen)||(ULen>=Size) )
    {
        return FERTN_ERAPP_ARG;
    }
    iRtn = FERTN_OK;
    UTF8Len = *PLen;
    *PLen = 0;
    UPos = 0;
    Len = 0;
    if ( FEUNICODE_4BYTES==ULen )
    {
        Unicode[Len] = 0;
        Unicode[Len+1] = 0;
        if ( 0xFC==(UCHAR)(UTF8[UPos]&0xFE) )
        {
            FEUNICODE2UTF8_BUFSIZE_TOSMALL(UPos,6,Size);
            Unicode[Len]   = ((UTF8[UPos]&0x01)<<4)|((UTF8[UPos+1]&0x3C)>>2);
            Unicode[Len+1] = ((UTF8[UPos+1]&0x03)<<6)|(UTF8[UPos+2]&0x3F);
            UPos += 3;
        }
        else if ( 0xF8==(UCHAR)(UTF8[UPos]&0xFC) )
        {
            FEUNICODE2UTF8_BUFSIZE_TOSMALL(UPos,5,Size);
            Unicode[Len]   = UTF8[UPos]&0x03;
            Unicode[Len+1] = (((UTF8[UPos+1])&0x3F)<<2) \
                |((UTF8[UPos+2]&0x30)>>4);
            UPos += 2;
        }
        else if ( 0xF0==(UCHAR)(UTF8[UPos]&0xF8) )
        {
            FEUNICODE2UTF8_BUFSIZE_TOSMALL(UPos,4,Size);
            Unicode[Len]   = 0;
            Unicode[Len+1] = ((UTF8[UPos]&0x07)<<2) \
                |((UTF8[UPos+1]&0x30)>>4);
            UPos ++;
        }
        else
        {
            Unicode[Len]   = 0;
            Unicode[Len+1] = 0;
        }
        Len = 2;
        if ( 0!=UPos )
        {
            Unicode[Len]   = ((UTF8[UPos]&0x0F)<<4)|((UTF8[UPos+1]&0x3F)>>4);
            Unicode[Len+1] = ((UTF8[UPos+1]&0x03)<<6)|(UTF8[UPos+1]&0x3F);
            UPos += 3;
            Len += 2;
        }
    }
    if ( 0==UPos )
    {
        if ( 0xE0==(UCHAR)(UTF8[UPos]&0xF0) )
        {
            FEUNICODE2UTF8_BUFSIZE_TOSMALL(UPos,3,Size);
            Unicode[Len] = ((UTF8[UPos]&0x0F)<<4)|((UTF8[UPos+1]&0x3C)>>2);
            Unicode[Len+1] = ((UTF8[UPos+1]&0x03)<<6)|(UTF8[UPos+2]&0x3F);
            UPos += 3;
        }
        else if ( 0xC0==(UCHAR)(UTF8[UPos]&0xE0) )
        {
            FEUNICODE2UTF8_BUFSIZE_TOSMALL(UPos,2,Size);
            Unicode[Len] = (UTF8[UPos]&0x1C)>>2;
            Unicode[Len+1] = ((UTF8[UPos]&0x03)<<6)|(UTF8[UPos+1]&0x3F);
            UPos += 2;
        }
        else if ( 0x00==(UCHAR)(UTF8[UPos]&0x80) )
        {
            FEUNICODE2UTF8_BUFSIZE_TOSMALL(UPos,1,Size);
            Unicode[Len] = 0;
            Unicode[Len+1] = UTF8[UPos]&0x7F;
            UPos ++;
        }
        ULen += 2;
    }
    *PLen = UPos;
    return iRtn;
}

INT32 FE2BytesUniToUTF8BigEndian(BYTE *Unicode,INT32 ULen \
    ,BYTE *UTF8,INT32 *PLen,INT32 Size)
{
    INT32 iRtn;
    INT32 UPos;
    INT32 Len;
    INT32 LL;

    if ( (NULL==Unicode)||(NULL==UTF8)||(NULL==PLen) )
    {
        return FERTN_ERAPP_ARG;
    }
    iRtn = FERTN_OK;
    *PLen = 0;
    UPos = 0;
    Len = 0;
    while ( (UPos+FEUNICODE_2BYTES<=ULen)&&(Len<Size) )
    {
        if ( FERTN_OK!=(iRtn=FEUniToUTF8BigEndian(Unicode+UPos \
            ,FEUNICODE_2BYTES \
            ,UTF8+Len,&LL,Size-Len)) )
        {
            break;
        }
        UPos += FEUNICODE_2BYTES;
        Len += LL;
    }/* while ( UPos<ULen ) */
    if ( FERTN_OK==iRtn )
    {
        *PLen = Len;
    }
    return iRtn;
}

INT32 FE2BytesUTF8ToUniBigEndian(BYTE *UTF8,INT32 ULen \
    ,BYTE *Unicode,INT32 *PLen,INT32 Size)
{
    INT32 iRtn;
    INT32 UPos;
    INT32 Len;
    INT32 LL;

    if ( (NULL==UTF8)||(NULL==Unicode)||(NULL==PLen) )
    {
        return FERTN_ERAPP_ARG;
    }
    iRtn = FERTN_OK;
    *PLen = 0;
    UPos = 0;
    Len = 0;
    while ( (UPos<ULen)&&(Len+FEUNICODE_2BYTES<Size) )
    {
        LL = ULen - UPos;
        if ( FERTN_OK!=(iRtn=FEUTF8ToUniBigEndian(UTF8+UPos,&LL \
            ,Unicode+Len,FEUNICODE_2BYTES,Size-Len)) )
        {
            break;
        }
        UPos += LL;
        Len += FEUNICODE_2BYTES;
    }
    if ( FERTN_OK==iRtn )
    {
        *PLen = Len;
    }
    return iRtn;
}

INT32 FE4BytesUniToUTF8BigEndian(BYTE *Unicode,INT32 ULen \
    ,BYTE *UTF8,INT32 *PLen,INT32 Size)
{
    INT32 iRtn;
    INT32 UPos;
    INT32 Len;
    INT32 LL;

    if ( (NULL==Unicode)||(NULL==UTF8)||(NULL==PLen) )
    {
        return FERTN_ERAPP_ARG;
    }
    iRtn = FERTN_OK;
    *PLen = 0;
    UPos = 0;
    Len = 0;
    while ( (UPos+FEUNICODE_4BYTES<=ULen)&&(Len<Size) )
    {
        if ( FERTN_OK!=(iRtn=FEUniToUTF8BigEndian(Unicode+UPos \
            ,FEUNICODE_4BYTES \
            ,UTF8+Len,&LL,Size-Len)) )
        {
            break;
        }
        UPos += FEUNICODE_4BYTES;
        Len += LL;
    }/* while ( UPos<ULen ) */
    if ( FERTN_OK==iRtn )
    {
        *PLen = Len;
    }
    return iRtn;
}

INT32 FE4BytesUTF8ToUniBigEndian(BYTE *UTF8,INT32 ULen \
    ,BYTE *Unicode,INT32 *PLen,INT32 Size)
{
    INT32 iRtn;
    INT32 UPos;
    INT32 Len;
    INT32 LL;

    if ( (NULL==UTF8)||(NULL==Unicode)||(NULL==PLen) )
    {
        return FERTN_ERAPP_ARG;
    }
    iRtn = FERTN_OK;
    *PLen = 0;
    UPos = 0;
    Len = 0;
    while ( (UPos<ULen)&&(Len+FEUNICODE_4BYTES<Size) )
    {
        LL = ULen - UPos;
        if ( FERTN_OK!=(iRtn=FEUTF8ToUniBigEndian(UTF8+UPos,&LL \
            ,Unicode+Len,FEUNICODE_4BYTES,Size-Len)) )
        {
            break;
        }
        UPos += LL;
        Len += FEUNICODE_4BYTES;
    }
    if ( FERTN_OK==iRtn )
    {
        *PLen = Len;
    }
    return iRtn;
}

#ifdef __cplusplus
}
#endif

