#include "argv.hpp"

#include <cstring>
#include <initializer_list>

Argv::Argv(std::initializer_list<const char *> args)
    : m_argv(new char *[args.size()]), m_argc(args.size()) {
  int i = 0;
  auto iter = args.begin();
  while (iter != args.end()) {
    auto len = std::strlen(*iter) + 1;
    auto ptr = std::unique_ptr<char[]>(new char[len]);

    std::strcpy(ptr.get(), *iter);
    m_args.push_back(std::move(ptr));
    m_argv.get()[i] = m_args.back().get();

    ++iter;
    ++i;
  }
}

char **Argv::argv() const { return m_argv.get(); }

size_t Argv::argc() const { return m_argc; }