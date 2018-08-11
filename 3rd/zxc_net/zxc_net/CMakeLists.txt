# set(SOURCE_FILES
        # EventLoop.cc EventLoop.h
        # EPoller.cc EPoller.h
        # Channel.cc Channel.h
        # Logger.h Logger.c
        # noncopyable.h
        # Acceptor.cc Acceptor.h
        # InetAddress.cc InetAddress.h
        # TcpConnection.cc TcpConnection.h
        # Callbacks.h
        # TcpServerSingle.cc TcpServerSingle.h
        # TcpServer.cc TcpServer.h
        # Buffer.h Buffer.cc
        # ThreadPool.cc ThreadPool.h
        # Connector.cc Connector.h
        # TcpClient.cc TcpClient.h
        # CountDownLatch.h
        # EventLoopThread.cc EventLoopThread.h
        # TimerQueue.cc TimerQueue.h
        # Timer.h
        # Timestamp.h
        # )

include_directories( ${PROJECT_SOURCE_DIR}/zxc_net )	
		
aux_source_directory(.  SOURCE_FILES)	
		
add_library(zxc_net STATIC ${SOURCE_FILES})    
target_link_libraries(zxc_net pthread)

                     # 在build.sh定义了安装目录, 
					 # [# DCMAKE_INSTALL_PREFIX=../Release-install]/lib or /include
install(TARGETS zxc_net DESTINATION lib)

#######################################
#######################################
set(HEADERS
        Accept.h
        Buffer.h
        Callbacks.h
        Channel.h
        EventLoop.h
        EventLoopThread.h
        EventLoopThreadPool.h
	    InetAddress.h	
        Logger.h
		Poller.h
	    TcpConnection.h
        TcpServer.h
		TcpServerMulti.h
		ThreadPool.h
	    Timer.h
        TimerQueue.h
        Timestamp.h	

        )
		
#   Connector.h   CountDownLatch.h     noncopyable.h    TcpClient.h

		
install(FILES ${HEADERS} DESTINATION include)





