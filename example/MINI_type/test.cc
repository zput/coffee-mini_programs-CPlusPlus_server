#include <MiniProgram_http/HttpServer.h>
#include <MiniProgram_http/HttpRequest.h>
#include <MiniProgram_http/HttpResponse.h>
#include <MiniProgram_http/Util.h>

#include <zxc_net/EventLoop.h>
#include <zxc_net/Logger.h>

#include <Tool.h>

#include <iostream>
#include <map>
#include <string>
using namespace std;



void onRequest(const HttpRequest& req, HttpResponse* resp)   
{                                   
	bool is_false=true;
	Tool tool;
	DEBUG(" do work IN user's onRequest()\n");                
	INFO("HttpResponse's path is %s\n",req.path().c_str() );      

	std::string path = req.path();
	auto it = std::find(path.begin()+1,path.end(),'/');  //FIXME

	if (it == path.end()) {
		resp->setStatusCode(HttpResponse::CODE_400);
		resp->setStatusMessage("Bad Request");
		return;
	}



	std::string is_client_or_backup(path.begin() + 1, it);
	int method_number = stoi( string(it+1,path.end()).c_str() );

	DEBUG(" is_client_or_backup:%s---method_number:%d\n", is_client_or_backup.c_str(), method_number );
	
	if (is_client_or_backup == "client") {
		std::string temp;
		switch (method_number) {
			case 1:  is_false = tool.client_1_handle_xhttp(req.getBody(), &temp);	 resp->setBody(temp);  break;
			case 2:  is_false = tool.client_2_handle_xhttp(req.getBody(), (req.getHeader("Content-Type") != string("")  )? req.getHeader("Content-Type"):req.getHeader("content-type")); break;
		
			case 3:  is_false = tool.client_3_handle_xhttp(req.getBody(), &temp);	 resp->setBody(temp);  break;

			case 4:  is_false = tool.client_4_handle_xhttp(req.getBody(), &temp);	 resp->setBody(temp);  break;
			default: {		
				ERROR("Request error \n");
				is_false = false; }
		}  //end switch
	} 
	else if (is_client_or_backup == "backup") {
            // FIXME   
	}
	else {
		ERROR("Request error \n");	
		is_false = false;
	}
	 
	resp->setCloseConnection(false);
    if(is_false == false)
    {
        resp->setStatusCode(HttpResponse::CODE_400);
        resp->setStatusMessage("Bad Request");
    }
    else
    {   
        resp->setStatusCode(HttpResponse::CODE_200);
        resp->setStatusMessage("OK");
        resp->setContentType("text/plain");
    } 
}






int main(int argc, char* argv[])
{
	setLogLevel(0);
    int numThreads = 0;
    if (argc > 1)
    {
	    //benchmark = true;
        numThreads = atoi(argv[1]);
    }

	zxc_net::EventLoop loop;
    HttpServer server(&loop, zxc_net::InetAddress(9020) );
    server.setHttpCallback(onRequest);
    server.setThreadNum(numThreads);
    server.start();
    loop.loop();
    return 0;
}
