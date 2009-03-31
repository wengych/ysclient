#include <boost/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/bind.hpp>
#include <boost/asio/io_service.hpp>

#include "Client.h"

// using boost::asio::ip::tcp;


int main(int argc, const char** argv)
{
    std::ostream& logger = std::cout;
    logger << "Starting...\n";

    try {
        boost::asio::io_service io_service;
        logger << "Create io_service!" << std::endl;

        Client c(io_service, logger);

        boost::thread
                t(boost::bind(&boost::asio::io_service::run, &io_service));
        logger << "Created thread!" << std::endl;

        while (!c.IsConnected()) {
            boost::xtime xt;
            boost::xtime_get(&xt, boost::TIME_UTC);
            xt.sec += 1;
            boost::thread::sleep(xt);
        }

        if (c.IsConnected()) {
            Request req;
            strcpy(req.buff, "123456");
            c.write(req);
        }

        t.join();
        c.close();
    } catch (std::exception& e) {
        logger << "Exception: " << e.what() << "\n";
    }

}
