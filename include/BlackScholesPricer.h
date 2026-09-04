#ifndef FOR_MONTE_BLACKSCHOLESPRICER_H
#define FOR_MONTE_BLACKSCHOLESPRICER_H

#include "Option.h"
#include <cmath>

class BlackScholesPricer {
public:
    double price(const Option& option, double spotPrice, double riskFreeRate,
                 double volatility) const {
        double maturity = option.getMaturity();
        double d1 = computeD1(option.getStrikePrice(), spotPrice, riskFreeRate, volatility, maturity);
        double d2 = computeD2(d1, volatility, maturity);

        bool isCall = (option.getType() == OptionType::Call);

        if (isCall) {
            return spotPrice * computeND(d1)
                 - option.getStrikePrice() * std::exp(-riskFreeRate * maturity) * computeND(d2);
        } else {
            return option.getStrikePrice() * std::exp(-riskFreeRate * maturity) * computeND(-d2)
                 - spotPrice * computeND(-d1);
        }
    }

    double delta(const Option& option, double spotPrice, double riskFreeRate,
                 double volatility) const {
        double d1 = computeD1(option.getStrikePrice(), spotPrice, riskFreeRate, volatility, option.getMaturity());
        double Nd1 = computeND(d1);
        return (option.getType() == OptionType::Call) ? Nd1 : Nd1 - 1;
    }

    double gamma(const Option& option, double spotPrice, double riskFreeRate,
                 double volatility) const {
        double maturity = option.getMaturity();
        double d1 = computeD1(option.getStrikePrice(), spotPrice, riskFreeRate, volatility, maturity);
        return pdf(d1) / (spotPrice * volatility * std::sqrt(maturity));
    }

    double vega(const Option& option, double spotPrice, double riskFreeRate,
                double volatility) const {
        double maturity = option.getMaturity();
        double d1 = computeD1(option.getStrikePrice(), spotPrice, riskFreeRate, volatility, maturity);
        return spotPrice * pdf(d1) * std::sqrt(maturity);
    }

    double theta(const Option& option, double spotPrice, double riskFreeRate,
                 double volatility) const {
        double maturity = option.getMaturity();
        double d1 = computeD1(option.getStrikePrice(), spotPrice, riskFreeRate, volatility, maturity);
        double d2 = computeD2(d1, volatility, maturity);
        double decayTerm = -(spotPrice * pdf(d1) * volatility) / (2 * std::sqrt(maturity));

        if (option.getType() == OptionType::Call) {
            return decayTerm - riskFreeRate * option.getStrikePrice()
                 * std::exp(-riskFreeRate * maturity) * computeND(d2);
        } else {
            return decayTerm + riskFreeRate * option.getStrikePrice()
                 * std::exp(-riskFreeRate * maturity) * computeND(-d2);
        }
    }

    double rho(const Option& option, double spotPrice, double riskFreeRate,
               double volatility) const {
        double maturity = option.getMaturity();
        double d1 = computeD1(option.getStrikePrice(), spotPrice, riskFreeRate, volatility, maturity);
        double d2 = computeD2(d1, volatility, maturity);

        if (option.getType() == OptionType::Call) {
            return option.getStrikePrice() * maturity * std::exp(-riskFreeRate * maturity) * computeND(d2);
        } else {
            return -option.getStrikePrice() * maturity * std::exp(-riskFreeRate * maturity) * computeND(-d2);
        }
    }

private:
    double computeD1(double strike, double spotPrice, double riskFreeRate,
                      double volatility, double maturity) const {
        double numerator = std::log(spotPrice / strike)
                          + (riskFreeRate + 0.5 * volatility * volatility) * maturity;
        double denominator = volatility * std::sqrt(maturity);
        return numerator / denominator;
    }

    double computeD2(double d1, double volatility, double maturity) const {
        return d1 - volatility * std::sqrt(maturity);
    }

    double computeND(double x) const {
        return 0.5 * (1 + std::erf(x / std::sqrt(2)));
    }

    static double pdf(double x) {
        static constexpr double invSqrt2Pi = 0.3989422804014327;
        return invSqrt2Pi * std::exp(-(x * x) / 2);
    }
};

#endif //FOR_MONTE_BLACKSCHOLESPRICER_H