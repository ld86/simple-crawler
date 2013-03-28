#include "save_worker.h"

namespace shad_pdc { namespace crawler {
    save_worker_t::save_worker_t(uint32_t id,
            queue_t<std::shared_ptr<page_t>>& page_queue,
            const parameters_t& parameters) :
        page_queue_(page_queue), 
        id_(id),
        parameters_(parameters) {
        }

    void save_worker_t::operator()() {
        for (;;) {
            auto page = page_queue_.take();

            // std::printf("[S%d] %lu\n", id_, page->content()->size());
            
            std::string save_path = page->url()->url;
            for (size_t i = 0; i < save_path.size(); ++i) {
                if (save_path[i] == '/') {
                    save_path[i] = '$';
                }
            }

            save_path = parameters_.save_path + "/" + save_path;
            std::ofstream output(save_path);
            output << *page->content();
        }
    }
}}

