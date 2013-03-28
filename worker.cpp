#include "worker.h"

namespace shad_pdc { namespace crawler {
    worker_t::worker_t(uint32_t id,
            url_queue_t& url_queue,
            queue_t<std::shared_ptr<page_t>>& page_queue)
        : url_queue_(url_queue),
        page_queue_(page_queue),
        id_(id) {
        }

    void worker_t::operator()() {
        for (;;) {
            auto next_url = url_queue_.next_url();
            std::printf("[%d] %d %s\n", id_, 
                    next_url->distance, 
                    next_url->url.c_str());

            auto page = get_page(next_url);
            uint32_t links_count = 0;
            for (auto url : page->get_links()) {
                if(url_queue_.add_url(url)) {
                    links_count++;
                }
            }
            std::printf("[%d] add %d links\n", id_, links_count);
            page_queue_.put(page);
        }
    }
}}

