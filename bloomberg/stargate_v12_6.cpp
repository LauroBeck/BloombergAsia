#include <iostream>
#include <string_view>
#include <vector>
#include <iomanip>

namespace Stargate::Telemetry {

    struct alignas(64) MarketTick { 
        std::string_view ticker;
        double price;
        double pct_change;
        std::string_view region;
    };

    // Stargate Cluster v12.6 - Live Snapshot [2026-03-26 21:48]
    const std::vector<MarketTick> active_feed = {
        {"NKY Index",     53603.65, -0.27, "ASIA"},  // Nikkei 225
        {"KOSPI Index",    5256.31, -3.74, "ASIA"},  // KOSPI (Supply Chain Stress)
        {"SENSEX Index",  75273.00,  1.63, "ASIA"},  // India Rotation (Relative Strength)
        {"BOL SS Equity",   481.80, -17.89, "EU"},   // Boliden (Mining Outlier)
        {"OMXS30 Index",   2889.81, -0.15, "EU"},    // Stockholm 30
        {"ES1 Index",      6501.03, -1.38, "US"},    // S&P 500 Futures
        {"CO1 Comdty",      106.66,  4.77, "CMD"}    // Brent Crude (Hormuz Chokepoint)
    };

    void process_geopolitical_risk(const MarketTick& t) {
        // Hormuz Logic: Brent > $105 signals de facto blockade escalation
        if (t.ticker == "CO1 Comdty" && t.price > 105.0) {
            std::cout << " \033[1;31m[BLOCKADE_ALERT: HORMUZ TOLL REGIME]\033[0m";
        }
        // Alpha Void: Significant single-name collapse
        if (t.pct_change < -10.0) {
            std::cout << " \033[1;33m[ALPHA_VOID: SYSTEMIC ANOMALY]\033[0m";
        }
    }
}

int main() {
    using namespace Stargate::Telemetry;
    std::cout << "\n\033[1;32mSTARGATE CLUSTER v12.6 | REAL-TIME TELEMETRY\033[0m\n";
    std::cout << "------------------------------------------------------------\n";
    
    for (const auto& tick : active_feed) {
        std::cout << std::left << std::setw(15) << tick.ticker 
                  << std::fixed << std::setprecision(2) << std::setw(10) << tick.price 
                  << (tick.pct_change > 0 ? " +" : " ") << std::setw(7) << tick.pct_change << "%"
                  << " | " << tick.region;
        process_geopolitical_risk(tick);
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------\n";
    return 0;
}
