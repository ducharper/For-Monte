#ifndef FOR_MONTE_STRESSTESTS_H
#define FOR_MONTE_STRESSTESTS_H

#include "BlackScholesPricer.h"
#include "Option.h"

void runVegaTest(const BlackScholesPricer& pricer, const Option& option,
                          double riskFreeRate, double volatility);

void runThetaTest(const BlackScholesPricer& pricer, const Option& option,
                            double spotPrice, double riskFreeRate, double volatility);

#endif //FOR_MONTE_STRESSTESTS_H