

#include"EventLoop.h"
#include"EventLoopThread.h"

using namespace zxc_net;


EventLoopThread::EventLoopThread():loop_(NULL) {
	
}



EventLoopThread::~EventLoopThread() {
	if(loop_!=NULL) {
		 loop_->quit();
		 thread_.join();
	}
	
	
}



EventLoop * EventLoopThread::startLoopInThread() {
	  
	  thread_=std::thread([this](){ this->threadFunctor();}  );
	  
	  {
		  //std::lock_guard<std::mutex>  lock1(mutex_);
		  std::unique_lock<std::mutex> lock1(mutex_);
		  while(loop_==NULL) {
			  cond_.wait(lock1);
		  }
	  }
	  
	  return loop_;
	
}

 void EventLoopThread::threadFunctor() {
	 EventLoop loop;
	 {
		 std::lock_guard<std::mutex> lock2(mutex_);
		 loop_=&loop;
	 }
	 cond_.notify_all();                          // 查一下 notify_all() and notify_all() 的区别. 
	 loop.loop();
 }
