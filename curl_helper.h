#pragma once

#include <curl/curl.h>

#include <string>
#include <memory>

namespace shad_pdc { namespace crawler {
    size_t string_write(void *contents, size_t size, size_t nmemb, void *userp);
    CURLcode curl_read(const std::string& url, std::string& buffer, long timeout);
    std::shared_ptr<std::string> wget_string(const std::string& url);
}}
