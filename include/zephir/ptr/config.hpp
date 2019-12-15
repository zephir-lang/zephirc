#ifndef ZEPHIR_PTR_CONFIG_HPP_
#define ZEPHIR_PTR_CONFIG_HPP_

#include <memory>

namespace zephir {
class Config;
using ConfigPtr = std::shared_ptr<Config>;
}  // namespace zephir

#endif  // ZEPHIR_PTR_CONFIG_HPP_
