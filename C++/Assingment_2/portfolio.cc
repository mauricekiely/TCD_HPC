#include <iostream>
#include <vector>
#include "portfolio.h"
#include "instruments.h"

/**
 * @brief
*/
double portfolio_payoff(const std::vector<Trade const *>& trades, const double S_T){
    double overall_payoff = 0.0;
    for (const Trade* trade : trades){
        overall_payoff += trade->payoff(S_T);
    }
    return overall_payoff;
}

double portfolio_profit(const std::vector<Trade const *>& trades, const double S_T) {
    double total_cost = 0.0;

    for (const Trade* trade : trades) {
        total_cost += trade->get_cost();
    }
    return (portfolio_payoff(trades, S_T) - total_cost);
}