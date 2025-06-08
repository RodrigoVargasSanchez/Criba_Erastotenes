#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <omp.h> // Requiere compilación con -fopenmp
#include <algorithm>

// Criba simple hasta un límite
std::vector<int> simple_sieve(int limit) {
    std::vector<bool> primes(limit + 1, true);
    primes[0] = primes[1] = false;

    for (int i = 2; i <= std::sqrt(limit); ++i) {
        if (primes[i]) {
            for (int j = i * i; j <= limit; j += i) {
                primes[j] = false;
            }
        }
    }

    std::vector<int> result;
    for (int i = 2; i <= limit; ++i) {
        if (primes[i]) {
            result.push_back(i);
        }
    }
    return result;
}

// Criba segmentada
std::vector<int> segmented_sieve(int n, int segment_size = 1000) {
    int limit = static_cast<int>(std::sqrt(n));
    std::vector<int> base_primes = simple_sieve(limit);
    std::vector<int> primes;

    for (int low = 0; low <= n; low += segment_size) {
        int high = std::min(low + segment_size - 1, n);
        std::vector<bool> segment(high - low + 1, true);

        for (int p : base_primes) {
            int start = std::max(p * p, ((low + p - 1) / p) * p);
            for (int multiple = start; multiple <= high; multiple += p) {
                segment[multiple - low] = false;
            }
        }

        for (int i = std::max(low, 2); i <= high; ++i) {
            if (segment[i - low]) {
                primes.push_back(i);
            }
        }
    }

    return primes;
}



int main() {
    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i <= 7; i++) {
        long n = 10000 * static_cast<long>(std::pow(10, i));
        int segment_size = static_cast<int>(sqrt(n));

        auto start = std::chrono::high_resolution_clock::now();

        std::vector<int> primes = segmented_sieve(n, segment_size);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "N: " << n << "\n";
        std::cout << "Segment size: " << segment_size << "\n";
        std::cout << "Primos encontrados: " << primes.size() << "\n";
        std::cout << "Tiempo: " << elapsed.count() * 1000 << " ms\n";
        std::cout << "----------------------------------------\n";
    }

    return 0;
}