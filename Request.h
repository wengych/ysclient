/*
 * Request.h
 *
 *  Created on: Mar 31, 2009
 *      Author: wengych
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include <ysdef.h>

struct Request
{
    Request(char* data) :
        m_data(NULL)
    {
    }

    size_t length() const
    {
        return PkgHeadSize + PkgDataSum;
    }

    UCHAR PkgVerM;
    UCHAR PkgVerS;
    UCHAR ReqType;
    UCHAR PkgType[YSPKG_HEADPKG_TYPE_LEN+1];
    UCHAR PkgSum;
    UCHAR PkgNum;
    INT32 PkgDataSum;
    INT32 PkgDataLen;

    static size_t PkgHeadSize;

    char* m_data;
};

#endif /* REQUEST_H_ */
