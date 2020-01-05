// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <memory>
#include <string>
#include <vector>

#include "Console/Application.hpp"
#include "Console/Commands/ApiCommand.hpp"
#include "Console/Commands/BuildCommand.hpp"
#include "Console/Commands/CleanCommand.hpp"
#include "Console/Commands/CompileCommand.hpp"
#include "Console/Commands/FullCleanCommand.hpp"
#include "Console/Commands/GenerateCommand.hpp"
#include "Console/Commands/InitCommand.hpp"
#include "Console/Commands/InstallCommand.hpp"
#include "Console/Commands/StubsCommand.hpp"
#include "FileSystem/FileSystem.hpp"

using namespace zephir::console::commands;

static inline std::vector<std::string> prepare_args(int argc, char** argv) {
  std::vector<std::string> args;
  args.reserve(static_cast<size_t>(argc - 1));
  for (int i = argc - 1; i > 0; i--) {
    args.emplace_back(argv[i]);
  }

  return args;
}

int main(int argc, char** argv) {
  auto args = prepare_args(argc, argv);
  auto base_path = zephir::filesystem::current_path();
  auto config = zephir::Config::factory(args, base_path + "/.zephir");

  auto app =
      std::make_unique<zephir::console::Application>(config, args, base_path);

  app->AddCommand(std::make_unique<ApiCommand>("api"));
  app->AddCommand(std::make_unique<BuildCommand>("build"));
  app->AddCommand(std::make_unique<CleanCommand>("clean"));
  app->AddCommand(std::make_unique<CompileCommand>("compile"));
  app->AddCommand(std::make_unique<FullCleanCommand>("fullclean"));
  app->AddCommand(std::make_unique<GenerateCommand>("generate"));
  app->AddCommand(std::make_unique<InitCommand>("init"));
  app->AddCommand(std::make_unique<InstallCommand>("install"));
  app->AddCommand(std::make_unique<StubsCommand>("stubs"));

  auto retval = app->Run();
  return retval;
}
