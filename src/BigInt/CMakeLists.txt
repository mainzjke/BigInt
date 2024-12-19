set(TARGET bigint)

file (GLOB_RECURSE FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
                         ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(${TARGET} ${FILES})

target_link_libraries(${TARGET})
target_include_directories(${TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/include)
