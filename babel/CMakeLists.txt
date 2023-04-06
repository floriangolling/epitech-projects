#DO NOT TOUCH
cmake_minimum_required(VERSION 3.19)
project(babel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_CXX_STANDARD 17)
set(CONAN_CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include(${CMAKE_BINARY_DIR}/../build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
#set(CONAN_DISABLE_CHECK_COMPILER True)
conan_basic_setup()
include_directories(${CMAKE_INCLUDE_PATH})

find_package(portaudio REQUIRED)
find_package(opus REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
#DO NOT TOUCH

#YOU CAN TOUCH
set (SERVER
        src/server/main_server.cpp
        src/server/ServerTCP.cpp
        src/server/ConnectionTCP.cpp
        src/server/Database.cpp
        src/common/PacketDecoder.cpp
        src/common/PacketEncoder.cpp)

set (CLIENT
        src/client/Core/core.cpp
        src/client/GUI/GraphLib/QtGraphic.cpp
        src/client/GUI/Pages/ipPage/IpPage.cpp
        src/client/GUI/Pages/Login/loginPage.cpp
        src/client/GUI/Pages/Register/registerPage.cpp
        src/client/GUI/Pages/Profile/profile.cpp
        src/client/GUI/Window/window.cpp
        src/client/Network/Qclient.cpp
        src/client/main.cpp
        src/common/PacketDecoder.cpp
        src/common/PacketEncoder.cpp
        src/client/Audio/Opus.cpp
        src/client/Audio/audio.cpp)


#YOU CAN TOUCH

#DO NOT TOUCH
add_executable(babel_server
        ${SERVER})
add_executable(babel_client
        ${CLIENT})

target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui)
target_link_libraries(babel_server ${CONAN_LIBS})

if (WIN32)
    target_link_libraries(babel_client portaudio_x64)
endif()

file(GLOB BUILD_DEPENDENCY "build_dependency/*")

file(COPY ${BUILD_DEPENDENCY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#DO NOT TOUCH