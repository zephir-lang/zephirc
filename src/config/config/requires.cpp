#include "zephir/config/requires.hpp"

#include <utility>

zephir::config::Requires::Requires() : extensions_{} {}

zephir::config::Requires::Requires(std::vector<std::string> extensions)
    : extensions_(std::move(extensions)) {}

bool zephir::config::Requires::operator==(
    const zephir::config::Requires &rhs) const {
  auto lhs_key = std::tie(extensions_);
  auto rhs_key = std::tie(rhs.extensions_);

  return lhs_key == rhs_key;
}

zephir::config::Requires &zephir::config::Requires::operator=(
    const zephir::config::Requires &rhs) = default;
