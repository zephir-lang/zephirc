// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_API_PTR_THEME_HPP_
#define ZEPHIR_CONFIG_API_PTR_THEME_HPP_

#include <memory>

namespace zephir::config::api {
class Theme;
using ThemePtr = std::shared_ptr<Theme>;
}  // namespace zephir::config::api

#endif  // ZEPHIR_CONFIG_API_PTR_THEME_HPP_
