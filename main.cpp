#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class SumThread {
private:
    int thread_id;
    long long total_sum;

public:
    SumThread(int id) : thread_id(id), total_sum(0) {}

    void calculate() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(1, 1000);

        for (int i = 0; i < 100; ++i) {
            total_sum += distr(gen);
        }
    }

    void print() const {
        std::cout << "Thread " << thread_id << ": " << total_sum << std::endl;
    }

    // For sorting (highest to lowest)
    bool operator<(const SumThread& other) const {
        return total_sum > other.total_sum; // Note: > for descending sort
    }

    // Getters
    long long get_sum() const { return total_sum; }
    int get_id() const { return thread_id; }
};

int main() {
    const int NUM_THREADS = 10;
    std::vector<SumThread> threads;

    std::cout << "Initializing " << NUM_THREADS << " thread simulations..." << std::endl;

    // Create and calculate sums for each thread simulation
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(i + 1);
        threads.back().calculate();
    }

    // Print in creation order
    std::cout << "\nThread results (in order):" << std::endl;
    for (const auto& thread : threads) {
        thread.print();
    }

    // Sort by sum (highest to lowest)
    std::sort(threads.begin(), threads.end());

    // Print sorted results
    std::cout << "\nThread results (sorted):" << std::endl;
    for (const auto& thread : threads) {
        thread.print();
    }

    // Print top performer details
    std::cout << "\nMAX THREAD:" << std::endl;
    std::cout << "Thread ID: " << threads[0].get_id() 
              << "\nTotal Sum: " << threads[0].get_sum() 
              << std::endl;

    return 0;
}