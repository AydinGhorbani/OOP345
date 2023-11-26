// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant
// 2023/11/17 - Cornel

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
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
	ProcessData::ProcessData(const std::string& filename) {
        ///;
        std::ifstream file(filename, std::ios::binary);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            total_items = 0;
            data = nullptr;
            return;
        }
        
        file.read(reinterpret_cast<char*>(&total_items), sizeof(int));

        data = new int[total_items];
        file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));

        file.close();
        
        ///;
        std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]" << std::endl;
	}

	ProcessData::~ProcessData() {
		delete[] data;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr;
	}

int ProcessData::operator()(const std::string& target_filename, double& avg, double& var) {
       try {
           // Create a vector to hold threads
           std::vector<std::thread> threads;

           // Specify the number of partitions (adjust as needed)
           const int num_partitions = 4;

           // Calculate the size of each partition
           int partition_size = total_items / num_partitions;

           // Vector to hold average results from each partition
           std::vector<double> avg_results(num_partitions, 0.0);

           // Launch threads to compute average for each partition
           for (int i = 0; i < num_partitions; ++i) {
               threads.emplace_back(std::bind(&computeAvgFactor, data + i * partition_size, partition_size, partition_size, std::ref(avg_results[i])));
           }

           // Join threads
           for (auto& thread : threads) {
               thread.join();
           }

           // Calculate total average from partition results
           avg = 0.0;
           for (double result : avg_results) {
               avg += result;
           }
           avg /= num_partitions;

           // Reset threads vector for variance computation
           threads.clear();

           // Vector to hold variance results from each partition
           std::vector<double> var_results(num_partitions, 0.0);

           // Launch threads to compute variance for each partition
           for (int i = 0; i < num_partitions; ++i) {
               threads.emplace_back(std::bind(&computeVarFactor, data + i * partition_size, partition_size, partition_size, avg, std::ref(var_results[i])));
           }

           // Join threads
           for (auto& thread : threads) {
               thread.join();
           }

           // Calculate total variance from partition results
           var = 0.0;
           for (double result : var_results) {
               var += result;
           }
           var /= num_partitions;

           // Open the target data file and write the data (total_items, and data) in binary format
           std::ofstream target_file(target_filename, std::ios::binary);

           if (!target_file.is_open()) {
               throw std::string("Unable to open the target file: " + target_filename);
           }

           target_file.write(reinterpret_cast<const char*>(&total_items), sizeof(int));
           target_file.write(reinterpret_cast<const char*>(data), total_items * sizeof(int));

           target_file.close();

           return 0; // Success
       }
       catch (const std::string& msg) {
           std::cerr << "Error: " << msg << std::endl;
           return -1; // Failure
       }
       catch (...) {
           std::cerr << "Error: Something went wrong!" << std::endl;
           return -1; // Failure
       }
   }
}





