#include "library.hpp"

int main() {
    LibraryManager mgr;
    mgr.init_sample();
    mgr.run_cli();
    return 0;
}
