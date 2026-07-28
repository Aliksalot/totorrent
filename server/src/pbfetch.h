#pragma once

#include"../../shared/third-party/json.hpp"

#include<string>
#include<vector>
#include<cstdint>

#include"../../shared/state.h"

namespace totorrent {
  class TorrentPageUtils : public TorrentPage {
  public:
    std::string generateMagnet() const;
  private:
    static std::string torrentTrackers();
  };
  SearchList search(const std::string& query);
  TorrentPage page(const std::string& torrentId);
}
