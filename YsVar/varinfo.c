/***************************************************************************/
/**[File Name    ]varinfo.c                                               **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/12/20                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for variant type name                       **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tagFEVarTypeInfo
{
    BYTE  VT;
    char  Name[FEVARNAMELEN-1];
}tFEVarTypeInfo;
#define FEVARTYPE_INFO_ST_SIZE      (sizeof(tFEVarTypeInfo))
#define FEVARTYPE_INFO_MEM_VT(v)     (((tFEVarTypeInfo*)(v))->VT)
#define FEVARTYPE_INFO_MEM_N(v)     (((tFEVarTypeInfo*)(v))->Name)
static const tFEVarTypeInfo gstFEVarTypeInfo[] = 
{
     {FEVARTYPE_MEM_VT_NOT      ,"unknown"      }
    ,{FEVARTYPE_MEM_VT_BOOL     ,"Bool"         }
    ,{FEVARTYPE_MEM_VT_BYTE     ,"Byte"         }
    ,{FEVARTYPE_MEM_VT_INT16    ,"Int16"        }
    ,{FEVARTYPE_MEM_VT_INT32    ,"Int32"        }
    ,{FEVARTYPE_MEM_VT_INT64    ,"Int64"        }
    ,{FEVARTYPE_MEM_VT_DOUBLE   ,"Double"       }
    ,{FEVARTYPE_MEM_VT_BIN      ,"Bin"          }
    ,{FEVARTYPE_MEM_VT_STRING   ,"String"       }
    ,{FEVARTYPE_MEM_VT_OBJECT   ,"Object"       }

    ,{FEVARTYPE_MEM_VT_P1       ,"P1"           }
    ,{FEVARTYPE_MEM_VT_P2       ,"P2"           }
    ,{FEVARTYPE_MEM_VT_P3       ,"P3"           }
    ,{FEVARTYPE_MEM_VT_P4       ,"P4"           }

    ,{FEVARTYPE_MEM_VT_ARRAY    ,"Array"        }
    ,{FEVARTYPE_MEM_VT_FIFO     ,"Fifo"         }
    ,{FEVARTYPE_MEM_VT_FILO     ,"Filo"         }
    ,{FEVARTYPE_MEM_VT_CICLE    ,"Circle"       }
    ,{FEVARTYPE_MEM_VT_HASH     ,"Hash"         }
    ,{FEVARTYPE_MEM_VT_LINK     ,"Link"         }
    ,{FEVARTYPE_MEM_VT_TREE     ,"Tree"         }
    ,{FEVARTYPE_MEM_VT_XML      ,"Xml"          }
};
#define FEVARTYPE_INFO_V_SIZE             \
    (sizeof(gstFEVarTypeInfo)/FEVARTYPE_INFO_ST_SIZE)

BYTE  FEVarTypeInfoGetVT(const char *Name)
{
    BYTE bRtn;
    INT32 i;
    bRtn = FEVARTYPE_MEM_VT_NOT;
    for ( i=0;i<FEVARTYPE_INFO_V_SIZE;i++ )
    {
        if ( !strcmp(FEVARTYPE_INFO_MEM_N( \
            &(gstFEVarTypeInfo[i])),Name) )
        {
            bRtn = FEVARTYPE_INFO_MEM_VT(&(gstFEVarTypeInfo[i]));
            break;
        } 
    }
    return bRtn;
}

char *FEVarTypeInfoGetName(const BYTE VT)
{
    char *pcRtn;
    INT32 i;
    pcRtn = FEVARTYPE_INFO_MEM_N(&(gstFEVarTypeInfo[0]));
    for ( i=0;i<FEVARTYPE_INFO_V_SIZE;i++ )
    {
        if ( VT==FEVARTYPE_INFO_MEM_VT(&(gstFEVarTypeInfo[i])) )
        {
            pcRtn = FEVARTYPE_INFO_MEM_N(&(gstFEVarTypeInfo[i]));
            break;
        } 
    }
    return pcRtn;
}

BOOL  FEVarTypeInfoIs(const BYTE VT)
{
    BOOL bRtn;
    INT32 i;
    bRtn = FALSE;
    for ( i=0;i<FEVARTYPE_INFO_V_SIZE;i++ )
    {
        if ( VT==FEVARTYPE_INFO_MEM_VT(&(gstFEVarTypeInfo[i])) )
        {
            bRtn = TRUE;
            break;
        } 
    }
    return bRtn;
}

BOOL  FEVarTypeInfoIsName(const char *Name)
{
    BOOL bRtn;
    INT32 i;
    bRtn = FALSE;
    for ( i=0;i<FEVARTYPE_INFO_V_SIZE;i++ )
    {
        if ( !strcmp(FEVARTYPE_INFO_MEM_N( \
            &(gstFEVarTypeInfo[i])),Name) )
        {
            bRtn = TRUE;
            break;
        } 
    }
    return bRtn;
}

#ifdef __cplusplus
}
#endif

