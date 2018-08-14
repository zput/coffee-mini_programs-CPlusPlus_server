//
// Created by frank on 17-9-1.
//



#include "Logger.h"
#include "TcpConnection.h"
#include "TcpServer.h"
#include "EventLoop.h"
#include "TcpServerMulti.h"


using namespace zxc_net;

TcpServerMulti::TcpServerMulti(EventLoop* loop, const InetAddress& local)
        : baseLoop_(loop),
          numThreads_(1),
          started_(false),
          local_(local),
          threadInitCallback_(defaultThreadInitCallback),
          connectionCallback_(defaultConnectionCallback),
          messageCallback_(defaultMessageCallback)
{
   INFO("create TcpServer() %s", local_.toIpPort().c_str());
}

TcpServerMulti::~TcpServerMulti()
{
    for (auto& loop: eventLoops_)
        if (loop != nullptr)
            loop->quit();
    for (auto& thread: threads_)
        thread->join();
    TRACE("~TcpServer()");
}

void TcpServerMulti::setNumThread(size_t n)
{
    baseLoop_->assertInLoopThread();
    assert(n > 0);
    assert(!started_);
    numThreads_ = n;
    eventLoops_.resize(n);
}

void TcpServerMulti::start()
{
    baseLoop_->assertInLoopThread();
    assert(!started_);
    started_ = true;

    INFO("TcpServer::start() %s with %lu eventLoop thread(s)",
         local_.toIpPort().c_str(), numThreads_);

    baseServer_ = std::make_unique<TcpServer>(baseLoop_, local_);
				  //TcpServerSingle::TcpServerSingle(EventLoop* loop, const InetAddress& local)
				  //	: loop_(loop),
				  //	acceptor_(loop, local)
				  //{
				  //	acceptor_.setNewConnectionCallback(std::bind(
				  //		&TcpServerSingle::newConnection, this, _1, _2, _3));
				  //}

    baseServer_->setConnectionCallback(connectionCallback_);
    baseServer_->setMessageCallback(messageCallback_);

    baseServer_->setWriteCompleteCallback(writeCompleteCallback_);
    threadInitCallback_(0);
	
    for (size_t i = 1; i < numThreads_; ++i) {
        auto thread = new std::thread(std::bind(
                &TcpServerMulti::runInThread, this, i));
        {
            std::unique_lock<std::mutex> lock(mutex_);
            while (eventLoops_[i] == nullptr)
                cond_.wait(lock);
        }
        threads_.emplace_back(thread);
    }
}







void TcpServerMulti::runInThread(size_t index)
{
    EventLoop loop;
    TcpServer server(&loop, local_);

    server.setConnectionCallback(connectionCallback_);
    server.setMessageCallback(messageCallback_);
    server.setWriteCompleteCallback(writeCompleteCallback_);

    {
        std::lock_guard<std::mutex> guard(mutex_);
        eventLoops_[index] = &loop;
        cond_.notify_one();
    }

    threadInitCallback_(index);
    loop.loop();
    eventLoops_[index] = nullptr;
}
