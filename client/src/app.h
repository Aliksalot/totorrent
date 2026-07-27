#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#include"third-party/cmdargs.h"
#pragma GCC diagnostic pop

namespace totorrent {

  class App {
  public:
    App() = default;

    void registerCommands();

    void run();
  private:
    void handleSearch();
    void handleDownload();
    void handleLookAt();

    cmdargs::CommandList<4> cl_;
    bool running = false;
  };

}
