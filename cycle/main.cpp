#include <iostream>
#include <fstream>
#include <vector>

void print(std::vector<unsigned int> z, int n) {
    for (int i = 0; i < n ; i++) {
        std::cout << z[i];
    }

    std::cout << '\n';
}

unsigned int min(unsigned int a, unsigned int b) {
    return a <= b ? a : b;
}

void minimize(std::vector<unsigned int> v, int n) {
    for (int i = 0; i < n; ++i) {
        v[i] = v[i] <= i ? v[i] : i;
    }
}

unsigned int max_border(std::vector<unsigned int> v, int n) {
    unsigned int max_border = 0;
    for (unsigned int i = n; i > n; i--) {
        if (n - i + 1 == v[i - 1] && v[i - 1] > max_border) {
            max_border = v[i - 1];
        }
    }
    return max_border;
}

std::vector<unsigned int> z_function(std::string &s, int n) {
    std::vector<unsigned int> z(n);
    for (unsigned int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    minimize(z, n);

    return z;
}

int cycle(const std::string &s1, const std::string &s2, int n) {
    std::string ST = s1 + s2;
    std::string TS = s2 + s1;
    int N = n * 2;

    std::vector<unsigned int> z1 = z_function(ST, N);
    std::vector<unsigned int> z2 = z_function(TS, N);

//    print(z1, N);
//    print(z2, N);

    unsigned int max_border1 = max_border(z1, N);
    unsigned int max_border2 = max_border(z2, N);
    if (max_border1 + max_border2 >= n) {
        if (max_border1 > n || max_border2 > n) {
            return -1;
        }
        return min(max_border1, max_border2);
    }

    if (n == max_border1 && max_border1 == max_border2) {
        return 0;
    }

    return -1;
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    unsigned int n;
    in >> n;
    std::string s1, s2;
    std::getline(in, s1);
    std::getline(in, s1);
    std::getline(in, s2);
    in.close();

    if (s1 == s2) {
        out << 0;
        out.close();
        return 0;
    }

    out << cycle(s1, s2, n);
    out.close();
    return 0;
}