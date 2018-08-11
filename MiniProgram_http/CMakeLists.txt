
include_directories(${PROJECT_SOURCE_DIR}/MiniProgram_http ) 


aux_source_directory(.  SOURCE_FILES)	


add_library(MiniProgram_http STATIC  ${SOURCE_FILES})
target_link_libraries(MiniProgram_http zxc_net )


install(TARGETS MiniProgram_http DESTINATION lib)



set(HEADERS
        HttpContext.h
		HttpRequest.h
		HttpResponse.h
		HttpResponse.h	
        Util.h)
install(FILES ${HEADERS} DESTINATION include)











