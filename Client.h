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

struct Request;
struct Response;

const int HEAD_BUFFER_SIZE = 21;
const unsigned int MAX_BODY_SIZE = 0xffff;

class Client
{
public:
    Client(boost::asio::io_service&, std::ostream&);

    void write(const Request &);
    Response read();
    void close();
    bool IsConnected();

private:
    boost::asio::io_service& m_io;
    boost::asio::ip::tcp::socket m_sock;
    bool m_connected;
    // tYSPkgHeadStruct m_head;
    char m_head_buff[HEAD_BUFFER_SIZE];
    char m_body_buff[MAX_BODY_SIZE];
    std::ostream& m_logger;
};

#endif /* CLIENT_H_ */
