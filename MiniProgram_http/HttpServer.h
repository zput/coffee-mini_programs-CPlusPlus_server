//HttpServer.h

#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__
#include <zxc_net/Logger.h>
#include <zxc_net/EventLoop.h>
#include <zxc_net/TcpServerMulti.h>
#include <zxc_net/TcpConnection.h>
#include <zxc_net/Buffer.h>

#include <utility>
#include <functional>
#include <iostream>
#include <string>

#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
using namespace std;


class HttpServer    // : std::noncopyable
{
    public:

    //http回调类型
    typedef std::function<void(const HttpRequest&, HttpResponse*)>  HttpCallback;

    //构造函数
    HttpServer(zxc_net::EventLoop* loop,
        const zxc_net::InetAddress& listenAddr);

    ~HttpServer();  // force out-line dtor, for scoped_ptr members.
	//   zxc_net::EventLoop* getLoop() const { return server_.getLoop(); }

    void setHttpCallback(const HttpCallback& cb)
    {
        httpCallback_ = cb;
    }
    void setThreadNum(int numThreads)
    {
        server_.setNumThread(numThreads);
    }
    void start();

    private:
    //onConnection
    void onConnection(const zxc_net::TcpConnectionPtr &conn);
    //onMessage
    void onMessage(const zxc_net::TcpConnectionPtr&conn,
		zxc_net::Buffer& buf );   

    //_________________________________//
    void onRequest(const zxc_net::TcpConnectionPtr&,const HttpRequest&);

	zxc_net::TcpServerMulti server_;
    HttpCallback httpCallback_;
};
#endif
