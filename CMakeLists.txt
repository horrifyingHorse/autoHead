cmake_minimum_required(VERSION 3.10)

project(autoHead)
#include_directories(${PROJECT_SOURCE_DIR}/utils)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")


file(GLOB SOURCES "${SRC_DIR}/*.cpp")

message(STATUS "SOURCES: ${SOURCES}")

add_executable(autoHead ${SOURCES})
