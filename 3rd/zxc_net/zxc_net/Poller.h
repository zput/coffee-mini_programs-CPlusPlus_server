#ifndef POLLER_H
#define POLLER_H

#include<vector>
#include<map>



struct pollfd;

namespace zxc_net {

class Channel;
class EventLoop;

class Poller {
	  
  public:
      
      Poller(EventLoop * p);
      ~Poller();
  
	  typedef std::vector<Channel *> ChannelList;
	  
	  void updateChannel(Channel *);
	  void deleteChannel(Channel *);
	  void  poll( int timeoutMs, ChannelList *activeChannels);
	 
	  
	
  private:
      void assertInLoopThread() ;
	  void fillActiveChannels(int numEvents,
	                         ChannelList * activeChannels) const;
	  
	  
	typedef  std::vector<struct pollfd> PollFdList;
	typedef  std::map<int,Channel* >   ChannelMap;
	PollFdList pollFds_;
    ChannelMap  channels_;
	
	EventLoop *  ownerLoop_;
	
};	
	
	
	
}

#endif






//   ---------------------

/*



1,   类型名卡头第一个字母用大写.


2,   在typedef 的定义中, 在每个不同的
      类都要重新再次定义一遍.
 
      Question: 有些它是在上面,有些它是在上面
	  在下面, 这是用什么规则的.
	  是自己类的, 或者是其他类就在上面吗

	  

*/

































