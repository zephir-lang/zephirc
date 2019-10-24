#include <cstring>
#include <iostream>

#include "commands/cmd.hpp"

int main(int argc, char **argv) {
  commands::Cmd cmd;
  std::memset(&cmd, 0, sizeof(cmd));

  if (!commands::parseopt(argv, cmd)) {
    return 1;
  }

  switch (cmd.kind) {
    case commands::NONE:
      std::cout << "NONE" << std::endl;
      break;
    case commands::API:
      std::cout << "API" << std::endl;
      std::cout << "\tbackend: " << (cmd.api.backend ? cmd.api.backend : "-")
                << std::endl;
      std::cout << "\tpath: " << (cmd.api.path ? cmd.api.path : "-")
                << std::endl;
      std::cout << "\toutput: " << (cmd.api.output ? cmd.api.output : "-")
                << std::endl;
      std::cout << "\toptions: " << (cmd.api.options ? cmd.api.options : "-")
                << std::endl;
      std::cout << "\turl: " << (cmd.api.url ? cmd.api.url : "-") << std::endl;
      std::cout << "\thelp: " << cmd.api.help << std::endl;
      break;
  }

  std::cout << "\nCOMMON OPTIONS" << std::endl;
  std::cout << "\tquiet: " << cmd.quiet << std::endl;
  std::cout << "\tcommon_help: " << cmd.common_help << std::endl;
  std::cout << "\tversion: " << cmd.version << std::endl;
  std::cout << "\tvernum: " << cmd.vernum << std::endl;
  std::cout << "\tdumpversion: " << cmd.dumpversion << std::endl;

  return 0;
}
