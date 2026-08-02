#ifndef FOR_MONTE_MONTECARLOENGINE_H
#define FOR_MONTE_MONTECARLOENGINE_H

#include "Option.h"
#include <random>
#include <cmath>

class MonteCarloEngine {
public:
    MonteCarloEngine(double spot, double riskFreeRate, double volatility, double maturity)
        : spotPrice(spot), riskFreeRate(riskFreeRate), volatility(volatility), maturity(maturity) {}

    PricingResult price(const Option& option, int numPaths) const {
        std::mt19937 generator(std:random_device{}());
        std::normal_distribution<double> normal (0.0, 1.0);

        double payoffSum = 0.0;
        double payoffSquaredSum = 0.0;

        for (int i = 0; i < numPaths; ++i) {
            double Z = normal(generator);
            double drift = (riskFreeRate - 0.5 * volatility * volatility) * maturity;
            double diffusion = volatility * std::sqrt(maturity) * Z;
            double terminalPrice = spotPrice * std::exp(drift + diffusion);

            double payoff = option.payoff(terminalPrice);
            payoffSum += payoff;
            payoffSquaredSum += payoff * payoff;
        }

        double discountFactor = std::exp(-riskFreeRate * maturity);
        double meanPayoff = payoffSum / numPaths;
        double price = discountFactor * meanPayoff;

        double variance = (payoffSquaredSum / numPaths) - (meanPayoff * meanPayoff);
        double standardError = discountFactor * std::sqrt(variance / numPaths);

        return PricingResult{price, standardError};
    }

private:
    double spotPrice;
    double riskFreeRate;
    double volatility;
    double maturity;

};

#endif // FOR_MONTE_MONTECARLOENGINE_H