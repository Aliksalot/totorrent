#pragma once

#include <curl/curl.h>
#include <string>
#include"pbfetch.h"
#include"utils/constants.h"

namespace pbscrape {

  std::string getRaw(const std::string& url);

  pbfetch::SearchList extractSearchPage(
      const std::string& raw);

  pbfetch::TorrentPage extractTorrentPage(
      const std::string& raw);

  std::string constructTorrentCall(
      const std::string& id);

  std::string constructSearchCall(
      const std::string& query);

  inline size_t writeCallback(
      void* contents, size_t size, size_t nmemb, void* userp) {
      ((std::string*)userp)->append(
        (char*)contents, size * nmemb);
      return size * nmemb;
  };
};
