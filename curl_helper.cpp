#include "curl_helper.h"

namespace shad_pdc { namespace crawler {
    size_t string_write(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    CURLcode curl_read(const std::string& url, std::string& buffer, long timeout = 30) {
        CURLcode code(CURLE_FAILED_INIT);
        CURL* curl = curl_easy_init();
        char user_agent[] = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1106.241 YaBrowser/1.5.1106.241 Safari/537.4";

        if(curl) {
            if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str()))
                    && CURLE_OK == 
                    (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, string_write))
                    && CURLE_OK == 
                    (code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer))
                    && CURLE_OK == 
                    (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
                    && CURLE_OK == 
                    (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
                    && CURLE_OK == 
                    (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
                    && CURLE_OK ==
                    (code = curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent))) {
                code = curl_easy_perform(curl);
            }
            curl_easy_cleanup(curl);
        }
        return code;
    }

    std::shared_ptr<page_t> get_page(std::shared_ptr<url_t> url) {
        auto content = std::shared_ptr<std::string>(new std::string());
        curl_read(url->url, *content);
        return std::shared_ptr<page_t>(new page_t(url, content));
    }
}}

