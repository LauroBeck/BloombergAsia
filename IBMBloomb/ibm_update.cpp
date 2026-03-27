#include <iostream>
#include <cstdio>
#include "telemetry.h"
#include "synergy.h"

int main() {
    printf("\033[1;34m[IBM INTEL - STARGATE CLUSTER - MAR 26, 2026 - CLOSE]\033[0m\n");
    printf("IBM: $243.45 (+0.85%%) | Brent: $108.01 (+5.66%%)\n");
    printf("Nasdaq: 21,408.08 (-2.38%%) | [10.65%% CORRECTION CONFIRMED]\n\n");
    
    printf("\033[1;32m[QUANTUM MILESTONE]\033[0m KCuF3 Magnetic Simulation: SUCCESS\n");
    printf("Hardware: IBM Quantum Heron (133-Qubit Processor)\n");
    printf("Execution: 50-Qubit precision circuit matching Oak Ridge Lab data.\n");
    printf("Note: Tunable couplers enabled the sub-1nm logic validation.\n\n");
    
    auto report = AnalystModel::get_projection();
    printf("\033[1;35m[SYNERGY]\033[0m Confluent $11B Integration: LIVE\n");
    printf("Projected Q2 Software ARR: $%0.2fB\n", report.net_arr);
    printf("RBC Bull Case Conviction: $%0.2f\n", report.rbc_bull_target);
    
    return 0;
}
