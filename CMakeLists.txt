cmake_minimum_required(VERSION 3.14)

project(libjpeg-turbo-playground)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(libjpeg-turbo 2.1.3 EXACT REQUIRED PATHS "${LIBJPEG_TURBO_ROOT}/lib/cmake/libjpeg-turbo")

# SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -Wl,--subsystem,windows")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(${PROJECT_NAME} 
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} libjpeg-turbo::turbojpeg-static)