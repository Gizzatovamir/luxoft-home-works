//#ifndef SERVICE_H#define SERVICE_H
#pragma once
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

#include "logging.h"

//std::this_thread::sleep_for(1s);

using namespace std::chrono_literals;

// Just implement a trivial functionality
int desiredFunction(int x) {
    return x * x;
}

class Method1_In {
public:
    int a;
};

class Method1_Out {
public:
    int b;
};

class Request : public MoveBase {
public:
    Request() = default;
    ~Request() = default;

    Request(const Request& r)
            : id(r.id), promiseResult(), futureResult(promiseResult.get_future()), method1_In(r.method1_In), method1_Out(r.method1_Out)
    {};

    Request& operator=(const Request&) = delete;
    Request& operator=(Request&&) = default;

    Request(const std::string &id, const Method1_In &in)
            : id(id), method1_In(in), promiseResult(), futureResult(promiseResult.get_future())
    {
    }

    std::string getId() {
        return id;
    }

    std::future<Method1_Out>& getFutureResult() {
        return futureResult;
    }

    std::promise<Method1_Out>& getPromiseResult() {
        return promiseResult;
    }

    const Method1_In& getMethod1_In() {
        return method1_In;
    }

private:
    std::string id;
    std::promise<Method1_Out> promiseResult;
    std::future<Method1_Out> futureResult;
    Method1_In method1_In;
    Method1_Out method1_Out;
};

class Service {
public:
    Service() {
        LOG(INFO) << "TaskProcessor()" << std::endl;
        finish = false;

        processorThread = std::thread([&]{
            processing();
        });

        LOG(INFO) << "Thread started" << std::endl;
    }

    ~Service() {
        LOG(INFO) << "~TaskProcessor()" << std::endl;
        finish = true;
        cv.notify_all();
        processorThread.join();
    }

    void processing() {
        LOG(INFO) << "Thread active" << std::endl;

        while (true) {

            Request request;
            {
                std::unique_lock<std::mutex> lk(m);
                cv.wait(lk,
                        [this] { return !readyRequests.empty() || finish; }
                );
                LOG(INFO) << "Reached" << std::endl;

                if (finish && readyRequests.empty()) {
                    return;
                }

                request = std::move(readyRequests.front());
                readyRequests.pop_front();

                cv.notify_all();
            }

            const Method1_In& in = request.getMethod1_In();
            Method1_Out out = { desiredFunction(in.a) };

            request.getPromiseResult().set_value(out);

            onResultAvailable(in, out);

            doneRequests.push_back(std::move(request));
            LOG(INFO) << "...request end" << std::endl;
        }
    }

    virtual void onResultAvailable(const Method1_In &in, const Method1_Out &out) {}

    std::future<Method1_Out>&
    postRequest(Request&& request) {
        std::lock_guard<std::mutex> lk(m);
        readyRequests.push_back(request);

        LOG(INFO) << "Push new element..." << std::endl;
        cv.notify_all();

        return readyRequests.back().getFutureResult();
    }

    void dump() {
        LOG(INFO) << "Done requests dump:" << std::endl;
        for (auto &request: readyRequests) {
            LOG(INFO) << "  " << request.getId() << std::endl;
        }

        LOG(INFO) << "Done requests dump:" << std::endl;
        for (auto &request: doneRequests) {
            LOG(INFO) << "  " << request.getId() << std::endl;
        }

        LOG(INFO) << "... end" << std::endl;
    }

private:
    std::thread processorThread;
    bool finish;
    std::mutex m;
    std::deque<Request> readyRequests;
    std::deque<Request> doneRequests;
    std::condition_variable cv;
};

class ServiceSkeleton : public Service {
private:	
    std::function<void(const Method1_In&, const Method1_Out&)> m_callback{};
public:
    std::future<Method1_Out>& method1(const Method1_In &in) {
        Request s("method1", in);

        std::future<Method1_Out> &f = postRequest(std::move(s));

        return f;
    }

    template<typename T>
    std::future<Method1_Out>& method1(const Method1_In &in, T callback) {
        m_callback = callback;
        return method1(in);
    }

    virtual void onMethod1ResultAvailable(const Method1_In &in, const Method1_Out &out) {}

    virtual void onResultAvailable(const Method1_In &in, const Method1_Out &out) override {
	m_callback ? m_callback(in,out) : onMethod1ResultAvailable(in, out);
	//if(m_callback)
	//{
	//    m_callback(in, out);
	//}
	//else
	//{
	//    onMethod1ResultAvailable(in, out);
	//}
    }
};

//#endif //SERVICE_H
