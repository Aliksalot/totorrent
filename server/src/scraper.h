#pragma once

#include <curl/curl.h>
#include <string>
#include"pbfetch.h"

namespace pbscrape {

  std::string getHtml(const std::string& url);

  pbfetch::SearchList extractSearchPage(
      const std::string& html);

  pbfetch::TorrentPage extractTorrentPage(
      const std::string& html);

  inline size_t writeCallback(
      void* contents, size_t size, size_t nmemb, void* userp) {
      ((std::string*)userp)->append(
        (char*)contents, size * nmemb);
      return size * nmemb;
  };
};
