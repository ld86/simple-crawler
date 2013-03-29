#include "page.h"

namespace shad_pdc { namespace crawler {
    page_t::page_t(std::shared_ptr<url_t> url, 
            std::shared_ptr<std::string> content) :
        url_(url),
        content_(content),
        link_re_("href=['\"](.+?)['\"]"){
        }

    bool is_url(const std::string& url) {
        if (url.find("http") == 0 ||
            url.find("/") == 0) {
            return true;
        }
        return false;
    }

    std::vector<std::shared_ptr<url_t>> page_t::get_links() {
        boost::sregex_iterator begin(content_->begin(),
                content_->end(), 
                link_re_);

        boost::sregex_iterator end;
        std::vector<std::shared_ptr<url_t>> links;

        for (auto it = begin; it != end; ++it) {
            std::string href_url = (*it)[1].str();
            if (is_url(href_url)) {
                links.push_back(url_->make_child(href_url));
            }
        }

        return links;
    }

    std::shared_ptr<std::string> page_t::content() const {
        return content_;
    }

    std::shared_ptr<url_t> page_t::url() const {
        return url_;
    }
}}

