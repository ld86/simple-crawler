#include <curl/curl.h>
#include <iostream>
#include <string>

size_t string_write(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

CURLcode curl_read(const std::string& url, std::string& buffer, long timeout = 30) {
    CURLcode code(CURLE_FAILED_INIT);
    CURL* curl = curl_easy_init();

    if(curl) {    
        if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str()))
        && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, string_write))
        && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer))
        && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
        && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
        && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))) {

          code = curl_easy_perform(curl);
        }
        curl_easy_cleanup(curl);
    }
    return code;
}

int main(int argc, const char* argv[]) {
    std::string url = argv[1];
    std::string content;
    CURLcode res = curl_read(url, content);
    if (res == CURLE_OK) {
        std::cout << content << std::endl;
    } else {
        std::cerr << "ERROR: " << curl_easy_strerror(res) << std::endl;
    }
}