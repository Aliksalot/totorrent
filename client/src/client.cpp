
#include"client.h"

namespace totorrent {
  
  bool Client::installTorrent(PromptType t, uint64_t q) {
    throw "TODO - generate";
  }

  TorrentStatus Client::fetchCurrentTorrentStatus() {
    throw "TODO - fetchStatus";
  }

  bool Client::search(const std::string& query) {
    throw "TODO - search";
  }

  bool Client::info(PromptType t, uint64_t q) {
    throw "TODO - getobject";
  }

  const SearchList& Client::getSearchList() const {
    return sl_;
  }
}
