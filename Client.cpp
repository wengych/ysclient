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

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

Client::Client(io_service& io_service, std::ostream& logger) :
    m_io(io_service), m_sock(io_service), m_connected(false), m_logger(logger)
{
    const char* ip = "";
    const char* port = "";

    tcp::resolver resolver(io_service);
    m_logger << "Created resolver!" << std::endl;
    tcp::resolver::query query(ip, port);
    m_logger << "Created query!" << std::endl;
    tcp::resolver::iterator iterator = resolver.resolve(query);
    m_logger << "Created solver::iterator!" << std::endl;

    tcp::endpoint endpoint = *iterator;
    m_sock.async_connect(endpoint, boost::bind(&Client::handle_connect, this,
            placeholders::error, ++iterator));
    m_logger << "Async connect.\n";
}

void Client::write(const Request &req)
{
    m_io.post(boost::bind(&Client::do_write, this, req));
    m_logger << "post a new message for write.\n";
}

void Client::close()
{
    m_io.post(boost::bind(&Client::do_close, this));
    m_logger << "Close connection.\n";
}

bool Client::IsConnected()
{
    return m_connected;
}

void Client::handle_connect(const error_code& error,
        tcp::resolver::iterator endpoint_iterator)
{
    if (!error) {
        m_connected = true;
        m_logger << "Connection created successful!\n";
    } else if (endpoint_iterator != tcp::resolver::iterator()) {
        m_sock.close();
        tcp::endpoint endpoint = *endpoint_iterator;
        m_sock.async_connect(endpoint, boost::bind(&Client::handle_connect,
                this, placeholders::error, ++endpoint_iterator));
    }
}

void Client::do_write(const Request &req)
{
    bool write_in_progress = !m_req_q.empty();
    m_req_q.push_back(req);

    if (!write_in_progress) {
        async_write(m_sock, buffer(m_req_q.front().data(),
                m_req_q.front().length()), boost::bind(&Client::handle_write,
                this, placeholders::error));
        m_logger << "Async write a new message: " << m_req_q.front().data()
                << "\n";
    }
}

void Client::handle_write(const error_code& error)
{
    if (!error) {
        async_read(m_sock, buffer(m_head_buff/*, sizeof(m_head)*/), boost::bind(
                &Client::handle_read_head, this,
                        placeholders::error));
        m_req_q.pop_front();
        if (!m_req_q.empty()) {
            async_write(m_sock, buffer(m_req_q.front().data(),
                    m_req_q.front().length()), boost::bind(
                    &Client::handle_write, this, placeholders::error));
            m_logger << "Async write a new message: " << m_req_q.front().data()
                    << "\n";
        }
    } else {
        do_close();
    }
}

void Client::handle_read_head(const error_code& error)
{
    async_read(m_sock, buffer(m_body_buff, m_head.PkgDataLen), boost::bind(
            &Client::handle_read_body, this, placeholders::error));
    m_logger << "head.PkgDataLen" << m_head.PkgDataLen << std::endl;
}

void Client::handle_read_body(const error_code& error)
{

}

void Client::do_close()
{
    m_sock.close();
}
