#pragma once

#include "url_queue.h"
#include "queue.h"
#include "page.h"

namespace shad_pdc { namespace crawler {
    class worker_t {
        url_queue_t& url_queue_;
        queue_t<page_t>& page_queue_;

        public:
        worker_t(url_queue_t& url_queue, queue_t<page_t>& page_queue);
        void operator()();
    };
}}
