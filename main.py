import time
import random
import omp_arrays


def generate_random_list(size, min_val=0, max_val=10000):
    return [random.randint(min_val, max_val) for _ in range(size)]


def measure_stat(function, array, name):
    result, duration = function(array)
    print(f"[{name}] = {result} (in {duration:.2f} ms)")
    return result


def print_header():
    print("Pybind11 + OpenMP: Array Operations")
    print("Operations: Minimum | Maximum | Sum")


def main():
    sizes = [1000000, 10000000, 50000000]

    print_header()

    for size in sizes:
        print(f"\nArray size: {size}")
        array = generate_random_list(size, 0, size)

        measure_stat(omp_arrays.parallel_min, array, "Minimum")
        measure_stat(omp_arrays.parallel_max, array, "Maximum")
        measure_stat(omp_arrays.parallel_sum, array, "Sum")

    print("\nFinished all statistics with OpenMP + Pybind11.")


if __name__ == "__main__":
    main()
