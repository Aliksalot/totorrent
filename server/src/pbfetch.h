#include<string>
#include<vector>

namespace pbfetch {
  struct SearchEntry {
    std::string name;
    std::string uploaded;
    std::string size;
    std::string seeders;
    std::string leder;
    std::string link;
  };

  struct TorrentPage {
    std::string uploaded;
    std::string leder;
    std::string seeders;
    std::string leechers;
    std::string magnet;
    std::string descripton;
    std::string id;
  };

  using SearchList = std::vector<SearchEntry>;

  SearchList search(const std::string& query);
  TorrentPage page(const std::string& torrentId);
}
