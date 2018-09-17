#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

int arraySize = 1000;
int K = 128;

void mkm_method(long alpha0, long beta, std::vector<double> &a, int size) {
    long M = 2147483648;

    for (int i = 0; i < size; ++i) {
        a[i] = beta * alpha0 - M * (int) ((beta * alpha0) / M);

        alpha0 = a[i];

        a[i] /= M;
    }
}

void maklaren_marsale(int K, std::vector<double> &a) {
    std::vector<double> b(arraySize + K, 0);
    std::vector<double> c(arraySize + K, 0);
    mkm_method(29791, 29791, b, arraySize + K);
    mkm_method(32771, 32771, c, arraySize + K);

    std::vector<double> V(b);
    V.resize(K);

    for (int i = 0; i < arraySize; ++i) {
        double s = int(c[i] * K);
        a[i] = V[s];
        V[s] = b[i + K];
    }
}

void hi_square(std::vector<double> &a) {
    std::vector<int> counter;
    for (int i = 0; i < 10; ++i) {
        counter.push_back(std::count_if(a.begin(), a.end(), [&i](double val) {
            return (val < i * 0.1 + 0.1 && val > i * 0.1);
        }));
    }

    double hi = 0;

    for (auto item : counter) {
        hi += std::pow(item - arraySize * 0.1, 2) / (arraySize * 0.1);
    }

    std::cout << "hi: " << hi << std::endl;
}


void find_max_difference(std::vector<double> &a)
{
    double max  = 0;
    double Dn = 0;

    for (int i = 0; i < arraySize; ++i)
    {
        Dn = std::abs(a[i] - i*0.001);
        if (Dn > max)
        {
            max = Dn;
        }
    }

    std::cout << "Dn*sqrt(n):" <<std::sqrt(1000)*max << std::endl;
}

void Kolmogorov(std::vector<double> &a)
{
    std::sort(a.begin(), a.end());

    find_max_difference(a);
}

int main() {
    std::vector<double> a(arraySize, 0);
    std::vector<double> b(arraySize, 0);

   // mkm_method(29791, 29791, a, arraySize);
    mkm_method(29791, 29791, b, arraySize);

    maklaren_marsale(128, a);

    hi_square(a);
    hi_square(b);

    Kolmogorov(a);
    Kolmogorov(b);



    return 0;
}