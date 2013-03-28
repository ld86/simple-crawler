#include "url_queue.h"

namespace shad_pdc { namespace crawler {
    url_queue_t::url_queue_t(const parameters_t& parameters) :
        parameters_(parameters) {
        }

    bool url_queue_t::add_url(std::shared_ptr<url_t> url) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (url->distance < parameters_.deep) {
            if (visited_pages_.find(url->url) == visited_pages_.end()) {
                visited_pages_.insert(url->url);
                url_queue_.put(url);
                return true;
            }        
        }
        return false;
    }

    std::shared_ptr<url_t> url_queue_t::next_url() {
        return url_queue_.take();
    }
}}
