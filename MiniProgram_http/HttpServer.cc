//HttpServer.cpp

#include "HttpServer.h"

#if 1
//默认HTTP回调，返回错误码
void defaultHttpCallback(const HttpRequest&, HttpResponse* resp)
{
#if 1
    resp->setStatusCode(HttpResponse::CODE_400);
    resp->setStatusMessage("Not Found");
    resp->setCloseConnection(true);
#endif
}
#endif


#if 1
//构造函数
HttpServer::HttpServer(zxc_net::EventLoop* loop,
					   const zxc_net::InetAddress& listenAddr)
    : server_(loop, listenAddr),
      httpCallback_(defaultHttpCallback)

{
    server_.setConnectionCallback(
        std::bind(&HttpServer::onConnection, this, std::placeholders::_1));

    server_.setMessageCallback(
        std::bind(&HttpServer::onMessage, this, std::placeholders::_1, std::placeholders::_2) );
}
//析构函数
HttpServer::~HttpServer()
{
}
void HttpServer::start()
{
  //  WARN("HttpServer[%s] starts listenning on %d \n", server_.name(), server_.ipPort(););
	  server_.start();
}
#endif







//新连接回调
void HttpServer::onConnection(const zxc_net::TcpConnectionPtr& conn)
{
	INFO("A new connection: [%s] \n", conn->name().c_str());
    if (conn->connected())
    {
        conn->setContext(HttpContext());
    }
}
//消息回调
void HttpServer::onMessage(const zxc_net::TcpConnectionPtr& conn,
	zxc_net::Buffer& buf)
{
	DEBUG("Recover request : %s\n",buf.readAheadALLAsStringNotRetrieve().c_str() );

    HttpContext*context=std::any_cast<HttpContext>(conn->getMutableContext());

        // 解析请求
    if(!context->parseRequest(&buf) )
    {
		DEBUG("parseRequesting is failure \n");
        conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
        conn->shutdown();
    }
    if (context->gotAll())          //state_==gotALL
    {
        // 请求已经解析完毕
		DEBUG("parseRequesting is successful \n");
        onRequest(conn, context->request());
        context->reset();//context reset
    }

}






#if 1
void HttpServer::onRequest(const zxc_net::TcpConnectionPtr& conn, const HttpRequest& req)
{
#if 1
    const string& connection = req.getHeader("Connection");
    bool close = connection == "close" ||
    (req.getVersion() == HttpRequest::HTTP10 && connection != "Keep-Alive");
    HttpResponse response(close);//构造响应

    httpCallback_(req, &response);//用户回调

	zxc_net::Buffer buf;
    //此时response已经构造好，将向客户发送Response添加到buffer中
    response.appendToBuffer(&buf);

	DEBUG("Recover send Message : %s\n", buf.readAheadALLAsStringNotRetrieve().c_str());
    conn->send(buf );
    //如果非Keep-Alive则直接关掉
    if (response.closeConnection())
    {
		ERROR("??shutdown FIXME \n");
        //conn->shutdown();
		conn->forceClose();
    }
#endif
}
#endif
