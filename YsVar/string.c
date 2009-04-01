/***************************************************************************/
/**[File Name    ]string.c                                                **/
/**[File Path    ]$(SRCDIR)/libsrc/fecom                                  **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(HOME)/lib                                             **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/04/28                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for string                                  **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <fecom.h>

#ifdef __cplusplus
extern "C"{
#endif

BOOL  FECharIsSetBit(UCHAR C,INT32 Idx)
{
    if ( (0>Idx)||(BITSOFBYTE<=Idx) )
    {
        return FALSE;
    }
    return FERTN_CMPBOOL(0!= ( ((0x80) >> Idx) & C) );
}

BOOL  FECharSetBit(UCHAR *C,INT32 Idx,BOOL Flag)
{
    if ( (NULL==C)||(0>Idx)||(BITSOFBYTE<=Idx) )
    {
        return FALSE;
    }
    if ( Flag )
    {
        *C |= ((0x80) >> Idx);
    }
    else
    {
        *C &= (((0x80) >> Idx) ^ 0xFF);
    }
    return TRUE;
}

BOOL  FEGetEnv(char *Str,INT32 Size,const char *Key)
{
    if ( (NULL==Str)||(0>Size)||(NULL==Key) )
    {
        return FALSE;
    }
    if ( !strlen(Key) )
    {
        return FALSE;
    }
    memset(Str,0,Size);
    if ( NULL==getenv(Key) )
    {
        return FALSE;
    }
    snprintf(Str,Size,"%s",getenv(Key));
    return TRUE;
}

/***************************************************************************/
/**  function : FEStrIsNumber                                             **/
/**  input    :                                                           **/
/**    : str    , buf of string                                           **/
/**    : len    , length of string                                        **/
/**  output   :                                                           **/
/**  return   :                                                           **/
/**    : RTN_OK (0) , is number                                           **/
/**    : RTN_ER (-1) , not number                                         **/
/***************************************************************************/
INT32 FEStrIsNumber(char *str,INT32 len)
{
  INT32 iRtn;
  char *p;
  if ( NULL==str )
  {
    return FERTN_ERAPP_ARG;
  }
  p = str;
  iRtn = 0;
  while( (CHAR_ZERO!=*p)&&(p-str<len) )
  {
    if ( (0x30>*p)||(0x39<*p) )
    {
      iRtn = -1;
      break;
    }
    p ++;
  }
  return iRtn;
}

/***************************************************************************/
/**  function : FEStrIsHex                                                **/
/**  input    :                                                           **/
/**    : str    , buf of string                                           **/
/**    : len    , length of string                                        **/
/**  output   :                                                           **/
/**  output   :                                                           **/
/**  return   :                                                           **/
/**    : RTN_OK (0)  , is hex string                                      **/
/**    : RTN_ER (-1) , not hex string                                     **/
/***************************************************************************/
INT32 FEStrIsHex(char *str,INT32 len)
{
  INT32 iRtn;
  char *p;
  if ( NULL==str )
  {
    return FERTN_ERAPP_ARG;
  }
  p = str;
  iRtn = 0;
  while( (CHAR_ZERO!=*p)&&(p-str<len) )
  {
    if ( ((0x30<=*p)&&(0x39>=*p)) \
       ||((CHAR_a <=*p)&&(CHAR_f >=*p)) \
       ||((CHAR_A <=*p)&&(CHAR_F >=*p)) )
    {
      p ++;
      continue;
    }
    iRtn = -1;
    break;
  }
  return iRtn;
}

/***************************************************************************/
/**  function : FEStrTrimSign                                             **/
/**  input    :                                                           **/
/**    : str       , string                                               **/
/**    : sign      , sign for trimm                                       **/
/**  output   :                                                           **/
/**    : str    , string for trim                                         **/
/**  return   :                                                           **/
/***************************************************************************/
char *FEStrTrimSign(char *str,char sign)
{
  char signs[2];
  signs[0] = sign;
  signs[1] = 0;
  FEStrTrimRightSigns(str,signs);
  return FEStrTrimLeftSigns(str,signs);
}

/***************************************************************************/
/**  function : FEStrTrimRightSigns                                      **/
/**  input    :                                                           **/
/**    : str    , buf of string                                           **/
/**    : signs  , signs for trim                                          **/
/**  output   :                                                           **/
/**    : str    , string for trim right                                   **/
/**  return   :                                                           **/
/**    : str    , string for trim right                                   **/
/***************************************************************************/
char *FEStrTrimRightSigns(char *str,char *signs)
{
  char *rr;
  char t;
  char *tt;
  INT32 len;
  INT32 iLen;
  if ( (NULL==str)||(NULL==signs) )
  {
    return str;
  }
  rr = str+strlen(str);
  len = strlen(signs);
  while( --rr>=str )
  {
    tt = signs;
    while( 0x00!=*tt )
    {
      if ( 0==(iLen=FEStr2Char(&t,tt,len-(tt-signs))) )
      {
        t = *tt;
        iLen ++;
      }
      if ( t==*rr )
      {
        break;
      }
      tt += iLen;
    }
    if ( t!=*rr )
    {
      break;
    }
    *rr = 0;
  }/* while( --rr>=str ) */
  return str;
}

/***************************************************************************/
/**  function : FEStrTrimLeftSigns                                        **/
/**  input    :                                                           **/
/**    : str    , buf of string                                           **/
/**    : signs  , signs for trim                                          **/
/**  output   :                                                           **/
/**    : str    , trim left for string                                    **/
/**  return   :                                                           **/
/**    : str    , trim left for string                                    **/
/***************************************************************************/
char *FEStrTrimLeftSigns(char *str,char *signs)
{
  char *l;
  char *ll;
  char t;
  char *tt;
  INT32 iLen;
  INT32 len;
  if ( (NULL==str)||(NULL==signs) )
  {
    return str;
  }
  ll = str;
  len = strlen(signs);
  while( 0x00!=*ll )
  {
    tt = signs;
    while( 0x00!=*tt )
    {
      if ( 0==(iLen=FEStr2Char(&t,tt,len-(tt-signs))) )
      {
        t = *tt;
        iLen ++;
      }
      if ( t==*ll )
      {
        break;
      }
      tt += iLen;
    }
    if ( t!=*ll )
    {
      break;
    }
    ll ++;
  }
  if ( ll!=str )
  {
    l = str;
    while( 0x00!=*ll )
    {
      *l++ = *ll++;
    }
    memset(l,0,ll-l);
  }
  return str;
}

/***************************************************************************/
/**  function : FEStrTrimSigns                                            **/
/**  input    :                                                           **/
/**    : str    , buf of string                                           **/
/**    : signs  , signs for trim                                          **/
/**  output   :                                                           **/
/**    : str    , trim string                                             **/
/**  return   :                                                           **/
/**    : str    , trim string                                             **/
/***************************************************************************/
char *FEStrTrimSigns(char *str,char *signs)
{
  FEStrTrimRightSigns(str,signs);
  return FEStrTrimLeftSigns(str,signs);
}

char *FEStrTrimChangeLine(char *str)
{
    FEStrTrimRightSigns(str,STR_CHANGELINE_SIGN);
    return FEStrTrimRightSigns(str,STR_CHANGELINE_SIGN);
}

/***************************************************************************/
/**  function : FEStrToUpper                                              **/
/**  input    :                                                           **/
/**    : str    , string line                                             **/
/**  output   :                                                           **/
/**    : str    , upper string                                            **/
/**  return   :                                                           **/
/**    : str    , upper string                                            **/
/***************************************************************************/
char *FEStrToUpper(char *pcLine)
{
  char *p;
  if ( NULL==pcLine )
  {
    return NULL;
  }
  p = pcLine;
  while( 0x00!=*p )
  {
    *p = ((CHAR_a<=*p)&&(CHAR_z>=*p))?((*p-CHAR_a)+CHAR_A):*p;
    p ++;
  }
  return pcLine;
}

/***************************************************************************/
/**  function : FEStrToLower                                              **/
/**  input    :                                                           **/
/**    : str    , string line                                             **/
/**  output   :                                                           **/
/**    : str    , lower string                                            **/
/**  return   :                                                           **/
/**    : str    , lower string                                            **/
/***************************************************************************/
char *FEStrToLower(char *pcLine)
{
  char *p;
  if ( NULL==pcLine )
  {
    return NULL;
  }
  p = pcLine;
  while( 0x00!=*p )
  {
    *p = ((CHAR_A<=*p)&&(CHAR_Z>=*p))?((*p-CHAR_A)+CHAR_a):*p;
    p ++;
  }
  return pcLine;
}

/***************************************************************************/
/**  function : FEStrDelChar                                              **/
/**  input    :                                                           **/
/**    : str    , string line                                             **/
/**  output   :                                                           **/
/**    : str    , dest  string                                            **/
/**  return   :                                                           **/
/**    : str    , dest  string                                            **/
/***************************************************************************/
char *FEStrDelChar(char *pcLine,char ch)
{
  char *s;
  char *d;
  if ( NULL==pcLine )
  {
    return NULL;
  }
  s = pcLine;
  d = pcLine;
  while( 0x00!=*s )
  {
    if ( (unsigned char)(*s)!=(unsigned char)ch )
    {
      *d++ = *s;
    }
    s ++;
  }
  memset(d,0,s-d);
  return pcLine;
}

/***************************************************************************/
/**  function : FEStrByte2Hex                                             **/
/**  input    :                                                           **/
/**    : str    , buf                                                     **/
/**    : size   , size of buf                                             **/
/**    : ch     , ch to change                                            **/
/**  output   :                                                           **/
/**    : str    , dest  string                                            **/
/**  return   :                                                           **/
/**    : 0      , not change                                              **/
/**    : 2      , len of hex                                              **/
/**  ex       :                                                           **/
/**    : '1'    , 31                                                      **/
/**    : '2'    , 32                                                      **/
/***************************************************************************/
INT32 FEStrByte2Hex(char *str,INT32 size,BYTE ch)
{
  char tmp[16];
  if ( 2>=size )
  {
    return 0;
  }
  memset(tmp,0,sizeof(tmp));
  sprintf(tmp,"%02X",(UCHAR)ch);
  strncpy(str,tmp,2);
  return 2;
}

/***************************************************************************/
/**  function : FEStrHex2Byte                                             **/
/**  input    :                                                           **/
/**    : str    , buf                                                     **/
/**    : ch     , ch to change                                            **/
/**  output   :                                                           **/
/**    : str    , dest  string                                            **/
/**  return   :                                                           **/
/**    : 0      , not change                                              **/
/**    : 2      , len of hex                                              **/
/**  ex       :                                                           **/
/**    : "32"   , '2'                                                     **/
/***************************************************************************/
INT32 FEStrHex2Byte(BYTE *ch,char *str)
{
  UCHAR uc;
  char ch0;
  char ch1;
  if ( -1==FEStrIsHex(str,2) )
  {
    return 0;
  }
  ch0 = (('a'<=str[0])&&('z'>=str[0]))?(str[0]-'a'+'A'):str[0];
  ch1 = (('a'<=str[1])&&('z'>=str[1]))?(str[1]-'a'+'A'):str[1];
  uc = (((ch0>='0')&&(ch0<='9'))?(ch0-'0'):(ch0-'A'+10))*16;
  uc += (((ch1>='0')&&(ch1<='9'))?(ch1-'0'):(ch1-'A'+10));
  *ch = uc;
  return 2;
}

/***************************************************************************/
/**  function : FEStrBytes2Hex                                            **/
/**  input    :                                                           **/
/**    : hex      , buf for store                                         **/
/**    : size     , size of buf                                           **/
/**    : bytes    , bytes for change                                      **/
/**    : len      , length of bytes                                       **/
/**  output   :                                                           **/
/**    : hex      , hex string of bytes to change                         **/
/**  return   :                                                           **/
/**    :   0    , not change                                              **/
/**    : > 0    , len of hex string                                       **/
/***************************************************************************/
INT32 FEStrBytes2Hex(char *hex,INT32 size,char *bytes,INT32 len)
{
  INT32 i;
  if ( (NULL==hex)||(size<2*len+1)||(NULL==bytes) )
  {
    return 0;
  }
  i = 0;
  while( i<len )
  {
    FEStrByte2Hex(hex+2*i,size-2*i,bytes[i]);
    i ++;
  }
  return 2*i;
}

/***************************************************************************/
/**  function : FEStrHex2Bytes                                            **/
/**  input    :                                                           **/
/**    : bytes    , bytes for store                                       **/
/**    : size     , size of buf for store                                 **/
/**    : hex      , hex for change                                        **/
/**    : len      , length of hex                                         **/
/**  output   :                                                           **/
/**    : bytes    , bytes for store                                       **/
/**  return   :                                                           **/
/**    :   0    , not change                                              **/
/**    : > 0    , len of hex string                                       **/
/***************************************************************************/
INT32 FEStrHex2Bytes(char *bytes,INT32 size,char *hex,INT32 len)
{
  INT32 i;
  if ( (NULL==hex)||(size<len/2+1)||(NULL==bytes) )
  {
    return 0;
  }
  i = 0;
  while( 2*i<len )
  {
    FEStrHex2Byte(&(bytes[i]),hex+2*i);
    i ++;
  }
  return i;
}

/***************************************************************************/
/**  function : FEStr2Char                                                **/
/**  input    :                                                           **/
/**    : ch        , pointer for char                                     **/
/**    : pc        , string buffer                                        **/
/**    : len       , length of pc                                         **/
/**  output   :                                                           **/
/**    : ch        , char by pc( return is 1)                             **/
/**  return   :                                                           **/
/**    :  >0    , length of pc for using change                           **/
/**    :   0    , not str                                                 **/
/**  example  :                                                           **/
/**    : \t     = tabstop                                                 **/
/**    : \n     = 0x0D                                                    **/
/**    : \r     = 0x0A                                                    **/
/**    : \\     = 0x5C                                                    **/
/***************************************************************************/
INT32 FEStr2Char(char *ch,char *pc,INT32 len)
{
  INT32 iRtn;
  if ( (NULL==pc)||(NULL==ch)||(2>len) )
  {
    return 0;
  }
  if ( CHAR_CHANGESIGN!=pc[0] )
  {
    return 0;
  }
  iRtn = 2;
  switch( pc[1] )
  {
    case 't':
      *ch = CHAR_TAB;
			break;
    case 'n':
      *ch = CHAR_LINE;
			break;
    case 'r':
      *ch = CHAR_RETURN;
			break;
    case '\\':
      *ch = CHAR_CHANGESIGN;
			break;
    case 'x':
      iRtn = FEStrHex2Byte((char *)ch,pc+2);
      iRtn += (0<iRtn)?2:0;
			break;
    default:
      iRtn = 0;
      break;
  }
  return iRtn;
}

/***************************************************************************/
/**  function : FEStrESC                                                  **/
/**  input    :                                                           **/
/**    : str    , string line                                             **/
/**  output   :                                                           **/
/**    : str    , dest  string                                            **/
/***************************************************************************/
void FEStrESC(char *pcLine)
{
  char *s;
  char *d;
  INT32 len;
  INT32 iLine;
  if ( NULL==pcLine )
  {
    return ;
  }
  s = pcLine;
  d = pcLine;
  iLine = strlen(pcLine);
  while( 0x00!=*s )
  {
    if ( CHAR_CHANGESIGN==(unsigned char)*s )
    {
      if ( 0>(len=FEStr2Char(d,s,iLine-(d-s))) )
      {
        break;
      }
      if ( 0<len )
      {
        d ++;
        s += len;
        continue;
      }
    }
    if ( s!=d )
    {
      *d = *s;
    }
    s ++;
    d ++;
  }
  memset(d,0,s-d);
}

/***************************************************************************/
/**  function : FEStrGetOneWordLen                                        **/
/**  input    :                                                           **/
/**    : piWordLen , pointer for length of word                           **/
/**    : str       , string buffer                                        **/
/**    : len       , length of string                                     **/
/**    : sign      , sign string                                          **/
/**    : signlen   , length of sign string                                **/
/**  output   :                                                           **/
/**    : piWordLen , length of word                                       **/
/**  return   :                                                           **/
/**    : -1     , error                                                   **/
/**    :  0     , no word for get                                         **/
/**    : >0     , pos of word & sign in string                            **/
/***************************************************************************/
INT32 FEStrGetOneWordLen(INT32 *piWordLen \
    ,char *str,INT32 len,char *sign,INT32 signlen)
{
  INT32 iLen;
  INT32 i;
  char *p;
  char uc;
  if ( (NULL==piWordLen)||(NULL==str)||(NULL==sign)||(0>=signlen) )
  {
    return -1;
  }

  p = str;
  *piWordLen = 0;
  while( p-str<len )
  {
    for ( i=0;i<signlen;i++ )
    {
      if ( 0==(iLen=FEStr2Char(&uc,sign+i,signlen-i)) )
      {
        uc = sign[i];
      }
      else
      {
        i += iLen;
      }
      if ( uc==(*p) )
      {
        break;
      }
    }/* for ( i=0;i<signlen;i++ ) */
    if ( uc==(*p) )
    {
      *piWordLen = (p-str);
      p ++;
      break;
    }
    p ++;
  }/* while( p-str<len ) */
  if ( (p-str)==len )
  {
    *piWordLen = (p-str);
  }
  while( p-str<len )
  {
    for ( i=0;i<signlen;i++ )
    {
      if ( 0==(iLen=FEStr2Char(&uc,sign+i,signlen-i)) )
      {
        uc = sign[i];
      }
      else
      {
        i += iLen;
      }
      if ( uc==(*p) )
      {
        break;
      }
    }/* for ( i=0;i<signlen;i++ ) */
    if ( uc!=(*p) )
    {
        break;
    }
    p ++;
  }/* while( p-str<len ) */
  return p-str;
}

/***************************************************************************/
/**  function : FEStrGetOneWord                                           **/
/**  input    :                                                           **/
/**    : piWordLen , pointer for length of word when this isn't NULL      **/
/**    : pcWord    , pointer for buffer                                   **/
/**    : size      , size of buffer                                       **/
/**    : str       , string buffer                                        **/
/**    : len       , length of string                                     **/
/**    : sign      , sign string                                          **/
/**    : signelen  , length of sign string                                **/
/**  output   :                                                           **/
/**    : piWordLen , length of word when this isn't NULL                  **/
/**    : pcWord    , poINT32er for buffer                                   **/
/**  return   :                                                           **/
/**    : -1     , error                                                   **/
/**    :  0     , no word for get                                         **/
/**    : >0     , pos of word & sign in string                            **/
/***************************************************************************/
INT32 FEStrGetOneWord(INT32 *piWordLen,char *pcWord,INT32 size \
    ,char *str,INT32 len,char *sign,INT32 signlen)
{
  INT32 iRtn;
  INT32 iLen;
  if ( (NULL==pcWord)||(0>=size) )
  {
    return -1;
  }
  memset(pcWord,0,size);
  if ( 0<(iRtn=FEStrGetOneWordLen(&iLen,str,len,sign,signlen)) )
  {
    if ( NULL!=piWordLen )
    {
      *piWordLen = iLen;
    }
    memcpy(pcWord,str,(iLen>size-1)?(size-1):iLen);
  }
  return iRtn;
}

/***************************************************************************/
/**  function : FEStrFindSign                                             **/
/**  input    :                                                           **/
/**    : str       , string                                               **/
/**    : ch        , char for find in strring                             **/
/**  output   :                                                           **/
/**  return   :                                                           **/
/**    : >=0       , index of char in strring                             **/
/**    : RTN_ER_   , not find                                             **/
/***************************************************************************/
INT32 FEStrFindSign(char *str,char ch)
{
  INT32 iRtn;
  char *s;
  iRtn = -1;
  if ( NULL==str )
  {
    return iRtn;
  }
  s = str;
  while( 0!=*s )
  {
    if ( ch==*s )
    {
      iRtn = (s-str);
      break;
    }
    s++;
  }
  return iRtn;
}

/***************************************************************************/
/**  function : FEStrFindLastSign                                         **/
/**  input    :                                                           **/
/**    : str       , string                                               **/
/**    : ch        , char for find in strring                             **/
/**  output   :                                                           **/
/**  return   :                                                           **/
/**    : >=0       , index of char in strring                             **/
/**    : RTN_ER_   , not find                                             **/
/***************************************************************************/
INT32 FEStrFindLastSign(char *str,char ch)
{
  INT32 iRtn;
  char *s;
  iRtn = -1;
  if ( NULL==str )
  {
    return iRtn;
  }
  s = str+strlen(str)-1;
  while( (0!=*s)&&(s>=str) )
  {
    if ( ch==*s )
    {
      iRtn = (s-str);
      break;
    }
    s--;
  }
  return iRtn;
}

BOOL  FEEndianIsBig()
{
    INT32 i;
    i = 0x1234;
    return FERTN_CMPBOOL(0x12==((UCHAR*)(&i))[0]);
}

void  FEEndianConversion(void *E,INT32 Size)
{
    UCHAR uc;
    INT32 i;
    INT32 S;
    if ( (NULL==E)||(1>=Size) )
    {
        return;
    }
    S = Size/2;
    for ( i=0;i<S;i++ )
    {
        uc = ((UCHAR*)E)[i];
        ((UCHAR*)E)[i] = ((UCHAR*)E)[Size-1-i];
        ((UCHAR*)E)[Size-1-i] = uc;
    }
}

void  FEEndianToHost(void *E,INT32 Size)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    FEEndianConversion(E,Size);
#endif
}

void  FEEndianToNet(void *E,INT32 Size)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    FEEndianConversion(E,Size);
#endif
}

char *FESetTrace(char *Buf,INT32 Size \
    ,const char *file,const INT32 line,const char *func)
{
    if ( (NULL==Buf)||(0>=Size) )
    {
        return NULL;
    }
    if ( (NULL==file)||(NULL==func) )
    {
        return NULL;
    }
    memset(Buf,0,Size);
    snprintf(Buf,Size,"%s,%d %s",file,line,func);
    return Buf;
}

INT32 FEHexToBufLine(char *Hex,INT32 Size,INT32 MaxLine \
    ,const char *Log,INT32 Len)
{
    INT32 i;
    INT32 LL;
    INT32 HPos;
    INT32 PPos;
    char *P;

    if ( (NULL==Hex)||(0>=MaxLine)||(NULL==Log) )
    {
        return 0;
    }
    LL = FECAL_MIN(MaxLine,Len);
    if ( LL*3+1+3+LL>=Size )
    {
        return 0;
    }
    P = Hex + MaxLine*3+3+1;
    HPos = 0;
    PPos = 0;
    for ( i=0;i<LL;i++ )
    {
        if ( (0!=i)&&(0==i%8) )
        {
            strcpy(Hex+HPos," ");
            HPos ++;
        }
        sprintf(Hex+HPos,"%02X ",(UCHAR)(Log[i]));
        if ( (0x20<((UCHAR)(Log[i])))&&(0xFF>((UCHAR)(Log[i]))) )
        {
            P[PPos] = Log[i];
        }
        else
        {
            P[PPos] = '.';
        }
        HPos += 3;
        PPos ++;
    }
    for ( ;i<MaxLine;i++ )
    {
        if ( (0!=i)&&(0==i%8) )
        {
            strcpy(Hex+HPos," ");
            HPos ++;
        }
        strcpy(Hex+HPos,"   ");
        P[PPos] = '-';
        HPos += 3;
        PPos ++;
    }
    memcpy(Hex+HPos," $ ",3);
    HPos += 3;
    memcpy(P+PPos," $ ",3);
    PPos += 3;
    return HPos+PPos;
}

#ifdef __cplusplus
}
#endif

