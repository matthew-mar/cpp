#include <vector>
#include <iostream>

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void simplifyFraction(std::pair<int, int>& fraction) {
    int div = gcd(fraction.first, fraction.second);
    fraction.first /= div;
    fraction.second /= div;
}

void sortFractions(std::vector<std::pair<int, int>>& fractions) {
    for (int pos = 0; pos < fractions.size() - 1; pos++) {
        for (int i = pos + 1; i < fractions.size(); i++) {
            simplifyFraction(fractions[i]);
            simplifyFraction(fractions[pos]);

            float v1 = (float)fractions[i].first / fractions[i].second;
            float v2 = (float)fractions[pos].first / fractions[pos].second;

            if (v1 < v2) {
                std::swap(fractions[i], fractions[pos]);
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    int q;
    std::cin >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    std::vector<int> c(q);
    for (int i = 0; i < q; i++) {
        std::cin >> c[i];
    }

    std::vector<std::pair<int, int>> fractions;
    for (int i : a) {
        for (int j : b) {
            fractions.push_back(std::make_pair(i, j));
        }
    }

    sortFractions(fractions);

    for (int cj : c) {
        std::cout << fractions[cj - 1].first << " " << fractions[cj - 1].second << std::endl;
    }

    return 0;
}
