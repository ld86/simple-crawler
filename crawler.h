#pragma once 

#include <memory>
#include <thread>
#include <atomic>

#include "queue.h"
#include "url_queue.h"
#include "page.h"
#include "parameters.h"
#include "worker.h"
#include "save_worker.h"
#include "parse_worker.h"

namespace shad_pdc { namespace crawler {
    class crawler_t {
        queue_t<std::shared_ptr<page_t>> save_queue_;
        queue_t<std::shared_ptr<page_t>> parse_queue_;
        url_queue_t url_queue_;

        parameters_t parameters_;

        public:
        crawler_t(const parameters_t& parameters);
        void run();
    };
}}
