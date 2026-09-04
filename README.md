# For Monte

A C++ Monte Carlo engine for pricing European options. Built from the ground up as both a deep .

# Overview

For Monte prices European options in two independent ways: closed-form Black-Scholes and Monte Carlo simulation under GBM. The results of the two are validated against each other, and convergence confirms both the mathematical model and the implementation are correct. 
The project also serves as a small testbed to explore the Greeks with user-created options, which should hopefully help build intuition behind the risk sensitivities so important in options trading. Currently, For Monte includes Theta and Vega stress tests.

The current next big step for the project is implementing Giles' Multilevel Monte Carlo. Regular Monte Carlo is computationally inefficient, but MLMC addresses this through a variance-reduction technique combining simulations across multiple discretization levels.

# Key References

Giles, M. B. (2008). Multilevel Monte Carlo Path Simulation

Black, F., & Scholes, M. (1973). The Pricing of Options and Corporate Liabilities
