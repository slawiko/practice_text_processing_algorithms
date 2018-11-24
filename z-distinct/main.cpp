#include <iostream>
#include <fstream>
#include <vector>

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(std::vector<int> &v) {
    int max = 0;
    for (int i = 0; i < v.size(); ++i) {
        max = v[i] > max ? v[i] : max;
    }
    return max;
}

int max_z_function(std::string &s) {
    int n = (int) s.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return max(z);
}

void print_vector_int(std::vector<int> &v) {
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i];
    }
}

int calculate_distinct_cnt(std::string s) {
    if (s.length() == 0) {
        return 0;
    }
    int cnt = 0;

    cnt = (int)s.length() - max_z_function(s) + calculate_distinct_cnt(s.substr(1));
    return cnt;
}


int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::string s;
    std::getline(in, s);
    in.close();

    out << calculate_distinct_cnt(s);
    out.close();


    return 0;
}