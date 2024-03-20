#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>


void generate_array(std::vector<int>& arr, std::mt19937& gen) {
    std::uniform_int_distribution<> dis(0, 99);

    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = dis(gen);
    }
}

class int_table{
public:
    std::vector<int> m_vec;
    std::size_t w;
    std::size_t h;
    int_table(std::size_t w,std::size_t h):m_vec(h*w,0),h{h},w{w}{}
    int&elem_at(std::size_t x,std::size_t y){
        #if 1
        return m_vec[y+x*h];
        #else
        return m_vec[x+y*w];
        #endif
    }

};

int lcs(const std::vector<int>& a, const std::vector<int>& b) {
    int m = a.size();
    int n = b.size();
    int_table dp((m + 1), ( n + 1));

    for (int i = 1; i <= m; ++i) {
        for  (int j = 1; j <= n; ++j){
            if (a[i - 1] == b[j - 1]) {
                dp.elem_at(i,j) = dp.elem_at(i - 1 , j - 1) + 1;
            } else {
                dp.elem_at(i,j) = std::max(dp.elem_at((i - 1), j), dp.elem_at(i, j - 1));
            }
        }
    }
    return dp.elem_at(m,n);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " n n_rep" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    int n_rep = std::atoi(argv[2]);

    int seed = 12345;
    std::mt19937 gen(seed);
    std::vector<int> a(n);
    std::vector<int> b(n);

    double duration = 0;
    for (int i = 0; i < n_rep; ++i) {
        generate_array(a, gen);
        generate_array(b, gen);

        auto start = std::chrono::high_resolution_clock::now();
        int length = lcs(a, b);
        auto end = std::chrono::high_resolution_clock::now();
        duration += std::chrono::duration<double>(end - start).count();
    }

    std::cout << "Time using native C++: " << duration << "s (n_rep=" << n_rep << ")" << std::endl;

    return 0;
}