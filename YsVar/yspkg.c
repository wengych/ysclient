/***************************************************************************/
/**[File Name    ]yspkg.c                                                 **/
/**[File Path    ]$(SRCDIR)/libsrc/yscom                                  **/
/**[Library Name ]libyscom.so                                             **/
/**[Library Path ]$(HOME)/lib                                             **/
/**[Author       ]Wang Honggang                                           **/
/**[Copyright    ]Wang Honggang                                           **/
/**[Date         ]2008/04/28                                              **/
/**[Version      ]0.1.0                                                   **/
/**[Memo         ]define func for pkg                                     **/
/**[Modify       ]                                                        **/
/***************************************************************************/
#include <yscom.h>

#ifdef __cplusplus
extern "C"{
#endif

BOOL  YSPkgTcpWritePkg(INT32 Sock,void *Head);

BOOL  YSPkgDataToStruct(void *PkgStruct,INT32 PkgSize,void *Pkg,INT32 PkgLen)
{
    INT32 RtnPos;
    INT32 MsgPos;
    INT32 DataPos;
    char Tmp[TMP_MAX_BUFFER];
    if ( (NULL==PkgStruct)||(YSPKG_HEADSTRUCT_ST_SIZE>PkgSize) \
        ||(NULL==Pkg)||(YSPKG_HEADPKG_LEN>PkgLen) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args are null.");
        return FALSE;
    }
    memset(PkgStruct,0,YSPKG_HEADSTRUCT_ST_SIZE);
    YSPKG_HEADSTRUCT_MEM_VERM(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_VERM_POS];
    YSPKG_HEADSTRUCT_MEM_VERS(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_VERS_POS];

    YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_REQT_POS];
    memcpy(YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct) \
        ,((UCHAR*)Pkg)+YSPKG_HEADPKG_TYPE_POS,YSPKG_HEADPKG_TYPE_LEN);

    YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_SUM_POS];
    YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
        = ((UCHAR*)Pkg)[YSPKG_HEADPKG_NUM_POS];
    if ( (0>=YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) \
        ||(YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
        >YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : PkgNum[%d](or <=0 )>PkgSum[%d]." \
            ,YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
            ,YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct));
        return FALSE;
    }

    memcpy((UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct))) \
        ,((UCHAR*)Pkg)+YSPKG_HEADPKG_DSUM_POS,YSPKG_HEADPKG_DSUM_LEN);
    FEEndianToHost((UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct))) \
        ,YSPKG_HEADPKG_DSUM_LEN);
    memcpy((UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct))) \
        ,((UCHAR*)Pkg)+YSPKG_HEADPKG_DLEN_POS,YSPKG_HEADPKG_DLEN_LEN);
    FEEndianToHost((UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct))) \
        ,YSPKG_HEADPKG_DLEN_LEN);

    if ( YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
        >YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : DataLen[%d]>DataSum[%d]." \
            ,YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
            ,YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct));
        return FALSE;
    }

    if ( (YSPKG_HEADPKG_REQT_RESP==YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) \
        && (1==YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) )
    {
        YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) \
            = ((UCHAR*)Pkg)[YSPKG_HEADPKG_RTNLEN_POS];
        YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct) \
            = ((UCHAR*)Pkg)[YSPKG_HEADPKG_MSGLEN_POS];
        RtnPos = YSPKG_HEADPKG_RTN_POS;
        MsgPos = RtnPos+YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct);
        DataPos = MsgPos+YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
        if ( (PkgLen<=RtnPos)||(PkgLen<=MsgPos)||(PkgLen<=DataPos) )
        {
        }
        else
        {
            MEMCPY(YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct),((UCHAR*)Pkg)+RtnPos \
                ,sizeof(YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct)) \
                ,YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct));
            MEMCPY(YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct),((UCHAR*)Pkg)+MsgPos \
                ,sizeof(YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct)) \
                ,YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct));
            if ( PkgLen \
                ==YSPKG_HEADPKG_LEN+YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) )
            {
                YSPKG_HEADSTRUCT_MEM_DATALEN(PkgStruct) \
                    = YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) \
                    -YSPKG_HEADPKG_RTNLEN_LEN \
                    -YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) \
                    -YSPKG_HEADPKG_MSGLEN_LEN \
                    -YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
            }
            else
            {
                YSPKG_HEADSTRUCT_MEM_DATALEN(PkgStruct) \
                    = YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
                    -YSPKG_HEADPKG_RTNLEN_LEN \
                    -YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) \
                    -YSPKG_HEADPKG_MSGLEN_LEN \
                    -YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
            }
            YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) = YSPKG_HEADPKG_LEN \
                +YSPKG_HEADPKG_RTNLEN_LEN \
                +YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) \
                +YSPKG_HEADPKG_MSGLEN_LEN \
                +YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
        }
    }
    else
    {
        YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) = 0;
        YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct) = 0;
        DataPos = YSPKG_HEADPKG_DATA_POS;
        YSPKG_HEADSTRUCT_MEM_DATALEN(PkgStruct) \
            = YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct);
        YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) = YSPKG_HEADPKG_LEN;
    }
    if ( PkgLen>DataPos )
    {
        YSPKG_HEADSTRUCT_MEM_DATA(PkgStruct) = ((UCHAR*)Pkg)+DataPos;
    }
    else
    {
        YSPKG_HEADSTRUCT_MEM_DATA(PkgStruct) = NULL;
    }
    YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct) \
        = YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct)+YSPKG_HEADPKG_LEN;
    return TRUE;
}

INT32 YSPkgStructToData(void *Pkg,INT32 PkgSize,void *PkgStruct)
{
    INT32 RtnPos;
    INT32 MsgPos;
    INT32 DataPos;
    char Tmp[TMP_MAX_BUFFER];
    if ( (NULL==Pkg)||(YSPKG_HEADPKG_LEN>PkgSize)||(NULL==PkgStruct) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args are null.");
        return YSRTN_ERAPP_ARG;
    }
    memset(Pkg,0,PkgSize);
    
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_VERM_POS] \
        = YSPKG_HEADSTRUCT_MEM_VERM(PkgStruct);
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_VERS_POS] \
        = YSPKG_HEADSTRUCT_MEM_VERS(PkgStruct);

    if ( !YSPKG_HEADPKG_ISREQT(YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : ReqType is error[%d]." \
            ,YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct));
        return YSRTN_ERPKG_PACK;
    }
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_REQT_POS] \
        = YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct);
        
    if ( 0==strlen(YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : PKGTYPE is null.");
        return YSRTN_ERPKG_PACK;
    }
    memcpy(((UCHAR*)Pkg)+YSPKG_HEADPKG_TYPE_POS \
        ,YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct),YSPKG_HEADPKG_TYPE_LEN);

    if ( (0>=YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) \
        ||(YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
        >YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct)) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : PkgNum[%d](or <=0 )>PkgSum[%d]." \
            ,YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
            ,YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct));
        return YSRTN_ERPKG_PACK;
    }
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_SUM_POS] = YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct);
    ((UCHAR*)Pkg)[YSPKG_HEADPKG_NUM_POS] = YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct);

    if ( PkgSize<YSPKG_HEADPKG_LEN+YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : DataLen[%d]>PkgSize[%d]." \
            ,YSPKG_HEADPKG_LEN+YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
            ,PkgSize);
        return YSRTN_ERPKG_PACK;
    }
    if ( YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
        >YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : DataLen[%d]>DataSum[%d]." \
            ,YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
            ,YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct));
        return YSRTN_ERPKG_PACK;
    }
    memcpy(((UCHAR*)Pkg)+YSPKG_HEADPKG_DSUM_POS \
        ,(UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct))) \
        ,YSPKG_HEADPKG_DSUM_LEN);
    FEEndianToNet(((UCHAR*)Pkg)+YSPKG_HEADPKG_DSUM_POS,YSPKG_HEADPKG_DSUM_LEN);
    memcpy(((UCHAR*)Pkg)+YSPKG_HEADPKG_DLEN_POS \
        ,(UCHAR*)(&(YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct))) \
        ,YSPKG_HEADPKG_DLEN_LEN);
    FEEndianToNet(((UCHAR*)Pkg)+YSPKG_HEADPKG_DLEN_POS,YSPKG_HEADPKG_DLEN_LEN);

    if ( (YSPKG_HEADPKG_REQT_RESP==YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) \
        && (1==YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) )
    {
        ((UCHAR*)Pkg)[YSPKG_HEADPKG_RTNLEN_POS] \
            = YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct)%0xFF;
         ((UCHAR*)Pkg)[YSPKG_HEADPKG_MSGLEN_POS] \
            = YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct)%0xFF;
        RtnPos = YSPKG_HEADPKG_RTN_POS;
        MsgPos = RtnPos+YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct);
        DataPos = MsgPos+YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct);
        if ( (PkgSize<RtnPos)||(0>=YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct)) \
            ||(PkgSize<MsgPos)||(PkgSize<DataPos) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : RtnPos[%d],MsgPos[%d],DataPos[%d]>PkgSize[%d]." \
                ,RtnPos,MsgPos,DataPos,PkgSize);
            return YSRTN_ERPKG_PACK;
        }
        if ( 0<YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) )
        {
            memcpy(((UCHAR*)Pkg)+RtnPos,YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct) \
                ,YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct));
        }
        if ( 0<YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct) )
        {
            memcpy(((UCHAR*)Pkg)+MsgPos,YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct) \
                ,YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct));
        }
    }
    if ( 0<YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) )
    {
        if ( NULL==YSPKG_HEADSTRUCT_MEM_DATA(PkgStruct) )
        {
            YSTracesError(YSAppArgsGetLogArgs() \
                ,YSSETTRACE(Tmp,sizeof(Tmp)),"Error : Data is null.");
            return YSRTN_ERPKG_PACK;
        }
    }
    if ( YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct) \
        !=YSPKG_HEADPKG_LEN+YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) )
    {
        return YSRTN_ERPKG_PACK;
    }
    return YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct);
}

BOOL  YSPkgStructInit(void *PkgStruct,BOOL ReqT,const char *Type \
    ,INT32 PkgSum,INT32 PkgNum,INT32 DSum,INT32 DLen,void *Data \
    ,INT32 RtnLen,void *Rtn,INT32 MsgLen,void *Msg)
{
    char Tmp[TMP_MAX_BUFFER];
    if ( (NULL==PkgStruct)||(NULL==Type) \
        ||(0>=PkgNum)||(PkgNum>PkgSum)||(0>DLen)||(DLen>DSum) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args are null.");
        return FALSE;
    }
    if ( 0==strlen(Type) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args are null.");
        return FALSE;
    }
    memset(PkgStruct,0,YSPKG_HEADSTRUCT_ST_SIZE);

    YSPKG_HEADSTRUCT_MEM_VERM(PkgStruct) = YSPKG_HEADPKG_VERM;
    YSPKG_HEADSTRUCT_MEM_VERS(PkgStruct) = YSPKG_HEADPKG_VERS;

    YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct) = \
        (ReqT)?YSPKG_HEADPKG_REQT_REQ:YSPKG_HEADPKG_REQT_RESP;
fprintf(stderr,"----REQT(BOOL)=%d,%d.\n",ReqT,YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct));

    MEMCPY(YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct),Type \
        ,sizeof((((tYSPkgHeadStruct*)(PkgStruct))->PkgType)),strlen(Type));

    YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct) = PkgSum;
    YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) = PkgNum;
    if ( !ReqT && (1==PkgNum) )
    {
        if ( (NULL==Rtn)||(0>=RtnLen) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Rtn is null or RtnLen(%d) is <=0.",RtnLen);
            return FALSE;
        }
        YSPKG_HEADSTRUCT_MEM_RTNLEN(PkgStruct) = RtnLen;
        YSPKG_HEADSTRUCT_MEM_MSGLEN(PkgStruct) = MsgLen;
        if ( (0<MsgLen)&&(NULL==Msg) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Msg is null or MsgLen(%d) is <=0.",MsgLen);
            return FALSE;
        }
        MEMCPY(YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct),Rtn \
            ,sizeof(YSPKG_HEADSTRUCT_MEM_RTN(PkgStruct)),RtnLen);
        if ( (0<MsgLen)&&(NULL!=Msg) )
        {
            MEMCPY(YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct),Msg \
                ,sizeof(YSPKG_HEADSTRUCT_MEM_MSG(PkgStruct)),MsgLen);
        }

        YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) = DSum \
            +YSPKG_HEADPKG_RTNLEN_LEN+RtnLen \
            +YSPKG_HEADPKG_MSGLEN_LEN+MsgLen;
        YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) = DLen \
            +YSPKG_HEADPKG_RTNLEN_LEN+RtnLen \
            +YSPKG_HEADPKG_MSGLEN_LEN+MsgLen;
        YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) = YSPKG_HEADPKG_LEN \
            +YSPKG_HEADPKG_RTNLEN_LEN+RtnLen \
            +YSPKG_HEADPKG_MSGLEN_LEN+MsgLen;
    }
    else
    {
        YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) = DSum;
        YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) = DLen;
        YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) = YSPKG_HEADPKG_LEN;
    }
    YSPKG_HEADSTRUCT_MEM_DATALEN(PkgStruct) = DLen;
    YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct) \
        = YSPKG_HEADPKG_LEN+YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct);
    YSPKG_HEADSTRUCT_MEM_DATA(PkgStruct) = Data;
    return TRUE;
    
}

void  YSPkgHeadStructShow(void *PkgStruct,INT32 T,void *Buf)
{
    char Tmp[TMP_MAX_BUFFER];
    char Tab[64];
    if ( NULL==PkgStruct )
    {
        return ;
    }
    memset(Tab,0,sizeof(Tab));
    YSVarToolsInitBufSpace(Tab,sizeof(Tab),T+1);

    memset(Tmp,0,sizeof(Tmp));
    snprintf(Tmp,sizeof(Tmp),"%s<Ver>%d.%d</Ver>\n" 
         "%s<PkgReq>%s</PkgReq>\n"
         "%s<PkgType>%s</PkgType>\n"
         "%s<PkgSum>%d</PkgSum>\n"
         "%s<PkgNum>%d</PkgNum>\n"
         "%s<DataSum>%d</DataSum>\n"
         "%s<DataLen>%d</DataLen>\n"
         "%s<HeadLen>%d</HeadLen>\n"
         "%s<PkgLen>%d</PkgLen>\n"
        ,Tab,YSPKG_HEADSTRUCT_MEM_VERM(PkgStruct) \
            ,YSPKG_HEADSTRUCT_MEM_VERS(PkgStruct) \
        ,Tab,YSPKG_HEADPKG_REQT_STR(YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_TYPE(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_SUM(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_NUM(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_DSUM(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_DLEN(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_HEADLEN(PkgStruct) \
        ,Tab,YSPKG_HEADSTRUCT_MEM_PKGLEN(PkgStruct));
    YSVarStringCat(Buf,Tmp,strlen(Tmp));
#if 0
    if ( (YSPKG_HEADPKG_REQT_RESP==YSPKG_HEADSTRUCT_MEM_REQT(PkgStruct)) \
        &&(1==SPKG_HEADSTRUCT_MEM_NUM(PkgStruct)) )
    {
        memset(Tmp,0,sizeof(Tmp));
        snprinf(Tmp,sizeof(Tmp),"%s<RtnCode>%s</RtnCode>\n" 
             "%s<RtnMsg>%s</RtnMsg>\n" \
            ,Tab,PKG_HEADSTRUCT_MEM_RTN(PkgStruct) \
            ,Tab,PKG_HEADSTRUCT_MEM_MSG(PkgStruct));
        YSVarStringCat(Buf,Tmp,strlen(Tmp));
    }
#endif
}

BOOL  YSPkgTcpRead(INT32 Sock,void *Pkg,void *Head)
{
    char SBuf[YSPKG_HEADPKG_MAXLEN+1];
    void *Buf;
    void *Recv;
    INT32 Len;
    INT32 iRtn;
    INT32 RLen;
    BOOL bRtn;

    char Tmp[TMP_MAX_BUFFER];
    if ( (0>Sock)||!YSVarIsInit2(Pkg,VARTYPE_MEM_VT_BIN)||(NULL==Head) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args are null.");
        return YSRTN_ERAPP_ARG;
    }

    Buf = NULL;
    while( 1 )
    {
        Recv = NULL;
        memset(SBuf,0,sizeof(SBuf));
        if ( YSPKG_HEADPKG_LEN!=recv(Sock,SBuf,YSPKG_HEADPKG_LEN,MSG_PEEK) )
        {
            YSTracesError(YSAppArgsGetLogArgs() \
                ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at recv(%d)[%d][%s]." \
                ,Sock,YSPKG_HEADPKG_LEN,strerror(errno));
            break;
        }
        memset(Head,0,YSPKG_HEADSTRUCT_ST_SIZE);
        if ( !YSPkgDataToStruct(Head,YSPKG_HEADSTRUCT_ST_SIZE \
            ,SBuf,YSPKG_HEADPKG_LEN) )
        {
            YSTracesError(YSAppArgsGetLogArgs() \
                ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at recv(%d)[%d][%s]." \
                ,Sock,YSPKG_HEADPKG_LEN,strerror(errno));
            break;
        }
        if ( YSVarIsInit(Buf) )
        {
            YSVarStringReset(Buf);
        }
        else if ( NULL==(Buf= \
            YSVarStringNew2(YSPKG_HEADSTRUCT_MEM_PKGLEN((Head)))) )
        {
            YSTracesError(YSAppArgsGetLogArgs() \
                ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSVarStringNew(%d).",Sock);
            break;
        }
        Len = 0;
        if ( 0>(iRtn=FETcpRead(Sock,TCP_TIMEOUT \
            ,YSVarStringGet(Buf),&Len,YSPKG_HEADSTRUCT_MEM_PKGLEN((Head)))) )
        {
            YSTracesError(YSAppArgsGetLogArgs() \
                ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error(%d) : Failed at FETcpRead(%d).",iRtn,Sock);
            break;
        }
        if ( 0<Len )
        {
            YSVarStringSetLen(Buf,Len);
        }
        if ( Len==YSPKG_HEADSTRUCT_MEM_PKGLEN(Head) )
        {
            if ( 1==YSPKG_HEADSTRUCT_MEM_NUM(Head) )
            {
                Recv = YSVarStringGet(Buf);
                RLen = Len;
            }
            else
            {
                Recv = ((char*)YSVarStringGet(Buf))+YSPKG_HEADPKG_LEN;
                RLen = Len-YSPKG_HEADPKG_LEN;
            }
            if ( !YSVarBinCat(Pkg,Recv,RLen) )
            {
                YSTracesError(YSAppArgsGetLogArgs() \
                    ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                    ,"Error : Failed at FETcpRead(%d).");
                break;
            }
        }
        /* 0 : time out & piRecvLen is length of data */
        /* 1 socket close or read over & piRecvLen is length of data */
        /* 2 read data of length */
        /* 3 : socket close & read data is 0 */
        if ( YSPKG_HEADSTRUCT_MEM_SUM(Head)==YSPKG_HEADSTRUCT_MEM_NUM(Head) )
        {
            bRtn = TRUE;
            break;
        }
        if ( (2!=iRtn) \
            ||(Len!=YSPKG_HEADSTRUCT_MEM_PKGLEN(Head)) )
        {
            YSTracesError(YSAppArgsGetLogArgs() \
                ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error(:%d) : Failed at FETcpRead(%d).[Close]" \
                ,iRtn,Sock);
            break;
        }
    }
    if ( bRtn )
    {
        if ( !YSPkgDataToStruct(Head,YSPKG_HEADSTRUCT_ST_SIZE \
            ,YSVarBinGet(Pkg),YSVarBinGetLen(Pkg)) )
        {
            YSTracesError(YSAppArgsGetLogArgs() \
                ,YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at recv(%d)[%d][%s]." \
                ,Sock,YSPKG_HEADPKG_LEN,strerror(errno));
            bRtn = FALSE;
        }
        else
        {
            YSHexTraceDebug(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,YSVarBinGet(Pkg),YSVarBinGetLen(Pkg));
        }
    }
    YSVarStringFree(Buf);
    Buf = NULL;
    return bRtn;
}

BOOL  YSPkgTcpWrite(INT32 Sock,void *Head)
{
    UINT32 DSum;
    INT32 DLen;
    INT32 Sum;
    INT32 Num;
    INT32 Pos;
    char *P;
    tYSPkgHeadStruct HS;
    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    if ( (0>Sock)||(NULL==Head) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args are null.");
        return FALSE;
    }
    bRtn = TRUE;
    DSum = YSPKG_HEADSTRUCT_MEM_DATALEN(Head);
    Sum = (YSPKG_MAX_SIZE<DSum)?(DSum/YSPKG_MAX_SIZE):1;
    Pos = 0;
    P = YSPKG_HEADSTRUCT_MEM_DATA(Head);
    for ( Num=1;Num<=Sum;Num++ )
    {
        DLen = DSum-Pos;
        DLen = YSCAL_MIN(YSPKG_MAX_SIZE,DLen);
        P = P+Pos;
        memset(&HS,0,sizeof(HS));
        if ( !YSPkgStructInit(&HS \
            ,YSRTN_CMPBOOL(YSPKG_HEADPKG_REQT_REQ \
                ==YSPKG_HEADSTRUCT_MEM_REQT(Head)) \
            ,YSPKG_HEADSTRUCT_MEM_TYPE(Head) \
            ,Sum,Num,DSum,DLen,P \
            ,YSPKG_HEADSTRUCT_MEM_RTNLEN(Head),YSPKG_HEADSTRUCT_MEM_RTN(Head) \
            ,YSPKG_HEADSTRUCT_MEM_MSGLEN(Head),YSPKG_HEADSTRUCT_MEM_MSG(Head)) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPkgStructInit[%d].",Num);
            bRtn = FALSE;
            break;
        }
        if ( !YSPkgTcpWritePkg(Sock,&HS) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : Failed at YSPkgTcpWritePkg[%d].",Num);
            bRtn = FALSE;
            break;
        }

        Pos += DLen;
    }
    return bRtn;
}

BOOL  YSPkgTcpWritePkg(INT32 Sock,void *Head)
{
    char SBuf[TMP_MAX_BUFFER];
    INT32 iRtn;

    BOOL bRtn;
    char Tmp[TMP_MAX_BUFFER];

    if ( (0>Sock)||(NULL==Head) )
    {
        YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,"Error : Args are null.");
        return FALSE;
    }
    bRtn = FALSE;
    while( 1 )
    {
        memset(SBuf,0,sizeof(SBuf));
        if ( YSPKG_HEADSTRUCT_MEM_PKGLEN(Head)!= \
            YSPkgStructToData(SBuf,sizeof(SBuf),Head) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error : PkgLen[%d]!=Length of Pkg." \
                ,YSPKG_HEADSTRUCT_MEM_PKGLEN(Head));
            break;
        }
fprintf(stderr,"========HeadLen=%d,DataLen=%d\n" \
    ,YSPKG_HEADSTRUCT_MEM_HEADLEN(Head) \
    ,YSPKG_HEADSTRUCT_MEM_DATALEN(Head));
        if ( 0>(iRtn=FETcpWrite(Sock,TCP_TIMEOUT,SBuf \
            ,YSPKG_HEADSTRUCT_MEM_HEADLEN(Head))) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error(%d) : Failed at FETcpWrite(%d).",iRtn);
            break;
        }
        if ( 0>(iRtn=FETcpWrite(Sock,TCP_TIMEOUT \
            ,YSPKG_HEADSTRUCT_MEM_DATA(Head) \
            ,YSPKG_HEADSTRUCT_MEM_DATALEN(Head))) )
        {
            YSTracesError(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
                ,"Error(%d) : Failed at FETcpWrite2(%d).",iRtn);
            break;
        }
        YSHexTraceDebug(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,SBuf,YSPKG_HEADSTRUCT_MEM_HEADLEN(Head));
        YSHexTraceDebug(YSAppArgsGetLogArgs(),YSSETTRACE(Tmp,sizeof(Tmp)) \
            ,YSPKG_HEADSTRUCT_MEM_DATA(Head) \
            ,YSPKG_HEADSTRUCT_MEM_DATALEN(Head));
        bRtn = TRUE;
        break;
    }
    return bRtn;
}

#ifdef __cplusplus
}
#endif

