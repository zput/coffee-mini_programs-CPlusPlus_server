//HttpResponse.h

#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__
#include <zxc_net/copyable.h>
#include <iostream>
#include <string>
#include <map>
#include <zxc_net/Buffer.h>
using namespace std;
class HttpResponse:public zxc_net::copyable
{
    public:
    enum HttpStatusCode
    {
        CODE_UNKNOWN,
        CODE_200=200,
        CODE_301=301,
        CODE_400=400,
        CODE_404=404
    };
    explicit HttpResponse(bool close)
        : statusCode_(CODE_UNKNOWN),
        closeConnection_(close)
    {
    }
    void setStatusCode(HttpStatusCode code);
    void setStatusMessage(const string&message);

    void setCloseConnection(bool on);
    bool closeConnection()const;

    void setContentType(const string&contentType);
    void addHeader(const string&key,const string&value);

    void setBody(const string &body);
    void appendToBuffer(zxc_net::Buffer*output)const;
    private:
    //响应头
    std::map<string,string>headers_;
    //响应码
    HttpStatusCode statusCode_;
    //状态信息
    string statusMessage_;
    //是否 keep-alive
    bool closeConnection_;
    //响应报文
    string body_;

};
#endif