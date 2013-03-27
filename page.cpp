#include "page.h"

namespace shad_pdc { namespace crawler {
    page_t::page_t(std::shared_ptr<url_t> url,
            std::shared_ptr<std::string> content) : 
        link_re_("href=['\"](.+?)['\"]"),
        content_(content),
        url_(url) {
        }

    bool is_url(const std::string& url) {
        if (url.find("/") == 0) {
            return true;
        }

        if (url.find("http://") == 0) {
            return true;
        }

        return false;
    }

    std::shared_ptr<url_t> page_t::make_child(const std::string& child_url) {
        if (child_url.find("/") == 0) {
            return std::shared_ptr<url_t>(
                    new url_t(url_->url + child_url, url_->distance + 1));
        }
        return std::shared_ptr<url_t>(new url_t(child_url, url_->distance + 1));
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
                std::shared_ptr<url_t> child = url_->make_child(href_url);
                links.push_back(child);
            }

        }

        return links;
    }
}}

