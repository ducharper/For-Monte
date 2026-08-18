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

    double blackscholes(const Option& option, bool isCall) const {
        double d1 = computeD1(option.getStrikePrice());
        double d2 = computeD2(d1);

        double Nd1 = computeND(d1);
        double negNd1 = computeND(-d1);
        double Nd2 = computeND(d2);
        double negNd2 = computeND(-d2);

        if (isCall) {
            return spotPrice * Nd1 - option.getStrikePrice() * std::exp(-riskFreeRate * maturity) * Nd2;
        } else {
            return option.getStrikePrice() * std::exp(-riskFreeRate * maturity) * negNd2 - spotPrice * negNd1;
        }
    }

    double delta(const Option& option, bool isCall) const {
        double d1 = computeD1(option.getStrikePrice());
        double Nd1 = computeND(d1);

        if (isCall) {
            return Nd1;
        } else {
            return Nd1 - 1;
        }
    }

    double gamma(const Option& option) const {
        double d1 = computeD1(option.getStrikePrice());

        return pdf(d1) / (spotPrice * volatility * std::sqrt(maturity));
    }

    double vega(const Option& option) const {
        double d1 = computeD1(option.getStrikePrice());

        return spotPrice * pdf(d1) * std::sqrt(maturity);
    }

    double theta(const Option& option, bool isCall) const {
        double d1 = computeD1(option.getStrikePrice());
        double d2 = computeD2(d1);
        double Nd2 = computeND(d2);
        double negNd2 = computeND(-d2);

        if (isCall) {
            return -(spotPrice * pdf(d1) * volatility) / (2 * std::sqrt(maturity)) - riskFreeRate * option.getStrikePrice() * std::exp(-riskFreeRate * maturity) * Nd2;
        } else {
            return -(spotPrice * pdf(d1) * volatility) / (2 * std::sqrt(maturity)) + riskFreeRate * option.getStrikePrice() * std::exp(-riskFreeRate * maturity) * negNd2;
        }
    }

    double rho(const Option& option, bool isCall) const {
        double d1 = computeD1(option.getStrikePrice());
        double d2 = computeD2(d1);
        double Nd2 = computeND(d2);
        double negNd2 = computeND(-d2);

        if (isCall) {
            return option.getStrikePrice() * maturity * std::exp(-riskFreeRate * maturity) * Nd2;
        } else {
            return -option.getStrikePrice() * maturity * std::exp(-riskFreeRate * maturity) * negNd2;
        }
    }

private:
    double spotPrice;
    double riskFreeRate;
    double volatility;
    double maturity;

    double computeD1(double strike) const {
        double numerator = std::log(spotPrice / strike) + (riskFreeRate + 0.5 * volatility * volatility) * maturity;
        double denominator = volatility * std::sqrt(maturity);
        return numerator / denominator;
    }

    double computeD2(double d1) const {
        return d1 - volatility * std::sqrt(maturity);
    }

    double computeND(double d1) const {
        return 0.5 * (1 + std::erf(d1 / std::sqrt(2)));
    }

    static double pdf(double x) {
        double pi = 2*acos(0.0);
        return (1 / std::sqrt((2 * pi))) * std::exp(-(x * x) / 2);
    }
};

#endif // FOR_MONTE_MONTECARLOENGINE_H