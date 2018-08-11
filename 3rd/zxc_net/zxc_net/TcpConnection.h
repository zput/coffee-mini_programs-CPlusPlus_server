#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H


#include"Callbacks.h"
#include"Buffer.h"
#include"InetAddress.h"
#include  <any>
namespace zxc_net{

class EventLoop;
class Channel;
class Buffer;
class InetAddress;

class TcpConnection: public std::enable_shared_from_this<TcpConnection>  {
	public:
		
			TcpConnection(EventLoop* loop, int conn,
				const InetAddress& local,
				const InetAddress& peer);

           ~TcpConnection ( );
		
		    void setMessageCallback(MessageCallback cb) {
			    messageCallback_ =cb;	   
		    }
		    void setWriteCallback(WriteCallback cb ) {
			    writeCallback_ = cb;
		    }
			void setConnectionCallback(ConnectionCallback cb ) {
			    connectionCallback_ = cb;
		    }


			void setHightWaterCallback(const HighWaterMarkCallback& cb, size_t mark) {
				highWaterMarkCallback_ = cb; highWaterMark_ = mark;
			}
			void setWriteCompleteCallback(const WriteCompleteCallback& cb)
			{
				writeCompleteCallback_ = cb;
			}

			void setremoveConnectionCallback(removeConnectionCallback cb ) {
			    removeConnection_ = cb;
		    }

			void connectEstablished();
			void destoryConn();	

			EventLoop* getLoop() { return loop_;  };
			bool connected()    const{ return state_ == kConnected; }
			bool disconnected() const{ return state_ == kDisconnected;}

			const InetAddress& local() const
			{
				return local_;
			}
			const InetAddress& peer() const
			{
				return peer_;
			}

			std::string name() const
			{
				return peer_.toIpPort() + " -> " + local_.toIpPort();
			}

	  public: 
		  void send(Buffer& buffer);
		  void send(const std::string& message);
		  void shutdown();
		  void forceClose();

		  void recoverRead();
		  void stopRead();


////////////////////for http////////////////
	 public:
		void setContext(const std::any& context){context_ = context; }
		const std::any&  getContext() const{return context_;}
		std::any*  getMutableContext(){ return &context_; }


	  private:
		void sendInLoop(const std::string& message);
		void shutdownInLoop();
		void forceCloseInLoop();

		void handleRead();
		void handleWrite();
		void handleClose();

		int stateAtomicGetAndSet(int newState);

	  private:
		   enum StateE { kConnecting, kConnected, kDisconnecting, kDisconnected, };
            void setState(StateE s) {
				state_=s;
			}
			
	  private:
	      		  
		  MessageCallback  messageCallback_;
          WriteCallback    writeCallback_;
		  ConnectionCallback connectionCallback_;
	      removeConnectionCallback  removeConnection_;
		  WriteCompleteCallback   writeCompleteCallback_;
		  HighWaterMarkCallback  highWaterMarkCallback_;

		  size_t highWaterMark_; 
      private:
			EventLoop * loop_;

            int connfd_;
            Channel* connChannel_;	
            char* readBuff;
            char* writeBuff;	
            Buffer inputBuffer_;			  
	        Buffer outputBuffer_;
			StateE state_;
	
			InetAddress local_;
			InetAddress peer_;

			std::any  context_;
};	

}

#endif

