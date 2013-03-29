#include "crawler.h"

namespace shad_pdc { namespace crawler {
    crawler_t::crawler_t(const parameters_t& parameters) :
        url_queue_(parameters),
        parameters_(parameters),
        saved_pages(0) {
            auto start_url = url_t::start_url(parameters_.start_url);
            url_queue_.add_url(start_url);
        }

    void crawler_t::run_download_workers() {
        const uint32_t download_concurrency = parameters_.download_concurrency;
        for (uint32_t i = 0; i < download_concurrency; ++i) {
            download_workers.push_back(
                    std::shared_ptr<download_worker_t>(
                        new download_worker_t(i,
                            url_queue_,
                            save_queue_,
                            parse_queue_)));

            download_threads.push_back(
                    std::shared_ptr<std::thread>(
                        new std::thread(std::ref(*download_workers[i]))));
        }


    }
    
    void crawler_t::run_parse_workers() {
        const uint32_t parse_concurrency = parameters_.parse_concurrency;
        for (uint32_t i = 0; i < parse_concurrency; ++i) {
            parse_workers.push_back(
                    std::shared_ptr<parse_worker_t>(
                        new parse_worker_t(i, url_queue_, parse_queue_)));

            parse_threads.push_back(
                    std::shared_ptr<std::thread>(
                        new std::thread(std::ref(*parse_workers[i]))));
        }


    }
    
    void crawler_t::run_save_workers() {
        const uint32_t save_concurrency = parameters_.save_concurrency;
        for (uint32_t i = 0; i < save_concurrency; ++i) {
            save_workers.push_back(
                    std::shared_ptr<save_worker_t>(
                        new save_worker_t(i,
                            save_queue_,
                            parameters_,
                            saved_pages,
                            url_queue_)));

            save_threads.push_back(
                    std::shared_ptr<std::thread>(
                        new std::thread(std::ref(*save_workers[i]))));
        }
        

    }

    void crawler_t::run() {
        run_download_workers();
        run_parse_workers();
        run_save_workers();

        

        for (uint32_t i = 0; i < download_threads.size(); ++i) {
            download_threads[i]->join();
        }

        for (uint32_t i = 0; i < parse_threads.size(); ++i) {
            parse_queue_.put(std::shared_ptr<page_t>());
        }

        for (uint32_t i = 0; i < save_threads.size(); ++i) {
            save_queue_.put(std::shared_ptr<page_t>());
        }

        for (uint32_t i = 0; i < parse_threads.size(); ++i) {
            parse_threads[i]->join();
        }

        for (uint32_t i = 0; i < save_threads.size(); ++i) {
            save_threads[i]->join();
        }        

    }
}}
