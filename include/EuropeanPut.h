#ifndef FOR_MONTE_EUROPEANPUT_H
#define FOR_MONTE_EUROPEANPUT_H

#include "Option.h"
#include <algorithm>

class EuropeanPut : public Option {
public:
    explicit EuropeanPut(double strike) : strikePrice(strike) {}

    double payoff(double S_T) const override {
        return std::max(strikePrice - S_T, 0.0);
    }

private:
    double strikePrice;
}

#endif //UNTITLED_EUROPEANPUT_H
