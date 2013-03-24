#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <queue>
#include <set>
#include <boost/regex.hpp>
#include <iterator>
#include <iostream>

#include <curl/curl.h>


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

std::string wget_string(const std::string& url) {
    std::string content;
    CURLcode res = curl_read(url, content);
    return content;
}

class parameters_t {
    friend class crawler_t;

    std::string start_url;
    int deep;
    int max_page_count;
    std::string save_path;

    public:
    parameters_t(int argc, char** argv) :
        start_url(argv[1]),
        deep(atoi(argv[2])),
        max_page_count(atoi(argv[3])),
        save_path(argv[4]) {
        }
};

template <typename T>
class queue_t {
    typedef T item_t;

    std::queue<item_t> inner_queue_;
    std::mutex mutex_;
    std::condition_variable cond_;

    public:
    void put(const item_t& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        inner_queue_.push(item);
        cond_.notify_one();
    }

    item_t take() {
        std::unique_lock<std::mutex> ulock(mutex_);
        while (inner_queue_.empty()) {
            cond_.wait(ulock);
        }
        item_t value = inner_queue_.front();
        inner_queue_.pop();
        return value;
    }
};

class url_t {
        std::string url_;
        uint32_t distance_;
     
        url_t(const std::string& url, uint32_t distance) :
            url_(url),
            distance_(distance) {
        }

    public:
        static url_t start_url(const std::string& url) {
            return url_t(url, 0);
        }
        
        url_t make_child(const std::string& url) {
            
        }

        bool operator<(const url_t& rhs) const {
            url_ < rhs.url_;
        }
};

class url_queue_t {
    std::mutex mutex_;
    std::set<url_t> visited_pages_;
    queue_t<url_t> url_queue_;

    public:
        void add_url(const url_t& url) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (visited_pages_.find(url) == visited_pages_.end()) {
                visited_pages_.insert(url);
                url_queue_.put(url);
            }        
        }

        url_t next_url() {
            return url_queue_.take();
        }
};

class page_t {
};

class worker_t {
    url_queue_t& url_queue_;
    queue_t<page_t>& page_queue_;

    public:
    worker_t(url_queue_t& url_queue,
             queue_t<page_t>& page_queue)
        : url_queue_(url_queue),
          page_queue_(page_queue) {
    }

    void operator()() {
        for (;;) {
            /*
            std::string next_url = url_queue_.next_url();
            std::string content = wget_string(next_url);

            std::printf("%s\n", next_url.c_str());

            boost::regex re("href=['\"](.+?)['\"]");

            boost::sregex_iterator begin(content.begin(), 
                                        content.end(), 
                                        re);
            boost::sregex_iterator end;

            for (auto it = begin; it != end; ++it) {
                std::string href_url = (*it)[1].str();
                std::printf("new: %s\n", href_url.c_str());
                url_queue_.add_url(href_url);
            }
            */
        }
    }
};

class crawler_t {
    queue_t<page_t> page_queue_;
    url_queue_t url_queue_;

    parameters_t parameters_;

    public:
    crawler_t(const parameters_t& parameters) 
        : parameters_(parameters) {
            url_t start_url = url_t::start_url(parameters_.start_url);
            url_queue_.add_url(start_url);
        }

    void run() {
        std::vector<std::shared_ptr<std::thread>> threads;
        std::vector<std::shared_ptr<worker_t>> workers;

        const int concurrency_level = 2;

        for (int i = 0; i < concurrency_level; ++i) {
            workers.push_back(
                    std::shared_ptr<worker_t>(
                        new worker_t(url_queue_, page_queue_)));

            threads.push_back(
                    std::shared_ptr<std::thread>(
                        new std::thread(std::ref(*workers[i]))));
        }

        for (int i = 0; i < concurrency_level; ++i) {
            threads[i]->join();
        }

    }
};

class runner_t {
    bool is_right_parameters(int argc, char** argv) {
        if (argc != 5) {
            return false;
        }

        return true;
    }

    int show_usage(char** argv) {
        std::printf("%s\n", argv[0]);
        return -1;
    }

    public:
    int run(int argc, char** argv) {
        if (!is_right_parameters(argc, argv)) {
            return show_usage(argv);
        }

        parameters_t parameters(argc, argv);
        crawler_t crawler(parameters);
        crawler.run();
    }
};

int main(int argc, char** argv) {
    runner_t runner;
    return runner.run(argc, argv);
}
