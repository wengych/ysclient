/***************************************************************************/
/**[File Name    ]fedef.h                                                 **/
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
#ifndef FEDEF_H__
#define FEDEF_H__

#include <define.h>
#include <macro.h>
#include <rtncode.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FELOG_LEVEL_ALL         LOG_LEVEL_ALL  
#define FELOG_LEVEL_DEBUG       LOG_LEVEL_DEBUG
#define FELOG_LEVEL_INFO        LOG_LEVEL_INFO 
#define FELOG_LEVEL_WARN        LOG_LEVEL_WARN 
#define FELOG_LEVEL_ERROR       LOG_LEVEL_ERROR
#define FELOG_LEVEL_FATAL       LOG_LEVEL_FATAL
#define FELOG_LEVEL_OFF         LOG_LEVEL_OFF  

/***************************************************************************/
/**  define variable in environment                                       **/
/***************************************************************************/
#define FEENV_APPDIR            ENV_APPDIR     
#define FEENV_HOME              ENV_HOME       
#define FEENV_LOGLEVEL          ENV_LOGLEVEL   
#define FEENV_LOGFILE           ENV_LOGFILE    
#define FEENV_LOGLISTFILE       ENV_LOGLISTFILE
#define FEENV_LOGDIR            ENV_LOGDIR     
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
/**  default log level is "FELOG_LEVEL_ERROR"                             **/
/***************************************************************************/
/** LOGFILEPATH=$(LOGDIR)/output                                         **/
/** LOGDIR=$(APPDIR)/log                                                 **/
#define FEENV_DEFAULT_DIR               ENV_DEFAULT_DIR         
#define FEENV_LOGDIR_DEFAULT            ENV_LOGDIR_DEFAULT      
#define FEENV_LOGFILE_DEFAULT           ENV_LOGFILE_DEFAULT     
#define FEENV_LOGLISTFILE_DEFAULT       ENV_LOGLISTFILE_DEFAULT 
#define FEENV_LOGLEVEL_DEFAULT          ENV_LOGLEVEL_DEFAULT    
/***************************************************************************/
/***************************************************************************/

#define FEFILE_MAX_BUFFER           FILE_MAX_BUFFER
#define FEVARNAMELEN                VARNAMELEN

/***************************************************************************/
/**  define character set                                                 **/
/***************************************************************************/
#define FECHARSET_ASCII         CHARSET_ASCII 
#define FECHARSET_BIN           CHARSET_BIN   
#define FECHARSET_UCS2          CHARSET_UCS2  
#define FECHARSET_GBK           CHARSET_GBK   
#define FECHARSET_UTF8          CHARSET_UTF8  
#define FECHARSET_UTF16         CHARSET_UTF16 

/***************************************************************************/
/***************************************************************************/
#define FETIME_HOUR_IN_DAY        TIME_HOUR_IN_DAY 
#define FETIME_MIN_IN_HOUR        TIME_MIN_IN_HOUR 
#define FETIME_SEC_IN_MIN         TIME_SEC_IN_MIN  
#define FETIME_MIN_IN_DAY         TIME_MIN_IN_DAY  
#define FETIME_SEC_IN_HOUR        TIME_SEC_IN_HOUR 
#define FETIME_SEC_IN_DAY         TIME_SEC_IN_DAY  
#define FETIME_ISMON(m)           TIME_ISMON(m)    )
#define FETIME_ISDAY_(d)          TIME_ISDAY_(d)   )
#define FETIME_ISHOUR(h)          TIME_ISHOUR(h)   
#define FETIME_ISMIN(m)           TIME_ISMIN(m)    
#define FETIME_ISSEC(s)           TIME_ISSEC(s)    
/***************************************************************************/
/***************************************************************************/

#ifdef __DEBUG__
#define FEDEBUG_STEP \
    fprintf(stderr,"%s,%d %s\n",__FILE__,__LINE__,__func__)
#define FEDEBUG_PSTEP \
    fprintf(stderr,"%s,%d %s --%d\n" \
        ,__FILE__,__LINE__,__func__,(INT32)pthread_self())
#endif

#define FEDEBUG_TRACE(Buf) \
    sprintf(Buf,"%s,%d %s",__FILE__,__LINE__,__func__)
#define FEDEBUG_TRACES  __FILE__,__LINE__,__func__


#define FECAL_MIN(N1,N2)            CALCULATE_MIN(N1,N2) 
#define FECAL_MAX(N1,N2)            CALCULATE_MAX(N1,N2)

#define FELUCK_NUM                  LUCK_NUM  
#define FELUCK_INIT(v)              ((v)=FELUCK_NUM)
#define FELUCK_INIT_NOT(v)          ((v)=0)
#define FELUCK_ISINIT(v)            (FERTN_CMPBOOL(FELUCK_NUM==(v)))

/****************************************************************************/
/** Var Array                                                              **/
/****************************************************************************/
#define FEARRAYSIZE_MIN             ARRAYSIZE_MIN
#define FEARRAYSIZE_MAX             ARRAYSIZE_MAX
#define FEARRAYSIZE_GETMIN(Size)   (FECAL_MIN(0,(Size)))
#define FEARRAYSIZE_GETMAX(Max) \
    ((0==FECAL_MAX(0,(Max))) \
    ?FEARRAYSIZE_MAX \
    :FECAL_MIN(FECAL_MIN(1,(Max)),FEARRAYSIZE_MAX))
#define FEARRAYSIZE_GETSIZE(Max,Size) \
    (FECAL_MIN(FEARRAYSIZE_GETMAX((Max)),FECAL_MAX(1,(Size))))
#define FEARRAYSIZE_ISREALLOC(Max,Size) \
    FERTN_CMP(FEARRAYSIZE_GETMAX((Max))>=FECAL_MAX(0,(Size)))
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/** Endian                                                                 **/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

/***************************************************************************/
/**                                                                       **/
/***************************************************************************/
#define FERTN_CMP(v,Rtn)           RTNCODE_CMP(v,Rtn)
#define FERTN_CMP1(v)              RTNCODE_CMP1(v)   
#define FERTN_CMPOKER(v)           RTNCODE_CMPOKER(v)
#define FERTN_CMPBOOL(v)           RTNCODE_CMPBOOL(v)

#define FERTN_OK                    RTNCODE_OK 
#define FERTN_OK1                   RTNCODE_OK1
#define FERTN_OK2                   RTNCODE_OK2
#define FERTN_OK3                   RTNCODE_OK3
#define FERTN_OK4                   RTNCODE_OK4
                                             
#define FERTN_ER                    RTNCODE_ER 
#define FERTN_ER2                   RTNCODE_ER2
#define FERTN_ER3                   RTNCODE_ER3
#define FERTN_ER4                   RTNCODE_ER4

/***************************************************************************/
/** System error (-100~-119)                                              **/
/***************************************************************************/
#define FERTN_ERBASE                RTNCODE_ERBASE               
#define FERTN_ERBASE_SYS            RTNCODE_ERBASE_SYS           
#define FERTN_ERSYS_MALLOC          RTNCODE_ERSYS_MALLOC         
#define FERTN_ERSYS_UN2BYTES2UTF8   RTNCODE_ERSYS_UN2BYTES2UTF8  
#define FERTN_ERSYS_UNICODENOT      RTNCODE_ERSYS_UNICODENOT     
#define FERTN_ERSYS_UN2BYTESNOT     RTNCODE_ERSYS_UN2BYTESNOT    
#define FERTN_ERSYS_UN4BYTESNOT     RTNCODE_ERSYS_UN4BYTESNOT    
#define FERTN_ERSYS_DLSYM           RTNCODE_ERSYS_DLSYM          
                                    
/***************************************************************************/
/** System error (-120~-139)                                              **/
/***************************************************************************/
#define FERTN_ERBASE_FILE           RTNCODE_ERBASE_FILE          
#define FERTN_ERFILE_DIROPEN        RTNCODE_ERFILE_DIROPEN       
#define FERTN_ERFILE_MKDIR          RTNCODE_ERFILE_MKDIR         
#define FERTN_ERFILE_OPEN           RTNCODE_ERFILE_OPEN          
#define FERTN_ERFILE_LOCK           RTNCODE_ERFILE_LOCK          
#define FERTN_ERFILE_READ           RTNCODE_ERFILE_READ          
#define FERTN_ERFILE_WRITE          RTNCODE_ERFILE_WRITE         
                                    
/***************************************************************************/
/** System error (-140~-159)                                              **/
/***************************************************************************/
#define FERTN_ERBASE_SOCK           RTNCODE_ERBASE_SOCK          
#define FERTN_ERSOCK_SOCKET         RTNCODE_ERSOCK_SOCKET        
#define FERTN_ERSOCK_LISTEN         RTNCODE_ERSOCK_LISTEN        
#define FERTN_ERSOCK_BIND           RTNCODE_ERSOCK_BIND          
#define FERTN_ERSOCK_READ           RTNCODE_ERSOCK_READ          
#define FERTN_ERSOCK_WRITE          RTNCODE_ERSOCK_WRITE         
#define FERTN_ERSOCK_CONNECT        RTNCODE_ERSOCK_CONNECT       
#define FERTN_ERSOCK_PTON           RTNCODE_ERSOCK_PTON          
#define FERTN_ERSOCK_SOCKNAME       RTNCODE_ERSOCK_SOCKNAME      
#define FERTN_ERSOCK_SELECT         RTNCODE_ERSOCK_SELECT        
#define FERTN_ERPKG_PACK            RTNCODE_ERPKG_PACK
#define FERTN_ERPKG_UNPACK          RTNCODE_ERPKG_UNPACK
                                    
/***************************************************************************/
/** System error (-160~-199)                                              **/
/***************************************************************************/
#define FERTN_ERBASE_PTHREAD        RTNCODE_ERBASE_PTHREAD       
#define FERTN_ERTHD_MUTEX           RTNCODE_ERTHD_MUTEX          
#define FERTN_ERTHD_COND            RTNCODE_ERTHD_COND           
#define FERTN_ERTHD_BUSY            RTNCODE_ERTHD_BUSY           
#define FERTN_ERTHD_TIMEOUT         RTNCODE_ERTHD_TIMEOUT        
#define FERTN_ERTHD_RESFREE         RTNCODE_ERTHD_RESFREE        
                                    
/***************************************************************************/
/** System error (-200~-500)                                              **/
/***************************************************************************/
#define FERTN_ERBASE_APP            RTNCODE_ERBASE_APP           
#define FERTN_ERAPP_ARG             RTNCODE_ERAPP_ARG            
#define FERTN_ERAPP_SIZE            RTNCODE_ERAPP_SIZE           
#define FERTN_ERAPP_LOCK            RTNCODE_ERAPP_LOCK           
#define FERTN_ERAPP_INITARG         RTNCODE_ERAPP_INITARG        
#define FERTN_ERAPP_BINARY          RTNCODE_ERAPP_BINARY         
#define FERTN_ERAPP_CWDDIR          RTNCODE_ERAPP_CWDDIR         
#define FERTN_ERAPP_APPDIR          RTNCODE_ERAPP_APPDIR         
#define FERTN_ERAPP_DIRS            RTNCODE_ERAPP_DIRS           
#define FERTN_ERAPP_LOGARGS         RTNCODE_ERAPP_LOGARGS        
#define FERTN_ERAPP_LOADLOGLIST     RTNCODE_ERAPP_LOADLOGLIST    
#define FERTN_ERAPP_INITFIFO        RTNCODE_ERAPP_INITFIFO       
#define FERTN_ERAPP_INITMGR         RTNCODE_ERAPP_INITMGR        
                                    
#define FERTN_ERAPP_LOADCFG         RTNCODE_ERAPP_LOADCFG        
#define FERTN_ERAPP_SAVECFG         RTNCODE_ERAPP_SAVECFG        
#define FERTN_ERAPP_CFG             RTNCODE_ERAPP_CFG            
#define FERTN_ERAPP_NOTFOUNDCFG     RTNCODE_ERAPP_NOTFOUNDCFG    
#define FERTN_ERAPP_ANALYSE         RTNCODE_ERAPP_ANALYSE
#define FERTN_ERAPP_EXISTVALUE      RTNCODE_ERAPP_EXISTVALUE
                                    
#define FERTN_ERAPP_LOADDICT        RTNCODE_ERAPP_LOADDICT       
#define FERTN_ERAPP_SAVEDICT        RTNCODE_ERAPP_SAVEDICT       
#define FERTN_ERAPP_EXISTDICT       RTNCODE_ERAPP_EXISTDICT      
                                    
#define FERTN_ERAPP_LOADSERVINFO    RTNCODE_ERAPP_LOADSERVINFO   
#define FERTN_ERAPP_LOADSERVINFO2   RTNCODE_ERAPP_LOADSERVINFO2  
#define FERTN_ERAPP_SAVESERVINFO    RTNCODE_ERAPP_SAVESERVINFO   
#define FERTN_ERAPP_EXISTSERVINFO   RTNCODE_ERAPP_EXISTSERVINFO  
                                    
#define FERTN_ERAPP_SAVESERVCALL    RTNCODE_ERAPP_SAVESERVCALL   
#define FERTN_ERAPP_SCALL_NEWBUS    RTNCODE_ERAPP_SCALL_NEWBUS   
#define FERTN_ERAPP_SCALL_SAVEBUS   RTNCODE_ERAPP_SCALL_SAVEBUS  
                                                               
#define FERTN_ERBASE_VAR            RTNCODE_ERBASE_VAR           
#define FERTN_ERVAR_VT              RTNCODE_ERVAR_VT             
#define FERTN_ERVAR_NEW             RTNCODE_ERVAR_NEW            
#define FERTN_ERVAR_ADD             RTNCODE_ERVAR_ADD            
#define FERTN_ERVAR_GET             RTNCODE_ERVAR_GET
#define FERTN_ERVAR_PACK            RTNCODE_ERVAR_PACK           
#define FERTN_ERVAR_UNPACK          RTNCODE_ERVAR_UNPACK         
                                    
#define FERTN_ERBASE_SERVICE        RTNCODE_ERBASE_SERVICE       
#define FERTN_ERSERV_GETINFO        RTNCODE_ERSERV_GETINFO       
#define FERTN_ERSERV_SAVERTN        RTNCODE_ERSERV_SAVERTN       

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FEDEF_H__ */ 

