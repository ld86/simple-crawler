#include "worker.h"

namespace shad_pdc { namespace crawler {
    worker_t::worker_t(url_queue_t& url_queue,
            queue_t<page_t>& page_queue)
        : url_queue_(url_queue),
        page_queue_(page_queue) {
        }

    void worker_t::operator()() {
        for (;;) {
            url_t next_url = url_queue_.next_url();
            page_t page = next_url.get_page();
            /*
            std::string content = wget_string(next_url.url);

            std::printf("%s\n", next_url.url.c_str());

            boost::regex re("href=['\"](.+?)['\"]");

            boost::sregex_iterator begin(content.begin(), 
                    content.end(), 
                    re);
            boost::sregex_iterator end;

            for (auto it = begin; it != end; ++it) {
                std::string href_url = (*it)[1].str();
                if (url_t::is_url(href_url)) {
                    url_t child = url.make_child(href_url);
                    std::printf("new: %s\n", child.url.c_str());
                }
            }
            */
        }
    }
}}

