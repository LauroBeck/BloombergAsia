#include <iostream>
#include <vector>
#include <cmath>
#include <immintrin.h> // AVX2
#include <iomanip>

double calculate_simd_correlation(const float* x, const float* y, size_t n) {
    // AVX2 uses 256-bit registers (8 floats at a time)
    __m256 sum_x = _mm256_setzero_ps();
    __m256 sum_y = _mm256_setzero_ps();
    __m256 sum_xx = _mm256_setzero_ps();
    __m256 sum_yy = _mm256_setzero_ps();
    __m256 sum_xy = _mm256_setzero_ps();

    for (size_t i = 0; i < n; i += 8) {
        __m256 vx = _mm256_loadu_ps(&x[i]);
        __m256 vy = _mm256_loadu_ps(&y[i]);

        sum_x  = _mm256_add_ps(sum_x, vx);
        sum_y  = _mm256_add_ps(sum_y, vy);
        sum_xx = _mm256_add_ps(sum_xx, _mm256_mul_ps(vx, vx));
        sum_yy = _mm256_add_ps(sum_yy, _mm256_mul_ps(vy, vy));
        sum_xy = _mm256_add_ps(sum_xy, _mm256_mul_ps(vx, vy));
    }

    // Horizontal add for AVX2
    alignas(32) float res[8];
    auto hsum = [&](__m256 v) {
        _mm256_store_ps(res, v);
        return res[0]+res[1]+res[2]+res[3]+res[4]+res[5]+res[6]+res[7];
    };

    float sx = hsum(sum_x);
    float sy = hsum(sum_y);
    float sxx = hsum(sum_xx);
    float syy = hsum(sum_yy);
    float sxy = hsum(sum_xy);

    double num = (double(n) * sxy) - (double(sx) * sy);
    double den = std::sqrt((double(n) * sxx - double(sx) * sx) * (double(n) * syy - double(sy) * sy));
    
    return (den == 0) ? 0 : num / den;
}

int main() {
    const size_t N = 1024; 
    alignas(32) float brent_ticks[N] = {0};
    alignas(32) float kospi_ticks[N] = {0};

    // Simulated data from Bloomberg Asia 2026-03-26
    for(int i=0; i<N; ++i) {
        brent_ticks[i] = 106.66f + (i * 0.01f);
        kospi_ticks[i] = 5460.46f - (i * 0.5f); // Inverse correlation
    }

    double corr = calculate_simd_correlation(brent_ticks, kospi_ticks, N);

    std::cout << "\033[1;32m[STARGATE AVX2 COMPUTE SUCCESS]\033[0m\n";
    std::cout << "Brent/KOSPI Correlation: " << std::fixed << std::setprecision(4) << corr << "\n";
    
    if (corr < -0.80) {
        std::cout << "\033[1;31mALERT: HORMUZ SHOCK DETECTED (Inverse Coupling)\033[0m\n";
    }

    return 0;
}
