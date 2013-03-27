#include "parameters.h"

namespace shad_pdc { namespace crawler {

    parameters_t::parameters_t(int argc, char** argv) :
        start_url(argv[1]),
        deep(atoi(argv[2])),
        max_page_count(atoi(argv[3])),
        save_path(argv[4]) {
        }


}}

