// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <zephir/config.hpp>

#include "env/base.hpp"

using input_t = std::vector<std::string>;

TEST(ConfigTest, DecodeString) {
  auto tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  auto yaml = YAML::Load(R"(
{
  namespace: '',
  name: '',
  description: '',
  author: 'Zephir Team',
  version: '0.0.1',
  backend: ZendEngine3,
  verbose: false,
  silent: false,
  requires: {
    extensions: []
  },
  stubs: {
    path: ide/%version%/%namespace%,
    stubs-run-after-generate: false,
    banner: ""
  },
  api: {
    path: doc/%version%,
    theme: {
      name: zephir,
      options: {
        github: "",
        analytics: "",
        main_color: "#3E6496",
        link_color: "#3E6496",
        link_hover_color: "#5F9AE7"
      }
    }
  },
  warnings: {
    unused-variable: true,
    unused-variable-external: false,
    possible-wrong-parameter: true,
    possible-wrong-parameter-undefined: false,
    nonexistent-function: true,
    nonexistent-class: true,
    non-valid-isset: true,
    non-array-update: true,
    non-valid-objectupdate: true,
    non-valid-fetch: true,
    invalid-array-index: true,
    non-array-append: true,
    invalid-return-type: true,
    unreachable-code: true,
    nonexistent-constant: true,
    not-supported-magic-constant: true,
    non-valid-decrement: true,
    non-valid-increment: true,
    non-valid-clone: true,
    non-valid-new: true,
    non-array-access: true,
    invalid-reference: true,
    invalid-typeof-comparison: true,
    conditional-initialization: true
  },
  optimizations: {
    call-gatherer-pass: true,
    check-invalid-reads: false,
    constant-folding: true,
    internal-call-transformation: false,
    local-context-pass: true,
    static-constant-class-folding: true,
    static-type-inference-second-pass: true,
    static-type-inference: true
  },
  extra: {
    indent: spaces,
    export-classes: false
  }
}
)");

  auto file = tests_root + "/fixtures/legacy.yml";
  input_t argv({});

  auto expected = zephir::Config::CreateFromArgv(argv, file);
  auto actual = std::make_shared<zephir::Config>();

  EXPECT_TRUE(YAML::convert<zephir::ConfigPtr>::decode(yaml, actual));
  EXPECT_EQ(*actual, *expected);
}

TEST(ConfigTest, DecodeInvalid) {
  auto yaml = YAML::Load("foo: bar");
  auto actual = std::make_shared<zephir::Config>();

  EXPECT_FALSE(YAML::convert<zephir::ConfigPtr>::decode(yaml["foo"], actual));
}
