#include <iostream>

#include "..\include\EuropeanCall.h"
#include "..\include\EuropeanPut.h"
#include "..\include\MonteCarloEngine.h"
#include "..\include\BlackScholesPricer.h"

int main() {
    // Setup
    double spotPrice = 100.0;
    double strikePrice = 100.0;
    double riskFreeRate = 0.05;
    double volatility = 0.2;
    double maturity = 1.0;

    EuropeanCall call(strikePrice, maturity);
    EuropeanPut put(strikePrice, maturity);

    BlackScholesPricer pricer;
    MonteCarloEngine mcEngine(spotPrice, riskFreeRate, volatility, maturity);

    // Black-Scholes
    double bsCallPrice = pricer.price(call, spotPrice, riskFreeRate, volatility);
    double bsPutPrice  = pricer.price(put, spotPrice, riskFreeRate, volatility);

    std::cout << "Black-Scholes Call Price: " << bsCallPrice << "\n";
    std::cout << "Black-Scholes Put Price:  " << bsPutPrice << "\n";

    // Monte Carlo Engine
    PricingResult mcCallPrice = mcEngine.price(call, 100000);
    PricingResult mcPutPrice = mcEngine.price(put, 100000);

    // Comparing Black-Scholes and Monte Carlo Engine
    std::cout << "Monte Carlo Call Price:   " << mcCallPrice.price
              << " (BS diff: " << std::abs(mcCallPrice.price - bsCallPrice) << ")\n";

    std::cout << "Monte Carlo Put Price:    " << mcPutPrice.price
              << " (BS diff: " << std::abs(mcPutPrice.price - bsPutPrice) << ")\n";

    // Greeks
    std::cout << "\nCall Greeks:\n";
    std::cout << "Delta: " << pricer.delta(call, spotPrice, riskFreeRate, volatility) << "\n";
    std::cout << "Gamma: " << pricer.gamma(call, spotPrice, riskFreeRate, volatility) << "\n";
    std::cout << "Vega:  " << pricer.vega(call, spotPrice, riskFreeRate, volatility) << "\n";
    std::cout << "Theta: " << pricer.theta(call, spotPrice, riskFreeRate, volatility) << "\n";
    std::cout << "Rho:   " << pricer.rho(call, spotPrice, riskFreeRate, volatility) << "\n";

    return 0;
}