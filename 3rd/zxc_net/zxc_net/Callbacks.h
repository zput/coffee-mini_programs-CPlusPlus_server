// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <functional>
#include <memory>

#include"InetAddress.h"

//#include "Timestamp.h"
//#include "Buffer.h"

namespace zxc_net
{

class TcpConnection;
class Buffer;
class InetAddress;

// All client visible callbacks go here.   // ???

typedef std::function<void()> TimerCallback;

typedef std::function<void(const std::shared_ptr<TcpConnection> &, Buffer& )> MessageCallback;

typedef std::function<void(char*)> WriteCallback;

// typedef std::function<void(int)>   NewconnectionCallback;
typedef std::function<void(int /*sockfd;*/,
							const InetAddress& /*local*/,
							const InetAddress& /*peer*/ )> NewconnectionCallback;

typedef std::function<void(const std::shared_ptr<TcpConnection> &)>  removeConnectionCallback;

typedef std::function<void(const std::shared_ptr<TcpConnection> &)>  ConnectionCallback;


/////////////////////////////////////////////////////////
// TcpServerMulti ThreadPool Logger
//
/////////////////////////////////////////////////////////
		//	using namespace std::string_view_literals;

			using std::placeholders::_1;
			using std::placeholders::_2;
			using std::placeholders::_3;
			using std::placeholders::_4;
			using std::placeholders::_5;

		//	class Buffer;
		//	class TcpConnection;
			class InetAddress;

			typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
			typedef std::function<void(const TcpConnectionPtr&)> CloseCallback;
			typedef std::function<void(const TcpConnectionPtr&)> WriteCompleteCallback;
			typedef std::function<void(const TcpConnectionPtr&, size_t)> HighWaterMarkCallback;

		//	typedef std::function<void(const TcpConnectionPtr&)> ConnectionCallback;
		//	typedef std::function<void(const TcpConnectionPtr&, Buffer&)> MessageCallback;

			typedef std::function<void()> ErrorCallback;
			typedef std::function<void()> Task;
			typedef std::function<void(size_t index)> ThreadInitCallback;


        /*
			typedef std::function<void(int sockfd,
				const InetAddress& local,
				const InetAddress& peer)> NewConnectionCallback;
        */
		//	typedef std::function<void()> TimerCallback;


			void defaultThreadInitCallback(size_t index);
			void defaultConnectionCallback(const TcpConnectionPtr& conn);
			void defaultMessageCallback(const TcpConnectionPtr& conn, Buffer& buffer);



}

#endif  // MUDUO_NET_CALLBACKS_H
