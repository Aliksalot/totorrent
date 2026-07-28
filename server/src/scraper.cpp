#include"scraper.h"
#include"pbfetch.h"
#include"utils/strutil.h"
#include"../../shared/third-party/json.hpp"
#include"../../shared/httpclient.h"

#include<string>
#include<string_view>
#include<stdexcept>
#include<iostream>

namespace totorrent {

  std::string getRaw(const std::string& url) {
    HttpClient httpClient;
    auto response = httpClient.get(url);
    if(response.status != 200) {
      throw std::runtime_error(std::string("Couldn't get ") + url);
    }
    return response.body;
  }

  SearchList extractSearchPage(
      const std::string& raw) {
    json entryListJson = json::parse(raw);

    SearchList out;
    for(const auto& itemJson: entryListJson) {
      //std::cout << itemJson.dump() << '\n';
      out.push_back(
          SearchEntry::fromJson(itemJson));
      std::cout << "Added " << out.back().name << '\n';
      std::cout << "  Dump: \n" << out.back().toJson().dump() << '\n';
    }

    return out;
  }

  TorrentPage extractTorrentPage(
      const std::string& raw) {

    json torrentPageJson = json::parse(raw);

    return TorrentPage::fromJson(torrentPageJson);
  }

  std::string constructTorrentCall(
      const std::string& id) {
    return std::string(PBAPI_INFO) + "?id=" + id;
  }

  std::string constructSearchCall(
      const std::string& query) {
    return std::string(PBAPI_SEARCH) + "?q=" + query +"&cat=0";
  }


}
