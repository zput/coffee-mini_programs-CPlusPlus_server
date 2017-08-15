#include <stdio.h>
#include <stdlib.h> 
                    //#include <string.h> 


#include "XTcp.h"
#include"XHTTP.h"

#ifdef _WIN32
#pragma warning(disable:4996)
#include <windows.h>
#pragma comment (lib,"ws2_32.lib")
#endif

//#include <iostream>
//#include <thread>
//using namespace std;


	  
int main(int argc, char** argv) 
{

//	#ifdef _WIN32
//	WSADATA ws;                          //  Windows Sockets Asynchronous
//	WSAStartup(MAKEWORD(2,2),&ws);
//	#endif 

//	//SOCKET sock;
//	

	
		XTcp socketMonitor;
		socketMonitor.socketCreat();
		socketMonitor.port=4443;
		if(argc>1) {
		  socketMonitor.port=atoi(argv[1]);  //argv[0] contained the name of main function;
		};
		 
        	printf("\n%d\n",socketMonitor.socket);
        	
        socketMonitor.socketBind();
        socketMonitor.socketListen(15);    //¡¡listen 10£¿£¿£¿
		 
		/*************************************** accept()***********************************/
		while(1) {
			     
				 XTcp socketConnect;
			//	 printf("\n------------------test_1111_thread---------------------\n");
				 socketConnect=socketMonitor.socketAccept();  
			//     printf("\n------------------test_2222_thread---------------------\n");
				 
			     //int sock_connect;   //int temp=sizeof(sockaddr); 
			                           //  socklen_t T=sizeof(sockaddr); 
				//sock_connect=accept(sock1,(sockaddr*)&cliAddr,&T);                 //(sockaddr*)&cliAddr, &temp); 
				//if(sock_connect<0 ) { break;}
				
				printf("Creat a new socket [%d]\n",socketConnect.socket);
//				
//				char * p=inet_ntoa(cliAddr.sin_addr); 
				printf("ClientAddress ip addr:>%s   port:>%d",socketConnect.ip.c_str(), socketConnect.port ); 

// important thread;;;
				
/**********************************************************************************/
				XHTTP * th=new XHTTP();               //	tcpThread tThread;
				th->socketConnect_1=socketConnect;
				
				    thread sth(&XHTTP::main_xhttp, th);   // beginning this thread;
													 //thread sth( function_reference, an object);
					
				    sth.detach();
				//	sth.join();
			//		printf("\n------------------test_3333_thread---------------------\n");

 	    }   ////end while





	   //	printf("[%d]\n",sock1);
		
     	socketMonitor.socketClose();
     	
	#ifdef _WIN32
	WSACleanup();
	#endif
	
	return 0;
}
