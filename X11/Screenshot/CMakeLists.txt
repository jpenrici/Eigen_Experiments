cmake_minimum_required(VERSION 3.25)

project(Experiences LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    functions.h
)

find_package(X11 REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${X11_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})

link_directories(${X11_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen ${X11_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
