#ifndef STATS_H_5IWZAED1
#define STATS_H_5IWZAED1

#include "instruments.h"

double portfolio_payoff(const std::vector<Trade const *>& trades, const double S_T);
double portfolio_profit(const std::vector<Trade const *>& trades, const double S_T);

#endif /* end of include guard: STATS_H_5IWZAED1 */
