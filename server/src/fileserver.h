#pragma once

#include<httplib.h>

namespace totorrent {
  class FileServer {
  public:
    FileServer() = default;

    void registerRoutes();
    void listen(const std::string& host, int port);
  private:

    void handleHelloWorld(
        const httplib::Request& req, httplib::Response& res);

    httplib::Server svr_;
  }
}
