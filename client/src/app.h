#pragma once

#include"third-party/cmdargs.h"
#include"client.h"

namespace totorrent {

  class App {
  public:
    App() = default;

    void registerCommands();

    void run();
  private:
    void handleSearch(const cmdargs::CommandArgs& args, const cmdargs::CommandArgs& flags);
    void handleDownload(const cmdargs::CommandArgs& args, const cmdargs::CommandArgs& flags);
    void handleLookAt(const cmdargs::CommandArgs& args, const cmdargs::CommandArgs& flags);

    cmdargs::CommandList<4> cl_;
    bool running = false;

    Client client_;
  };

}
