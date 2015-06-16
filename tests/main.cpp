#include "../static_if.hpp"
#include <type_traits> 

template <int N>
struct s {
    static_assert(N < 100, "");
};
template <class T>
struct g {
    static_assert(!std::is_same<T, int>{}, "");
};

int main() {
    int V = 0;
    const int N = 20;
    STATIC_IF(N < 1) {
        g<LAZY_TYPE(int)> h;
        s<LAZY_VALUE(N)> y;
        y.mem();
        N;
        STATIC_IF(true) {
        } STATIC_ENDIF
    } STATIC_ELSEIF(false) {
        s<LAZY_VALUE(500)> y;
    } STATIC_ELSE {
        s<40> z;  
        g<LAZY_TYPE(std::integral_constant<short, 0>)> a;
    } STATIC_ENDIF
    return 0;
}
