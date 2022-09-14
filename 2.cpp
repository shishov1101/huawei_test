#include <iostream>
#include <set>
#include <vector>

int main(){
    std::set<int> sums;
    std::vector<int> vect;
    int n,m;
    int cases = 0;
    int input;

    for(;;) {
        std::cin >> n >> m;
        if(n==0 && m==0) break;
        for(int i = 0; i < n; i++) {
            std::cin >> input;
            if(input <= m) {
                sums.insert(input);
            }
        }

        for(auto i : sums) {
            if(i + i + i + i <= m) vect.push_back(i + i + i + i);
            else if(i + i + i <= m) vect.push_back(i + i + i);
            else if(i + i <= m) vect.push_back(i + i);
            for(auto b : sums) {
                if(i + b + b + b <= m) vect.push_back(i + b + b + b);
                if(i + i + b + b <= m) vect.push_back(i + i + b + b);
                if(i + i + i + b <= m) vect.push_back(i + i + i + b);
            }
        }
        for (const int &i : vect) {
            sums.insert(i);
        }
        cases++;
        std::cout << "Case " << cases <<": " << *(sums.rbegin()) << std::endl;
        std::cout << std::endl;
        sums.clear();
        vect.clear();
    }
    return 0;
}