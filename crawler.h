#pragma once 

#include <memory>
#include <thread>
#include <atomic>

#include "queue.h"
#include "url_queue.h"
#include "page.h"
#include "parameters.h"
#include "download_worker.h"
#include "save_worker.h"
#include "parse_worker.h"

namespace shad_pdc { namespace crawler {
    class crawler_t {
        queue_t<std::shared_ptr<page_t>> save_queue_;
        queue_t<std::shared_ptr<page_t>> parse_queue_;
        url_queue_t url_queue_;
        parameters_t parameters_;
        std::vector<std::shared_ptr<std::thread>> download_threads;
        std::vector<std::shared_ptr<download_worker_t>> download_workers;
        std::vector<std::shared_ptr<std::thread>> save_threads;
        std::vector<std::shared_ptr<save_worker_t>> save_workers;
        std::vector<std::shared_ptr<std::thread>> parse_threads;
        std::vector<std::shared_ptr<parse_worker_t>> parse_workers;
        std::atomic_size_t saved_pages;
    
        void run_download_workers();
        void run_parse_workers();
        void run_save_workers();
        public:
        crawler_t(const parameters_t& parameters);
        void run();
    };
}}
