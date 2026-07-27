
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#include"third-party/cmdargs.h"
#pragma GCC diagnostic pop

#include"app.h"

namespace totorrent {
  void App::registerCommands() {
    cl_.add("search")
      .arg(cmdargs::CommandArgType::Required, "query", "Search query.")
      .describe("Search for movie titles")
      .does([](
          const cmdargs::CommandArgs& args,
          const cmdargs::CommandArgs&) {
        std::cout << "searching " << args.valueOpt("query").value_or("what happened?") << std::endl;
      });
    cl_.add("get")
      .arg(cmdargs::CommandArgType::Required,
          "index", "Index of the movie in the search buffer.")
      .flag(cmdargs::CommandFlagType::NoValue,
          "id", "id", "Downloads movie via id, not index in search buffer.")
      .describe("Downloads the specified movie. ")
      .does([this](
        const cmdargs::CommandArgs&,
        const cmdargs::CommandArgs&) {
          throw "TODO";
      });
    cl_.add("info")
      .arg(cmdargs::CommandArgType::Required,
          "index", "Index of the movie in the search buffer.")
      .flag(cmdargs::CommandFlagType::NoValue,
          "id", "id", "View movie info via id, not via index in search buffer")
      .describe("Displays specified movie's description page. ")
      .does([this](
        const cmdargs::CommandArgs&,
        const cmdargs::CommandArgs&) {
          throw "TODO";
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

  void App::handleSearch() {
  }
  void App::handleDownload() {
  }
  void App::handleLookAt() {
  }

}
