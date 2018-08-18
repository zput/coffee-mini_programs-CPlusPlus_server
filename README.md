# coffee-mini_programs-CPlusPlus-_server

它可以分为三个部分: 

- 底层使用自己的支持多线程网络库zxc_net, 进行数据的收发. 
- 中层使用HTTP解析器, 解析HTTP的请求行, 请求头, 请求body, 支持Content-Type: multipart/form-data 文件格式, 数据的自动接收保存,方便上层用户层的使用调用. 
- 上层用户层支持把数据做相应的转换, 通过使用自定义mysql类, 进行用户数据的保存.



做了一个提交信息喝免费咖啡的微信小程序，它的后端是C++ socket写的，使用微信的wx.request() 与后端的C++服务器进行交流
