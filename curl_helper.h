#pragma once

#include <curl/curl.h>

#include <string>
#include <memory>

#include "page.h"

namespace shad_pdc { namespace crawler {
    class page_t;
    class url_t;
    size_t string_write(void *contents, size_t size, size_t nmemb, void *userp);
    CURLcode curl_read(const std::string& url, std::string& buffer, long timeout);
    std::shared_ptr<page_t> get_page(std::shared_ptr<url_t> url);
}}
