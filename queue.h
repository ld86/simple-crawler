#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace shad_pdc { namespace crawler {
    template <typename T>
        class queue_t {
            typedef T item_t;

            std::queue<item_t> inner_queue_;
            mutable std::mutex mutex_;
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

            bool is_empty() const {
                std::lock_guard<std::mutex> lock(mutex_);
                return inner_queue_.empty();
            }
        };

}}
