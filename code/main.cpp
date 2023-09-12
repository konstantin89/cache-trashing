#include <iostream>
#include <array>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>

constexpr auto NUMBER_OF_SAMPLES = 36;
constexpr auto SIZE = 1000;
using MatrixType = std::array<std::array<int, SIZE>, SIZE>;

void CorrectAccess()
{
    auto counter = 0;
    MatrixType matrix;

    for(auto x=0; x<SIZE; x++)
     {
        for(auto y=0; y<SIZE; y++)
        {
            matrix[x][y] = counter;
            counter++;
        }
    }
}

void TrashCache()
{
    auto counter = 0;
    MatrixType matrix;

    for(auto x=0; x<SIZE; x++)
     {
        for(auto y=0; y<SIZE; y++)
        {
            matrix[y][x] = counter; // Notice the difference
            counter++;
        }
    }
}

void ProcessMeasurements(std::vector<long> measurements)
{
    long sum = std::accumulate(measurements.begin(), measurements.end(), 0);
    auto avg = sum / measurements.size();

    auto min = std::min_element(measurements.begin(), measurements.end());
    auto man = std::max_element(measurements.begin(), measurements.end());

    std::cout << "Number of samples " <<  measurements.size() << std::endl;
    std::cout << "Avg measurement: " <<  avg << std::endl;
    std::cout << "Min measurement: " << *min << std::endl;
    std::cout << "Max measurement: " << *man << std::endl;
}

int main()
{
    std::vector<long> correctMeasurementsNs = {};
    std::vector<long> trashMeasurementsNs = {};

    for(auto i=0; i<NUMBER_OF_SAMPLES; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        TrashCache();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        trashMeasurementsNs.push_back(duration.count());

        start = std::chrono::high_resolution_clock::now();
        CorrectAccess();
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        correctMeasurementsNs.push_back(duration.count());
    }

    std::cout << "Cache trashing access results" << std::endl;
    ProcessMeasurements(trashMeasurementsNs);
    std::cout << std::endl;

    std::cout << "Correct cache access results" << std::endl;
    ProcessMeasurements(correctMeasurementsNs);
    std::cout << std::endl;

    return 0;   
}