#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

struct GICSSector {
    std::string name;
    double weight_delta; // Percentage change from Bloomberg telemetry
};

class SectorMatrix {
public:
    void log_gics_audit() {
        std::vector<GICSSector> sectors = {
            {"Information Technology", 0.56},
            {"Consumer Discretionary", 1.10},
            {"Health Care",            0.98},
            {"Industrials",           0.68},
            {"Consumer Staples",       0.52},
            {"Financials",            0.22},
            {"Energy",               -0.52} // Red segment in visual map
        };

        std::cout << "\033[1;35m[GICS MATRIX] MARCH 25 SECTOR AUDIT\033[0m" << std::endl;
        std::cout << "------------------------------------------" << std::endl;
        
        for (const auto& sector : sectors) {
            std::string color = (sector.weight_delta >= 0) ? "\033[32m" : "\033[31m";
            std::cout << std::left << std::setw(25) << sector.name 
                      << ": " << color << std::fixed << std::setprecision(2) 
                      << (sector.weight_delta > 0 ? "+" : "") << sector.weight_delta 
                      << "%\033[0m" << std::endl;
        }
    }
};

int main() {
    SectorMatrix matrix;
    matrix.log_gics_audit();
    return 0;
}
