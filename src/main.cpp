#include <cstring>
#include <iostream>

#include "commands/cmd.hpp"
#include "commands/optionexception.hpp"
#include "commands/options.hpp"

int main(int argc, char** argv) {
  commands::Cmd cmd;
  std::memset(&cmd, 0, sizeof(cmd));

  auto options = new commands::Options;

  try {
    options->parseopt(argv, cmd);

    switch (cmd.kind) {
      case commands::CmdKind::NONE:
        std::cout << "NONE" << std::endl;
        break;
      case commands::CmdKind::API:
        std::cout << "API" << std::endl;
        std::cout << "\tbackend: " << (cmd.api.backend ? cmd.api.backend : "-")
                  << std::endl;
        std::cout << "\tpath: " << (cmd.api.path ? cmd.api.path : "-")
                  << std::endl;
        std::cout << "\toutput: " << (cmd.api.output ? cmd.api.output : "-")
                  << std::endl;
        std::cout << "\toptions: " << (cmd.api.options ? cmd.api.options : "-")
                  << std::endl;
        std::cout << "\turl: " << (cmd.api.url ? cmd.api.url : "-")
                  << std::endl;
        std::cout << "\thelp: " << cmd.api.help << std::endl;
        break;
    }

    std::cout << "\nCOMMON OPTIONS" << std::endl;
    std::cout << "\tquiet: " << cmd.common.quiet << std::endl;
    std::cout << "\tcommon_help: " << cmd.common.help << std::endl;
    std::cout << "\tversion: " << cmd.common.version << std::endl;
    std::cout << "\tvernum: " << cmd.common.vernum << std::endl;
    std::cout << "\tdumpversion: " << cmd.common.dumpversion << std::endl;

    delete options;
    return 0;
  } catch (const commands::OptionException& e) {
    std::cerr << e.what() << std::endl;

    delete options;
    return 1;
  }
}
