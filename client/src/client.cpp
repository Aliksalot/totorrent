
#include<string>
#include<iostream>

#include"client.h"
#include"../../shared/constants.h"
#include"../../shared/httpclient.h"

namespace totorrent {
  
  bool Client::installTorrent(PromptType t, uint64_t q) {
    throw "TODO - generate";
  }

  TorrentStatus Client::fetchCurrentTorrentStatus() {
    throw "TODO - fetchStatus";
  }

  bool Client::search(const std::string& query) {
    std::string uri = std::string(BASE_URL) + "search?q=" + 
      HttpClient::encodeURIComponent(query);
    std::cout << "uri: " << uri << std::endl;
    auto response = httpClient_.get(uri);

    if(response.status != 200) {
      return false;
    }

    try {
      sl_ = SearchList::fromJson(json::parse(response.body));
    }catch(const std::exception& e) {
      std::cerr << e.what() << '\n';
      return false;
    }

    return true;
  }

  bool Client::info(PromptType t, uint64_t q) {
    throw "TODO - getobject";
  }

}
