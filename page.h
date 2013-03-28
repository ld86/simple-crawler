#pragma once

#include <string>
#include <vector>
#include <memory>

#include <boost/regex.hpp>

#include "url.h"

namespace shad_pdc { namespace crawler {
    class url_t;
    class page_t {
        std::shared_ptr<url_t> url_;
        std::shared_ptr<std::string> content_;
        const boost::regex link_re_;
        public:
            page_t(std::shared_ptr<url_t> url, 
                    std::shared_ptr<std::string> content);

            std::vector<std::shared_ptr<url_t>> get_links();
            std::shared_ptr<std::string> content() const;
            std::shared_ptr<url_t> url() const;
    };
}}
