//HttpContext.h

#ifndef __HTTPCONTEXT_H__
#define __HTTPCONTEXT_H__

#include <zxc_net/copyable.h>
#include <zxc_net/Buffer.h>
#include <zxc_net/Logger.h>

#include "HttpRequest.h"
class Buffer;
class HttpContext:public zxc_net::copyable
{
    public:
		//解析请求的状态
			enum HttpRequestParseState
			{
				kExpectRequestLine,
				kExpectHeaders,
				kExpectBody,
				kGotAll,
			};

			enum ParseReturn
			{
				parseFailure=0,
				parseSuccess=1,
				parseNeedMore=2
			};

			HttpContext()
				: state_(kExpectRequestLine)
			{
			}

			HttpContext::ParseReturn parseRequest(zxc_net::Buffer* buf);

			bool gotAll() const
			{ return state_ == kGotAll; }

			const HttpRequest& request() const
			{ return request_; }


			void reset()
			{
				state_ = kExpectRequestLine;
				HttpRequest dummy;
				request_.swap(dummy);
			}

		//返回Http请求
			HttpRequest& request(){ 
				      return request_;
			}

    private: 
		std::string parserBoundary(std::string );
		bool parserContentType_MultipartFormData(void);

		//解析请求行
			bool processRequestLine(const char* begin, const char* end);
	
    private:
			HttpRequestParseState state_;

		//解析的结果将保存在request_成员中
			HttpRequest request_;
};
#endif