/***************************************************************************/
/**[File Name    ]ysrtn.h                                                 **/
/**[File Path    ]$(TOPDIR)/include/                                      **/
/**[Library Name ]                                                        **/
/**[Library Path ]                                                        **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define rtncode                                          **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#ifndef YSRTN_H__
#define YSRTN_H__

#include <macro.h>
#include <define.h>
#include <rtncode.h>

#ifdef __cplusplus
extern "C" {
#endif

#define YSRTN_CMP(v,Rtn)           RTNCODE_CMP(v,Rtn)
#define YSRTN_CMP1(v)              RTNCODE_CMP1(v)   
#define YSRTN_CMPOKER(v)           RTNCODE_CMPOKER(v)
#define YSRTN_CMPBOOL(v)           RTNCODE_CMPBOOL(v)

#define YSRTN_OK                    RTNCODE_OK 
#define YSRTN_OK1                   RTNCODE_OK1
#define YSRTN_OK2                   RTNCODE_OK2
#define YSRTN_OK3                   RTNCODE_OK3
#define YSRTN_OK4                   RTNCODE_OK4
                                             
#define YSRTN_ER                    RTNCODE_ER 
#define YSRTN_ER2                   RTNCODE_ER2
#define YSRTN_ER3                   RTNCODE_ER3
#define YSRTN_ER4                   RTNCODE_ER4

/***************************************************************************/
/** System error (-100~-119)                                              **/
/***************************************************************************/
#define YSRTN_ERBASE                RTNCODE_ERBASE               
#define YSRTN_ERBASE_SYS            RTNCODE_ERBASE_SYS           
#define YSRTN_ERSYS_MALLOC          RTNCODE_ERSYS_MALLOC         
#define YSRTN_ERSYS_UN2BYTES2UTF8   RTNCODE_ERSYS_UN2BYTES2UTF8  
#define YSRTN_ERSYS_UNICODENOT      RTNCODE_ERSYS_UNICODENOT     
#define YSRTN_ERSYS_UN2BYTESNOT     RTNCODE_ERSYS_UN2BYTESNOT    
#define YSRTN_ERSYS_UN4BYTESNOT     RTNCODE_ERSYS_UN4BYTESNOT    
#define YSRTN_ERSYS_DLSYM           RTNCODE_ERSYS_DLSYM          
                                    
/***************************************************************************/
/** System error (-120~-139)                                              **/
/***************************************************************************/
#define YSRTN_ERBASE_FILE           RTNCODE_ERBASE_FILE          
#define YSRTN_ERFILE_DIROPEN        RTNCODE_ERFILE_DIROPEN       
#define YSRTN_ERFILE_MKDIR          RTNCODE_ERFILE_MKDIR         
#define YSRTN_ERFILE_OPEN           RTNCODE_ERFILE_OPEN          
#define YSRTN_ERFILE_LOCK           RTNCODE_ERFILE_LOCK          
#define YSRTN_ERFILE_READ           RTNCODE_ERFILE_READ          
#define YSRTN_ERFILE_WRITE          RTNCODE_ERFILE_WRITE         
                                    
/***************************************************************************/
/** System error (-140~-159)                                              **/
/***************************************************************************/
#define YSRTN_ERBASE_SOCK           RTNCODE_ERBASE_SOCK          
#define YSRTN_ERSOCK_SOCKET         RTNCODE_ERSOCK_SOCKET        
#define YSRTN_ERSOCK_LISTEN         RTNCODE_ERSOCK_LISTEN        
#define YSRTN_ERSOCK_BIND           RTNCODE_ERSOCK_BIND          
#define YSRTN_ERSOCK_READ           RTNCODE_ERSOCK_READ          
#define YSRTN_ERSOCK_WRITE          RTNCODE_ERSOCK_WRITE         
#define YSRTN_ERSOCK_CONNECT        RTNCODE_ERSOCK_CONNECT       
#define YSRTN_ERSOCK_PTON           RTNCODE_ERSOCK_PTON          
#define YSRTN_ERSOCK_SOCKNAME       RTNCODE_ERSOCK_SOCKNAME      
#define YSRTN_ERSOCK_SELECT         RTNCODE_ERSOCK_SELECT        
#define YSRTN_ERPKG_PACK            RTNCODE_ERPKG_PACK
#define YSRTN_ERPKG_UNPACK          RTNCODE_ERPKG_UNPACK
                                    
/***************************************************************************/
/** System error (-160~-199)                                              **/
/***************************************************************************/
#define YSRTN_ERBASE_PTHREAD        RTNCODE_ERBASE_PTHREAD       
#define YSRTN_ERTHD_MUTEX           RTNCODE_ERTHD_MUTEX          
#define YSRTN_ERTHD_COND            RTNCODE_ERTHD_COND           
#define YSRTN_ERTHD_BUSY            RTNCODE_ERTHD_BUSY           
#define YSRTN_ERTHD_TIMEOUT         RTNCODE_ERTHD_TIMEOUT        
#define YSRTN_ERTHD_RESFREE         RTNCODE_ERTHD_RESFREE        
                                    
/***************************************************************************/
/** System error (-200~-500)                                              **/
/***************************************************************************/
#define YSRTN_ERBASE_APP            RTNCODE_ERBASE_APP           
#define YSRTN_ERAPP_ARG             RTNCODE_ERAPP_ARG            
#define YSRTN_ERAPP_SIZE            RTNCODE_ERAPP_SIZE           
#define YSRTN_ERAPP_LOCK            RTNCODE_ERAPP_LOCK           
#define YSRTN_ERAPP_INITARG         RTNCODE_ERAPP_INITARG        
#define YSRTN_ERAPP_BINARY          RTNCODE_ERAPP_BINARY         
#define YSRTN_ERAPP_CWDDIR          RTNCODE_ERAPP_CWDDIR         
#define YSRTN_ERAPP_APPDIR          RTNCODE_ERAPP_APPDIR         
#define YSRTN_ERAPP_DIRS            RTNCODE_ERAPP_DIRS           
#define YSRTN_ERAPP_LOGARGS         RTNCODE_ERAPP_LOGARGS        
#define YSRTN_ERAPP_LOADLOGLIST     RTNCODE_ERAPP_LOADLOGLIST    
#define YSRTN_ERAPP_INITFIFO        RTNCODE_ERAPP_INITFIFO       
#define YSRTN_ERAPP_INITMGR         RTNCODE_ERAPP_INITMGR        
                                    
#define YSRTN_ERAPP_LOADCFG         RTNCODE_ERAPP_LOADCFG        
#define YSRTN_ERAPP_SAVECFG         RTNCODE_ERAPP_SAVECFG        
#define YSRTN_ERAPP_CFG             RTNCODE_ERAPP_CFG            
#define YSRTN_ERAPP_NOTFOUNDCFG     RTNCODE_ERAPP_NOTFOUNDCFG    
#define YSRTN_ERAPP_ANALYSE         RTNCODE_ERAPP_ANALYSE
#define YSRTN_ERAPP_EXISTVALUE      RTNCODE_ERAPP_EXISTVALUE
                                    
#define YSRTN_ERAPP_LOADDICT        RTNCODE_ERAPP_LOADDICT       
#define YSRTN_ERAPP_SAVEDICT        RTNCODE_ERAPP_SAVEDICT       
#define YSRTN_ERAPP_EXISTDICT       RTNCODE_ERAPP_EXISTDICT      
                                    
#define YSRTN_ERAPP_LOADSERVINFO    RTNCODE_ERAPP_LOADSERVINFO   
#define YSRTN_ERAPP_LOADSERVINFO2   RTNCODE_ERAPP_LOADSERVINFO2  
#define YSRTN_ERAPP_SAVESERVINFO    RTNCODE_ERAPP_SAVESERVINFO   
#define YSRTN_ERAPP_EXISTSERVINFO   RTNCODE_ERAPP_EXISTSERVINFO  
                                    
#define YSRTN_ERAPP_SAVESERVCALL    RTNCODE_ERAPP_SAVESERVCALL   
#define YSRTN_ERAPP_SCALL_NEWBUS    RTNCODE_ERAPP_SCALL_NEWBUS   
#define YSRTN_ERAPP_SCALL_SAVEBUS   RTNCODE_ERAPP_SCALL_SAVEBUS  

#define YSRTN_ERAPP_USERTHD         RTNCODE_ERAPP_USERTHD
                                                               
#define YSRTN_ERBASE_VAR            RTNCODE_ERBASE_VAR
#define YSRTN_ERVAR_VT              RTNCODE_ERVAR_VT
#define YSRTN_ERVAR_NEW             RTNCODE_ERVAR_NEW
#define YSRTN_ERVAR_ADD             RTNCODE_ERVAR_ADD
#define YSRTN_ERVAR_GET             RTNCODE_ERVAR_GET
#define YSRTN_ERVAR_PACK            RTNCODE_ERVAR_PACK
#define YSRTN_ERVAR_UNPACK          RTNCODE_ERVAR_UNPACK
                                    
#define YSRTN_ERBASE_SERVICE        RTNCODE_ERBASE_SERVICE       
#define YSRTN_ERSERV_GETINFO        RTNCODE_ERSERV_GETINFO       
#define YSRTN_ERSERV_SAVERTN        RTNCODE_ERSERV_SAVERTN       

#ifdef __cplusplus
}
#endif

#endif /* #ifndef YSRTN_H__ */ 

