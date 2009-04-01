/***************************************************************************/
/**[File Name    ]defineh                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define const variable                                   **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef DEFINE_H__
#define DEFINE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_LEVEL_ALL         10
#define LOG_LEVEL_DEBUG       20
#define LOG_LEVEL_INFO        30
#define LOG_LEVEL_WARN        40
#define LOG_LEVEL_ERROR       50
#define LOG_LEVEL_FATAL       60
#define LOG_LEVEL_OFF         70
#define LOG_LEVEL_STR(v) \
    (((LOG_LEVEL_ALL==(v)/10)?"All" \
        :((LOG_LEVEL_DEBUG==(v)/10)?"Debug" \
            :((LOG_LEVEL_INFO==(v)/10)?"Info" \
                :((LOG_LEVEL_WARN==(v)/10)?"Warn" \
                    :((LOG_LEVEL_ERROR==(v)/10)?"Error":"Off") \
                ) \
            ) \
        ) \
    ))

/***************************************************************************/
/**  define variable in environment                                       **/
/***************************************************************************/
#define ENV_APPDIR            "APPDIR"
#define ENV_HOME              "HOME"
#define ENV_LOGLEVEL          "LOGLEVEL"
#define ENV_LOGFILE           "LOGFILE"
#define ENV_LOGLISTFILE       "LOGLISTFILE"
#define ENV_LOGDIR            "LOGDIR" 
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  define logfile                                                       **/
/**  logpath:                                                             **/
/**    1. user define                                                     **/
/**    2. $APPDIR/log                                                     **/
/**    3. $APPDIR                                                         **/
/**    4. $HOME/log                                                       **/
/**    5. $HOME                                                           **/
/**  logfile:                                                             **/
/**    1. user define (.log, .trace)                                      **/
/**    2. output      (.log, .trace)                                      **/
/**  default log level is "LOG_LEVEL_ERROR"                             **/
/***************************************************************************/
/** LOGFILEPATH=$(LOGDIR)/output                                         **/
/** LOGDIR=$(APPDIR)/log                                                 **/
#define ENV_DEFAULT_DIR               "/tmp"
#define ENV_LOGDIR_DEFAULT            "log" 
#define ENV_LOGFILE_DEFAULT           "output"
#define ENV_LOGLISTFILE_DEFAULT       "loglist.cfg"
#define ENV_LOGLEVEL_DEFAULT          LOG_LEVEL_ERROR
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  define bufsize                                                       **/
/***************************************************************************/
#define BITSOFBYTE                  8
#define BUFSIZE_8                   8
#define BUFSIZE_16                  16
#define BUFSIZE_32                  32
#define BUFSIZE_64                  64
#define BUFSIZE_128                 128
#define BUFSIZE_256                 256
#define BUFSIZE_512                 512
#define BUFSIZE_1024                1024
#define BUFSIZE_2048                2048
#define BUFSIZE_4096                4096
#define BUFSIZE_8192                8192
#define BUFSIZE_MAX                 16777216 /* 16*1024*1024 */

#ifndef PATH_MAX
#define PATH_MAX                    (BUFSIZE_4096)
#endif
 
#ifndef MAXPATH
#define MAXPATH                     (PATH_MAX)
/*
PATH_MAX = 4096
#define MAXPATH                     (_PC_PATH_MAX)
#define MAXPATH                     (BUFSIZE_256-1)
*/
#endif
#ifndef MAXFUNCNAME
#define MAXFUNCNAME                 (BUFSIZE_64-1)
#endif
#ifndef MAXKVBUF
#define MAXKEYBUF                   (BUFSIZE_64-1)
#define MAXVALUEBUF                 (BUFSIZE_1024-1)
#endif
#define MAXHEXLOGLINE               16
#define MAXHEXLOGINDEXLEN           5 
#define MAXHEXLOGINDEXLEN_FMT       "%05d"

#define FILE_MAX_BUFFER             BUFSIZE_4096
#define LOG_MAX_BUFFER              BUFSIZE_4096
#define PKG_MIN_BUFFER              BUFSIZE_512
#define TMP_MAX_BUFFER              BUFSIZE_1024

#define VARNAMELEN                  (MAXFUNCNAME-BUFSIZE_16)

/***************************************************************************/
/***************************************************************************/
#define IP_MAX_LEN                  (BUFSIZE_16-1)
#define TCP_LISTEN                  5

#define SOCK_MIN_BUFFER             BUFSIZE_4096
#define TCP_TIMEOUT                 75

/***************************************************************************/
/***************************************************************************/

typedef char            BYTE;
typedef unsigned char   UCHAR;
typedef short           INT16;
typedef unsigned short  UINT16;
typedef int             INT32;
typedef unsigned int    UINT32;
#ifdef __MACHINE_OS_64__
typedef long            INT64;
typedef unsigned long   UINT64;
#else
typedef long long       INT64;
typedef unsigned long long UINT64;
#endif
typedef INT32           BOOL;
typedef double          DOUBLE;

#define BOOL_SIZE       (sizeof(BOOL))
#define BYTE_SIZE       (sizeof(BYTE))
#define UCHAR_SIZE      (sizeof(UCHAR))
#define INT16_SIZE      (sizeof(INT16))
#define UINT16_SIZE     (sizeof(UINT16))
#define INT32_SIZE      (sizeof(INT32))
#define UINT32_SIZE     (sizeof(UINT32))
#define INT64_SIZE      (sizeof(INT64))
#define UINT64_SIZE     (sizeof(UINT64))
#define BOOL_SIZE       (sizeof(BOOL))
#define DOUBLE_SIZE     (sizeof(DOUBLE))
#define POINTER_SIZE    (sizeof(void*))

typedef void (*funcarg0non)();
typedef void (*funcarg1non)(void *);
typedef void (*funcarg2non)(void *,void *);
typedef void (*funcarg3non)(void *,void *,void *);
typedef INT32 (*funcarg0int)();
typedef INT32 (*funcarg1int)(void *);
typedef INT32 (*funcarg2int)(void *,void *);
typedef INT32 (*funcarg3int)(void *,void *,void *);
typedef void* (*funcarg0vp)();
typedef void* (*funcarg1vp)(void *);
typedef void* (*funcarg2vp)(void *,void *);
typedef void* (*funcarg3vp)(void *,void *,void *);

/***************************************************************************/
/**  define character set                                                 **/
/***************************************************************************/
#define CHARSET_ASCII         0x00
#define CHARSET_BIN           0x04
#define CHARSET_UCS2          0x08
#define CHARSET_GBK           0x15
#define CHARSET_UTF8          0x81
#define CHARSET_UTF16         0x82
/***************************************************************************/
/***************************************************************************/

/***************************************************************************/
/**  define char hex                                                      **/
/***************************************************************************/
#define CHAR_ZERO               0x00
#define CHAR_TAB                0x09          /* \t */
#define CHAR_LINE               0x0A          /* \n */
#define CHAR_RETURN             0x0D          /* \r */
#define CHAR_SPACE              0x20
#define CHAR_CHANGESIGN         0x5C          /* \\ */
#define CHAR_0                  '0' 
#define CHAR_9                  '9' 
#define CHAR_A                  'A'
#define CHAR_a                  'a'
#define CHAR_F                  'F'
#define CHAR_f                  'f'
#define CHAR_Z                  'Z'
#define CHAR_z                  'z'
#define CHAR_ASTERISK           '*'
 
#define CHAR_2F                 0x2f          /* /  */
 
#define STR_KEYVALUE_SIGN       "\t =|"
#define STR_TRIMLINE_SIGN       "\t "
#define STR_CHANGELINE_SIGN     "\r\n"
#define STR_VALUE_SIGN          "\t,|"
/***************************************************************************/
/***************************************************************************/
#define TIME_HOUR_IN_DAY        24
#define TIME_MIN_IN_HOUR        60
#define TIME_SEC_IN_MIN         60
#define TIME_MIN_IN_DAY         1440
#define TIME_SEC_IN_HOUR        3600
#define TIME_SEC_IN_DAY         86400
#define TIME_ISMON(m)           ((1<=(m))&&(12>=(m)))
#define TIME_ISDAY_(d)          ((1<=(d))&&(31>=(d)))
#define TIME_ISHOUR(h)          ((0<=(h))&&(24>(h)))
#define TIME_ISMIN(m)           ((0<=(m))&&(60>(m)))
#define TIME_ISSEC(s)           ((0<=(s))&&(60>(s)))
/***************************************************************************/
/***************************************************************************/
#define VARTYPE_MEM_VT_NOT        0

#define VARTYPE_MEM_VT_BOOL       1  
#define VARTYPE_MEM_VT_BYTE       2  
#define VARTYPE_MEM_VT_INT16      3  
#define VARTYPE_MEM_VT_INT32      4  
#define VARTYPE_MEM_VT_INT64      5  
#define VARTYPE_MEM_VT_DOUBLE     6  
#define VARTYPE_MEM_VT_BIN        7  
#define VARTYPE_MEM_VT_STRING     8  
#define VARTYPE_MEM_VT_OBJECT     9  

#define VARTYPE_MEM_VT_P1         50  
#define VARTYPE_MEM_VT_P2         51  
#define VARTYPE_MEM_VT_P3         52 
#define VARTYPE_MEM_VT_P4         53 

#define VARTYPE_MEM_VT_ARRAY      101
#define VARTYPE_MEM_VT_FIFO       102
#define VARTYPE_MEM_VT_FILO       103
#define VARTYPE_MEM_VT_CICLE      104
#define VARTYPE_MEM_VT_HASH       105
#define VARTYPE_MEM_VT_LINK       106
#define VARTYPE_MEM_VT_TREE       107
#define VARTYPE_MEM_VT_XML        108
/***************************************************************************/
/***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DEFINE_H__ */ 

