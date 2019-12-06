// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_LOGGER_FACADE_HPP_
#define ZEPHIR_LOGGER_FACADE_HPP_

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <string>

namespace zephir::logger {

typedef std::vector<std::tuple<std::string, std::string>> Context;

/**
 * @brief Wrap third party log library
 * and provide minimalistic interface for Zephir log writer
 */
template <class T>
class Facade {
 private:
  // spdlog's global registry name
  const std::string _logger_name = "zephir_logger";

  std::shared_ptr<T> _logger;

 public:
  Facade();

  /**
   * @brief Construct a new logger
   *
   * @param logger - shared pointer to logger instance
   */
  Facade(std::shared_ptr<T> logger);

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
   * @param ctx - The process context detail
   */
  void exception(const std::exception& error, const Context& ctx);

  /**
   * @brief Add a log record with specified level, category and context
   *
   * @param message - The log message
   * @param level - The logging level
   * @param category - The log category
   * @param ctx - The log context
   */
  void log(const std::string& message, int level, const std::string& category,
           const Context& ctx);
};

}  // namespace zephir::logger

#endif  // ZEPHIR_LOGGER_FACADE_HPP_
