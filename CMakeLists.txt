project(TCC-DYN)

add_executable(TCC-DYN-BIN src/main.c)
IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(TCC-DYN-BIN libdl.so libtcc.so)
ENDIF()
