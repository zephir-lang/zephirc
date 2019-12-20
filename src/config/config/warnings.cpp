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
    : container_({
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

zephir::config::Warnings::Warnings(std::map<std::string, bool> container)
    : container_(std::move(container)) {}

bool zephir::config::Warnings::operator==(
    const zephir::config::Warnings &rhs) const {
  auto lhs_key = std::tie(container_);
  auto rhs_key = std::tie(rhs.container_);

  return lhs_key == rhs_key;
}

zephir::config::Warnings &zephir::config::Warnings::operator=(
    const zephir::config::Warnings &rhs) = default;

bool zephir::config::Warnings::SetValue(const std::string &key,
                                        const bool &value) {
  auto it = container_.find(key);
  if (it != container_.end()) {
    it->second = value;
    return true;
  }

  return false;
}
