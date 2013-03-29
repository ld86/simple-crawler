#pragma once

#include <memory>
#include <atomic>
#include <fstream>

#include "queue.h"
#include "page.h"
#include "parameters.h"

namespace shad_pdc { namespace crawler {
    class save_worker_t {
        queue_t<std::shared_ptr<page_t>>& page_queue_;
        const uint32_t id_;
        parameters_t parameters_;
        std::atomic_size_t& saved_pages_count_;

        public:
        save_worker_t(uint32_t id,
                queue_t<std::shared_ptr<page_t>>& page_queue,
                const parameters_t& parameters,
                std::atomic_size_t& saved_pages_count);
        void operator()();

    };
}}
