set (HEADERS  Tool.h 
              parsing_from_weixinLittleP_data.h
			  mysql_communicate.h)

set (application_floor  Tool.h  Tool.cpp
                        parsing_from_weixinLittleP_data.h
                        parsing_from_weixinLittleP_data.cpp
						mysql_communicate.h
                        mysql_communicate.cpp )
						
# include_directories(  
				    # SYSTEM	"/usr/include")	
					
# include_directories(
                    # ${PROJECT_SOURCE_DIR}/example/MINI_type)		

include_directories(  
				    	"/usr/include")	
					
include_directories(
                    ${PROJECT_SOURCE_DIR}/example/MINI_type)						
					
link_directories(  "/usr/lib"  )					
					
add_library(application_floor_library  STATIC  ${application_floor} )
#target_link_libraries(application_floor_library   zxc_net  /usr/lib/x86_64-linux-gnu/libmysqlclient.a libpthread.a libm.a libz.a  libdl.a  )
target_link_libraries(application_floor_library   zxc_net  /usr/lib/x86_64-linux-gnu/libmysqlclient.so )


install(TARGETS application_floor_library  DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)



##################################################################################

include_directories(  
                    ${PROJECT_SOURCE_DIR}/example/MINI_type  )	
add_executable(MINI_type test.cc)
target_link_libraries(MINI_type zxc_net MiniProgram_http application_floor_library)

install(TARGETS MINI_type  DESTINATION bin)
install(FILES mime.types index.html duration.png    DESTINATION bin)




