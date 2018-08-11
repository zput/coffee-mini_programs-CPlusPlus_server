
#ifndef TIMER_H
#define TIMER_H

#include "Callbacks.h"
#include"Timestamp.h"
#include<assert.h>


namespace zxc_net {
	
	class Timer {
		public:
		   Timer(TimerCallback cb,Timestamp when, Nanosecond interval)
           : cb_(cb),
		     when_(when),
			 interval_(interval)  
		   {
			 // if(interval!=0) repeat_= true;   
			 // else  repeat_=false;
			 repeat_=interval_ > Nanosecond::zero();
			 
			  canceled_=false; 
		   }
		   ~Timer () {
			   
			   
		   }
		   void run() {
			   if(cb_) cb_();
			   
		   }
		   bool repeat() const { 
		       return repeat_;
		   }
		bool expired( Timestamp now) const {
			   return now >= when_;
			
		}   
		Timestamp when() const  {
			return when_;
			
		}
		   void restart() {
			    when_+=interval_; //???              ---Timestamp type  Nanosecond type---

		   } 
		   
		void cancel() {
			assert(!canceled_);
			canceled_=true;
		}          
		   bool canceled() {
			   return canceled_;
		   }
		   
		
		private:
		  TimerCallback cb_;
		  Timestamp when_;
		  Nanosecond interval_;
		  bool repeat_;
		  bool canceled_;
		
		
	};
	
	
	
	
}


#endif