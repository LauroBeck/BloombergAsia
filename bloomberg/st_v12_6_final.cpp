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

    // Stargate Cluster v12.6 | BloombergAsia Update [2026-03-26 21:13]
    const std::vector<MarketTick> v12_6_feed = {
        {"HSI Index",    24856.43, -1.89, "HK"},  // Hang Seng (Tech Drag)
        {"USD JPY",        159.55, -0.22, "FX"},  // Yen Strength (Safety Play)
        {"VIX Index",       27.44,  8.33, "US"},  // Fear Gauge (Alert Zone)
        {"BRENT FUT",      106.30, -1.58, "CMD"}, // Brent (Timeline Extension)
        {"005930 KS",    173600.0, -3.61, "KR"},  // Samsung (Semiconductor Stress)
        {"CNOOC LTD",       29.22,  2.53, "HK"}   // Energy Outlier
    };

    void evaluate_risk(const MarketTick& t) {
        if (t.ticker == "VIX Index" && t.price > 25.0) {
            std::cout << " \033[1;31m[VOL_SPIKE]\033[0m";
        }
        if (t.ticker == "HSI Index" && t.price < 25000) {
            std::cout << " \033[1;33m[HSI_LEVEL_BREAK]\033[0m";
        }
    }
}

int main() {
    using namespace Stargate::Telemetry;
    std::cout << "\033[1;36m>> STARGATE CLUSTER V12.6 | MULTI-VECTOR MONITOR\033[0m\n";
    std::cout << "------------------------------------------------------------\n";
    
    for (const auto& tick : v12_6_feed) {
        std::cout << std::left << std::setw(15) << tick.ticker 
                  << std::fixed << std::setprecision(2) << std::setw(11) << tick.price 
                  << (tick.pct_change > 0 ? " +" : " ") << std::setw(8) << tick.pct_change << "%"
                  << " | " << tick.region;
        evaluate_risk(tick);
        std::cout << "\n";
    }
    return 0;
}
