


#include"Channel.h"
#include"EventLoop.h"

#include <sstream>
#include <poll.h>

/*
using namespace [ns] 表示命名空间 [ns] 下所有的域变成可见的。

如果是using [ns]的话，则只有ns是本身是可用的。对于ns下的域仍然必须
使用 ns.xxx 
*/



using namespace zxc_net;

	const int Channel::kNoneEvent =0;
	const int Channel::kReadEvent = POLLIN |POLLPRI;
	const int Channel::kWriteEvent = POLLOUT;

	

	Channel::Channel( EventLoop * loop, int fd)
	 : fd_(fd), 
	   loop_(loop),
	   events_(0),
	   revents_(0),
	   index_(-1),
	   eventHandling_(false)
	{	
	}

	Channel::~Channel() 
	{
		  assert(!eventHandling_);
	}

	void Channel::update() {
		loop_->updateChannel(this);
	}



 
    void Channel::handleEvent() {
       eventHandling_ = true;

	   if(revents_ & POLLNVAL ) {
		  printf("error\n");
	  }  
	    // 没有POLLIN , 但是有 POLLHUP . 
	  if ((revents_ & POLLHUP) && !(revents_ & POLLIN)) {
       // LOG_WARN << "Channel::handle_event() POLLHUP";
        if (closeCallback_) closeCallback_();
      }
	  if(revents_ & (POLLERR | POLLNVAL) ) {
		   if( errorCallback_) 
			   errorCallback_(); 
	  }
	  if( revents_ &(POLLIN |POLLPRI |POLLRDHUP) ) {
		  if(readCallback_) 
			  readCallback_();
	  }	
	  if(revents_ & POLLOUT) {
		  if(writeCallback_) 
			  writeCallback_();
	  }	
	 eventHandling_ = false;
	 
   }

 void Channel::deleteChanel(){
	  loop_->deleteChannel(this);
	 	 
 }
 