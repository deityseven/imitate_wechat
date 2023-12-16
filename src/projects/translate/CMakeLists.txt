project(translate)

#C++标准 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TRANSLATE_SRC
	translate.h
	translate.cpp
)

set(SRCS
	${TRANSLATE_SRC}
)

#筛选显示
source_group(translate FILES ${TRANSLATE_SRC})

#包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR}
					${CMAKE_SOURCE_DIR}/external
					${CMAKE_SOURCE_DIR}/src/projects/util
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
	util
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

#共享库
add_library(${PROJECT_NAME} STATIC ${SRCS})

#链接库
target_link_libraries(${PROJECT_NAME}
)
