g++ -std=c++20 -Wall -Wextra ./src/torrent.cpp ./src/scraper.cpp ./src/pbfetch.cpp ./src/tot-server.cpp -o tot-server.out -lcurl $(pkg-config --cflags --libs libtorrent-rasterbar) && ./tot-server.out
