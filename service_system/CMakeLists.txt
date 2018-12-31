cmake_minimum_required(VERSION 3.12)
project(service_system)

set(CMAKE_CXX_STANDARD 14)

add_executable(service_system main.cpp constants.h request.cpp request.h queues.cpp queues.h flow_request.cpp flow_request.h utils.cpp utils.h)