#ifndef TIMERQUEUE_H
#define TIMERQUEUE_H

#include<set>
#include<vector>
#include <sys/timerfd.h>

#include<thread>  // c++11里面有 std::mutex ??

#include"Channel.h"
#include"Callbacks.h"
#include"Timer.h"            // --- class Timer ;   那么 class Timerstamp ???



namespace zxc_net {
  /*	
	typedef std::function<void ()> Callback
	
	class EventLoop;
	class Timer;
	class TimerStamp;  // ???
  */	

  	class EventLoop;
	class Timer;
  
	class TimerQueue {
		public:
		    TimerQueue(EventLoop * loop);
			~TimerQueue();
			
						//	void setReadCallback(TimerCallback cb) {   readCallback =cb; }
		    
			Timer* addTimer(const TimerCallback  & cb,  Timestamp when, Nanosecond interval);
		
		
		
		private:
			typedef std::pair<Timestamp,Timer *> Entry;
			typedef std::set<Entry> TimerList;
		
		    void handleRead();
		    std::vector<Entry> getExpired(Timestamp now);
						void reset(const std::vector<Entry>& expired, Timestamp now);

					//	bool insert(Timer * timer);
			
					//	void restart(Timer timer);   //  进行重复的repeat触发.
			
					//	TimerCallback readCallback;
	
        private:	
      //下面的这些也是有规律的排序, 在construction中的排序.		
			EventLoop * loop_;
			const int timerfd_;                          // const int 应该在哪里就绑定?
		    Channel timerfdChannel_;
		    

			TimerList timerList_;
					
	};
}

#endif 