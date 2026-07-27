
#include"fileserver.h"

#include<string>
#include"third-party/httplib.h"

namespace totorrent {

  void FileServer::registerRoutes() {
    svr_.Get("/", [this](const auto& req, auto& res) {
        handleHelloWorld(req, res); });
  }
  void FileServer::listen(const std::string& host, int port) {
    svr_.listen(host, port);
  }

  void FileServer::handleHelloWorld(
    const httplib::Request& req, httplib::Response& res) {
    std::cout << "Hello, world!" << std::endl;
    res.send
  }
}
