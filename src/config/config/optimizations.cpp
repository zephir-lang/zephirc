#include "zephir/config/optimizations.hpp"

#include <tuple>

zephir::config::Optimizations::Optimizations()
    : sti_(true),
      stisp_(true),
      lcp_(true),
      cf_(true),
      sccf_(true),
      cgp_(true),
      cir_(false),
      ict_(false) {}

zephir::config::Optimizations::Optimizations(bool sti, bool stisp, bool lcp,
                                             bool cf, bool sccf, bool cgp,
                                             bool cir, bool ict)
    : sti_(sti),
      stisp_(stisp),
      lcp_(lcp),
      cf_(cf),
      sccf_(sccf),
      cgp_(cgp),
      cir_(cir),
      ict_(ict) {}

bool zephir::config::Optimizations::operator==(
    const zephir::config::Optimizations &rhs) const {
  auto lhs_key = std::tie(sti_, stisp_, lcp_, cf_, sccf_, cgp_, cir_, ict_);
  auto rhs_key = std::tie(rhs.sti_, rhs.stisp_, rhs.lcp_, rhs.cf_, rhs.sccf_,
                          rhs.cgp_, rhs.cir_, rhs.ict_);

  return lhs_key == rhs_key;
}

zephir::config::Optimizations &zephir::config::Optimizations::operator=(
    const zephir::config::Optimizations &rhs) = default;
