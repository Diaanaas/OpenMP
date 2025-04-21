#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <limits>
#include <omp.h>
#include <chrono>

namespace py = pybind11;

// Пошук мінімального елемента без reduction(min:)
int parallel_min(const std::vector<int>& arr) {
    int global_min = std::numeric_limits<int>::max();
    int n = arr.size();

    #pragma omp parallel num_threads(10)
    {
        int local_min = std::numeric_limits<int>::max();
        #pragma omp for nowait
        for (int i = 0; i < n; ++i) {
            if (arr[i] < local_min) {
                local_min = arr[i];
            }
        }

        #pragma omp critical
        {
            if (local_min < global_min) {
                global_min = local_min;
            }
        }
    }

    return global_min;
}

// Пошук максимального елемента без reduction(max:)
int parallel_max(const std::vector<int>& arr) {
    int global_max = std::numeric_limits<int>::min();
    int n = arr.size();

    #pragma omp parallel num_threads(10)
    {
        int local_max = std::numeric_limits<int>::min();
        #pragma omp for nowait
        for (int i = 0; i < n; ++i) {
            if (arr[i] > local_max) {
                local_max = arr[i];
            }
        }

        #pragma omp critical
        {
            if (local_max > global_max) {
                global_max = local_max;
            }
        }
    }

    return global_max;
}

// Паралельне обчислення суми елементів масиву (використовує стандартну reduction, вона стабільна)
long long parallel_sum(const std::vector<int>& arr) {
    long long sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }
    return sum;
}

PYBIND11_MODULE(omp_arrays, m) {
    m.doc() = "Parallel min, max, sum using OpenMP without reduction(min/max)";

    m.def("parallel_min", [](const std::vector<int>& arr) {
        auto start = std::chrono::high_resolution_clock::now();
        int result = parallel_min(arr);
        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        return py::make_tuple(result, duration);
    });

    m.def("parallel_max", [](const std::vector<int>& arr) {
        auto start = std::chrono::high_resolution_clock::now();
        int result = parallel_max(arr);
        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        return py::make_tuple(result, duration);
    });

    m.def("parallel_sum", [](const std::vector<int>& arr) {
        auto start = std::chrono::high_resolution_clock::now();
        long long result = parallel_sum(arr);
        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        return py::make_tuple(result, duration);
    });
}
