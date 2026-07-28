#pragma once

#include<vector>
#include"../../shared/state.h"

namespace totorrent {

  class Client {

    enum class PromptType {
      Id, Index
    }

    bool installTorrent(PromptType t, uint64_t q);

    TorrentStatus fetchCurrentTorrentStatus();

    bool search(const std::string& query);

    bool info(PromptType t, uint64_t q);

    const SearchList& getSearchList() const {
      return sl_;
    }

    const TorrentPag& getLastSearched() const {
      return lastSearchedTorrent_;
    }

    private:
      std::string torrentInstallationUid;
      //Result of last keyword search
      SearchList sl_;
      //Result of last torrent lookup
      TorrentPage lastSearchedTorrent_;
  }
}
