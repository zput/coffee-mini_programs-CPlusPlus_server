
#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include<vector>
#include<memory>
#include<functional>
#include <sys/eventfd.h>
#include<sys/syscall.h>
#include<sys/types.h>


#include<boost/scoped_ptr.hpp>
#include <mutex>

#include"Callbacks.h"
#include"Channel.h"
#include"Timestamp.h"
#include"Logger.h"

namespace zxc_net 
{

class Poller ;
class Channel;
class Timer;
class TimerQueue;

//   timerCallback;

class EventLoop {
    public:
	typedef std::function<void()> Functor;
	    EventLoop();
		~EventLoop();
		
		void loop();
	
        void assertInLoopThread();

        bool isInLoop();
        void quit();
     	
	void updateChannel( Channel * ) ;
	void deleteChannel(Channel * );
    void runInLoop(const Functor& function);
    void queueInLoop(const Functor & function );
	
	
	Timer* runAt(const Timestamp time, TimerCallback cb);
	Timer* runAfter(const Second duration, TimerCallback cb );
	Timer* runEvery(const Second interval, TimerCallback cb) ;
	
	bool isInLoopThread() const { return threadId_ == syscall(SYS_gettid); }
	

	
	private:
	   void abortFromLoop();	
	   typedef std::vector<Channel *>  ChannelList;
      	
	   void handleRead();                
	   void doPendingFunction();
	                 //   void runInQueue(Functor); 
	   void wakeUp();
	   
	
	private:	
		ChannelList  channels_;	     // 这个是Poller::poll返回的参数返回的值. 
		boost::scoped_ptr<Poller> poller_;
		const pid_t threadId_;
		bool  looping_;
		bool quit_;
		
		
		std::shared_ptr<TimerQueue>  timerQueue_;
		
		
		const int wakefd_;
		Channel eventfdChannel_;              
		bool isInDoPendingFunction_;
		std::vector<TimerCallback> pendingFunctor_;
		std::mutex mutex_;
	
};


}

#endif





//--------------------------------------------
/*
/usr/include/boost/core/checked_delete.hpp: In instantiation of ‘void boost::checked_delete(T*) [with T = zxc_net::Poller]’:
/usr/include/boost/smart_ptr/scoped_ptr.hpp:82:30:   required from ‘boost::scoped_ptr<T>::~scoped_ptr() [with T = zxc_net::Poller]’
EventLoop.cc:17:63:   required from here
/usr/include/boost/core/checked_delete.hpp:32:47: error: invalid application of ‘sizeof’ to incomplete type ‘zxc_net::Poller’
     typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
                                               ^
1,注意一下命名空间， 和  #ifndef xxxxx


2,  //	boost::scoped_ptr<Poller> poller_; 的问题，应该是它，
RAII 它需要定义即初始化吗？ ， 所以报错。---没有在construct函数中设置?
		/usr/include/boost/core/checked_delete.hpp: In instantiation of ‘void boost::checked_delete(T*) [with T = zxc_net::Poller]’:
		/usr/include/boost/smart_ptr/scoped_ptr.hpp:82:30:   required from ‘boost::scoped_ptr<T>::~scoped_ptr() [with T = zxc_net::Poller]’
		EventLoop.cc:17:63:   required from here
		/usr/include/boost/core/checked_delete.hpp:32:47: error: invalid application of ‘sizeof’ to incomplete type ‘zxc_net::Poller’
			 typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
		
		---- 回答, 不是这样的, 我在头文件中定义了Poller class的
             定义,它就可以了.
			  class Poller {
				int a;
			  };

			  boost::scoped_ptr<Poller> poller_;
	

	3,  syscall(SYS_gettid) 
        #include <sys/types.h>
		#include <sys/syscall.h>	
	    而且linux的得到线程的PID, 没有库函数,
        只能调用系统自带的函数!		
											   
	4, #include <sys/types.h>
       #include <sys/syscall.h>										   
											   							   
											   
*/
