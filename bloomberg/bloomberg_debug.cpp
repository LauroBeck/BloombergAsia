#include <iostream>
#include <string_view>
#include <vector>
#include <iomanip>

namespace FinancialFlows {

    struct BloombergField {
        static constexpr std::string_view LAST_PRICE = "PX_LAST";
        static constexpr std::string_view CHG_PCT    = "PCT_CHG_1D";
    };

    struct alignas(64) MarketTick { 
        std::string_view ticker;
        double price;
        double pct_change;
    };

    const std::vector<MarketTick> current_snapshot = {
        {"NKY Index",     52706.26, -1.67}, // Nikkei 225
        {"KOSPI Index",    5256.31, -3.74}, // KOSPI - Outlier Alert
        {"AS51 Index",     8476.40, -0.58}, // S&P/ASX 200
        {"CO1 Comdty",      107.01, -0.93}, // Brent Crude
        {"ES1 Index",      6542.00,  0.26}, // S&P Futures
        {"USGG10YR Index",  4.4216,  0.22}, // US 10-Year Yield
        {"JPY Curncy",      159.72,  0.06}  // USD-JPY
    };
}

int main() {
    std::cout << "--- STARGATE CLUSTER: BLOOMBERG ASIA DEBUG [2026-03-26] ---\n";
    std::cout << std::left << std::setw(15) << "TICKER" 
              << std::setw(12) << "PRICE" 
              << "CHANGE (%)" << "\n";
    
    for (const auto& tick : FinancialFlows::current_snapshot) {
        std::cout << std::left << std::setw(15) << tick.ticker 
                  << std::fixed << std::setprecision(2) << std::setw(12) << tick.price 
                  << (tick.pct_change > 0 ? "+" : "") << tick.pct_change << "%\n";
    }
    return 0;
}
