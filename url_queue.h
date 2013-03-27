#pragma once

#include <set>
#include <mutex>
#include <memory>

#include "url.h"
#include "queue.h"

namespace shad_pdc { namespace crawler {
    class url_queue_t {
        std::mutex mutex_;
        std::set<std::shared_ptr<url_t>> visited_pages_;
        queue_t<std::shared_ptr<url_t>> url_queue_;

        public:
        void add_url(std::shared_ptr<url_t> url);
        std::shared_ptr<url_t> next_url();
    };
}}
