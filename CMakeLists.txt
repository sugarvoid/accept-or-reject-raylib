cmake_minimum_required(VERSION 2.8)
project( Game LANGUAGES CXX )
set( TARGET ${PROJECT_NAME} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )


set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )
set( HEADER_PATH "${PROJECT_SOURCE_DIR}/src/include" )
set( LIBRARY_PATH "${PROJECT_SOURCE_DIR}/lib/libraylib.a")

find_library(libraylib ${LIBRARY_PATH})


file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.h" )
file( GLOB_RECURSE HPPS2 "${HEADER_PATH}/*.hpp" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )


add_executable( ${TARGET} ${CPPS} ${HPPS} ${HPPS2})
target_link_libraries(${TARGET} ${LIBRARY_PATH})


#include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src/header)
#target_include_directories(GameOutput PUBLIC ${CMAKE_SOURCE_DIR}/include PUBLIC ${CMAKE_SOURCE_DIR}/src/header)

# Including directories for headers
# include_directories(
#     "${PROJECT_SOURCE_DIR}/include/" # Header files
#     "${PROJECT_SOURCE_DIR}/src/header/" # Header files in source directory
# )

target_include_directories(
    ${TARGET} PUBLIC ${INCLUDE_PATH} 
    ##GameOutput PUBLIC "${PROJECT_SOURCE_DIR}/src/header/"
    )

install( 
    TARGETS ${TARGET} 
    RUNTIME DESTINATION 
)
