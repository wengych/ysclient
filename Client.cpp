/*
 * Client.cpp
 *
 *  Created on: Mar 31, 2009
 *      Author: wengych
 */

// #include <libxml++/libxml++.h>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/bind.hpp>

#include "Client.h"

#include "Request.h"
#include "Response.h"

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

Client::Client(io_service& io_service, std::ostream& logger) :
    m_io(io_service), m_sock(io_service), m_connected(false), m_logger(logger)
{
    const char* ip = "192.168.0.105";
    const char* port = "9000";

    tcp::resolver resolver(io_service);
    m_logger << "Created resolver!" << std::endl;
    tcp::resolver::query query(ip, port);
    m_logger << "Created query!" << std::endl;
    tcp::resolver::iterator iterator = resolver.resolve(query);
    m_logger << "Created solver::iterator!" << std::endl;

    error_code error;
    m_sock.connect(*iterator++, error);
    if (!error)
        m_connected = true;

    m_logger << "Async connect.\n";
}

void Client::write(const Request &req)
{
    m_logger << "Send " << req.length() << " of bytes." << std::endl;
    m_sock.write_some(buffer(req.data(), req.length()));
}

Response Client::read()
{
    const int sz = 1024;
    char buf[sz] = { 'a' };
    m_logger << buf << std::endl;
    size_t nRead = m_sock.read_some(buffer(buf));
    Response resp;
}

void Client::close()
{
    m_sock.close();
    m_logger << "Close connection.\n";
}

bool Client::IsConnected()
{
    return m_connected;
}
