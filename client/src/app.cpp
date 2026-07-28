
#include"third-party/cmdargs.h"

#include"app.h"

namespace totorrent {
  void App::registerCommands() {

    cl_.add("search")
      .arg(cmdargs::CommandArgType::Required, "query", "Search query.")
      .describe("Search for movie titles")
      .does([this](
          const cmdargs::CommandArgs& args,
          const cmdargs::CommandArgs& flags) {
        std::cout << "searching " << args.valueOpt("query").value_or("what happened?") << std::endl;
        handleSearch(args, flags);
      });

    cl_.add("get")
      .flag(cmdargs::CommandFlagType::WithValue,
          "id", "id", "Downloads movie via id. ")
      .flag(cmdargs::CommandFlagType::WithValue,
          "index", "i", "Downloads movie via index in search list. ")
      .describe("Downloads the specified movie. If there is no flag provided, it tries to download the last searched movie. ")
      .does([this](
        const cmdargs::CommandArgs& args,
        const cmdargs::CommandArgs& flags) {
          handleDownload(args, flags);
      });

    cl_.add("info")
      .flag(cmdargs::CommandFlagType::WithValue,
          "id", "id", "View movie info via id. ")
      .flag(cmdargs::CommandFlagType::WithValue,
          "index", "i", "View movie info via index in search list. ")
      .describe("Displays specified movie's description page. If there is no flag provided, it tries to display the info for the last searched movie. ")
      .does([this](
        const cmdargs::CommandArgs& args,
        const cmdargs::CommandArgs& flags) {
          handleLookAt(args, flags);
      });

    cl_.add("done")
      .describe("Quits the program. ")
      .does([this](
        const cmdargs::CommandArgs&,
        const cmdargs::CommandArgs&) {
        this->running = false;
      });

    cl_.includeHelp();
  }

  void App::run() {
    running = true;

    std::cout << "Welcome. Type \"help\" for usage." << std::endl;
    while(running) {
      std::string input;
      std::getline(std::cin, input);
      cl_.execute(input);
    }

  }

  void App::handleSearch(const cmdargs::CommandArgs& args, const cmdargs::CommandArgs&) {
    std::string query = args.value("query");

    bool result = client_.search(query);
    if(!result) {
      std::cout << "Couldn't execute search. " << std::endl;
      return;
    }

    auto sl = client_.getSearchList();

    for(const auto& si: sl) {
      std::cout << si.toJson().dump() << std::endl;
    }

  }
  void App::handleDownload(const cmdargs::CommandArgs& args, const cmdargs::CommandArgs& flags) {
  }
  void App::handleLookAt(const cmdargs::CommandArgs& args, const cmdargs::CommandArgs& flags) {
  }

}
