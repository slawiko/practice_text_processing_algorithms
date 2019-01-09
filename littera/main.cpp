#include <iostream>
#include <fstream>
#include <vector>

unsigned int min(unsigned int a, unsigned int b) {
    return a <= b ? a : b;
}

void z_function(unsigned int* z, std::string &s) {
    int n = (int) s.length();
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}

void prefix_function(unsigned int* pi, std::string s) {
    int n = (int) s.length();
    for (int i = 1; i < n; ++i) {
        unsigned int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
}

bool is_char(const char &c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

std::string calculate_diff(const std::string &s1, const std::string &s2, int n) {
    char diff = 0;
    int skipped = 0;
    char* result = new char[n];
    int result_size = 0;
    for (int i = 0; i < n; i++) {
        if (!is_char(s2[i])) {
            skipped++;
            continue;
        }
        diff = s2[i] - s1[i];
        if (diff <= 0) {
            diff += 26;
        }

        result[result_size] = diff + 'a' - 1;
        result_size++;
    }

    return std::string(result, result_size);
}

std::string min_cyclic_shift(std::string s) {
    s += s;
    int n = (int) s.length();
    int i = 0, ans = 0;
    while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) {
                k = i;
            } else {
                ++k;
            }
            ++j;
        }
        while (i <= k) {
            i += j - k;
        }
    }

    return s.substr(ans, n / 2);
}

void readlines(int n, std::string &s, std::ifstream &in) {
    int read = 0;
    std::string buffer;

    while (n - read > 0) {
        std::getline(in, buffer);
        s += buffer;
        read += buffer.length();
    }
}

void print(unsigned int* v, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << ' ';
    }
}

int period_size(unsigned int* pi, int n) {
    int last = n - 1;
    int size = n;

    while (size > 0) {
        if (size % (size - pi[last]) == 0) {
            return size - pi[last];
        }

        last--;
        size--;
    }

    return n;
}

int period_size_2(unsigned int* z, int n) {
    for (int i = 0; i < n; ++i) {
        if (i + z[i] == n) {
            return i;
        }
    }

    return n;
}

int main() {
    std::ifstream in("littera.in");
    std::ofstream out("littera.out");

    int n;
    in >> n;

    std::string s1, s2;

    readlines(n, s1, in);
    readlines(n, s2, in);
    in.close();

    std::string diff = calculate_diff(s1, s2, n);
    int diff_size = (int) diff.length();

//    unsigned int* pi = new unsigned int[diff_size];
    unsigned int* z = new unsigned int[diff_size];
    for (int i = 0; i < diff_size; ++i) {
//        pi[i] = 0;
        z[i] = 0;
    }
//    prefix_function(pi, diff);
    z_function(z, diff);

//    int period = period_size(pi, diff_size);
    int period = period_size_2(z, diff_size);
    out << min_cyclic_shift(diff.substr(0, period));

    out.close();

    return 0;
}