/*
 * Client.h
 *
 *  Created on: Mar 31, 2009
 *      Author: wengych
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <deque>
#include "Request.h"

typedef std::deque<Request> request_queue;
const int HEAD_BUFFER_SIZE = 21;
const unsigned int MAX_BODY_SIZE = 0xffffff;

class Client
{
public:
    Client(boost::asio::io_service&, std::ostream&);

    void write(const Request &);
    void close();
    bool IsConnected();

private:
    void handle_connect(const boost::system::error_code&,
            boost::asio::ip::tcp::resolver::iterator);
    void do_write(const Request &);
    void handle_write(const boost::system::error_code& error);
    void handle_read_head(const boost::system::error_code& error);
    void handle_read_body(const boost::system::error_code& error);

    void do_close();


private:
    boost::asio::io_service& m_io;
    boost::asio::ip::tcp::socket m_sock;
    request_queue m_req_q;
    bool m_connected;
    tYSPkgHeadStruct m_head;
    char m_head_buff[HEAD_BUFFER_SIZE];
    char m_body_buff[MAX_BODY_SIZE];
    std::ostream& m_logger;
};

#endif /* CLIENT_H_ */
