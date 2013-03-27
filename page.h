#pragma once

#include <string>
#include <vector>
#include <memory>

#include <boost/regex.hpp>

namespace shad_pdc { namespace crawler {
    class url_t;
    class page_t {
        boost::regex link_re_;
        const std::shared_ptr<std::string> content_;
        std::shared_ptr<url_t> url_;

        std::shared_ptr<url_t> make_child(const std::string& child_url);
        public:
        page_t(std::shared_ptr<url_t> url,
                std::shared_ptr<std::string> content);
        std::vector<std::shared_ptr<url_t>> get_links();
    };
}}
