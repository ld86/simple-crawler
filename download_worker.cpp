#include "download_worker.h"

namespace shad_pdc { namespace crawler {
    download_worker_t::download_worker_t(uint32_t id,
            url_queue_t& url_queue,
            queue_t<std::shared_ptr<page_t>>& save_queue,
            queue_t<std::shared_ptr<page_t>>& parse_queue)
        : url_queue_(url_queue),
        save_queue_(save_queue),
        parse_queue_(parse_queue),
        id_(id) {
        }

    void download_worker_t::operator()() {
        for (;;) {
            auto next_url = url_queue_.next_url();

            if (!next_url) {
                break;
            }

            std::printf("[D%d] > %d %s\n", id_, 
                    next_url->distance, 
                    next_url->url.c_str());

            auto page = get_page(next_url);

            std::printf("[D%d] < %d %s\n", id_, 
                    next_url->distance, 
                    next_url->url.c_str());

            save_queue_.put(page);
            parse_queue_.put(page);
        }
        std::printf("[D%d] exit\n", id_);
    }
}}

