#pragma once

#include <cstdio>

#include "parameters.h"
#include "crawler.h"

namespace shad_pdc { namespace crawler {
    class runner_t {
        bool is_right_parameters(int argc, char** argv);
        int show_usage(char** argv);

        public:
        int run(int argc, char** argv);
    };
}}
