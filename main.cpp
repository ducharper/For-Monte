#include <iostream>

#include "include/EuropeanCall.h"
#include "include/MonteCarloEngine.h"

int main() {
    EuropeanCall my_call(100);
    MonteCarloEngine my_engine(100, 0.05, 0.2, 1);
    PricingResult engine_result = my_engine.price(my_call, 1000000);
    double bs_result = my_engine.blackscholes(my_call, true);
    double delta_result = my_engine.delta(my_call, true);
    double gamma_result = my_engine.gamma(my_call);
    double vega_result = my_engine.vega(my_call);
    double theta_result = my_engine.theta(my_call, true);
    double rho_result = my_engine.rho(my_call, true);

    std::cout << "Black-Scholes:" << bs_result << std::endl;
    std::cout << "Monte Carlo Price:" << engine_result.price << std::endl;
    std::cout << "Monte Carlo Error:" << engine_result.standardError<< std::endl;
    std::cout << "Delta:" << delta_result << std::endl;
    std::cout << "Gamma:" << gamma_result << std::endl;
    std::cout << "Vega:" << vega_result << std::endl;
    std::cout << "Theta:" << theta_result << std::endl;
    std::cout << "Rho:" << rho_result << std::endl;

    for (double i = 0.1; i <= 0.5; i += 0.05) {
        MonteCarloEngine tempEngine(100, 0.05, i, 1);
        tempEngine.price(my_call, 100000);
        std::cout << tempEngine.vega(my_call) << std::endl;
    }
    for (double i = 20; i >= 1; i -= 1) {
        double m = i * 0.1;
        MonteCarloEngine tempEngine(100, 0.05, 0.2, m);
        std::cout << "Maturity " << m << ": " << tempEngine.theta(my_call, true) << std::endl;
    }
}
