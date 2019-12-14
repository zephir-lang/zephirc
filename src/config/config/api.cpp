// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <string>
#include <tuple>
#include <utility>

#include <zephir/config/api.hpp>

zephir::config::Api::Api() : path_("doc/%version%"), theme_() {}

zephir::config::Api::Api(std::string path,
                         const zephir::config::api::Theme &theme)
    : path_(std::move(path)), theme_(theme) {}

bool zephir::config::Api::operator==(const zephir::config::Api &rhs) const {
  auto lhs_key = std::tie(path_, theme_);
  auto rhs_key = std::tie(rhs.path_, rhs.theme_);

  return lhs_key == rhs_key;
}

zephir::config::Api &
zephir::config::Api::operator=(const zephir::config::Api &rhs) = default;
