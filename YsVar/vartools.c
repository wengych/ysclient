/***************************************************************************/
/**[File Name    ]vartools.c                                              **/
/**[File Path    ]$(TOPDIR)/src/libsrc/fecom                              **/
/**[Library Name ]libfecom.so                                             **/
/**[Library Path ]$(APPDIR)/lib                                           **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/11/11                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for var tool                                **/
/**[Modify       ]                                                        **/
/***************************************************************************/


#include <var.h>

#ifdef __cplusplus
extern "C"{
#endif

void  FEVarToolsInitBuf(char *Buf,INT32 Size,INT32 Len,UCHAR ch)
{
    INT32 L;
    if ( (NULL==Buf)||(0>Size) )
    {
        return;
    }
    memset(Buf,0,Size);
    L = FECAL_MAX(0,Len);
    L = FECAL_MIN(Size-1,Len);
    memset(Buf,ch,L);
}

#ifdef __cplusplus
}
#endif

