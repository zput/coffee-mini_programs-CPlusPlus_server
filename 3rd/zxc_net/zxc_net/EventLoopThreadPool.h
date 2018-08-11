
#ifndef EVENTLOOPTHREADPOOL_H
#define EVENTLOOPTHREADPOOL_H

#include"EventLoopThread.h"
#include<vector>



namespace zxc_net {
	class EventLoop;
	class EventLoopThread;

	class EventLoopThreadPool {
	public:

		EventLoopThreadPool(EventLoop * loop,int threadNumber)
			:baseLoop_(loop), threadNumber_(threadNumber), round_robin_(0){
		
		}
		~EventLoopThreadPool() {
		
		
		}

		void start();


		EventLoop*  getOneLoop();

	private:
		std::vector<EventLoop *> loops_;
		EventLoop*  baseLoop_;
		int threadNumber_;
		int round_robin_;
	};

}

#endif  // end EVENTLOOPTHREADPOOL_H
