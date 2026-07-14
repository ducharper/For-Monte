#ifndef UNTITLED_EUROPEANCALL_H
#define UNTITLED_EUROPEANCALL_H

#include "Option.h"
#include <algorithm> // for std::max

class EuropeanCall : public Option {
    public:
        explicit EuropeanCall(double strike) : strikePrice(strike) {}

        double payoff(double S_T) const override {
            return std::max(S_T - strikePrice, 0.0);
        }

    private:
        double strikePrice;
};

#endif //FOR_MONTE_EUROPEANCALL_H
