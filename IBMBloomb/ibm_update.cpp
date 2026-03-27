#include <iostream>
#include <cstdio>
#include "market_data.h"
#include "telemetry.h"

int main() {
    MarketSnapshot m;
    
    printf("\033[1;34m[BLOOMBERG TERMINAL SYNC - %s]\033[0m\n", m.date);
    printf("IBM: $%.2f (+0.12%%) | S&P 500: %.2f (-1.74%%)\n", m.ibm_close, m.sp500);
    printf("Nasdaq: %.2f (-2.38%%) | US 10 Yr: 4.40 (0.07%%)\n\n", m.nasdaq);
    
    printf("\033[1;31m[SENTIMENT SHOCK]\033[0m\n");
    printf("AAII Bull-Bear Spread: %.2f%% (Extreme Bearish)\n", m.bull_bear);
    printf("Cumulative US Equity ETF Flows: $%.0fM (Record High YTD)\n\n", m.etf_flows);
    
    printf("\033[1;32m[QUANTUM/TECH MILESTONE]\033[0m\n");
    printf("Hardware: IBM Quantum Heron (133-Qubits)\n");
    printf("Validation: KCuF3 Magnetic Simulation vs. Oak Ridge Neutron Data\n");
    
    return 0;
}
