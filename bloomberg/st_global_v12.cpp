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

    const std::vector<MarketTick> v12_6_feed = {
        {"NKY Index",     52706.26, -1.67, "ASIA"},  // Nikkei 225
        {"KOSPI Index",    5256.31, -3.74, "ASIA"},  // KOSPI (Blockade Stress)
        {"NIFTY Index",   23306.45,  1.72, "ASIA"},  // Nifty 50 (India Rotation)
        {"OMXS30 Index",   2889.81, -0.15, "EU"},    // Stockholm OMX
        {"BOL SS Equity",   242.40, -19.87, "EU"},   // Boliden (Garpenberg Outlier)
        {"ES1 Index",      6542.00,  0.26, "US"},    // S&P Futures
        {"CO1 Comdty",      107.01, -0.93, "CMD"}    // Brent Crude (Hormuz Monitor)
    };

    void evaluate_risk(const MarketTick& t) {
        if (t.ticker == "CO1 Comdty" && t.price > 105.0) {
            std::cout << " [HORMUZ_HIGH_RISK]";
        }
        if (t.pct_change < -10.0) {
            std::cout << " [ALPHA_CRITICAL_VOID]";
        }
    }
}

int main() {
    using namespace Stargate::Telemetry;
    std::cout << "\033[1;36m>> STARGATE CLUSTER V12.6 | GLOBAL FLOW DEBUG\033[0m\n";
    std::cout << "--------------------------------------------------------\n";
    
    for (const auto& tick : v12_6_feed) {
        std::cout << std::left << std::setw(15) << tick.ticker 
                  << std::fixed << std::setprecision(2) << std::setw(10) << tick.price 
                  << (tick.pct_change > 0 ? " +" : " ") << std::setw(8) << tick.pct_change << "%"
                  << " | " << tick.region;
        evaluate_risk(tick);
        std::cout << "\n";
    }
    return 0;
}
