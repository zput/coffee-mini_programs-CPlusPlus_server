#pragma once
#include <string>


class XTcp {

public:

    void socketCreat();
    int socketBind();
    void socketListen( int member);
     XTcp  socketAccept();
   int  socketRecv(char *recvBuf, int recvSize);
//   int  socketRecv(char *recvBuf, int recvSize);
    int socketSend(const char *sendBuf, int ought_sendSize);
   void socketClose();
   
   bool socketConnect_client(const char * ip, const unsigned short port,int timeoutms=1000); 
   
   bool Connect(const char *ip, unsigned short port, int timeoutms = 1000);

   bool setBlock(bool isblock); 
   
   	XTcp();
   	~XTcp();
   	
private:
public:
	// In order to ensuring the flag=ip+port, so,the class member including the ip and port;
    std::string  ip;
    unsigned short port;
    
    // unique socket.
    int socket;
    
    
};
