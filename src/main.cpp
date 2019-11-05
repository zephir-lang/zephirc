// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <iostream>

#include "commands/optionexception.hpp"
#include "commands/options.hpp"
#include "commands/parse_result.hpp"

int main(int argc, char** argv) {
  auto options = new commands::Options;

  try {
    auto pr = options->parseopt(argc, argv);

    switch (pr.get_kind()) {
      case commands::CmdKind::NONE:
        std::cout << "NONE" << std::endl;
        break;
      case commands::CmdKind::API:
        std::cout << "API" << std::endl;
        std::cout << "\tbackend: " << (pr.api.backend ? pr.api.backend : "-")
                  << std::endl;
        std::cout << "\tpath: " << (pr.api.path ? pr.api.path : "-")
                  << std::endl;
        std::cout << "\toutput: " << (pr.api.output ? pr.api.output : "-")
                  << std::endl;
        std::cout << "\toptions: " << (pr.api.options ? pr.api.options : "-")
                  << std::endl;
        std::cout << "\turl: " << (pr.api.url ? pr.api.url : "-") << std::endl;
        std::cout << "\thelp: " << pr.api.help << std::endl;
        break;
      case commands::CmdKind::INIT:
        std::cout << "INIT" << std::endl;
        std::cout << "\tbackend: " << (pr.init.backend ? pr.init.backend : "-")
                  << std::endl;
        std::cout << "\tnamespace: " << (pr.init.ns ? pr.init.ns : "-")
                  << std::endl;
        std::cout << "\thelp: " << pr.init.help << std::endl;
    }

    std::cout << "\nCOMMON OPTIONS" << std::endl;
    std::cout << "\tquiet: " << pr.common.quiet << std::endl;
    std::cout << "\tcommon_help: " << pr.common.help << std::endl;
    std::cout << "\tversion: " << pr.common.version << std::endl;
    std::cout << "\tvernum: " << pr.common.vernum << std::endl;
    std::cout << "\tdumpversion: " << pr.common.dumpversion << std::endl;

    delete options;
    return 0;
  } catch (const commands::OptionException& e) {
    std::cerr << e.what() << std::endl;

    delete options;
    return 1;
  }
}
