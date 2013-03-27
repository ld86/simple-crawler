#include "crawler.h"

namespace shad_pdc { namespace crawler {
    crawler_t::crawler_t(const parameters_t& parameters) 
        : parameters_(parameters) {
            url_t start_url = url_t::start_url(parameters_.start_url);
            url_queue_.add_url(start_url);
        }

    void crawler_t::run() {
        std::vector<std::shared_ptr<std::thread>> threads;
        std::vector<std::shared_ptr<worker_t>> workers;

        const int concurrency_level = 2;

        for (int i = 0; i < concurrency_level; ++i) {
            workers.push_back(
                    std::shared_ptr<worker_t>(
                        new worker_t(url_queue_, page_queue_)));

            threads.push_back(
                    std::shared_ptr<std::thread>(
                        new std::thread(std::ref(*workers[i]))));
        }

        for (int i = 0; i < concurrency_level; ++i) {
            threads[i]->join();
        }

    }
}}
