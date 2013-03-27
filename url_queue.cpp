#include "url_queue.h"

namespace shad_pdc { namespace crawler {
    void url_queue_t::add_url(std::shared_ptr<url_t> url) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (visited_pages_.find(url) == visited_pages_.end()) {
            visited_pages_.insert(url);
            url_queue_.put(url);
        }        
    }

    std::shared_ptr<url_t> url_queue_t::next_url() {
        return url_queue_.take();
    }
}}
