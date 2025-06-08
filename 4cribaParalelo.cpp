#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <omp.h> // Requiere compilación con -fopenmp

std::vector<int> simple_sieve(int limit) {
    std::vector<bool> primes(limit + 1, true);
    primes[0] = primes[1] = false;

    int sqrt_limit = static_cast<int>(std::sqrt(limit));
    for (int i = 2; i <= sqrt_limit; i++) {
        if (primes[i]) {
            for (int j = i * i; j <= limit; j += i) {
                primes[j] = false;
            }
        }
    }

    std::vector<int> result;
    for (int i = 2; i <= limit; i++) {
        if (primes[i]) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> segmented_sieve(int n, int segment_size) {
    int limit = static_cast<int>(std::sqrt(n));
    std::vector<int> base_primes = simple_sieve(limit);
    std::vector<int> primes;

    // OpenMP: vector de vectores locales por cada hilo
    int num_segments = (n + segment_size - 1) / segment_size;
    std::vector<std::vector<int>> primes_per_thread(num_segments);

    #pragma omp parallel for schedule(dynamic)
    for (int segment = 0; segment < num_segments; segment++) {
        int low = segment * segment_size;
        int high = std::min(low + segment_size - 1, n);
        std::vector<bool> segment_vec(high - low + 1, true);

        for (int p : base_primes) {
            int start = std::max(p * p, ((low + p - 1) / p) * p);
            for (int multiple = start; multiple <= high; multiple += p) {
                segment_vec[multiple - low] = false;
            }
        }

        for (int i = std::max(low, 2); i <= high; i++) {
            if (segment_vec[i - low]) {
                primes_per_thread[segment].push_back(i);
            }
        }
    }

    // Fusiona los resultados de los hilos
    for (const auto& segment_primes : primes_per_thread) {
        primes.insert(primes.end(), segment_primes.begin(), segment_primes.end());
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

