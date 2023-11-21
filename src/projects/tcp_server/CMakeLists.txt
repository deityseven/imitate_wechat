project(tcpserver)

#C++标准 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CLIENT_SRC
	server.h
	server.cpp
)

set(HANDLES_SRC
)

set(SRCS 
	${HANDLES_SRC}
	${CLIENT_SRC}
)

#筛选显示
source_group(server FILES ${CLIENT_SRC})
source_group(handles FILES ${HANDLES_SRC})

#包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR}
					${CMAKE_SOURCE_DIR}/external
					${CMAKE_SOURCE_DIR}/external/spdlog/include
					${CMAKE_SOURCE_DIR}/external/asio/include
					${CMAKE_SOURCE_DIR}/src/projects
)

#库目录
link_directories(
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

#指定编译字符集
if(WIN32)
add_compile_options(/utf-8)
endif(WIN32)

if(WIN32)
add_definitions(-D_WIN32_WINNT=0x0601)
endif(WIN32)

#预编译宏
#add_definitions(XXXX)

#链接静态库
link_libraries(
    spdlog
)

if(WIN32)
#链接库
link_libraries( 
)
endif(WIN32)

if(UNIX)
#链接库
link_libraries( 
) 
endif(UNIX)

#可执行文件
add_library(${PROJECT_NAME} STATIC ${SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${output_dir}/bin/${CMAKE_CFG_INTDIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_ENVIRONMENT "Path=$(Path);${CMAKE_PREFIX_PATH}/bin")

target_compile_definitions(${PROJECT_NAME} PUBLIC ASIO_STANDALONE)

#链接动态库
target_link_libraries(${PROJECT_NAME}
)
