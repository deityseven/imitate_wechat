project(configfile)

#C++标准 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PARSER_SRC
	./parser_builder/parser/config_file_content_parser_handle.h
    ./parser_builder/parser/config_file_content_parser_handle.cpp
    ./parser_builder/parser/config_file_content_parser_handle_builder.h
    ./parser_builder/parser/config_file_content_parser_handle_builder.cpp
    ./parser_builder/parser/config_file_content_parser.h
	./parser_builder/parser/config_file_content_parser.cpp
    ./parser_builder/parser/ini_parser_handle.h
    ./parser_builder/parser/ini_parser_handle.cpp
    ./parser_builder/parser/json_parser_handle.h
    ./parser_builder/parser/json_parser_handle.cpp
    ./parser_builder/parser/xml_parser_handle.h
    ./parser_builder/parser/xml_parser_handle.cpp
)

set(BUILDER_SRC
	./parser_builder/builder/config_file_content_builder_handle.h
    ./parser_builder/builder/config_file_content_builder_handle.cpp
    ./parser_builder/builder/config_file_content_builder_handle_builder.h
    ./parser_builder/builder/config_file_content_builder_handle_builder.cpp
    ./parser_builder/builder/config_file_content_builder.h
	./parser_builder/builder/config_file_content_builder.cpp
    ./parser_builder/builder/ini_builder_handle.h
    ./parser_builder/builder/ini_builder_handle.cpp
    ./parser_builder/builder/json_builder_handle.h
    ./parser_builder/builder/json_builder_handle.cpp
    ./parser_builder/builder/xml_builder_handle.h
    ./parser_builder/builder/xml_builder_handle.cpp
)

set(CONFIG_SRC
    config_file.h
    config_file.cpp
)

set(SRCS
	${CONFIG_SRC}
	${PARSER_SRC}
	${BUILDER_SRC}
)

#筛选显示
source_group(configfile FILES ${CONFIG_SRC})
source_group(parser FILES ${PARSER_SRC})
source_group(builder FILES ${BUILDER_SRC})

#包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR}
					${CMAKE_SOURCE_DIR}/external
					${CMAKE_SOURCE_DIR}/external/pugixml/include
					${CMAKE_SOURCE_DIR}/src/projects/common
					${CMAKE_SOURCE_DIR}/src/projects/util
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

link_libraries(
    pugixml
    util
)

#共享库
add_library(${PROJECT_NAME} STATIC ${SRCS})

#链接库
target_link_libraries(${PROJECT_NAME}
)
