#include <iostream>
#include <vector>

#include "..\include\StressTests.h"
#include "..\include\EuropeanCall.h"

void runVegaTest(const BlackScholesPricer& pricer, const Option& option,
                          double riskFreeRate, double volatility) {
    std::cout << "\nSpot Price vs. Vega\n";
    for (double spot = 50.0; spot <= 150.0; spot += 10.0) {
        double vega = pricer.vega(option, spot, riskFreeRate, volatility);
        std::cout << "Spot: " << spot << "  Vega: " << vega << "\n";
    }
}

void runThetaTest(const BlackScholesPricer& pricer, const Option& baseOption,
                            double spotPrice, double riskFreeRate, double volatility) {
    std::cout << "\nTime to Maturity vs. Theta\n";

    for (double maturity = 1.0; maturity >= 0.01; maturity -= 0.1) {
        EuropeanCall shortDatedCall(baseOption.getStrikePrice(), maturity);
        double theta = pricer.theta(shortDatedCall, spotPrice, riskFreeRate, volatility);
        std::cout << "T: " << maturity << "  Theta: " << theta << "\n";
    }
}