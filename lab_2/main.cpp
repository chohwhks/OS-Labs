#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void min_max(const std::vector<int>& arr, int& minVal, int& maxVal, size_t& minIdx, size_t& maxIdx) {
    minVal = maxVal = arr[0];
    minIdx = maxIdx = 0;
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < minVal) {
            minVal = arr[i];
            minIdx = i;
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxIdx = i;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(7));
    }
    std::cout << "min_max: минимум = " << minVal << ", максимум = " << maxVal << "\n";
}

void average(const std::vector<int>& arr, double& avg) {
    double sum = 0;
    for (int v : arr) {
        sum += v;
        std::this_thread::sleep_for(std::chrono::milliseconds(12));
    }
    avg = sum / arr.size();
    std::cout << "average: среднее значение = " << avg << "\n";
}

int main() {
    size_t n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;

    std::vector<int> arr(n);
    std::cout << "Введите " << n << " элементов:\n";
    for (size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int minVal, maxVal;
    size_t minIdx, maxIdx;
    double avg;

    std::thread tMinMax(min_max, std::cref(arr), std::ref(minVal), std::ref(maxVal), std::ref(minIdx), std::ref(maxIdx));
    std::thread tAverage(average, std::cref(arr), std::ref(avg));

    tMinMax.join();
    tAverage.join();

    arr[maxIdx] = static_cast<int>(avg);
    arr[minIdx] = static_cast<int>(avg);

    std::cout << "\nИтоговый массив:\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
