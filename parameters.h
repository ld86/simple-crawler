#pragma once

#include <string>

namespace shad_pdc { namespace crawler {

    class parameters_t {
        public:
            const std::string start_url;
            const int deep;
            const int max_page_count;
            const std::string save_path;

            parameters_t(int argc, char** argv);
    };

}}
