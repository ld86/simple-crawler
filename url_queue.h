#pragma once

#include <set>
#include <mutex>
#include <memory>
#include <atomic>

#include "queue.h"
#include "page.h"
#include "parameters.h"

namespace shad_pdc { namespace crawler {
    class url_queue_t {
        std::mutex mutex_;
        std::set<std::string> visited_pages_;
        queue_t<std::shared_ptr<url_t>> url_queue_;
        parameters_t parameters_;

        public:
        url_queue_t(const parameters_t& parameters);
        bool add_url(std::shared_ptr<url_t> url);
        std::shared_ptr<url_t> next_url();
        bool is_empty() const;
    };
}}
