#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int count=0, sum =0;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::for_each(numbers.begin(), numbers.end(), [&](int n) {
        sum += n;
        count++;
    });
    double average = static_cast<double>(sum) / count;

    std::cout << "The average is: " << average << std::endl;
    std::cout << "The count is: " << count << std::endl;
    std::cout << "The sum is: " << sum << std::endl;


    auto it1 = numbers.begin();
    using iter_i =  std::vector<int>::iterator;
    std::for_each(it1, numbers.end(), [&](const iter_i& it) {
        std::cout << *it << " ";
    });
    
    return 0;
}