#include "runner.h"

int main(int argc, char** argv) {
    using shad_pdc::crawler::runner_t;

    runner_t runner;
    return runner.run(argc, argv);
}
