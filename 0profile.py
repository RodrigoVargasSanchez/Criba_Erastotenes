import math
import time
import tracemalloc

def simple_sieve(limit):
    primes = [True] * (limit + 1)
    primes[0:2] = [False, False]
    for i in range(2, int(math.sqrt(limit)) + 1):
        if primes[i]:
            for j in range(i * i, limit + 1, i):
                primes[j] = False
    return [i for i, is_prime in enumerate(primes) if is_prime]

@profile
def segmented_sieve(n, segment_size=1000):
    limit = int(math.sqrt(n))
    base_primes = simple_sieve(limit)

    primes = []

    for low in range(0, n + 1, segment_size):
        high = min(low + segment_size - 1, n)
        segment = [True] * (high - low + 1)

        for p in base_primes:
            start = max(p * p, (low + p - 1) // p * p)
            for multiple in range(start, high + 1, p):
                segment[multiple - low] = False

        for i in range(max(low, 2), high + 1):
            if segment[i - low]:
                primes.append(i)

    return primes

n = 10000000
segment_size = int(math.sqrt(n))
tracemalloc.start()
start = time.time()

primes = segmented_sieve(n, segment_size)

end = time.time()
current, peak = tracemalloc.get_traced_memory()
tracemalloc.stop()

print(f"N: {n:,}")
print(f"Segment size: {segment_size:,}")
print(f"Primos encontrados: {len(primes)}")
print(f"Tiempo: {(end - start)*1000:.2f} ms")
print(f"Memoria pico: {peak / 1024 / 1024:.2f} MB")
print("-" * 50)