#include"scraper.h"
#include"pbfetch.h"
#include"utils/strutil.h"
#include"third-party/json.hpp"

#include<string>
#include<string_view>
#include<stdexcept>
#include<iostream>

namespace pbscrape {

  std::string getRaw(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl)
      throw std::runtime_error("Failed to initialize curl");

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
      throw std::runtime_error(curl_easy_strerror(res));

    return response;
  }

  pbfetch::SearchList extractSearchPage(
      const std::string& raw) {
    json entryListJson = json::parse(raw);

    pbfetch::SearchList out;
    for(const auto& itemJson: entryListJson) {
      //std::cout << itemJson.dump() << '\n';
      out.push_back(
          pbfetch::SearchEntry::fromJson(itemJson));
      std::cout << "Added " << out.back().name << '\n';
    }

    return out;
  }

  pbfetch::TorrentPage extractTorrentPage(
      const std::string& raw) {

    json torrentPageJson = json::parse(raw);

    return pbfetch::TorrentPage::fromJson(torrentPageJson);
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
