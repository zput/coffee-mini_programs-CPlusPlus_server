#ifndef CHANNEL_H
#define CHANNEL_H

#include<functional>

namespace zxc_net {

class EventLoop;

class Channel {

	public:
	   typedef std::function<void ()> EventCallback;
	   
	   Channel(EventLoop * loop, int fd);
	   ~Channel();
	   
	   void handleEvent() ;
	   void deleteChanel();
	   void setReadCallback(const EventCallback & cb)
	    {  readCallback_ = cb ; }
	   void setWriteCallback(const EventCallback& cb)
	    {  writeCallback_ = cb; }  
	   void setErrorCallback (const EventCallback & cb) 
	    {  errorCallback_ = cb; }
	   void setCloseCallback (const EventCallback & cb) 
	    {  closeCallback_ = cb; }
	   
	   
	   // importance ??? get_handle(); ·µ»Øhandle ? 
	   int 	    fd() const { return fd_;}



	   int  events() const { return events_;}
	   void set_revents( int revents ) { revents_ = revents ;}
	   	    // for Poller
	   int index() { return index_; }
	   void set_index(int idx) {index_ = idx;}
		
		
       bool isNoneEvent() const 
				{ return events_ == kNoneEvent; }
	   bool isReading() const {
		   return (bool)(events_ & kReadEvent);
	   }
	   bool isWriting() const {
		   return (bool)(events_ & kWriteEvent);
	   }

		EventLoop * ownerLoop() {return loop_;}
		
	    void enableReading()  { events_ |= kReadEvent;     update(); }
		void disableReading() { events_ &=(~kReadEvent);   update(); }
		void enableWriting()  { events_ |= kWriteEvent;    update(); }
	    void disableWriting() { events_ &= (~kWriteEvent); update(); }
	    void disableAll()     { events_ &= kNoneEvent;     update(); }
	  
	private:	
	    void update();
	
	    static const int kNoneEvent;
		static const int kReadEvent;
		static const int kWriteEvent;
		
			/*	
				int isNoneEvent;
				int readEvent;
				int writeEvent;
				int errorEvent;
			*/				
		
	   
		const int fd_;
		EventLoop * loop_;
		int events_;
		int revents_;
		// used by find PollFds
		int index_;
		/*
			// for poller
			   int idx_;
		*/
		
		bool eventHandling_;
		
		EventCallback readCallback_;
		EventCallback writeCallback_;
		EventCallback errorCallback_;
		EventCallback closeCallback_;
   };
	
	
}
#endif
