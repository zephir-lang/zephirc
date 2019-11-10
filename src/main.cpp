// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <filesystem>
#include <memory>

#include "zephir/config.hpp"

int main(int argc, char** argv) {
  auto config = std::make_unique<core::Config>();
  auto cwd = std::filesystem::current_path();

  auto retval =
      core::load_config(config.get(), argc, argv, cwd.string() + "/config.yml");
  if (retval != EXIT_SUCCESS) {
    return retval;
  }

  return EXIT_SUCCESS;
}
