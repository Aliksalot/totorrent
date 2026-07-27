
#include"pbfetch.h"
#include"utils/constants.h"
#include"utils/strutil.h"

#include<stdexcept>
#include <curl/curl.h>

namespace totorrent{
  json SearchEntry::toJson() const {
    throw std::runtime_error("TODO");
  }

  SearchEntry SearchEntry::fromJson(const json& j) {
    return SearchEntry{
      .name =
        j.value("name", UNKNOWN_FIELD_VALUE),
      .uploaded =
        j.value("added", "0"),
      .size =
        j.value("size", "0"),
      .seeders =
        j.value("seeders", "0"),
      .leder =
        j.value("username", UNKNOWN_FIELD_VALUE),
      .id =
        j.value("id", "0")
    };
  }

  json TorrentPage::toJson() const {
    throw std::runtime_error("TODO");
  }

  TorrentPage TorrentPage::fromJson(const json& j) {
    return TorrentPage{
      .uploaded = 
        j.value("added", -1),
      .leder = 
        j.value("username", UNKNOWN_FIELD_VALUE),
      .seeders = 
        j.value("seeders", 0),
      .leechers =
        j.value("leechers",0),
      .name = 
        j.value("name", UNKNOWN_FIELD_VALUE),
      .descripton = 
        j.value("descr", UNKNOWN_FIELD_VALUE),
      .info_hash =
        j.value("info_hash", UNKNOWN_FIELD_VALUE),
      .status =
        j.value("status", UNKNOWN_FIELD_VALUE),
      .id = 
        j.value("id", 0),
      .size =
        j.value("size", 0)
    };
  }

  std::string TorrentPage::generateMagnet() const {
    std::string out = "magnet:?xt=urn:btih:";
    out += info_hash + "&dn=";
    out += name;
    out += torrentTrackers();
    return out;
  }

  std::string TorrentPage::torrentTrackers() {
    std::string tr;

    auto add_tracker = [&tr](const std::string& uri) {
      tr += "&tr=" + encodeSafeUri(uri);
      return tr;
    };

    add_tracker("udp://tracker.opentrackr.org:1337");
    add_tracker("udp://open.stealth.si:80/announce");
    add_tracker("udp://tracker.torrent.eu.org:451/announce");
    add_tracker("udp://tracker.bittor.pw:1337/announce");
    add_tracker("udp://public.popcorn-tracker.org:6969/announce");
    add_tracker("udp://tracker.dler.org:6969/announce");
    add_tracker("udp://exodus.desync.com:6969");
    add_tracker("udp://open.demonii.com:1337/announce");
    add_tracker("udp://glotorrents.pw:6969/announce");
    add_tracker("udp://tracker.coppersurfer.tk:6969");
    add_tracker("udp://torrent.gresille.org:80/announce");
    add_tracker("udp://p4p.arenabg.com:1337");
    add_tracker("udp://tracker.internetwarriors.net:1337");

    return tr;
  }
}
