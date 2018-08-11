#include <MiniProgram_http/HttpServer.h>
#include <MiniProgram_http/HttpRequest.h>
#include <MiniProgram_http/HttpResponse.h>
#include <MiniProgram_http/Util.h>

#include <zxc_net/EventLoop.h>
#include <zxc_net/Logger.h>

#include <iostream>
#include <map>
#include <string>
using namespace std;



void onRequest(const HttpRequest& req, HttpResponse* resp)
{
	DEBUG(" do work IN user's onRequest()\n");
	INFO("HttpResponse's path is %s\n",req.path().c_str() );

    string path=Util::ConstructPath(req.path());
    string extent=Util::GetExtent(path);

	INFO("path's %s ---extent is %s\n",  path.c_str(),extent.c_str());

    string contentType="";
    Util::GetContentType(extent,contentType);
    string content=Util::GetContent(path);
    if(content.empty())
    {
        resp->setStatusCode(HttpResponse::CODE_404);
        resp->setStatusMessage("Not Found");
    }
    else
    {
        resp->setBody(content);
        resp->setStatusCode(HttpResponse::CODE_200);
        resp->setStatusMessage("OK");
        resp->setContentType(contentType);
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
    HttpServer server(&loop, zxc_net::InetAddress(8000) );
    server.setHttpCallback(onRequest);
    server.setThreadNum(numThreads);
    server.start();
    loop.loop();
    return 0;
}
