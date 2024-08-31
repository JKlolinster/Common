cmake_minimum_required(VERSION 3.5)

project(CommonDemo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(LIBNAME "Common")
set(LIBINSTALLPATH ${PROJECT_SOURCE_DIR}/install)

set(spdlog_DIR "E:\\deps\\spdlog\\install\\lib\\cmake\\spdlog")

find_package(spdlog REQUIRED CONFIG)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE HEADER include/*.h)


add_library(${LIBNAME} SHARED ${SRC} ${HEADER})
message(STATUS "HEADER: ${HEADER}")
message(STATUS "SRC: ${SRC}")
target_link_libraries(${LIBNAME} PRIVATE spdlog::spdlog)

include(GenerateExportHeader)
generate_export_header(${LIBNAME} BASE_NAME ${LIBNAME})
file(COPY ${PROJECT_SOURCE_DIR}/build/${LIBNAME}_export.h DESTINATION ${PROJECT_SOURCE_DIR}/include)

install(TARGETS ${LIBNAME}
    LIBRARY DESTINATION ${LIBINSTALLPATH}/lib
    ARCHIVE DESTINATION ${LIBINSTALLPATH}/lib
    RUNTIME DESTINATION ${LIBINSTALLPATH}/bin)

install(FILES ${HEADER} DESTINATION ${LIBINSTALLPATH}/include)

add_executable(${PROJECT_NAME} 
    main.cpp)


target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBNAME})


install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/install_exe)

install(TARGETS ${LIBNAME}
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/install_exe)

install(TARGETS ${LIBNAME}
    RUNTIME DESTINATION E:\\projects\\depdlls)
