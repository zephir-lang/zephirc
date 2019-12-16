// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <memory>
#include <string>
#include <vector>

#include <zephir/cli/application.hpp>
#include <zephir/cli/commands/api_command.hpp>
#include <zephir/cli/commands/build_command.hpp>
#include <zephir/cli/commands/clean_command.hpp>
#include <zephir/cli/commands/compile_command.hpp>
#include <zephir/cli/commands/fullclean_command.hpp>
#include <zephir/cli/commands/generate_command.hpp>
#include <zephir/cli/commands/init_command.hpp>
#include <zephir/filesystem.hpp>
#include <zephir/main.hpp>

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

  auto retval = app->Run();
  if (retval == EXIT_HELP) {
    retval = EXIT_SUCCESS;
  }

  return retval;
}
