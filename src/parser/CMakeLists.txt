cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)


# SET AUTOMOC ON FOR UI FILES AND HEADER FILES
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(HEADER_LIST
        transformpayload.h)


target_sources(BsfApp
        PRIVATE
            transformpayload.cpp
        PUBLIC
            ${HEADER_LIST})
