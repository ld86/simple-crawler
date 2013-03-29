#include "url.h"

namespace shad_pdc { namespace crawler {
    url_t::url_t(const std::string& url, uint32_t distance) : 
        url(url),
        distance(distance) {
        }


    std::shared_ptr<url_t> url_t::start_url(const std::string& url) {
        return std::shared_ptr<url_t>(new url_t(url, 0));
    }

    std::shared_ptr<url_t> url_t::make_child(const std::string& href_url) {
        std::string child_url = href_url;
        if ( href_url.find("/") == 0) {
            if (url[url.size() - 1] == '/')
            {
                child_url = url + href_url.substr(1);
            } else {
                child_url = url + href_url;
            }
        }
        return std::shared_ptr<url_t>(new url_t(child_url, distance + 1));
    }
}}
