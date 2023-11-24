project(base64)

#C++标准 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
	base64.h
	base64.cpp
)

set(SRCS
	${SRC}
)

#筛选显示
source_group(src FILES ${COMMON_SRC})

#指定编译字符集
if(WIN32)
add_compile_options(/utf-8)
endif(WIN32)

#共享库
add_library(${PROJECT_NAME} STATIC ${SRCS})
