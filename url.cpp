#include "url.h"

namespace shad_pdc { namespace crawler {
    url_t::url_t(const std::string& url, uint32_t distance) :
        url(url),
        distance(distance) {
        }

    std::shared_ptr<url_t> url_t::start_url(const std::string& url) {
        return std::shared_ptr<url_t>(new url_t(url, 0));
    }

    std::shared_ptr<page_t> url_t::get_page() {
        std::shared_ptr<std::string> content = wget_string(url);
        return std::shared_ptr<page_t>(
                new page_t(std::shared_ptr<url_t>(this), content));
    }

    bool url_t::operator<(const url_t& rhs) const {
        return url < rhs.url;
    }
}}
