#include "parameters.h"

namespace shad_pdc { namespace crawler {

    parameters_t::parameters_t(int argc, char** argv) :
        start_url(argv[1]),
        deep(atoi(argv[2])),
        max_page_count(atoi(argv[3])),
        save_path(argv[4]),
        download_concurrency(8), 
        save_concurrency(2), 
        parse_concurrency(2) {
            if (argc >= 6) {
                download_concurrency = atoi(argv[5]);
            }
            if (argc >= 7) {
                save_concurrency = atoi(argv[6]);
            }
            if (argc >= 8) {
                parse_concurrency = atoi(argv[7]);
            }
        }


}}

