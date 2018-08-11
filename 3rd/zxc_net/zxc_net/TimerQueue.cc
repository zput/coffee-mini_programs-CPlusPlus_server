

#include"TimerQueue.h"
#include"EventLoop.h"


			//#include"Timer.h"
			//#include"TimerStamp.h"

#include<functional>             // std::bind(  ) -----[]() {}
#include<sys/timerfd.h>
#include<strings.h>
#include<unistd.h>
#include<ratio>         // std::nano::den  ??? 


using namespace zxc_net;


namespace {
	 int timerfdCreate() {
		 int fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK |TFD_CLOEXEC );
		 if(fd == -1){
			//  SYSFATAL("timer_create()");			 
		 }
		 return fd;
		 
	 }
	
	  
	 void timerfdRead( int fd)  {
		 uint64_t val;
		 ssize_t n= read(fd, &val, sizeof(val));
		 if (n != sizeof(val))
			 printf("read  error \n");
		  //  ERROR("TIMERFDrEAD GET %LD, NOT %LU ", n, sizeof(val));
	 }
	 
	 
	 
	 	struct timespec durationFromNow( Timestamp when ) {
		   struct timespec ret;
		   Nanosecond ns = when -clock::now();
		   if(ns<1ms) ns=1ms;
		   
		   ret.tv_sec = static_cast<time_t>( ns.count() / std::nano::den   );
		   ret.tv_nsec = ns.count() % std::nano::den;
		   
		   return ret;
		
		
	}
	 
	 
	 void timerfdSet( int  fd, Timestamp when)  {
		 
		 
		 struct itimerspec oldtime, newtime;
		 bzero( &oldtime, sizeof(itimerspec));
         bzero(&newtime,  sizeof(itimerspec));		 
		 newtime.it_value =durationFromNow(when);
		 
		 int ret = timerfd_settime(fd, 0, &newtime, &oldtime);
		 if (ret == -1)
			 printf("write error \n");
		 //  SYSERR("timerfd_settime()");
		 
		 
	 }
	 
	
	

	
}






 TimerQueue::TimerQueue(EventLoop* loop )
   : loop_(loop),
     timerfd_(timerfdCreate() ),
	 timerfdChannel_(loop, timerfd_),
	 timerList_()

 { 
      loop_ ->assertInLoopThread();
	  timerfdChannel_.setReadCallback(
	       std::bind( &TimerQueue::handleRead, this) ); // Yes? 
		   
      
	  timerfdChannel_.enableReading();
    
    /*	
	 timerfd_=timer_create();
	 loop_(loop);
	 channel_timer(timerfd_,loop_);
	*/
}

 TimerQueue::~TimerQueue() {
	 // 里面没有new malloc 声明heap space , 这里不需要写什么东西吧.
	 ::close(timerfd_);
	 
	 for(TimerList::iterator it = timerList_.begin();
	     it != timerList_.end(); ++it) 
	 
	 {
		  delete it->second;  // 为什么要删除Timer * ??
		 
	 }
	 
	 
 }

 Timer*  TimerQueue::addTimer(const TimerCallback  & cb, 
	 Timestamp when, 
	 Nanosecond  interval) {
								
	 Timer * temp_timer =new Timer(std::move(cb), when, interval);
	// loop_->assertInLoopThread();
	 
	 loop_->runInLoop(
	         [=]() {
			 auto ret= timerList_.insert( {when, temp_timer});   // 这个返回来的是什么 ?
             assert(ret.second);			 
			
	         
			 if(timerList_.begin() == ret.first) 
				 timerfdSet(timerfd_,when); 
	      }
	 );
	 
	        /*			
				 timerList_.push_back(std::make_pair(time, temp_timer) );  // std::set 
						  // timerList_.emplace(Timer(cb, time, repeat));
				 if( (timerList_.begin())->second == temp_timer ) {  // * 跟 . 哪一个更 亲近些.   *(timerList_.begin())
					 // 这里应该怎么修改它 定时触发的时间?
					 timer_change() // ?? 
				 }
	        */
		return temp_timer;
 }
 
 
 void TimerQueue::handleRead (){
	  loop_->assertInLoopThread();
	  timerfdRead(timerfd_);
	  
	  Timestamp now(clock::now());
	  for(auto& e: getExpired(now) ) {
		    Timer* timer =e.second;
		    assert(timer->expired(now));
			
			if(!timer->canceled())
				 timer->run();
			if(!timer->canceled() && timer->repeat()) {
				timer->restart();
				
				e.first= timer->when();
				timerList_.insert(e);			
			}
			else delete timer;
	  }
	  if(!timerList_.empty()){
		  timerfdSet(timerfd_, timerList_.begin()->first);
		  
	  }
	 
	 
	 
	 /*
				Uint32_  temp;
				read(timerfd, temp, 1);  // 这里需要判断吗??
				
				std::vector<Timer *> temp_Timer_list;
				temp_Timer_list=getExpired( std::system_clock.now() );  // 对吗?? No		
				
				for(auto:e temp_Timer_list) {
					e->run();
				}	
     */				
  }
  
 std::vector<TimerQueue::Entry> TimerQueue::getExpired( Timestamp now) {
	
	Entry en(now+1ns, nullptr);
	std::vector<Entry> entries;
	
	auto end=timerList_.lower_bound(en);  // 为什么low_bound()只判断first???
	entries.assign(timerList_.begin(), end);  //  查看 assign() Function   
	timerList_.erase(timerList_.begin(), end);
	
	return entries;
	
	/*
	TimerList::iterator it=timerList_.low_bxxx(now);  // ??
	
	std::copy(timerList_.begin(), it, );  // 应该是移动的 . 
	   // 移动到 std::vector<Timer *> 里面;
	std::vector<Timer *> return_value;
	
	for(auto e: return_value) {
		if(e->repeat >0 ) {
			// 这里重新加入里面, 为什么不复用 addTimer() ??
			// 用了一个restart ? 
		}    
		
	} 
	 */
 }
 
 
 
 /*
 
 void  TimerQueue::restart( Timer timer) {
	 
	 
 }
 
 */
 
 
 
 
 
