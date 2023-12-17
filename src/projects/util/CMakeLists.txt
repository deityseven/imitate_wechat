project(util)

#C++标准 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RANDOM_SRC
    random_util.hpp
)

set(PLATFORM_SRC
    platform_util.h
    platform_util.cpp
)

set(FILE_SRC
	file_util.h
	file_util.cpp
)

set(STRING_SRC
	string_util.h
	string_util.cpp
)

set(THREAD_SRC
	threadpool.hpp
)

set(SRCS
	${RANDOM_SRC}
	${THREAD_SRC}
	${STRING_SRC}
	${PLATFORM_SRC}
	${FILE_SRC}
)

#筛选显示
source_group(random FILES ${RANDOM_SRC})
source_group(thread FILES ${THREAD_SRC})
source_group(string FILES ${STRING_SRC})
source_group(platform FILES ${PLATFORM_SRC})
source_group(file FILES ${FILE_SRC})

#包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR}
					${CMAKE_SOURCE_DIR}/external
					${CMAKE_SOURCE_DIR}/src/projects/common
					E:\QT_Project\GenerateSystem\src\GenerateSystem
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
