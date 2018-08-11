
#ifndef  EVENTLOOPTHREAD_H
#define  EVENTLOOPTHREAD_H


#include <mutex>
#include<thread>
#include <condition_variable>


namespace zxc_net {
	
    class EventLoop;

	
	class EventLoopThread {
         public:
		    EventLoopThread();
		    ~EventLoopThread();
		 	EventLoop*   startLoopInThread();
			
         private: 
		 	    void    threadFunctor() ;
		 
                std::mutex mutex_;
                EventLoop* loop_;
                std::condition_variable  cond_;
				std::thread thread_;
				
	};
		
}

#endif
