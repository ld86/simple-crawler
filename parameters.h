#pragma once

#include <string>

namespace shad_pdc { namespace crawler {

    class parameters_t {
        public:
            const std::string start_url;
            const uint32_t deep;
            const uint32_t max_page_count;
            const std::string save_path;

            parameters_t(int argc, char** argv);
    };

}}
