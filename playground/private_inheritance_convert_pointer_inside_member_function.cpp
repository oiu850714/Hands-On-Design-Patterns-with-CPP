#include <vector>

class Container : private std::vector<int> {
public:
    using std::vector<int>::size;

    void convert(const Container& C) {
        const std::vector<int> &V = C; // mind=blown works
    }
};

int main() {
    Container C;
    C.convert(Container{});

    const std::vector<int> &V = C; // GG
}
