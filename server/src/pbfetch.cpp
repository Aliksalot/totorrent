
#include"pbfetch.h"
#include"scraper.h"
#include"../../shared/constants.h"
#include"../../shared/httpclient.h"
#include"utils/strutil.h"

#include<stdexcept>
#include <curl/curl.h>

namespace totorrent{

  std::string TorrentPageUtils::generateMagnet() const {
    std::string out = "magnet:?xt=urn:btih:";
    out += info_hash + "&dn=";
    out += name;
    out += torrentTrackers();
    return out;
  }

  std::string TorrentPageUtils::torrentTrackers() {
    std::string tr;

    auto add_tracker = [&tr](const std::string& uri) {
      tr += "&tr=" + HttpClient::encodeURIComponent(uri);
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

  SearchList search(const std::string& query) {
    std::string uri = constructSearchCall(
        HttpClient::encodeURIComponent(query));
    std::string raw = getRaw(uri);
    SearchList out = extractSearchPage(raw);
    return out;
  }
  TorrentPage page(const std::string& torrentId) {
    std::string uri = constructTorrentCall(torrentId);
    std::string raw = getRaw(uri);
    TorrentPage out = extractTorrentPage(raw);
    return out;
  }
}
