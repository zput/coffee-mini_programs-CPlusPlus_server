#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "XTcp.h"

	
#ifdef _WIN32
#pragma warning(disable:4996)
#include <windows.h>
#pragma comment (lib,"ws2_32.lib")
#define  socklen_t int

#else
#include <sys/types.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>  
#include <fcntl.h>
#define closesocket close

#endif	
	
	
	
	XTcp::XTcp()
{
	#ifdef WIN32
		static bool first = true;
		if (first)
		{
			first = false;
			WSADATA ws;
			WSAStartup(MAKEWORD(2, 2), &ws);
		}
	#endif
}
XTcp::~XTcp()
{
}
	
/********************************************************************************************/	
	
void XTcp::socketCreat()
	{
	   	socket=::socket(AF_INET,SOCK_STREAM ,0);
		
	
		if(socket==-1) {
		   printf("It is failure to construct the socket");
		   //return -1;
		}
	   // return socket;
	
	}

    int XTcp::socketBind()
    {
	  	sockaddr_in serAddr;                           //	sockaddr serAddr;//SOCKADDR_IN serAddr;
	  	
		serAddr.sin_family=AF_INET;
		serAddr.sin_port=htons(port);
		serAddr.sin_addr.s_addr=htonl(0);
		
		int TEMP=::bind(socket, (sockaddr*)&serAddr, sizeof(sockaddr));
		if(TEMP) {
		   printf(" the failure about the bind"); 
		   //return -1; 
		} 
		else  
		printf("\nthe success about the bind,port:%d\n",port ); 
	    
	    return TEMP;
	}
    
    void XTcp::socketListen( int member)
    {
	   		
		/***************************************listen() and accept()******************************************/ 
		
		listen(socket,member); 

	}
    
  XTcp  XTcp::socketAccept()
    { 
              XTcp sock_connect;
              sockaddr_in cliAddr;  
	          socklen_t T=sizeof(sockaddr); 
	                                                   //unsigned int sock_connect;
			  sock_connect.socket=accept(socket,(sockaddr*)&cliAddr,&T);                 //(sockaddr*)&cliAddr, &temp); 
	          sock_connect.port=ntohs(cliAddr.sin_port);
	          sock_connect.ip=inet_ntoa(cliAddr.sin_addr);
	
	      return sock_connect;
	}
    
   int  XTcp::socketRecv(char *recvBuf, int recvSize)
    {
	
	   	//char buf[256] ={'\0'};
	   // printf("\nI am safe in second\n");
		int recvLen=recv(socket,recvBuf, recvSize, 0);
//	    if(recvLen<0||strcmp(recvBuf,"quit")==0) {
//		     return -1; 
//		} 
//					buf[recvlen] ='\0';
//				 	if(strcmp(buf,"quit")==0 )  {
//				 		char send_[256]="service has quitted successful";
//				 		send(sock_connect,send_,strlen(send_)+1,0);
//					    break; 
//				    }
	    
	    //recvBuf[recvLen] ='\0';
	    
	    return recvLen;		
}
    
 int  XTcp::socketSend(const char *sendBuf, int ought_sendSize)
    {
	       //SOCKET_ERROR==-1;
	                                                 //int sendLen=send(socket,"ok\n",4,0);
	                                                 
	                                   //  send(socket,sendBuf,strlen(sendBuf)+1,0);
	     	int sendedSize = 0;
			while (sendedSize != ought_sendSize)
			{
				int len = send(socket, sendBuf + sendedSize, ought_sendSize - sendedSize, 0);
				if (len <= 0)break;
				sendedSize += len;
			}
			return sendedSize;
	
	}
    
    void XTcp::socketClose()
    {
	 
	   closesocket(socket);
	
	}
    
bool XTcp::socketConnect_client(const char * ip, const unsigned short port,int timeoutms)
{
      sockaddr_in  serAddr;
      serAddr.sin_family=AF_INET;
      serAddr.sin_port=htons(port);
      serAddr.sin_addr.s_addr=inet_addr(ip);
	//  INADDR_ANY;
         if(setBlock(false)==false)  printf(" setBlock is fail\n");
         
         fd_set set;
      if( ::connect(socket,(sockaddr*) &serAddr,sizeof(serAddr))!=0) {
	     FD_ZERO(&set);
	     FD_SET(socket,&set);
	     
	     timeval tm;
	     tm.tv_sec=0;
	     tm.tv_usec=timeoutms*1000;
	     
	     if(select(socket+1,0,&set,0,&tm)<=0) {
			    printf("connection timeout or error");
			 
			    printf("connect the TCP service(ip:%s, port:%d) is failure,the reason is %s\n",ip, port, strerror(errno));
		        return -1;
		 } 
	   }
	    
	    setBlock(true );  // if connection is success, we need to set the zusai mode for the recv();
        printf("connect the TCP service(ip:%s, port:%d) is success\n",ip, port);
        return 0;


}


bool XTcp::Connect(const char *ip, unsigned short port, int timeoutms)
{
	//SERV_PORT;
	if (socket <= 0) socketCreat();
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ip);
	setBlock(false);
	fd_set set;
	if (connect(socket, (sockaddr*)&saddr, sizeof(saddr)) != 0)
	{
		FD_ZERO(&set);
		FD_SET(socket, &set);
		timeval tm;
		tm.tv_sec = 0;
		tm.tv_usec = timeoutms * 1000;
		if (select(socket + 1, 0, &set, 0, &tm) <= 0)
		{
			printf("connect timeout or error!\n");
			printf("connect %s:%d failed!:%s\n", ip, port, strerror(errno));
			return false;
		}
	}
	setBlock(true);
	printf("connect %s:%d success!\n", ip, port);
	return true;
}



 bool XTcp::setBlock(bool isblock)
 {
     if(socket<=0) return false;
     
    #ifdef  _WIN32 
		     unsigned long ul=0; //block;
		     if(!isblock) ul=1;//not block;   
		     
		     ioctlsocket(socket,FIONBIO,&ul);
    #else
            int flags=fcntl(socket,F_GETFL,0);        
            if(flags<0) return false;  // need to judge whether the function of fcntl has returned correctly (0 or 1)
            
            if(isblock==true) {
            	flags=flags&~O_NONBLOCK;
            	
            }
            else 
			    flags=flags|O_NONBLOCK;	
			    
		
   	     if(fcntl(socket,F_SETFL,flags)!=0)  return false;
    
    #endif

     return true;
 
 }


  
