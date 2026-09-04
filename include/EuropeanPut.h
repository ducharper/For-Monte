#ifndef FOR_MONTE_EUROPEANPUT_H
#define FOR_MONTE_EUROPEANPUT_H

#include "Option.h"
#include <algorithm>

class EuropeanPut : public Option {
public:
    EuropeanPut(double strikePrice, double maturity)
        : Option(strikePrice, maturity) {}

    double payoff(double spotPriceAtMaturity) const override {
        return std::max(strikePrice - spotPriceAtMaturity, 0.0);
    }

    OptionType getType() const override {
        return OptionType::Put;
    }
};

#endif //FOR_MONTE_EUROPEANPUT_H