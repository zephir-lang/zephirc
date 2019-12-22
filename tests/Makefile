# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
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
	@echo "*** $@ ***"
	@find $(TESTSDIR)/fixtures -name compile-errors.log -o -name compile.log -delete
	@find $(TESTSDIR)/fixtures -name .zephir -type d -exec rm -rf {} +
	@find $(TESTSDIR)/fixtures -name ext -type d -exec rm -rf {} +
	@find $(TESTSDIR)/output -type f -not -name .gitignore -delete
	@rm -rf "trash "directory.*

.PHONY: clean-test-results
clean-test-results:
	@echo "*** $@ ***"
	@rm -rf test-results

.PHONY: $(T)
$(T): clean-test-results deps
	@echo "*** $@ ***"
	./$@

.PHONY: aggregate
aggregate: clean-test-results $(T)
	@echo "*** $@ ***"
	ls test-results/t*-*.sh.*.counts | $(AGGREGATE)

.PHONY: deps
deps: $(TESTSDIR)/$(SHARNESS)

$(TESTSDIR)/$(SHARNESS): git
	@echo "*** checking $@ ***"
	@cd "$(PROJECTDIR)" git submodule update --init

git:
	@echo "*** checking $@ ***"
	@which git >/dev/null || (echo "Please install git!" && false)
