#ifndef ZEPHIR_TEST_ARGV_HPP_
#define ZEPHIR_TEST_ARGV_HPP_

#include <initializer_list>
#include <memory>
#include <vector>

class Argv {
 public:
  explicit Argv(std::initializer_list<const char*> args);
  char** argv() const;
  size_t argc() const;

 private:
  std::vector<std::unique_ptr<char[]>> m_args;
  std::unique_ptr<char*[]> m_argv;
  size_t m_argc;
};

#endif  // ZEPHIR_TEST_ARGV_HPP_
