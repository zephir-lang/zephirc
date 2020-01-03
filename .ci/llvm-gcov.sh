#!/usr/bin/env bash

# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

[[ "$(command -v llvm-cov 2>/dev/null || true)" = "" ]] && {
  >&2 echo "The llvm-cov not found. Aborting."
  exit 1
}

exec llvm-cov gcov "$@"
