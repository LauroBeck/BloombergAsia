#include <iostream>
#include <string_view>
#include <vector>
#include <iomanip>
#include <algorithm>

namespace Stargate::Telemetry {

    struct alignas(64) MarketTick { 
        std::string_view ticker;
        double price;
        double pct_change;
        std::string_view region;
    };

    // Global Feed Snapshot: 2026-03-26 22:15
    const std::vector<MarketTick> v12_6_feed = {
        {"NKY Index",     53603.65, -0.27, "ASIA"},  // Nikkei 225
        {"KOSPI Index",    5460.46, -3.22, "ASIA"},  // KOSPI (Regional Stress)
        {"NIFTY Index",   23306.45,  1.72, "ASIA"},  // Nifty 50 (Relative Strength)
        {"BOL SS Equity",   470.20, -19.87, "EU"},   // Boliden (Mining Outlier)
        {"OMXS30 Index",   2889.81, -0.15, "EU"},    // Stockholm OMX
        {"ES1 Index",      6501.03, -1.38, "US"},    // S&P Futures
        {"CO1 Comdty",      106.66,  4.77, "CMD"}    // Brent Crude (Hormuz Monitor)
    };

    void run_diagnostics(const MarketTick& t) {
        // Energy-based Risk Flag
        if (t.ticker == "CO1 Comdty" && t.price > 105.0) {
            std::cout << " \033[1;31m[HORMUZ_BLOCKADE_ACTIVE]\033[0m";
        }
        // Systematic Volatility Flag (Threshold -10%)
        if (t.pct_change < -10.0) {
            std::cout << " \033[1;33m[VOL_SHOCK: ALPHA_VOID]\033[0m";
        }
    }
}

int main() {
    using namespace Stargate::Telemetry;
    std::cout << "\033[1;36m>> STARGATE CLUSTER V12.6 | MISSION TELEMETRY\033[0m\n";
    std::cout << "------------------------------------------------------------\n";
    
    for (const auto& tick : v12_6_feed) {
        std::cout << std::left << std::setw(15) << tick.ticker 
                  << std::fixed << std::setprecision(2) << std::setw(10) << tick.price 
                  << (tick.pct_change > 0 ? " +" : " ") << std::setw(7) << tick.pct_change << "%"
                  << " | " << tick.region;
        run_diagnostics(tick);
        std::cout << "\n";
    }
    return 0;
}
