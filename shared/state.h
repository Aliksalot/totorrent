#pragma once

#include"third-party/json.hpp"
#include"constants.h"

namespace totorrent {

  class TorrentStatus {
  public:
    std::string name;
    int progress;
    int download_rate;
    int num_peers;

    std::string dump() const {
      std::string out = name + " ";
      out += progress * 100;
      out += "% ";
      out += download_rate / 1000;
      out += " KB/s ";
      out += num_peers;
      out += " peers ";

      return out;
    }

  };

  class SearchEntry {
  public:
    std::string name;
    std::string uploaded;
    std::string size;
    std::string seeders;
    std::string leder;
    std::string id;


    json toJson() const {
      return json {
        {"name", name},
        {"uploaded", uploaded},
        {"size", size},
        {"seeders", seeders},
        {"leder", leder},
        {"id", id}
      };
    }

    static SearchEntry fromJson(const json& j) {
      return SearchEntry{
        .name =
          j.value("name", UNKNOWN_FIELD_VALUE),
        .uploaded =
          j.value("added", "0"),
        .size =
          j.value("size", "0"),
        .seeders =
          j.value("seeders", "0"),
        .leder =
          j.value("username", UNKNOWN_FIELD_VALUE),
        .id =
          j.value("id", "0")
      };
    }

  };

  class TorrentPage {
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

    json toJson() const {
      return json{
        {"uploaded", uploaded},
        {"leder", leder},
        {"seeders", seeders},
        {"leechers", leechers},
        {"name", name},
        {"descripton", descripton},
        {"info_hash", info_hash},
        {"status", status},
        {"id", id},
        {"size", size}
      };
    }

    static TorrentPage fromJson(const json& j) {
      return TorrentPage{
        .uploaded = 
          j.value("added", -1),
        .leder = 
          j.value("username", UNKNOWN_FIELD_VALUE),
        .seeders = 
          j.value("seeders", 0),
        .leechers =
          j.value("leechers",0),
        .name = 
          j.value("name", UNKNOWN_FIELD_VALUE),
        .descripton = 
          j.value("descr", UNKNOWN_FIELD_VALUE),
        .info_hash =
          j.value("info_hash", UNKNOWN_FIELD_VALUE),
        .status =
          j.value("status", UNKNOWN_FIELD_VALUE),
        .id = 
          j.value("id", 0),
        .size =
          j.value("size", 0)
      };
    }

  };

  class SearchList : public std::vector<SearchEntry> {
  public:
    json toJson() {
      json j = json::array();
      for(const SearchEntry& entry: *this) {
        j.push_back(entry.toJson());
      }
      return j;
    }
    
    static SearchList fromJson(const json& j) {
      SearchList out;
      out.reserve(j.size());
      for(const auto& item: j) {
        out.push_back(SearchEntry::fromJson(item));
      }

      return out;
    }
  };
}
