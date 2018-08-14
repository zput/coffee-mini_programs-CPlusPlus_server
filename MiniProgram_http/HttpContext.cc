#include "HttpContext.h"

//解析请求头
HttpContext::ParseReturn HttpContext::parseRequest(zxc_net::Buffer* original_buf)
{
	zxc_net::Buffer buff(*original_buf);
	zxc_net::Buffer* buf = &buff;
	
    bool ok= true;
    bool hasMore=true;
    while(hasMore)
    {
        //解析请求行
        if(state_==kExpectRequestLine)
        {
            const char*crlf=buf->findCRLF();
            if(crlf)
            {
                //开始解析请求行
                ok=processRequestLine(buf->peek(),crlf);
                if(ok)
                {
					DEBUG("parser is successful \n");
                     //解析成功
                     //request_.setReceiveTime(receiveTime);
                     //回收请求行buffer
                    buf->retrieveUntil(crlf+2);
                    state_=kExpectHeaders;
                }
                else
                {
                    hasMore=false;
                }
            }
            else
            {
                hasMore=false;
            }
        }
        //解析请求头
        else if(state_==kExpectHeaders)
        {
            const char* crlf = buf->findCRLF();
            if (crlf)
            {
                //冒号
                const char* colon = std::find(buf->peek(), crlf, ':');
                if (colon != crlf)
                {
                    request_.addHeader(buf->peek(), colon, crlf);
                }
                else
                {
					// empty line, end of header
					// FIXME:
					state_ = kExpectBody;

#if 0
					state_ = kGotAll;
					hasMore = false;
#endif
                }
                buf->retrieveUntil(crlf + 2);//回收
            }
            else
            {
                hasMore = false;
            }
        }
        else if(state_==kExpectBody)
        {
			//FIXME 如何保证它的body 的数据全部读到了readBuff 里? , 如果还有数据在路上该怎么办 ? 
			int temp =atoi(std::string(request_.getHeader("Content-Length") != std::string("") ? request_.getHeader("Content-Length") : request_.getHeader("content-length")).c_str() );
			
			if (buf->readableBytes() < temp) {
				DEBUG("more datas need to receive ...Now:%d---Need:%d \n",buf->readableBytes(),temp);
				//  Not needing to modify the original buff data;
				return  ParseReturn::parseNeedMore;
			}

			request_.setBody(buf->peek(), buf->peek() + temp);
			  // parsing the body type is: multipart-form-data, it includes boundary;
			if ( std::string::npos !=( (request_.getHeader("Content-Type") != std::string("")) ? request_.getHeader("Content-Type") : request_.getHeader("content-type") ).find("multipart/form-data") ) {
				if (parserContentType_MultipartFormData() == false) {
					ERROR("parsing Multipart-form-data ERROR\n");
					return  ParseReturn::parseFailure;
				}
			}
			buf->retrieve( temp );
			hasMore = false;
			state_ = kGotAll;
			original_buf->swap(buff);
        }

    }//endwhile

    return ok? ParseReturn::parseSuccess :ParseReturn::parseFailure;
}



//解析请求头
bool HttpContext::processRequestLine(const char*begin, const char*end)
{
	bool succeed = false;
	const char*start = begin;
	const char*space = std::find(start, end, ' ');
	//设置请求方法//method_
	if (space != end && request_.setMethod(start, space))
	{
		start = space + 1;
		space = std::find(start, end, ' ');
		if (space != end)
		{
			//解析URI
			const char* question = std::find(start, space, '?');
			if (question != space)
			{
				request_.setPath(start, question);
				request_.setQuery(question, space);
			}
			else
			{
				request_.setPath(start, space);
			}
			//解析HTTP版本号
			start = space + 1;
			succeed = end - start == 8 && std::equal(start, end - 1, "HTTP/1.");
			if (succeed)
			{
				if (*(end - 1) == '1')
				{
					request_.setVersion(HttpRequest::HTTP11);
				}
				else if (*(end - 1) == '0')
				{
					request_.setVersion(HttpRequest::HTTP10);
				}
				else
				{
					succeed = false;
				}
			}//endif
		}//endif
	}//endif
	return succeed;
}


std::string  HttpContext::parserBoundary(std::string content_type ) {
	  // get boundary
	std::string boundary = "";
	auto temp = std::find(content_type.begin(), content_type.end(), '=');
	if (temp == content_type.end()) {
		return std::string("");
	}
	boundary = std::string(temp + 1, content_type.end());     //FIXME
	DEBUG("boundary:%s\n", boundary.c_str());
	return boundary;

}



bool HttpContext::parserContentType_MultipartFormData(void) {

  std::string boundary = parserBoundary(  (request_.getHeader("Content-Type") != std::string("")) ? request_.getHeader("Content-Type") : request_.getHeader("content-type")   );
  if (boundary == std::string()) {
	  DEBUG("parsing boundary ERROR\n");
	  return false;
  }



  //assert(request_.getBody()!=std::string(""))
  const std::string temp = request_.getBody();

  int name_head_position = 0;
  int data_head = 0;
  int data_tail = 0;
  std::string name;
  std::string data;
  while (1) {
	     // name
	  name_head_position = temp.find("name=\"",data_tail);
	  if (name_head_position == std::string::npos) {
		  DEBUG("parsering multipartFormData\n");
		  return  false;
	  }
	  name_head_position += 6;
	  name = std::string(temp.begin() + name_head_position, temp.begin() + temp.find('\"', name_head_position));
	  DEBUG("the name:%s\n",name.c_str());
        // data
	  data_head = temp.find("\r\n\r\n",name_head_position);
	  if (data_head == std::string::npos) {
		  DEBUG("parsering multipartFormData\n");
		  return  false;
	  }
	  data_head += 4;
	  data_tail = temp.find(boundary, data_head);
	  if (data_tail == std::string::npos) {
		  DEBUG("parsering multipartFormData\n");
		  return  false;
	  }
	  data_tail -= 4;    //\r\n--${boundary}
	  data = std::string(temp.begin() + data_head, temp.begin() + data_tail);
	     //save to std::map
	  request_.addMultipartFormData(name, data);



	  if ( *(temp.begin()+data_tail+4+boundary.length() ) == '-'  ) {
		   // is end;
		  DEBUG("parsering the MultipartFormData is END\n");
		  break;
	  }
	  else {
		  DEBUG("\n-------THE NEXT----------\n");
	  }

  }
  
  return true;

}
