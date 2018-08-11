

#include "EventLoopThreadPool.h"

using namespace zxc_net;

void EventLoopThreadPool::start() {

	for (int i = 0; i < threadNumber_; i++) {
		EventLoopThread* t = new EventLoopThread();
		loops_.push_back(t->startLoopInThread());

	}
}


EventLoop*  EventLoopThreadPool::getOneLoop() {
	EventLoop* temp = baseLoop_;
	if (loops_.empty() == 0) {   // empty()'s return is 1 or 0 ?
		temp = loops_[round_robin_];
		round_robin_++;
		if (round_robin_ == threadNumber_)
			round_robin_ = 0;
	}
	return temp;
}



