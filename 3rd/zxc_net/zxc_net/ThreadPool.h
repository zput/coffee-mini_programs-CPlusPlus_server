#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <vector>
#include <deque>

//#include "noncopyable.h"
#include "Callbacks.h"

namespace zxc_net
{
	// : noncopyable
class ThreadPool
{
public:
    explicit
    ThreadPool(size_t numThread,
               size_t maxQueueSize = 65536,
               const ThreadInitCallback& cb = nullptr);
    ~ThreadPool();

    void runTask(const Task& task);
    void runTask(Task&& task);
    void stop();
    size_t numThreads() const
    { return threads_.size(); }

private:
    void runInThread(size_t index);
    Task take();

    typedef std::unique_ptr<std::thread> ThreadPtr;
    typedef std::vector<ThreadPtr> ThreadList;

    ThreadList threads_;
    std::mutex mutex_;
    std::condition_variable notEmpty_;       //  如果queue为空的话, 等待queue 有task() 进来再说, .   
    std::condition_variable notFull_;     //  如果 queue满了的话, 使用notFull_来等待queue不满的时候再进行下面的, 添加task() 到queue中去. 
    std::deque<Task> taskQueue_;
    const size_t maxQueueSize_;
    std::atomic_bool running_;
    ThreadInitCallback threadInitCallback_;
};

}

#endif //THREADPOOL_H
