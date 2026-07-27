#include"scraper.h"
#include"torrent.h"

#include<iostream>
#include<string>
#include<fstream>

#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/magnet_uri.hpp>

using namespace totorrent;

int main() {
  
  std::string raw = getRaw("https://apibay.org/q.php?q=sausage%20party&cat=");

  //std::cout << raw << std::endl;
  auto foo = extractSearchPage(raw);
  std::string raw1 = getRaw(
      constructTorrentCall("75920856"));
  //std::cout << raw1 << std::endl;
  auto foo1 = extractTorrentPage(raw1);
  std::cout << "Got torrent: " << foo1.name << std::endl;
  std::string myMagnet = foo1.generateMagnet();
  std::string correctMagnet = "magnet:?xt=urn:btih:B339794BE78F5CDEC665201F7767444C361F0D15&dn=Sausage.Party.2016.1080p.BluRay.DDP5.1.x265.10bit-GalaxyRG265&tr=udp%3A%2F%2Ftracker.opentrackr.org%3A1337&tr=udp%3A%2F%2Fopen.stealth.si%3A80%2Fannounce&tr=udp%3A%2F%2Ftracker.torrent.eu.org%3A451%2Fannounce&tr=udp%3A%2F%2Ftracker.bittor.pw%3A1337%2Fannounce&tr=udp%3A%2F%2Fpublic.popcorn-tracker.org%3A6969%2Fannounce&tr=udp%3A%2F%2Ftracker.dler.org%3A6969%2Fannounce&tr=udp%3A%2F%2Fexodus.desync.com%3A6969&tr=udp%3A%2F%2Fopen.demonii.com%3A1337%2Fannounce&tr=udp%3A%2F%2Fglotorrents.pw%3A6969%2Fannounce&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Ftorrent.gresille.org%3A80%2Fannounce&tr=udp%3A%2F%2Fp4p.arenabg.com%3A1337&tr=udp%3A%2F%2Ftracker.internetwarriors.net%3A1337";
    
  std::ofstream out("magnet.log");
  out << "Mine:\n" << myMagnet << '\n';
  out << "Expected:\n" << correctMagnet<< '\n';
  std::cout << "  Dumpted both into file: magnet.log" << std::endl;
  std::cout << "  Are equal: " << std::boolalpha << (myMagnet == correctMagnet) << std::endl;

  auto t = Torrent("../../downloaded_movies", myMagnet);

  t.begin_seeding();

  return 0;
}
