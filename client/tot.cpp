#include"src/app.h"

using namespace totorrent;

int main(int argc, char** argv) {
  App app{};
  app.registerCommands();
  app.run();
}

//tot
//  search "my movie name"
//    1.
//    2.
//    ...
//  lookat -id 0128383921987571
//  lookat 1
//    <info page>
//  download 1
//  download -id 0128383921987571
