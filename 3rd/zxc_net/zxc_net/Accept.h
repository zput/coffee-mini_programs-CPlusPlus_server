
#ifndef ACCEPT_H
#define ACCEPT_H

#include"Callbacks.h"

namespace zxc_net{
	
	
	class InetAddress;
	class Channel;
	class EventLoop;
	
	class Accept{
	     public:
		   Accept(EventLoop* loop, const InetAddress* address);
		   ~Accept();
		
		  void handleRead();
		
			
		    void setNewconnectionCallback(NewconnectionCallback  cb ){
				newconnectionCallback_ = cb;
			}
		
		    void setMessageCallback(MessageCallback cb) {
			    messageCallback =cb;	   
		    }

		    
		
		private:
		    NewconnectionCallback  newconnectionCallback_;
			MessageCallback  messageCallback;
	     
		
		private:
		    EventLoop* loop_;
		    const  InetAddress* address_;
		    int acceptfd_;
            Channel* acceptChannel_;
            			 
		
	};
	
	
}




#endif
