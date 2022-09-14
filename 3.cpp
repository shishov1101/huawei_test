#include <iostream>
#include <algorithm>
#include <vector>

#define SIZE 1000000

struct algorithm_x
{
private:
    std::vector<int> L;
    std::vector<int> R;
    std::vector<int> U;
    std::vector<int> D;
    std::vector<int> col;
    std::vector<int> row;
    std::vector<int> H;
    std::vector<int> S;
    int answer;
    int _n, _m, _len;

public:
    void init(int n,int m) {
        L.resize(SIZE);
        R.resize(SIZE);
        U.resize(SIZE);
        D.resize(SIZE);
        col.resize(SIZE);
        row.resize(SIZE);
        H.resize(SIZE);
        S.resize(SIZE);
        _n = n;
        _m = m;
        for(int i = 0; i <= _m; i++) {
            U[i] = i;
            D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
            S[i] = 0;
        }
        R[m] = 0;
        L[0] = _m;
        _len = _m;
        answer = -1;
        for(int i = 1; i <= n; i++) H[i] = -1;
    }

    int getAnswer() {
        return answer;
    }

    void link(int r,int j) {
        D[++_len] = D[j];
        U[D[j]] = _len;
        U[_len] = j;
        D[j] = _len;
        row[_len] = r;
        col[_len] = j;
        S[j]++;
        if(H[r] < 0) {
            H[r] = _len;
            R[_len] = _len;
            L[_len] =_len;
        }
        else {
            R[_len] = R[H[r]];
            L[R[H[r]]] = _len;
            L[_len] = H[r];
            R[H[r]] = _len;
        }
    }

    void remove(int c) {
        L[R[c]]=L[c];
        R[L[c]]=R[c];
        for(int i=D[c];i!=c;i=D[i]) {
            for(int j=R[i];j!=i;j=R[j]) {
                U[D[j]]=U[j];
                D[U[j]]=D[j];
                S[col[j]]--;
            }
        }
    }

    void resume(int r) {
        for(int i = U[r]; i != r; i = U[i]) {
            for(int j = L[i]; j != i; j = L[j]) {
                U[D[j]] = j;
                D[U[j]] = j;
                S[col[j]]++;
            }
        }
        L[R[r]] = r;
        R[L[r]] = r;
    }

    void dance(int d)
    {
        if(answer != -1 && d >= answer) return;
        if(R[0] == 0) {
            if(answer == -1) answer = d;
            else answer = std::min(answer, d);
            return;
        }
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i]) {
            if(S[i] < S[c]) c = i;
        }
        remove(c);
        for(int i = D[c]; i != c; i = D[i]) {
            for(int j = R[i]; j != i; j = R[j]) remove(col[j]);
            dance(d + 1);
            for(int j = L[i]; j != i; j = L[j]) resume(col[j]);
        }
        resume(c);
    }
}DLX;


int main() {
    int cases;
    int n;
    int m;
    int p;
    int x1, x2, y1, y2;
    std::cin >> cases;
    if(cases > 10 || cases < 1) return -1;
    for(int i = 0; i < cases; i++) {
        std::cin >> n >> m >> p;
        if(n < 1) return -2;
        if(m > 30) return -3;
        if(p > 100 || p < 1) return -4;
        DLX.init(p,n * m);
        for(int k = 1; k <= p; k++) {
            std::cin >> x1 >> y1 >> x2 >> y2;
            for(int q = x1; q < x2; q++) {
                for(int j = y1 + 1; j <= y2; j++) DLX.link(k, q * m + j);
            }
        }
        DLX.dance(0);
        std::cout << DLX.getAnswer() << std::endl;
    }
    return 0;
}