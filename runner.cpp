#include "runner.h"

namespace shad_pdc { namespace crawler {
    bool runner_t::is_right_parameters(int argc, char** argv) {
        if (argc < 5) {
            return false;
        }

        return true;
    }

    int runner_t::show_usage(char** argv) {
        std::printf("%s "
                    "<start url> "
                    "<max deep> "
                    "<max saved page> "
                    "<download directory> "
                    "[download concurrency] "
                    "[save concurrency] "
                    "[parse concurrency]\n", argv[0]);
        return -1;
    }

    int runner_t::run(int argc, char** argv) {
        if (!is_right_parameters(argc, argv)) {
            return show_usage(argv);
        }

        parameters_t parameters(argc, argv);
        crawler_t crawler(parameters);
        crawler.run();

        return 0;
    }
}}
