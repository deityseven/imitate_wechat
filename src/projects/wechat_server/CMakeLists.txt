project(wechat_server)

#C++标准 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SERVER_SRC
	wechat_server.h
	wechat_server.cpp
)

set(MAIN_SRC
	main.cpp
)

set(SRCS 
	${MAIN_SRC}
	${SERVER_SRC}
)

#筛选显示
source_group(server FILES ${SERVER_SRC})
source_group(main FILES ${MAIN_SRC})

#包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR}
					${CMAKE_SOURCE_DIR}/external
					${CMAKE_SOURCE_DIR}/external/spdlog/include
					${CMAKE_SOURCE_DIR}/src/projects
					${CMAKE_SOURCE_DIR}/src/projects/common
)

#库目录
link_directories(
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

#指定编译字符集
if(WIN32)
add_compile_options(/utf-8)
endif(WIN32)

#预编译宏
#add_definitions(XXXX)

#链接静态库
link_libraries(
    common
    httpserver
    configfile
    spdlog
	mysqlclient
	libmysql
)

add_executable(${PROJECT_NAME} ${SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${output_dir}/bin/${CMAKE_CFG_INTDIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_ENVIRONMENT "Path=$(Path);${CMAKE_PREFIX_PATH}/bin")

#链接动态库
target_link_libraries(${PROJECT_NAME}
	libmysql
)
