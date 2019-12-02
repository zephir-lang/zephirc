// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_LOGGER_FACADE_HPP_
#define ZEPHIR_LOGGER_FACADE_HPP_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <string>

namespace zephir::logger {

/**
 * @brief Wrap third party log library
 * and provide minimalistic interface for Zephir log writer
 */
template <class Type>
class Facade {
 private:
  // spdlog's global registry name
  const std::string _logger_name = "zephir_logger";

  std::shared_ptr<Type> _logger;

 public:
  Facade();

  /**
   * @brief Construct a new logger
   *
   * @param logger - shared pointer to logger instance
   */
  Facade(std::shared_ptr<Type> logger);

  ~Facade();

  /**
   * @brief Add a log record with INFO level
   *
   * @param message - The log message
   */
  void info(const std::string& message);

  /**
   * @brief Add a log record with WARNING level
   *
   * @param message - The log message
   */
  void warning(const std::string& message);

  /**
   * @brief Add a log record with ERROR level
   *
   * @param message - The log message
   */
  void error(const std::string& message);

  /**
   * @brief Add a log record with DEBUG level
   *
   * @param message - The log message
   */
  void debug(const std::string& message);

  /**
   * @brief Add a log record from Exception
   *
   * @param message - The log message
   * @param context - The process context detail
   */
  void exception(const std::exception& error, const Type& context);

  /**
   * @brief Add a log record with specified level, category and context
   *
   * @param message - The log message
   * @param level - The logging level
   * @param category - The log category
   * @param context - The log context
   */
  void log(const std::string& message, int level, const std::string& category,
           const Type& context);
};

}  // namespace zephir::logger

#endif  // ZEPHIR_LOGGER_FACADE_HPP_
