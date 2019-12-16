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
#include <zephir/commands.hpp>
#include <zephir/filesystem.hpp>
#include <zephir/main.hpp>

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

  auto retval = zephir::commands::CreateFromArgv(args);

  if (retval == EXIT_HELP) {
    retval = EXIT_SUCCESS;
  }

  return retval;
}
