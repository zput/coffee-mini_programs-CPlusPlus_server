# coffee-mini_programs-CPlusPlus-_server

它可以分为三个部分: 

- 底层使用自己的支持多线程网络库zxc_net, 进行数据的收发. 
- 中层使用HTTP解析器, 解析HTTP的请求行, 请求头, 请求body, 支持Content-Type: multipart/form-data 文件格式, 数据的自动接收保存,方便上层用户层的使用调用. 
- 上层用户层支持把数据做相应的转换, 通过使用自定义mysql类, 进行用户数据的保存.

中层的HTTP分为了: HttpServer HttpResponse  HttpRequest  HttpContext 类. 

其中HTTPContext类对客户端的请求信息,进行自动的解析.包含的成员函数如下. 
```C++
HttpContext::ParseReturn HttpContext::parseRequest(zxc_net::Buffer* original_buf)

bool HttpContext::processRequestLine(const char*begin, const char*end)

bool HttpContext::parserContentType_MultipartFormData(void)

std::string  HttpContext::parserBoundary(std::string content_type ) 

```

对与HTTP body 的信息的解析, 使用content-length 来判断是否HTTP body的数据已经接收完成, 否则,等待下次数据流到达, read事件
被调用,再次解析body. 
```C++
			//FIXME 如何保证它的body 的数据全部读到了readBuff 里? , 如果还有数据在路上该怎么办 ? 
			int temp =atoi(std::string(request_.getHeader("Content-Length") != std::string("") ? request_.getHeader("Content-Length") : request_.getHeader("content-length")).c_str() );
			
			if (buf->readableBytes() < temp) {
				DEBUG("more datas need to receive ...Now:%d---Need:%d \n",buf->readableBytes(),temp);
				//  Not needing to modify the original buff data;
				return  ParseReturn::parseNeedMore;
			}

```

## 安装
需要gcc 7.x

```sh
$ ./build.sh 
$ ./build.sh install

```
安装在 `../MiniProgram_http-build/Release/{include, lib, bin}`

