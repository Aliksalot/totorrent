
#include"torrent.h"

#include<chrono>
#include<iostream>
#include<thread>

#include<libtorrent/session.hpp>
#include<libtorrent/add_torrent_params.hpp>
#include<libtorrent/magnet_uri.hpp>
#include<libtorrent/torrent_handle.hpp>
#include<libtorrent/torrent_status.hpp>



namespace torrent {

  namespace lt = libtorrent;

  Torrent::Torrent(
      const std::string& out_dir, const std::string& magnet) 
    : out_dir_(out_dir), magnet_(magnet) { }

  void Torrent::begin_seeding(bool quiet) {
    lt::settings_pack settings;
    settings.set_int(lt::settings_pack::alert_mask,
        lt::alert_category::status
      | lt::alert_category::error);

    lt::session session(settings);
    auto params = lt::parse_magnet_uri(magnet_);

    params.save_path = out_dir_;

    lt::torrent_handle handle =
      session.add_torrent(std::move(params));

    this->is_seeding = true;

    while(!handle.status().is_seeding) {

      status = handle.status();

      if(!quiet) {
        std::cout
          << "\r"
          << status.name << " "
          << int(status.progress * 100)
          << "% "
          << status.download_rate / 1000 << " KB/s "
          << status.num_peers << " peers"
          << std::flush;
      }

       std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if(!quiet) 
      std::cout << "\nFinished\n";

    this->is_seeding = false;
  }

}

