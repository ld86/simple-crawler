#pragma once

#include <memory>
#include <atomic>

#include "url_queue.h"
#include "queue.h"
#include "page.h"

namespace shad_pdc { namespace crawler {
    class parse_worker_t {
        url_queue_t& url_queue_;
        queue_t<std::shared_ptr<page_t>>& page_queue_;
        const uint32_t id_;
            
        public:
        parse_worker_t(uint32_t id, url_queue_t& url_queue,
                queue_t<std::shared_ptr<page_t>>& page_queue);
        void operator()();
    };
}}
