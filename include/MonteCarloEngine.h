#ifndef FOR_MONTE_MONTECARLOENGINE_H
#define FOR_MONTE_MONTECARLOENGINE_H

#include "Option.h"
#include <random>
#include <cmath>

struct PricingResult {
    double price;
    double standardError;
};

class MonteCarloEngine {
public:
    MonteCarloEngine(double spot, double riskFreeRate, double volatility, double maturity)
        : spotPrice(spot), riskFreeRate(riskFreeRate), volatility(volatility), maturity(maturity) {}

    PricingResult price(const Option& option, int numPaths) const {
        std::mt19937 generator(std::random_device{}());
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

    double blackscholes(const Option& option, bool isCall) {
        double d1 = (std::log(spotPrice / option.getStrikePrice()) + ((riskFreeRate + 0.5 * (volatility * volatility)) * maturity)) / (volatility * std::sqrt(maturity));
        double d2 = d1 - volatility * std::sqrt(maturity);

        double Nd1 = 0.5 * (1 + std::erf(d1 / std::sqrt(2)));
        double negNd1 = 0.5 * (1 + std::erf(-d1 / std::sqrt(2)));
        double Nd2 = 0.5 * (1 + std::erf(d2 / std::sqrt(2)));
        double negNd2 = 0.5 * (1 + std::erf(-d2 / std::sqrt(2)));

        if (isCall) {
            return spotPrice * Nd1 - option.getStrikePrice() * std::exp(-riskFreeRate * maturity) * Nd2;
        } else {
            return option.getStrikePrice() * std::exp(-riskFreeRate * maturity) * negNd2 - spotPrice * negNd1;
        }
    }

private:
    double spotPrice;
    double riskFreeRate;
    double volatility;
    double maturity;

};

#endif // FOR_MONTE_MONTECARLOENGINE_H