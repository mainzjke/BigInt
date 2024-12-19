set(TARGET test.e)
file (GLOB_RECURSE TEST-FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
                                ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_executable(${TARGET} ${TEST-FILES})
target_include_directories(${TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${TARGET} bigint)

