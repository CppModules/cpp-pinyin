project(Test)

#file(GLOB_RECURSE _src *.h *.cpp)
include_directories(../include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${CMAKE_BINARY_DIR}/../../build/libcpp-pinyin.a
)

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND
#        ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_CURRENT_SOURCE_DIR}/testData
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>/testData
#)