/***************************************************************************/
/**[File Name    ]rtncode.h                                               **/
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
#ifndef RTNCODE_H__
#define RTNCODE_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE            1
#endif
#ifndef FALSE
#define FALSE           0
#endif

#define RTNCODE_CMP(v,Rtn)            ((v)?RTNCODE_OK:(Rtn))
#define RTNCODE_CMP1(v)               ((v)?RTNCODE_OK:RTNCODE_OK1)
#define RTNCODE_CMPOKER(v)            ((v)?RTNCODE_OK:RTNCODE_ER)
#define RTNCODE_CMPBOOL(v)            ((v)?TRUE:FALSE)

#define RTNCODE_OK                    0
#define RTNCODE_OK1                   1
#define RTNCODE_OK2                   2
#define RTNCODE_OK3                   3
#define RTNCODE_OK4                   4
                                     
#define RTNCODE_ER                    -1
#define RTNCODE_ER2                   -2
#define RTNCODE_ER3                   -3
#define RTNCODE_ER4                   -4
                                     
#define RTNCODE_ERBASE                -100
#define RTNCODE_ERBASE_SYS            RTNCODE_ERBASE
#define RTNCODE_ERSYS_MALLOC          (RTNCODE_ERBASE_SYS)
#define RTNCODE_ERSYS_UN2BYTES2UTF8   (RTNCODE_ERBASE_SYS-1)
#define RTNCODE_ERSYS_UNICODENOT      (RTNCODE_ERBASE_SYS-2)
#define RTNCODE_ERSYS_UN2BYTESNOT     RTNCODE_ERSYS_UNICODENOT
#define RTNCODE_ERSYS_UN4BYTESNOT     RTNCODE_ERSYS_UNICODENOT
#define RTNCODE_ERSYS_DLSYM           (RTNCODE_ERBASE_SYS-3)

#define RTNCODE_ERBASE_FILE           (RTNCODE_ERBASE_SYS-20)
#define RTNCODE_ERFILE_DIROPEN        (RTNCODE_ERBASE_FILE)
#define RTNCODE_ERFILE_MKDIR          (RTNCODE_ERBASE_FILE-1)
#define RTNCODE_ERFILE_OPEN           (RTNCODE_ERBASE_FILE-2)
#define RTNCODE_ERFILE_LOCK           (RTNCODE_ERBASE_FILE-3)
#define RTNCODE_ERFILE_READ           (RTNCODE_ERBASE_FILE-4)
#define RTNCODE_ERFILE_WRITE          (RTNCODE_ERBASE_FILE-5)

#define RTNCODE_ERBASE_SOCK           (RTNCODE_ERBASE_SYS-40)
#define RTNCODE_ERSOCK_SOCKET         (RTNCODE_ERBASE_SOCK)
#define RTNCODE_ERSOCK_LISTEN         (RTNCODE_ERBASE_SOCK-1)
#define RTNCODE_ERSOCK_BIND           (RTNCODE_ERBASE_SOCK-2)
#define RTNCODE_ERSOCK_READ           (RTNCODE_ERBASE_SOCK-3)
#define RTNCODE_ERSOCK_WRITE          (RTNCODE_ERBASE_SOCK-4)
#define RTNCODE_ERSOCK_CONNECT        (RTNCODE_ERBASE_SOCK-5)
#define RTNCODE_ERSOCK_PTON           (RTNCODE_ERBASE_SOCK-6)
#define RTNCODE_ERSOCK_SOCKNAME       (RTNCODE_ERBASE_SOCK-7)
#define RTNCODE_ERSOCK_SELECT         (RTNCODE_ERBASE_SOCK-8)

#define RTNCODE_ERPKG_PACK            (RTNCODE_ERBASE_SOCK-9)
#define RTNCODE_ERPKG_UNPACK          (RTNCODE_ERBASE_SOCK-10)

#define RTNCODE_ERBASE_PTHREAD        (RTNCODE_ERBASE_SYS-60)
#define RTNCODE_ERTHD_MUTEX           (RTNCODE_ERBASE_PTHREAD)
#define RTNCODE_ERTHD_COND            (RTNCODE_ERBASE_PTHREAD-1)
#define RTNCODE_ERTHD_BUSY            (RTNCODE_ERBASE_PTHREAD-2)
#define RTNCODE_ERTHD_TIMEOUT         (RTNCODE_ERBASE_PTHREAD-3)
#define RTNCODE_ERTHD_RESFREE         (RTNCODE_ERBASE_PTHREAD-4)

#define RTNCODE_ERBASE_APP            (RTNCODE_ERBASE_SYS-200)
#define RTNCODE_ERAPP_ARG             (RTNCODE_ERBASE_APP)
#define RTNCODE_ERAPP_SIZE            (RTNCODE_ERBASE_APP-1)
#define RTNCODE_ERAPP_LOCK            (RTNCODE_ERBASE_APP-2)
#define RTNCODE_ERAPP_INITARG         (RTNCODE_ERBASE_APP-3)
#define RTNCODE_ERAPP_BINARY          (RTNCODE_ERBASE_APP-4)
#define RTNCODE_ERAPP_CWDDIR          (RTNCODE_ERBASE_APP-5)
#define RTNCODE_ERAPP_APPDIR          (RTNCODE_ERBASE_APP-6)
#define RTNCODE_ERAPP_DIRS            (RTNCODE_ERBASE_APP-7)
#define RTNCODE_ERAPP_LOGARGS         (RTNCODE_ERBASE_APP-8)
#define RTNCODE_ERAPP_LOADLOGLIST     (RTNCODE_ERBASE_APP-9)
#define RTNCODE_ERAPP_INITFIFO        (RTNCODE_ERBASE_APP-10)
#define RTNCODE_ERAPP_INITMGR         (RTNCODE_ERBASE_APP-11)

#define RTNCODE_ERAPP_LOADCFG         (RTNCODE_ERBASE_APP-20)
#define RTNCODE_ERAPP_SAVECFG         (RTNCODE_ERBASE_APP-21)
#define RTNCODE_ERAPP_CFG             (RTNCODE_ERBASE_APP-22)
#define RTNCODE_ERAPP_NOTFOUNDCFG     (RTNCODE_ERBASE_APP-23)
#define RTNCODE_ERAPP_ANALYSE         (RTNCODE_ERBASE_APP-24)
#define RTNCODE_ERAPP_EXISTVALUE      (RTNCODE_ERBASE_APP-25)

#define RTNCODE_ERAPP_LOADDICT        (RTNCODE_ERBASE_APP-30)
#define RTNCODE_ERAPP_SAVEDICT        (RTNCODE_ERBASE_APP-31)
#define RTNCODE_ERAPP_EXISTDICT       (RTNCODE_ERBASE_APP-32)

#define RTNCODE_ERAPP_LOADSERVINFO    (RTNCODE_ERBASE_APP-35)
#define RTNCODE_ERAPP_LOADSERVINFO2   (RTNCODE_ERBASE_APP-36)
#define RTNCODE_ERAPP_SAVESERVINFO    (RTNCODE_ERBASE_APP-37)
#define RTNCODE_ERAPP_EXISTSERVINFO   (RTNCODE_ERBASE_APP-38)

#define RTNCODE_ERAPP_SAVESERVCALL    (RTNCODE_ERBASE_APP-40)
#define RTNCODE_ERAPP_SCALL_NEWBUS    (RTNCODE_ERBASE_APP-41)
#define RTNCODE_ERAPP_SCALL_SAVEBUS   (RTNCODE_ERBASE_APP-42)

#define RTNCODE_ERAPP_USERTHD         (RTNCODE_ERBASE_APP-50)

#define RTNCODE_ERBASE_VAR            (RTNCODE_ERBASE_APP-200)
#define RTNCODE_ERVAR_VT              (RTNCODE_ERBASE_VAR)
#define RTNCODE_ERVAR_NEW             (RTNCODE_ERBASE_VAR-1)
#define RTNCODE_ERVAR_ADD             (RTNCODE_ERBASE_VAR-2)
#define RTNCODE_ERVAR_GET             (RTNCODE_ERBASE_VAR-3)
#define RTNCODE_ERVAR_PACK            (RTNCODE_ERBASE_VAR-4)
#define RTNCODE_ERVAR_UNPACK          (RTNCODE_ERBASE_VAR-5)

#define RTNCODE_ERBASE_SERVICE        (RTNCODE_ERBASE_APP-220)
#define RTNCODE_ERSERV_GETINFO        (RTNCODE_ERBASE_SERVICE)
#define RTNCODE_ERSERV_SAVERTN        (RTNCODE_ERBASE_SERVICE-1)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef RTNCODE_H__ */ 

