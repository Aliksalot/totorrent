#pragma once

#include<string>

#include<libtorrent/torrent_status.hpp>

namespace totorrent {
  class Torrent {
  public:
    Torrent(const std::string& out_dir, const std::string& magnet);

    void begin_seeding(bool quiet = false);

    lt::torrent_status status;
    bool is_seeding = false;;
  private:
    std::string out_dir_;
    std::string magnet_;
  };
}
