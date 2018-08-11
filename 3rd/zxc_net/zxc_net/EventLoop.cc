#include"EventLoop.h"
#include"Poller.h"
#include"Channel.h"
#include"TimerQueue.h"
#include"Timestamp.h"

#include<assert.h>
#include<boost/scoped_ptr.hpp>
#include<stdio.h>
#include<poll.h>
#include <sys/types.h>
#include <sys/syscall.h>


using namespace zxc_net;

int getCurrentThreadId() {
	
	 return syscall(SYS_gettid);
	
}


static int createEventfd()
{
  int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if (evtfd < 0)
  {
   // LOG_SYSERR << "Failed in eventfd";
    abort();
  }
  return evtfd;
}


EventLoop::EventLoop ()
			: poller_(new Poller(this)),
			  threadId_( getCurrentThreadId()), 
			  looping_( false ), 
			  quit_(false),
			  
			  timerQueue_(new TimerQueue(this)),
			  wakefd_(createEventfd()),
			  eventfdChannel_(this ,wakefd_),
			  isInDoPendingFunction_(false)
			  

{
	 eventfdChannel_.setReadCallback([=](){ handleRead();}     );
	 eventfdChannel_.enableReading();
}

EventLoop:: ~EventLoop () {
	::close(wakefd_);
	
	
}


Timer* EventLoop::runAt(const Timestamp time, TimerCallback cb) {
	
	return timerQueue_->addTimer(std::move(cb), time /* zxc_net::clock::now() */, Millisecond::zero());
	
}

Timer* EventLoop::runAfter(const Second  duration, TimerCallback cb ) {
	return runAt(zxc_net::clock::now()+duration, cb);
}

Timer* EventLoop::runEvery(const Second  interval, TimerCallback cb) {
	 return timerQueue_->addTimer(std::move(cb), zxc_net::clock::now(), std::chrono::duration_cast<Millisecond>(interval) );
}



void EventLoop::loop() {
       const int mm=10000;
	   assertInLoopThread();

	   looping_ = true;    
	   quit_ = false;
		  while (!quit_)
       {
			channels_.clear();
			
			// return value is zero;
			poller_->poll(mm, &channels_);
			for(ChannelList::const_iterator i =channels_.cbegin();
				i!= channels_.cend();   i++) {	
				  (*i)->handleEvent();		
			}
			doPendingFunction();		
       }

	   //   ::poll(NULL, 0, 5);	 
	   looping_ = false;

}



void EventLoop::quit()
{
  quit_ = true;
  // wakeup();
}


	void  EventLoop::updateChannel( Channel * channel) {
		poller_->updateChannel(channel);		
	}
  
    void  EventLoop::deleteChannel(Channel * channel) {		
		poller_->deleteChannel(channel);	
	}




void EventLoop::assertInLoopThread() {	
	if(!isInLoop() ) {
		abortFromLoop();
	}
	
}

bool EventLoop::isInLoop () {	
	return threadId_ == syscall(SYS_gettid);
}

void  EventLoop::abortFromLoop() {
	printf(" not in this loop /n");		
}




////////////////////////////////-------------------------------------///////////////////////

void EventLoop::handleRead() {
	uint64_t val;
			// int number
	
	ssize_t n =::read(wakefd_,&val, sizeof val);
	       /*
			if(number<1) {
				// xxxxxxxxxxxxxxxxxxxxx;
			}
		   */
	if(n != sizeof val) {
		// LOG_ERROR <<"EventLoop::handleRead() reads"<<n<<" bytes instead of 8 ";
	}	   
			
}

void EventLoop::doPendingFunction(){   
   isInDoPendingFunction_ = true;
   std::vector<Functor> temp;
   
   {
	  // mutex_ 
	  //std::lock_guard<std::mutex> guard(mutex_);
	  
	  std::lock_guard<std::mutex> guard(mutex_);
	  temp.swap(pendingFunctor_);	   
   }
   
   for(auto& e:temp) {
	   e();         
   }
   isInDoPendingFunction_ = false ;
   
}



void EventLoop::queueInLoop(const Functor & function ){
	 assert(!isInLoopThread() );
	{ 
		//MutexLockGuard lock(mutex_);
		std::lock_guard<std::mutex> guard(mutex_);
		pendingFunctor_.push_back(function);
		DEBUG("Ready to send function to other thread\n");
	}
	 
	if(!isInLoopThread() || isInDoPendingFunction_) {
			// 由于doPendingFunctors()调用的Functor可能再
			// 调用queueInLoop(cb), 这时queueInLoop()就必须wakeup()
			// [因为,doPendingFunctors() 后面,如果循环没退出,那么又会poll(), 此时没有wakeup(),就可能不能立即跳出]
			//  否则这些新加的cb就不能被及时调用了.----同理在IO线程中调用Cabllback() Function时, 它的下一步就是
			// doPendingFunctors(), 就不存在不能立即调用的问题. 
	 	wakeUp(); 	 
	}
	 
}    

void EventLoop::runInLoop(const Functor& function) {
	    if(isInLoopThread()) {
			function();	
		} else {
			queueInLoop(function);
		}
}


 void EventLoop::wakeUp() {
	 uint64_t one =1;
	 ssize_t n = ::write(wakefd_,&one, sizeof(one));
     if(n != sizeof one) {
		//LOG_ERROR<<"EventLoop::wakeUp() writes " << n <<"bytes instead of 8";
	      printf("\n EventLoop::wakeUP error\n");
	}
	 
 }


/////////////////////////////////////////////////////////////////





