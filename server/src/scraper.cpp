#include"./scraper.h"
#include<string>
#include<stdexcept>

namespace pbscrape {

  std::string getHtml(const std::string& url) {
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
      const std::string& html) {
    throw std::logic_error("TODO");
  }

  pbfetch::TorrentPage extractTorrentPage(
      const std::string& html) {
    throw std::logic_error("TODO");
  }

}
