// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <tuple>

#include <zephir/config/optimizations.hpp>

zephir::config::Optimizations::Optimizations()
    : container_({{"static-type-inference", true},
                  {"static-type-inference-second-pass", true},
                  {"local-context-pass", true},
                  {"constant-folding", true},
                  {"static-constant-class-folding", true},
                  {"call-gatherer-pass", true},
                  {"check-invalid-reads", false},
                  {"internal-call-transformation", false}}) {}

zephir::config::Optimizations::Optimizations(
    std::map<std::string, bool> container)
    : container_(std::move(container)) {}

bool zephir::config::Optimizations::operator==(
    const zephir::config::Optimizations &rhs) const {
  auto lhs_key = std::tie(container_);
  auto rhs_key = std::tie(rhs.container_);

  return lhs_key == rhs_key;
}

zephir::config::Optimizations &zephir::config::Optimizations::operator=(
    const zephir::config::Optimizations &rhs) = default;
