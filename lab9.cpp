#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

bool isOdd(int n) {
    return n % 2 != 0;
}

void task1() {
    std::list<int> myList(20);
    for (int &n : myList) n = rand() % 100;

    myList.erase(std::remove_if(myList.begin(), myList.end(), isOdd), myList.end());
    
    std::cout << "Task 1: ";
    for (int n : myList) std::cout << n << " ";
    std::cout << "\n";
}

void task2() {
    std::array<std::string, 5> names = {"Oleksandr", "Ivan", "Anastasiia", "Petro", "Anna"};
    
    std::sort(names.begin(), names.end(), [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    });

    std::cout << "Task 2: ";
    for (const auto& name : names) std::cout << name << " ";
    std::cout << "\n";
}

struct TaxApplier {
    double rate;
    TaxApplier(double r) : rate(r) {}
    void operator()(double &price) const {
        price += price * rate;
    }
};

void task3() {
    std::deque<double> prices = {100.0, 250.5, 30.0, 500.0};
    std::for_each(prices.begin(), prices.end(), TaxApplier(0.20));

    std::cout << "Task 3: ";
    for (double p : prices) std::cout << p << " ";
    std::cout << "\n";
}

struct WithinRange {
    int min, max;
    WithinRange(int mn, int mx) : min(mn), max(mx) {}
    bool operator()(int n) const {
        return n >= min && n <= max;
    }
};

void task4() {
    std::set<int> numbers = {10, 25, 40, 55, 70, 85, 100};
    int count = std::count_if(numbers.begin(), numbers.end(), WithinRange(30, 80));
    std::cout << "Task 4: " << count << "\n";
}

void task5() {
    std::map<std::string, int> warehouse = {{"Apples", 150}, {"Oranges", 80}, {"Bananas", 200}, {"Milk", 50}};
    std::cout << "Task 5: ";
    std::for_each(warehouse.begin(), warehouse.end(), [](const std::pair<std::string, int>& item) {
        if (item.second > 100) std::cout << item.first << " ";
    });
    std::cout << "\n";
}

void task6() {
    std::vector<int> vec = {10, -5, 20, -30, 40, -1};
    std::replace_if(vec.begin(), vec.end(), [](int n) { return n < 0; }, 0);
    
    std::cout << "Task 6: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << "\n";
}

void task7() {
    std::vector<int> vec = {10, 20, 30, 40, 50};
    double sum = 0;
    
    std::for_each(vec.begin(), vec.end(), [&sum](int n) {
        sum += n;
    });

    double avg = vec.empty() ? 0 : sum / vec.size();
    std::cout << "Task 7: Sum = " << sum << ", Avg = " << avg << "\n";
}

void task8() {
    std::string text = "Hello STL World";
    std::string vowels = "aeiouAEIOU";
    
    int count = std::count_if(text.begin(), text.end(), [&](char c) {
        return vowels.find(c) != std::string::npos;
    });
    
    std::cout << "Task 8: " << count << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    return 0;
}
