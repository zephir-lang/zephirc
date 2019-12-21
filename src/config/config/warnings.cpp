// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "warnings.hpp"

#include <algorithm>
#include <tuple>

zephir::config::Warnings::Warnings()
    : container({
          {"unused-variable", true},
          {"unused-variable-external", false},
          {"possible-wrong-parameter", true},
          {"possible-wrong-parameter-undefined", false},
          {"nonexistent-function", true},
          {"nonexistent-class", true},
          {"non-valid-isset", true},
          {"non-array-update", true},
          {"non-valid-objectupdate", true},
          {"non-valid-fetch", true},
          {"invalid-array-index", true},
          {"non-array-append", true},
          {"invalid-return-type", true},
          {"unreachable-code", true},
          {"nonexistent-constant", true},
          {"not-supported-magic-constant", true},
          {"non-valid-decrement", true},
          {"non-valid-increment", true},
          {"non-valid-clone", true},
          {"non-valid-new", true},
          {"non-array-access", true},
          {"invalid-reference", true},
          {"invalid-typeof-comparison", true},
          {"conditional-initialization", true},
      }) {}

zephir::config::Warnings::Warnings(std::map<std::string, bool> new_container)
    : container(std::move(new_container)) {}

bool zephir::config::Warnings::operator==(
    const zephir::config::Warnings &rhs) const {
  return std::tie(container) == std::tie(rhs.container);
}

zephir::config::Warnings &zephir::config::Warnings::operator=(
    const zephir::config::Warnings &rhs) = default;

bool zephir::config::Warnings::update(const std::string &key,
                                      const bool &value) {
  auto it = container.find(key);
  if (it != container.end()) {
    it->second = value;
    return true;
  }

  return false;
}
