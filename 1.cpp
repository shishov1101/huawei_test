#include <iostream>
#include <vector>
#include <string>

std::string reverse(std::string const &s)
{
    std::string rev;

    std::string::const_reverse_iterator it = s.crbegin();
    while (it != s.crend()) {
        rev = rev.append(1, *(it++));
    };

    return rev;
}

void cinValues(std::string *s_a, std::string *s_b, int n) {
    for (int i = 0; i < n; ++i) {
        std::cin >> s_a[i] >> s_b[i];

        s_a[i] = reverse(s_a[i]);
        s_b[i] = reverse(s_b[i]);
    }
}

void coutValues(std::string *s_a, std::string *s_b, std::vector<int> *sum, int n) {
    int euclidean = 0;
    size_t size_a;
    size_t size_b;
    size_t min_size;
    size_t current_id = 0;
    for (int i = 0; i < n; ++i) {
        size_a = s_a[i].size();
        size_b = s_b[i].size();
        min_size = std::min(size_a, size_b);
        for (int j = 0; j < min_size; ++j) {
            euclidean = euclidean +((int)(s_a[i].at(j)) - 48) + ((int)(s_b[i].at(j)) - 48);
            sum[i].push_back(euclidean % 10);
            euclidean /= 10;
            current_id = j;
        }
        current_id++;
        if(size_a > min_size) {
            for (int j = current_id; j < size_a; ++j) {
                euclidean = euclidean + ((int)(s_a[i].at(j)) - 48);
                sum[i].push_back(euclidean % 10);
                euclidean /= 10;
            }
            if (euclidean % 10 > 0) sum[i].push_back(euclidean % 10);
        }
        else if(size_b >  min_size) {
            for (int j = current_id; j < size_b; ++j) {
                euclidean = euclidean + ((int)(s_b[i].at(j)) - 48);
                sum[i].push_back(euclidean % 10);
                euclidean /= 10;
            }
            if (euclidean % 10 > 0) sum[i].push_back(euclidean % 10);
        }
        else {
            if (euclidean % 10 > 0) sum[i].push_back(euclidean % 10);
        }
        current_id = 0;
        euclidean = 0;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << "Case " << i + 1 << ":" << std::endl;
        std::cout << reverse(s_a[i]);
        std::cout << " + ";
        std::cout << reverse(s_b[i]);
        std::cout << " = ";
        for (auto it = sum[i].crbegin(); it != sum[i].crend(); it++) {
            std::cout << *it;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}


int main() {
    unsigned int n = 0;
    std::cin >> n;
    if(n <= 0 || n > 20) return -1;
    std::string a[n];
    std::string b[n];
    std::vector<int> sum[n];
    cinValues(a, b, n);
    coutValues(a, b, sum, n);
    return 0;
}