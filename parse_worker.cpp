#include "parse_worker.h"

namespace shad_pdc { namespace crawler {
    parse_worker_t::parse_worker_t(uint32_t id,
            url_queue_t& url_queue,
            queue_t<std::shared_ptr<page_t>>& page_queue)
        : url_queue_(url_queue),
        page_queue_(page_queue),
        id_(id) {
        }

    void parse_worker_t::operator()() {
        for (;;) {
            auto page = page_queue_.take();
            if (!page) {
                break;
            }

            uint32_t links_count = 0;
            for (auto url : page->get_links()) {
                if(url_queue_.add_url(url)) {
                    links_count++;
                }
            }
            std::printf("[P%d] %d\n", id_, links_count);
        }
        std::printf("[P%d] exit\n", id_);
    }
}}
