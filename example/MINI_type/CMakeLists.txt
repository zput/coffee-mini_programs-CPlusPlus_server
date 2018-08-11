add_executable(MINI_type test.cc)

target_link_libraries(MINI_type zxc_net MiniProgram_http)

install(TARGETS MINI_type  DESTINATION bin)
install(FILES mime.types index.html duration.png    DESTINATION bin)



















