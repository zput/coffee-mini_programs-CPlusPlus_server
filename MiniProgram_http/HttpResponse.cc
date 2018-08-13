//HttpResponse.cpp

#include "HttpResponse.h"
//set和get方法
void HttpResponse::setStatusCode(HttpStatusCode code)
{
    statusCode_=code;
}
void HttpResponse::setStatusMessage(const string& message)
{
    statusMessage_ = message;
}
void HttpResponse::setCloseConnection(bool on)
{
    closeConnection_ = on;
}
bool HttpResponse::closeConnection() const
{
    return closeConnection_;
}
void HttpResponse::setContentType(const string& contentType)
{
    addHeader("Content-Type", contentType);
}
void HttpResponse::addHeader(const string& key, const string& value)
{
    headers_[key] = value;
}
void HttpResponse::setBody(const string& body)
{
    body_ = body;
}

void HttpResponse::appendToBuffer(zxc_net::Buffer* output) const
{
    char buf[32];

    //构造响应行
    snprintf(buf, sizeof buf, "HTTP/1.1 %d ", statusCode_);
    output->append(buf,strlen(buf) );
    output->append(statusMessage_);
    output->append("\r\n",2);

    if (closeConnection_)
    {
        //
		std::string temp_closeConnection = "Connection: close\r\n";
        output->append(temp_closeConnection);
    }
    else
    {
        //Keep-Alive需要Content-Length
		snprintf(buf, sizeof buf, "Content-Length: %zd\r\n", body_.size());
		output->append(buf, strlen(buf) );

		std::string temp = "Connection: Keep-Alive\r\n";
        output->append(temp);
    }

    for (std::map<string, string>::const_iterator it = headers_.begin();
        it != headers_.end();
        ++it)   
    {
        //迭代构造响应头
        output->append(it->first);
        output->append(": ",2);
        output->append(it->second);
        output->append("\r\n", 2);
    }

    output->append("\r\n",2);


    //响应报文body
    output->append(body_);

}
