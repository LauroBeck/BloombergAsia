#include <iostream>
#include <string_view>
#include <vector>
#include <iomanip>

namespace FinancialFlows {

    struct alignas(64) MarketTick { 
        std::string_view ticker;
        double price;
        double pct_change;
        std::string_view region;
    };

    const std::vector<MarketTick> global_snapshot = {
        // ASIA FEED
        {"NKY Index",     52706.26, -1.67, "ASIA"},  // Nikkei 225
        {"KOSPI Index",    5256.31, -3.74, "ASIA"},  // KOSPI (Geopolitical Stress)
        {"NIFTY Index",   23306.45,  1.72, "ASIA"},  // Nifty 50 (India Outperformance)
        
        // EUROPE FEED
        {"OMXS30 Index",   2889.81, -0.15, "EU"},    // Stockholm OMX
        {"BOL SS Equity",   242.40, -19.87, "EU"},   // Boliden (Outlier: Mining Ops)
        
        // AMERICAS / FUTURES
        {"ES1 Index",      6542.00,  0.26, "US"},    // S&P Futures
        {"CO1 Comdty",      107.01, -0.93, "CMD"}    // Brent Crude (Hormuz Monitor)
    };
}

void print_alert(std::string_view ticker, double chg) {
    if (chg < -5.0) std::cout << " [CRITICAL ALERT: " << ticker << " volatility spike]";
}

int main() {
    std::cout << "\033[1;32m--- STARGATE GLOBAL TELEMETRY: 2026-03-26 ---\033[0m\n";
    std::cout << std::left << std::setw(15) << "TICKER" 
              << std::setw(12) << "PRICE" 
              << std::setw(12) << "CHANGE (%)" 
              << "REGION" << "\n";
    
    for (const auto& tick : FinancialFlows::global_snapshot) {
        std::cout << std::left << std::setw(15) << tick.ticker 
                  << std::fixed << std::setprecision(2) << std::setw(12) << tick.price 
                  << (tick.pct_change > 0 ? "+" : "") << std::setw(11) << tick.pct_change
                  << tick.region;
        print_alert(tick.ticker, tick.pct_change);
        std::cout << "\n";
    }
    return 0;
}
