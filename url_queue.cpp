#include "url_queue.h"

namespace shad_pdc { namespace crawler {
    url_queue_t::url_queue_t(const parameters_t& parameters) :
        parameters_(parameters),
        found_deep_urls_(false),
        stop_(false) {
        }

    bool url_queue_t::add_url(std::shared_ptr<url_t> url) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (!stop_.load()) {
            if (url->distance < parameters_.deep) {
                if (visited_pages_.find(url->url) == visited_pages_.end()) {

                    visited_pages_.insert(url->url);
                    url_queue_.put(url);
                    return true;
                }        
            } else {
                if (!found_deep_urls_) {
                    found_deep_urls_ = true;

                    for (size_t i = 0; i < parameters_.download_concurrency; ++i) {
                        url_queue_.put(std::shared_ptr<url_t>());
                    }
                }
            }
        }
        return false;
    }

    std::shared_ptr<url_t> url_queue_t::next_url() {
        if (stop_.load()) {
            return std::shared_ptr<url_t>();
        }
        return url_queue_.take();
    }

    bool url_queue_t::is_empty() const {
        return url_queue_.is_empty();
    }

    void url_queue_t::stop() {
        std::lock_guard<std::mutex> lock(mutex_);        

        if (!stop_.load()) {
            stop_.store(true); 
        }
    }
}}
