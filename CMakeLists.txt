cmake_minimum_required(VERSION 3.16)
project(iowe)

string(TOLOWER ${PROJECT_NAME} EXECUTABLE)

set(CMAKE_CXX_STANDARD 17)

include_directories(
		${PROJECT_SOURCE_DIR}/include
                .
)
 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}../bin)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB NESTEDSOURCES ${PROJECT_SOURCE_DIR}/src/*/*.cpp)
file(GLOB NESTEDSOURCES2 ${PROJECT_SOURCE_DIR}/src/*/*/*.cpp)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)


set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(${EXECUTABLE} ${SOURCES} ${NESTEDSOURCES} ${NESTEDSOURCES2} ${HEADERS})
