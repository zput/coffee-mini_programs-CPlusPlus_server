
#include<unistd.h>
#include<sys/socket.h>

#include"EventLoop.h"
#include"Channel.h"
#include"TcpConnection.h"
#include "Logger.h"



namespace zxc_net
{


	void defaultThreadInitCallback(size_t index)
	{
		TRACE("EventLoop thread #%lu started", index);
	}

	void defaultConnectionCallback(const TcpConnectionPtr& conn)
	{
		//  INFO("connection %s -> %s %s",
		//	conn->peer().toIpPort().c_str(),
		//	conn->local().toIpPort().c_str(),
		//	conn->connected() ? "up" : "down");

		TRACE("\ndefaultConnectionCallback\n");
	}

	void defaultMessageCallback(const TcpConnectionPtr& conn, Buffer& buffer)
	{
		//  TRACE("connection %s -> %s recv %lu bytes",
		//	conn->peer().toIpPort().c_str(),
		//	conn->local().toIpPort().c_str(),
		//	buffer.readableBytes());
		//  buffer.retrieveAll();
		TRACE("\ndefaultMessageCallback\n");
	}

}





using namespace zxc_net;

TcpConnection::TcpConnection (EventLoop* loop, int conn,
							   const InetAddress& local,
							   const InetAddress& peer )
					:loop_(loop),
					connfd_(conn),
					connChannel_(new Channel(loop_, connfd_) ),
					readBuff(new char[200]()),
					writeBuff(new char[200]()),
					state_(kConnecting),
					local_(local),
					peer_(peer)      {
	 connChannel_->setReadCallback( std::bind(&TcpConnection::handleRead,this) );
	 connChannel_->setWriteCallback( [this](){handleWrite();} );
  // connChannel_->enableReading();
	
}

TcpConnection::~TcpConnection ( ){
	INFO("~TcpConnection() \n");
	
}

void TcpConnection::send(const std::string& message)
{
  if (state_ == kConnected) {
    if (loop_->isInLoopThread()) {
      sendInLoop(message);
    } else {
      loop_->runInLoop(
          std::bind(&TcpConnection::sendInLoop, this, message));
    }

  }
}

void TcpConnection::sendInLoop(const std::string& message)
{
  loop_->assertInLoopThread();
  ssize_t nwrote = 0;
  // if no thing in output queue, try writing directly
  if (!connChannel_->isWriting() && outputBuffer_.readableBytes() == 0) {
    nwrote = ::write(connChannel_->fd(), message.data(), message.size());
    if (nwrote >= 0) {
      if ((size_t)nwrote < message.size()) {
	   TRACE("\nI am going to write more data\n");
	  } else if (writeCompleteCallback_) {
			  // user may send data in writeCompleteCallback_
			  // queueInLoop can break the chain
			  loop_->queueInLoop(std::bind(
				  writeCompleteCallback_, shared_from_this()));
		 }
    } else {
      nwrote = 0;
      if (errno != EWOULDBLOCK) {   // #define	EWOULDBLOCK	EAGAIN	/* Operation would block */
		  SYSERR("TcpConnection::write()---sendInLoop"); 
      }
    }
  }

  assert(nwrote >= 0);
  if ((size_t)nwrote < message.size()) {
	  if (highWaterMarkCallback_) {
		  size_t oldLen = outputBuffer_.readableBytes();
		  size_t newLen = oldLen + message.size()-(size_t)nwrote;
		  if (oldLen < highWaterMark_ && newLen >= highWaterMark_)
			  loop_->queueInLoop(std::bind(
				  highWaterMarkCallback_, shared_from_this(), newLen));
	  }

    outputBuffer_.append(message.data()+nwrote, message.size()-nwrote);
    if (!connChannel_->isWriting()) {
		connChannel_->enableWriting();
    }
  }
}




void TcpConnection::send(Buffer& buffer)
{
	if (state_ != kConnected) {
		WARN("TcpConnection::send() not connected, give up send");
		return;
	}
	if (loop_->isInLoopThread()) {
		sendInLoop(buffer.retrieveAllAsString());
		buffer.retrieveAll();
	}
	else {
		loop_->queueInLoop(
			[ptr = shared_from_this(), str = buffer.retrieveAllAsString()]()
		{ ptr->sendInLoop(str); });
	}
}









void TcpConnection::shutdown()
{
	assert(state_ <= kDisconnecting);
	if (stateAtomicGetAndSet(kDisconnecting) == kConnected) {
		if (loop_->isInLoopThread())
			shutdownInLoop();
		else {
			loop_->queueInLoop(std::bind(
				&TcpConnection::shutdownInLoop, shared_from_this()));
		}
	}
}

void TcpConnection::shutdownInLoop()
{
	loop_->assertInLoopThread();
	if (state_ != kDisconnected && !connChannel_->isWriting()) {
		if (::shutdown(connfd_, SHUT_WR) == -1)        // FIXME
			SYSERR("TcpConnection:shutdown()");
	}
}

void TcpConnection::forceClose()
{
	if (state_ != kDisconnected) {
		if (stateAtomicGetAndSet(kDisconnecting) != kDisconnected) {
			loop_->queueInLoop(std::bind(
				&TcpConnection::forceCloseInLoop, shared_from_this()));
		}
	}
}

void TcpConnection::forceCloseInLoop()
{
	loop_->assertInLoopThread();
	if (state_ != kDisconnected) {
		handleClose();
	}
}

int TcpConnection::stateAtomicGetAndSet(int newState)
{
	return __atomic_exchange_n(&state_, newState, __ATOMIC_SEQ_CST);
}


    //////////////////////////////////////////////
void TcpConnection::handleRead(){
	assert(state_ != kDisconnected);
	int savedErrno, n;
	n = inputBuffer_.readFd(connfd_, &savedErrno);
	  
	 if(n>0){ 
		//	std::string temp; 
		//  temp=inputBuffer_.retrieveAsString();
			messageCallback_(shared_from_this(),inputBuffer_);
		//	connChannel_->enableWriting();
	} 
	else if (n==0) {
		// 有触发,但是读到的是zero, 说明对端关闭了
          handleClose();
		  TRACE("\nTcpConnection::handleRead()---handlClose\n");
	}
	else {
		// 其它有错误应该怎么处理呢? 
	}
		
}
      


void TcpConnection::handleWrite()
{

	if (state_ == kDisconnected) {
		WARN("TcpConnection::handleWrite() disconnected, "
			"give up writing %lu bytes", outputBuffer_.readableBytes());
		return;
	}
	assert(outputBuffer_.readableBytes() > 0);
	assert(connChannel_->isWriting());
	ssize_t n = ::write(connChannel_->fd(), outputBuffer_.peek(), outputBuffer_.readableBytes());
	if (n == -1) {
		SYSERR("TcpConnection::write()");
	}
	else {
		outputBuffer_.retrieve(static_cast<size_t>(n));
		if (outputBuffer_.readableBytes() == 0) {
			connChannel_->disableWriting();
			if (state_ == kDisconnecting)
				shutdownInLoop();
			if (writeCompleteCallback_) {         // 如果已经写完了, writeCompleteCallback_;
				loop_->queueInLoop(std::bind(
					writeCompleteCallback_, shared_from_this()));
			}
		}
	}

}

void TcpConnection::handleClose() {

	loop_->assertInLoopThread();
	assert(state_ == kConnected ||
	state_ == kDisconnecting);
	state_ = kDisconnected;

     connChannel_->disableAll(); 

     if(removeConnection_) {
	  	 removeConnection_(shared_from_this());
	 }
    // FIXME :   else 没有removeConnection_ 那么会怎样, 只是 LOG<< xxx ??? 
}





void TcpConnection::connectEstablished()
{  	
	loop_->assertInLoopThread();     
	assert(state_ == kConnecting);
  
	DEBUG("A new connection has created\n");
	setState(kConnected);
	connChannel_->enableReading();
	connectionCallback_(shared_from_this());
}



void TcpConnection::destoryConn(){
	 // 上方的channel HandleEvent已经结束了, 所以要删除poll 的struct pollfd; 
	 setState(kDisconnected);
   	 connChannel_->deleteChanel();

}


void TcpConnection::stopRead() {
	loop_->runInLoop([this]() {
		if (connChannel_->isReading())
			connChannel_->disableReading();
	});
}

void TcpConnection::recoverRead() {
	loop_->runInLoop([this]() {
		if (!connChannel_->isReading())
			connChannel_->enableReading();
	});
}
