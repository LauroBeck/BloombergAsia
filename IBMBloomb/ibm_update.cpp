#include <iostream>
#include <string_view>
#include <vector>
#include <cstdio>

struct MarketIndex {
    std::string_view name;
    std::string_view level;
    std::string_view change;
    std::string_view driver;
};

struct BankTrace {
    std::string_view bank;
    std::string_view stance;
    std::string_view target;
};

void print_header(std::string_view title, std::string_view color = "\033[1;34m") {
    std::cout << "\n" << color << title << "\033[0m\n";
    std::cout << "----------------------------------------------------------------------\n";
}

int main() {
    print_header("🔵 IBM (NYSE: IBM) DAILY BRIEF - MARCH 26, 2026");
    std::cout << "Last Price: ~$225.10 | Sentiment: Neutral/Volatile\n";
    std::cout << "Focus: Quantum KCuF3 Milestone vs. Hormuz Risk-Off Shock\n\n";

    std::cout << "\033[1;32m[1] QUANTUM: SIMULATING MAGNETIC MATERIALS (KCuF3)\033[0m\n";
    std::cout << "    - Achievement: Accurately matched Oak Ridge Lab neutron scattering data.\n";
    std::cout << "    - Tech: Utilized 50 qubits on Heron processor with zero-noise extrapolation.\n";
    std::cout << "    - Note: IBM's Charles Bennett receives ACM Turing Award (March 17).\n\n";

    print_header("🏛️ INSTITUTIONAL TRACE: MARCH '26 PRICE TARGETS", "\033[1;35m");
    
    std::vector<BankTrace> traces = {
        {"JPMorgan", "Neutral", "$317.00"},
        {"BofA/Merrill", "Buy", "$335.00"},
        {"Wells Fargo", "Overweight", "$305.00"},
        {"BNY Mellon", "Hold", "$290.00"}
    };

    printf("%-18s | %-15s | %-10s\n", "INSTITUTION", "RATING", "TARGET");
    std::cout << "----------------------------------------------------------------------\n";
    for (const auto& t : traces) {
        printf("%-18.*s | %-15.*s | %-10.*s\n", 
               (int)t.bank.size(), t.bank.data(), 
               (int)t.stance.size(), t.stance.data(), 
               (int)t.target.size(), t.target.data());
    }

    print_header("📉 MACRO CONTEXT: THE HORMUZ SHOCK");
    
    std::vector<MarketIndex> indices = {
        {"S&P 500", "6,555.86", "-1.70%", "Geopolitical Risk Premium"},
        {"Nasdaq", "21,693.17", "-2.40%", "Correction (10% off highs)"},
        {"Brent Crude", "$101.89", "+4.80%", "Hormuz 'Toll System' Impact"}
    };

    printf("%-15s | %-12s | %-8s | %-25s\n", "INDEX", "LEVEL", "CHANGE", "DRIVER");
    std::cout << "----------------------------------------------------------------------\n";
    for (const auto& i : indices) {
        printf("%-15.*s | %-12.*s | %-8.*s | %-25.*s\n", 
               (int)i.name.size(), i.name.data(), 
               (int)i.level.size(), i.level.data(), 
               (int)i.change.size(), i.change.data(), 
               (int)i.driver.size(), i.driver.data());
    }

    std::cout << "\n\033[1;31mURGENT ALERT:\033[0m Iran formalizing a maritime 'toll system' in the Strait.\n";
    std::cout << "Preferential access granted to 5 nations (CN, RU, IN, IQ, PK).\n\n";
    
    return 0;
}
