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
    
}
