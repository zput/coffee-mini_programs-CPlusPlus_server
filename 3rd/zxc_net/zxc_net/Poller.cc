

#include "Poller.h"
#include "EventLoop.h"
#include "Channel.h"
#include "Logger.h"
#include <errno.h>
#include <poll.h>
namespace zxc_net {
	
	
	Poller::Poller(EventLoop * p): ownerLoop_(p) {
		
		
		
	}
	
	Poller::~Poller() {
		
		
		
	}
	
		
	
	void    Poller::poll( int timeoutMs ,ChannelList * activeChannels) {
		assertInLoopThread();                          
	  	
		// or pollFds_.data()
		int numEvents = ::poll(&*pollFds_.begin(), pollFds_.size(), timeoutMs);
		
		
		if(numEvents > 0) {
			fillActiveChannels(numEvents, activeChannels);
			
		} else if (numEvents ==0 ) {			
			DEBUG("no thing--channels_ is %d \n",channels_.size());
			
		} else {
			printf("Poller error %d---%d\n",pollFds_.size(),errno);
			SYSERR("Poller::poll()");
		}
		// return now;
		return ; 
	}
	
	void Poller::fillActiveChannels(int numEvents, ChannelList * activeChannels)  const
	
	{
		int i= numEvents;
        for(PollFdList::const_iterator it=pollFds_.cbegin();
		     i>0 && it!= pollFds_.cend(); it++ ) {
			if(it->revents>0) {
				ChannelMap::const_iterator ch = channels_.find(it->fd);
				Channel * temp = ch->second;
				
				temp->set_revents(it->revents);
                activeChannels->push_back(temp);				
				i--;
			}
			
		}		
		
			
	}
	
	void Poller::updateChannel(Channel * channel) {
		// 移除的事情我不管
		if(channel->index() < 0) {
			// a new 
			struct pollfd temp;
			temp.fd = channel->fd();
			temp.events =static_cast<short> (channel->events());
			temp.revents =0;
 			
			pollFds_.push_back(temp);
			int idx = static_cast<int>(pollFds_.size())-1;
			
			channel->set_index(idx);

           ////////////////////////////////////////////////
		   // 添加到ChannelMap中;
		   channels_[temp.fd] = channel;
			
			
		} else{
			pollFds_[channel->index()].events = static_cast<short>(channel->events()); 
            pollFds_[channel->index()].revents =0;
			
			if( channel->isNoneEvent()) {	
				pollFds_[channel->index()].fd = -channel->fd()-1;   
			}			
		}
		
	}
	
    void  Poller::deleteChannel(Channel * channel) {
		  // std::map delete ???
		 if( pollFds_.size()-1 == ( channel->index())) {
			 pollFds_.pop_back();			 
			 
		 }else {
			 // 肯能存在, 非尾部的已经关闭, 尾部的也已经关闭(-1)
             // 此时就会出现   segment dump	
          /*			 
			 Channel* temp=channels_[pollFds_.back().fd];
			 if(temp==NULL){
				 temp=channels_.at(pollFds_.back().fd);
				 printf("\nPoller::deleteChannel%d\n",pollFds_.back().fd);
			 }
		  */
				 int channelAtEnd =pollFds_.back().fd;
				 std::swap(pollFds_[channel->index()],pollFds_.back());  // ???
				 if (channelAtEnd < 0) {
				  channelAtEnd = -channelAtEnd-1;
				 }
				 channels_[channelAtEnd]->set_index(channel->index());	 
				 pollFds_.pop_back();
			 
		 }   
		 
		 channels_.erase(channel->fd());  

	}
	
	
	
	
	  void Poller::assertInLoopThread() {
	   ownerLoop_ ->assertInLoopThread();
	  
	}

	
	
	
}