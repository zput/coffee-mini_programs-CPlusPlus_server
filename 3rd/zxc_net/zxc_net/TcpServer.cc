#include"EventLoop.h"
#include"InetAddress.h"

#include"Accept.h"

#include"TcpConnection.h"
#include"TcpServer.h"
#include"Logger.h"

using namespace zxc_net;

TcpServer::TcpServer(EventLoop* loop, const InetAddress& local)
	:loop_(loop),
	address_(&local),
	accept_(new Accept(loop_, address_)),
	eventLoopThreadPool_( new EventLoopThreadPool(loop_,1) )
{
	eventLoopThreadPool_->start();
	accept_->setMessageCallback(messageCallback_);
	accept_->setNewconnectionCallback(std::bind(&TcpServer::newConnection, this, 
		                                        std::placeholders::_1, 
		                                        std::placeholders::_2, 
		                                        std::placeholders::_3));
}

 TcpServer::TcpServer (EventLoop* loop, std::string& ip, uint16_t port)
          :loop_(loop),
		   address_( new InetAddress(ip, port)),
		   accept_(new Accept(loop_,address_))  {

	  accept_->setMessageCallback(messageCallback_);
   // accept_->setNewconnectionCallback([this](){newConnection( );});
	  accept_->setNewconnectionCallback(std::bind(&TcpServer::newConnection, this,
		  std::placeholders::_1,
		  std::placeholders::_2,
		  std::placeholders::_3));

 }

TcpServer::~TcpServer () {
	delete eventLoopThreadPool_;
}



  void TcpServer::newConnection( int connfd, 
						   const InetAddress& local,
						   const InetAddress& peer ) {

	    EventLoop* ioLoop =eventLoopThreadPool_->getOneLoop();

	    std::shared_ptr<TcpConnection > conn(new TcpConnection(ioLoop, connfd, local, peer));
	    conn->setWriteCallback(writeCallback_);
		conn->setMessageCallback(messageCallback_);
		conn->setConnectionCallback(connectionCallback_);

		conn->setWriteCompleteCallback(writeCompleteCallback_);
	    conn->setremoveConnectionCallback(bind(&TcpServer::removeConnection,this,std::placeholders::_1));

		ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished,conn) );
        connLists_.push_back(conn);

  }
   
void TcpServer::removeConnection( const std::shared_ptr<TcpConnection>& conn ) {
	// 当一到到达这个函数 , 证明现在已经在TcpServer中的clientfd 的线程池里的某个线程中(Loop)
	// 我们需要跳到 TcpServer所在的主线程中, acceptfd? 
	loop_->runInLoop( std::bind(&TcpServer::removeConnectionInLoop, this, conn) );
	  
  }
  
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn) {
	for (CONNLISTS::iterator i = connLists_.begin(); i != connLists_.end(); i++) {
		if (*i == conn) {					
			connLists_.erase(i);
			break;
		}
	}
	EventLoop* ioLoop = conn->getLoop();
	ioLoop->queueInLoop(std::bind(&TcpConnection::destoryConn, conn));
	TRACE("\nTcpServer::removeConnection ---close \n");

}
