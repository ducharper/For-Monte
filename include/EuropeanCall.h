#ifndef FOR_MONTE_EUROPEANCALL_H
#define FOR_MONTE_EUROPEANCALL_H

#include "Option.h"
#include <algorithm>

class EuropeanCall : public Option {
public:
    EuropeanCall(double strikePrice, double maturity)
        : Option(strikePrice, maturity) {}

    double payoff(double spotPriceAtMaturity) const override {
        return std::max(spotPriceAtMaturity - strikePrice, 0.0);
    }

    OptionType getType() const override {
        return OptionType::Call;
    }
};

#endif //FOR_MONTE_EUROPEANCALL_H
