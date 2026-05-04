#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <string>
#include <type_traits>

class Item {
public:
    int value;
    Item(int v = 0) : value(v) {}
    bool operator<=(const Item& other) const { return value <= other.value; }
    bool operator==(const Item& other) const { return value == other.value; }
    bool isEven() const { return value % 2 == 0; }
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "Item(" << item.value << ")";
    return os;
}

template <typename T, size_t N, size_t M>
std::array<T, N + M> mergeArrays(const std::array<T, N>& arr1, const std::array<T, M>& arr2) {
    std::array<T, N + M> result;
    auto it1 = arr1.begin();
    auto it2 = arr2.begin();
    auto itRes = result.begin();

    while (it1 != arr1.end() && it2 != arr2.end()) {
        if (*it1 <= *it2) {
            *itRes = *it1;
            ++it1;
        } else {
            *itRes = *it2;
            ++it2;
        }
        ++itRes;
    }

    while (it1 != arr1.end()) {
        *itRes = *it1;
        ++it1; ++itRes;
    }
    while (it2 != arr2.end()) {
        *itRes = *it2;
        ++it2; ++itRes;
    }

    return result;
}

template <typename T>
bool checkEven(const T& val) {
    if constexpr (std::is_same_v<T, Item>) {
        return val.isEven();
    } else {
        return val % 2 == 0;
    }
}

template <typename T>
void splitVector(const std::vector<T>& src, std::vector<T>& even, std::vector<T>& odd) {
    for (auto it = src.begin(); it != src.end(); ++it) {
        if (checkEven(*it)) {
            even.push_back(*it);
        } else {
            odd.push_back(*it);
        }
    }
}

template <typename T>
bool isPalindrome(const std::deque<T>& dq) {
    if (dq.empty()) return true;
    auto startIt = dq.begin();
    auto endIt = dq.end() - 1;
    while (startIt < endIt) {
        if (!(*startIt == *endIt)) {
            return false;
        }
        ++startIt;
        --endIt;
    }
    return true;
}

int main() {
    std::array<int, 3> a1 = {1, 3, 5};
    std::array<int, 3> a2 = {2, 4, 6};
    auto res1 = mergeArrays(a1, a2);
    for (int x : res1) std::cout << x << " ";
    std::cout << "\n";

    std::vector<Item> v = {Item(10), Item(15), Item(20), Item(25)};
    std::vector<Item> e, o;
    splitVector(v, e, o);
    for (const auto& i : e) std::cout << i << " ";
    std::cout << "| ";
    for (const auto& i : o) std::cout << i << " ";
    std::cout << "\n";

    std::deque<std::string> d = {"abc", "def", "abc"};
    std::cout << std::boolalpha << isPalindrome(d) << "\n";

    return 0;
}
