
#include"third-party/httplib.h"

#include"fileserver.h"
#include"pbfetch.h"

#include<string>

namespace totorrent {

  void FileServer::handleHelloWorld(
    const httplib::Request& req, httplib::Response& res) {
    std::cout << "Hello, world!" << std::endl;
  }

  void FileServer::handleSearch(
      const httplib::Request& req, httplib::Response& res) {
    std::cout << "Got search request" << std::endl;
    if(!req.has_param("q")) {
      std::cout <<  " No query provided" << std::endl;
      res.status = 400;
      res.set_content(json{{"error", "missing 'q' param"}}.dump(), "application/json");
      return;
    }
    std::string query = req.get_param_value("q");
    std::cout << "  Got search query: " << query << std::endl;
    SearchList sl;
    try{
      sl = search(query);
    }catch(...){
      std::cout << "  Search failed. Something isn't correct yet again" << std::endl;
      res.status = 400;
      res.set_content(json{{"error", "missing 'q' param"}}.dump(), "application/json");
      return;
    }

    std::cout << "  Search OK" << query << std::endl;

    json j = json::array();
    for(auto& si: sl) j.push_back(si.toJson());

    std::cout << "  JSON-ing OK" << query << std::endl;

    res.set_content(j.dump(), "application/json");
  }

  void FileServer::handleGenerateTorrent(
      const httplib::Request& req, httplib::Response& res) {
  }

  void FileServer::handleTorrentStatus(
      const httplib::Request& req, httplib::Response& res) {
  }

  void FileServer::handleGetTorrent(
      const httplib::Request& req, httplib::Response& res) {
  }

  void FileServer::handleInfo(
      const httplib::Request& req, httplib::Response& res) {
    std::cout << "Got info request" << std::endl;
    if(!req.has_param("q")) {
      std::cout <<  "No query provided" << std::endl;
      res.status = 400;
      res.set_content(json{{"error", "missing 'q' param"}}.dump(), "application/json");
      return;
    }
    std::string query = req.get_param_value("q");
    std::cout << "  Got info query: " << query << std::endl;
    TorrentPage tp;
    try{
      tp = page(query);
    }catch(...){
      std::cout << "  Search failed. Something isn't correct yet again" << std::endl;
      res.status = 400;
      res.set_content(json{{"error", "missing 'q' param"}}.dump(), "application/json");
      return;
    };

    std::cout << "  Search OK" << query << std::endl;

    res.set_content(tp.toJson().dump(), "application/json");
  }

  void FileServer::registerRoutes() {
     svr_.set_exception_handler([](const auto& req, auto& res, std::exception_ptr ep) {
     try {
       std::rethrow_exception(ep);
     } catch (const std::exception& e) {
       std::cerr << "EXCEPTION: " << e.what() << "\n";
       res.status = 500;
       res.set_content(std::string("Error: ") + e.what(), "text/plain");
     } catch (...) {
       std::cerr << "UNKNOWN EXCEPTION\n";
       res.status = 500;
       res.set_content("Unknown error", "text/plain");
     }
    });
    svr_.Get("/", [this](const auto& req, auto& res) {
        handleHelloWorld(req, res); });
    svr_.Get("/search", [this](const auto& req, auto& res) { 
        handleSearch(req, res); });
    svr_.Post("/generate", [this](const auto& req, auto& res) {
        handleGenerateTorrent(req, res); });

    svr_.Get(R"(/generate/(\d+)/status)",[this](const auto& req, auto& res) {
        handleTorrentStatus(req, res); });

    svr_.Get(R"(/generate/(\d+))",[this](const auto& req, auto& res) {
        handleGetTorrent(req, res); });

    svr_.Get("/info",[this](const auto& req, auto& res) {
        handleInfo(req, res); });
  }
  void FileServer::listen(const std::string& host, int port) {
    svr_.listen(host, port);
  }


}
