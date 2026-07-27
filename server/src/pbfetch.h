#pragma once

#include"third-party/json.hpp"

#include<string>
#include<vector>
#include<cstdint>
#include <curl/curl.h>

namespace totorrent {

  using json = nlohmann::json;

  class SearchEntry {
  public:
    std::string name;
    std::string uploaded;
    std::string size;
    std::string seeders;
    std::string leder;
    std::string id;

    json toJson() const;

    static SearchEntry fromJson(const json& j);
  };

  class TorrentPage {
  public: 
    json toJson() const;

    static TorrentPage fromJson(const json& j);

    std::string generateMagnet() const;
  private:
    static std::string torrentTrackers();

  public:

    int64_t uploaded;
    std::string leder;
    int64_t seeders;
    int64_t leechers;
    std::string name;
    std::string descripton;
    std::string info_hash;
    std::string status;
    int64_t id;
    int64_t size;
  };

  using SearchList = std::vector<SearchEntry>;

  SearchList search(const std::string& query);
  TorrentPage page(const std::string& torrentId);
  
}
