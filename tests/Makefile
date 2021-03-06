# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# NOTE: run with TEST_VERBOSE=1 for verbose sharness tests.

T = $(sort $(wildcard t[0-9][0-9][0-9][0-9]-*.sh))
SHARNESSDIR = sharness
SHARNESS = $(SHARNESSDIR)/sharness.sh
AGGREGATE = $(SHARNESSDIR)/aggregate-results.sh

PROJECTDIR=$(shell cd $(SHARNESSDIR)/../.. || exit 1; pwd)
TESTSDIR=$(shell cd $(PROJECTDIR)/tests || exit 1; pwd)

# TODO: Call "make all" to compile zephir in case of absence
BINS = zephir

.PHONY: all
all: aggregate

.PHONY: clean
clean: clean-test-results
	@find $(TESTSDIR)/fixtures -name compile-errors.log -o -name compile.log -delete
	@find $(TESTSDIR)/fixtures -name .zephir -type d -exec rm -rf {} +
	@find $(TESTSDIR)/fixtures -name ext -type d -exec rm -rf {} +
	@find $(TESTSDIR)/output -type d -not -name output -exec rm -rf {} +
	@find $(TESTSDIR)/output -type f -not -name .gitignore -delete
	@rm -rf "trash "directory.*

.PHONY: clean-test-results
clean-test-results:
	@rm -rf test-results

.PHONY: $(T)
$(T): clean-test-results deps
	./$@

.PHONY: aggregate
aggregate: clean-test-results $(T)
	ls test-results/t*-*.sh.*.counts | $(AGGREGATE)

.PHONY: deps
deps: $(TESTSDIR)/$(SHARNESS)

$(TESTSDIR)/$(SHARNESS): git
	@cd "$(PROJECTDIR)" git submodule update --init

git:
	@which git >/dev/null || (echo "Please install git!" && false)
