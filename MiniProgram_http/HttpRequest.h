//HttpRequest.h

#ifndef __HTTPREQUEST_H__
#define __HTTPREQUEST_H__
#include <iostream>
#include <zxc_net/copyable.h>

#include <zxc_net/Timestamp.h>
#include <string>
#include <map>
using namespace std;
class HttpRequest:zxc_net::copyable
{
    public:
			enum Method
			{
				INVALID,
				GET,
				POST,
				HEAD,
				PUT,
				DELETE
			};
			enum Version
			{
				UNKNOWN,
				HTTP10,
				HTTP11
			};

			HttpRequest();

			//set和get方法声明
			void setVersion(Version v);
			Version getVersion() const;

			bool setMethod(const char *start,const char* end);
			Method method()const;
			const char*methodString()const;

			void setPath(const char*start,const char*end);
			const string& path()const;

			void setQuery(const char* start, const char* end);
			const string& query() const;

			void setReceiveTime(zxc_net::Timestamp t);
			zxc_net::Timestamp receiveTime() const;

			void addHeader(const char*start,const char*colon,const char*end);
			string getHeader(const string& field)const;

			const map<string,string>&headers()const;


			void swap(HttpRequest& that);

     private:
			Method method_;
			Version version_;
			string path_;
			string query_;
		//	zxc_net::Timestamp receiveTime_;
			std::map<string,string>headers_;
};
#endif 
