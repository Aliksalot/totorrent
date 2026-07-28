#pragma once

#include"third-party/httplib.h"

#include"pbfetch.h"

#include<string>
#include<vector>

namespace totorrent {

  struct Job {

  };
  class FileServer {
  public:
    FileServer() = default;

    void registerRoutes();
    void listen(const std::string& host, int port);
  private:

    void handleHelloWorld(
        const httplib::Request& req, httplib::Response& res);

    void handleSearch(
        const httplib::Request& req, httplib::Response& res);

    void handleGenerateTorrent(
        const httplib::Request& req, httplib::Response& res);

    void handleTorrentStatus(
        const httplib::Request& req, httplib::Response& res);

    void handleGetTorrent(
        const httplib::Request& req, httplib::Response& res);

    void handleInfo(
        const httplib::Request& req, httplib::Response& res);

    httplib::Server svr_;

    std::vector<Job> jobs_;

  };
}
