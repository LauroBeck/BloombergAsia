#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <iomanip>

/**
 * STARGATE CLUSTER v12.6 | BRL VOLATILITY MODULE
 * Monitoring USD/BRL Stability for Brazil-based Operations.
 */

double calculate_volatility(const std::vector<double>& prices) {
    size_t n = prices.size();
    if (n < 2) return 0.0;
    
    double sum = std::accumulate(prices.begin(), prices.end(), 0.0);
    double mean = sum / n;
    
    double sq_sum = std::inner_product(prices.begin(), prices.end(), prices.begin(), 0.0);
    return std::sqrt((sq_sum / n) - (mean * mean));
}

int main() {
    // Recent USD/BRL snapshot (March 26, 2026)
    std::vector<double> brl_feed = {5.2383, 5.2473, 5.2525, 5.2344, 5.2240, 5.2374};
    
    double current_vol = calculate_volatility(brl_feed);
    
    std::cout << "\033[1;33m[RIO_TELEMETRY] USD/BRL Snapshot: " << brl_feed.back() << "\033[0m\n";
    std::cout << "Rolling Volatility: " << std::fixed << std::setprecision(4) << current_vol << "\n";
    
    if (current_vol > 0.05) {
        std::cout << "\033[1;31mWARNING: BRL Volatility Spike Detected\033[0m\n";
    } else {
        std::cout << "\033[1;32mSTATUS: BRL Stability Maintained within Stargate Parity\033[0m\n";
    }
    
    return 0;
}
