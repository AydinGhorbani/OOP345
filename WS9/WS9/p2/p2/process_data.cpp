// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant
// 2023/11/17 - Cornel

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <numeric>
#include <mutex>
#include <thread>
#include "process_data.h"

namespace sdds
{
// The following function receives array (pointer) as the first argument, number of array
//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument.
//   size and divisor are not necessarily same. When size and divisor hold same value, avg will
//   hold average of the array elements. When they are different, avg will hold a value called
// 	 as average-factor. For part 1, you will be using same value for size and double. Use of
//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
    avg = 0;
    for (int i = 0; i < size; i++) {
        avg += arr[i];
    }
    avg /= divisor;
}

// The following function receives array (pointer) as the first argument, number of array elements
//   (size) as second argument, divisor as the third argument, computed average value of the data items
//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the
//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of
//   the array elements. When they are different, var will hold a value called as variance factor.
//   For part 1, you will be using same value for size and double. Use of different values for size
//   and divisor will be useful for multi-threaded implementation in part-2.
void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
    var = 0;
    for (int i = 0; i < size; i++) {
        var += (arr[i] - avg) * (arr[i] - avg);
    }
    var /= divisor;
}

// The following constructor of the functor receives name of the data file, opens it in
//   binary mode for reading, reads first int data as total_items, allocate memory space
//   to hold the data items, and reads the data items into the allocated memory space.
//   It prints first five data items and the last three data items as data samples.
//
ProcessData::ProcessData(const std::string& filename, int n_threads)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&total_items), sizeof(int));

    data = new int[total_items];
    file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));

    file.close();

    ///////
    std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
    std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
              << data[total_items - 3] << ", " << data[total_items - 2] << ", "
              << data[total_items - 1] << "]" << std::endl;

    // Following statements initialize the variables added for multi-threaded
    //   computation
    num_threads = n_threads;
    averages = new double[num_threads];
    variances = new double[num_threads];
    p_indices = new int[num_threads + 1];
    for (int i = 0; i < num_threads; i++)
        p_indices[i] = i * (total_items / num_threads);
    p_indices[num_threads] = total_items;
}

ProcessData::~ProcessData() {
    delete[] data;
    delete[] averages;
    delete[] variances;
    delete[] p_indices;
}

ProcessData::operator bool() const {
    return total_items > 0 && data;
}

int ProcessData::operator()(const std::string& target_filename, double& avg, double& var) {
    try {
        // Create a vector to hold threads
        std::vector<std::thread> threads;

        // Specify the number of partitions (adjust as needed)
        const int num_partitions = num_threads;

        // Vector to hold average results from each partition
        std::vector<double> avg_results(num_partitions, 0.0);

        // Vector to hold variance results from each partition
        std::vector<double> var_results(num_partitions, 0.0);

        // Mutex for synchronization
        std::mutex mutex;
        // Launch threads to compute average and variance for each partition
        for (int i = 0; i < num_partitions; ++i) {
            threads.emplace_back([this, i, &avg_results, &var_results, &mutex]() {
                double local_avg = 0.0;
                double local_var = 0.0;

                for (int j = p_indices[i]; j < p_indices[i + 1]; ++j) {
                    local_avg += data[j];
                    local_var += data[j] * data[j];
                }

                // Lock the mutex before updating shared data
                std::lock_guard<std::mutex> lock(mutex);
                avg_results[i] = local_avg;
                var_results[i] = local_var;
            });
        }

        // Join threads
        for (auto& thread : threads) {
            thread.join();
        }

        // Calculate total average and variance from partition results
        double sum_avg = 0.0;
        double sum_var = 0.0;

        for (int i = 0; i < num_partitions; ++i) {
            sum_avg += avg_results[i];
            sum_var += var_results[i];
        }

        avg = sum_avg / total_items;
        var = (sum_var - total_items * avg * avg) / total_items;

        // Rest of the code to write to the target file and set avg and var

        return 0; // Success
    } catch (const std::string& msg) {
        std::cerr << "Error: " << msg << std::endl;
        return -1; // Failure
    } catch (...) {
        std::cerr << "Error: Something went wrong!" << std::endl;
        return -1; // Failure
    }
}
}
