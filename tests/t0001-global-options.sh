#!/usr/bin/env bash

# shellcheck disable=SC2034
test_description="Test global CLI options"

# shellcheck disable=SC1091
source ./setup.sh

test_expect_success "Should exit with 0 status code on: --help" "
  test_expect_code 0 zephirc --help
"

test_expect_success "Should exit with 0 status code on: --version" "
  test_expect_code 0 zephirc --version
"

test_expect_success "Should exit with 0 status code on: --version" "
  test_expect_code 0 zephirc --vernum
"

test_expect_success "Should exit with 0 status code on: --dumpversion" "
  test_expect_code 0 zephirc --dumpversion
"

test_expect_success "Should exit with 0 status code when no options" "
  test_expect_code 0 zephirc
"

test_done
