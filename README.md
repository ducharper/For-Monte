For Monte

A C++ Monte Carlo engine for pricing European options, built from the ground up as both a deep dive into quantitative finance and a showcase of systems-level C++ programming.

Named for its purpose (for Monte Carlo) — a personal project exploring option pricing theory, stochastic simulation, and production-grade C++ design.

Overview

For Monte simulates the terminal price of an underlying asset under Geometric Brownian Motion (GBM), uses those simulated paths to price European call and put options, and validates the results against the closed-form Black-Scholes model. On top of pricing, it computes the full set of analytical Greeks — the risk sensitivities that matter to anyone actually managing an options position.

The project is under active development, with each phase building toward a more realistic and technically ambitious risk engine — culminating in a from-scratch implementation of Multilevel Monte Carlo (MLMC), based on Giles (2008).
