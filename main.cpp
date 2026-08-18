#include <iostream>

#include "include/EuropeanCall.h"
#include "include/MonteCarloEngine.h"

int main() {
    EuropeanCall my_call(100);
    MonteCarloEngine my_engine(100, 0.05, 0.2, 1);
    PricingResult engine_result = my_engine.price(my_call, 1000000);
    double bs_result = my_engine.blackscholes(my_call, true);

    std::cout << "Black-Scholes:" << bs_result << std::endl;
    std::cout << "Monte Carlo Price:" << engine_result.price << std::endl;
    std::cout << "Monte Carlo Error:" << engine_result.standardError<< std::endl;
}
