#include "crawler.h"

namespace shad_pdc { namespace crawler {
    crawler_t::crawler_t(const parameters_t& parameters) : 
        url_queue_(parameters),
        parameters_(parameters) {
            auto start_url = url_t::start_url(parameters_.start_url);
            url_queue_.add_url(start_url);
        }

    void crawler_t::run() {
        std::vector<std::shared_ptr<std::thread>> download_threads;
        std::vector<std::shared_ptr<worker_t>> download_workers;

        std::vector<std::shared_ptr<std::thread>> save_threads;
        std::vector<std::shared_ptr<save_worker_t>> save_workers;

        const int download_concurrency_level = 2;
        const int save_concurrency_level = 1;

        for (int i = 0; i < download_concurrency_level; ++i) {
            download_workers.push_back(
                    std::shared_ptr<worker_t>(
                        new worker_t(i, url_queue_, page_queue_)));

            download_threads.push_back(
                    std::shared_ptr<std::thread>(
                        new std::thread(std::ref(*download_workers[i]))));
        }

        for (int i = 0; i < save_concurrency_level; ++i) {
            save_workers.push_back(
                    std::shared_ptr<save_worker_t>(
                        new save_worker_t(i, page_queue_, parameters_)));

            save_threads.push_back(
                    std::shared_ptr<std::thread>(
                        new std::thread(std::ref(*save_workers[i]))));
        }
        
        for (int i = 0; i < download_concurrency_level; ++i) {
            download_threads[i]->join();
        }

        for (int i = 0; i < save_concurrency_level; ++i) {
            save_threads[i]->join();
        }
    }
}}
