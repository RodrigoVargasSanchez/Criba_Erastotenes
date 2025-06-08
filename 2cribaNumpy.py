import numpy as np
import math
import time
import tracemalloc

def simple_sieve(limit):
    sieve = np.ones(limit + 1, dtype=bool)
    sieve[:2] = False
    for i in range(2, int(math.sqrt(limit)) + 1):
        if sieve[i]:
            sieve[i*i:limit+1:i] = False
    return np.nonzero(sieve)[0]  # Índices donde hay True (números primos)

def segmented_sieve(n, segment_size=100000):
    limit = int(math.sqrt(n))
    base_primes = simple_sieve(limit)

    primes = []

    for low in range(0, n + 1, segment_size):
        high = min(low + segment_size - 1, n)
        segment = np.ones(high - low + 1, dtype=bool)

        for p in base_primes:
            start = max(p * p, (low + p - 1) // p * p)
            segment_indices = np.arange(start, high + 1, p) - low
            segment[segment_indices] = False


        segment_primes = np.nonzero(segment)[0] + low
        segment_primes = segment_primes[segment_primes >= 2]  # descartar < 2
        primes.extend(segment_primes.tolist())

    return primes

def run_tests():
    ns = [10_000 * (10 ** i) for i in range(7)]  # [10_000, 100_000, ..., 100_000_000]
    for n in ns:
        segment_size = int(math.sqrt(n))
        tracemalloc.start()
        start = time.time()

        primes = segmented_sieve(n, segment_size)

        end = time.time()
        current, peak = tracemalloc.get_traced_memory()
        tracemalloc.stop()

        print(f"N: {n:,}")
        print(f"Segment size (√n): {segment_size:,}")
        print(f"NumPy - Primos encontrados: {len(primes)}")
        print(f"Tiempo: {(end - start)*1000:.2f} ms")
        print(f"Memoria pico: {peak / 1024 / 1024:.2f} MB")
        print("-" * 50)

run_tests()

