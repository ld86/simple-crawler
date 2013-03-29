#pragma once

#include <memory>

#include "url_queue.h"
#include "queue.h"
#include "page.h"

namespace shad_pdc { namespace crawler {
    class worker_t {
        url_queue_t& url_queue_;
        queue_t<std::shared_ptr<page_t>>& save_queue_;
        queue_t<std::shared_ptr<page_t>>& parse_queue_;
        const uint32_t id_;

        public:
        worker_t(uint32_t id, url_queue_t& url_queue,
                queue_t<std::shared_ptr<page_t>>& save_queue,
                queue_t<std::shared_ptr<page_t>>& parse_queue);
        void operator()();
    };
}}
