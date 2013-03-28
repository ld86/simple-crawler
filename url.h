#pragma once 

#include <string>
#include <memory>

#include "curl_helper.h"

namespace shad_pdc { namespace crawler {
    class url_t {
        url_t(const std::string& url, uint32_t distance);

        public:
        const std::string url;
        const uint32_t distance;

        static std::shared_ptr<url_t> start_url(const std::string& url);
        std::shared_ptr<url_t> make_child(const std::string& href_url);
    };
}}
