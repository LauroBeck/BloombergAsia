#ifndef MARKET_DATA_H
#define MARKET_DATA_H

struct MarketSnapshot {
    const char* date = "March 26, 2026";
    float ibm_close = 241.67f;      // Per Bloomberg Screenshot
    float sp500 = 6477.16f;        // -1.74%
    float nasdaq = 21408.08f;      // -2.38%
    float bull_bear = -21.60f;     // AAII Spread per Chart
    float etf_flows = 51080.00f;   // Cumulative YTD ($M)
};

#endif
