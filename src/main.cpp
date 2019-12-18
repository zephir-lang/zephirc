// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <memory>
#include <string>
#include <vector>

#include <zephir/main.hpp>

#include "cli/application.hpp"
#include "cli/commands/api.hpp"
#include "cli/commands/build.hpp"
#include "cli/commands/clean.hpp"
#include "cli/commands/compile.hpp"
#include "cli/commands/fullclean.hpp"
#include "cli/commands/generate.hpp"
#include "cli/commands/init.hpp"
#include "cli/commands/install.hpp"
#include "cli/commands/stubs.hpp"
#include "filesystem/filesystem.hpp"

using namespace zephir::cli::commands;

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
  auto base_path = zephir::filesystem::GetCurrentWorkingPath();
  auto app = std::make_unique<zephir::cli::Application>(args, base_path);

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
  if (retval == EXIT_HELP) {
    retval = EXIT_SUCCESS;
  }

  return retval;
}
