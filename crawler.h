#pragma once 

#include <memory>
#include <thread>

#include "queue.h"
#include "url_queue.h"
#include "page.h"
#include "parameters.h"
#include "worker.h"

namespace shad_pdc { namespace crawler {
    class crawler_t {
        queue_t<page_t> page_queue_;
        url_queue_t url_queue_;

        parameters_t parameters_;

        public:
        crawler_t(const parameters_t& parameters);
        void run();
    };
}}
