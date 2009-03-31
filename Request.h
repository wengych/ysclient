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
    char buff[8];
    tYSPkgHeadStruct m_head;

    const char* data()
    {
        return buff;
    }
    unsigned length()
    {
        return 8;
    }
};

#endif /* REQUEST_H_ */
