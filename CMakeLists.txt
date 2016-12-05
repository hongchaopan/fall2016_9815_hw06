cmake_minimum_required(VERSION 3.6)
project(fall2016_9815_hw06)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/usr/include/boost")
include_directories("/usr/include/Eigen")


set(SOURCE_FILES
        executionservice.hpp
        historicaldataservice.hpp
        inquiryservice.hpp
        marketdataservice.hpp
        positionservice.hpp
        pricingservice.hpp
        products.hpp
        riskservice.hpp
        soa.hpp
        streamingservice.hpp
        tradebookingservice.hpp
        main.cpp BondTradeBookingService.hpp BondServiceListener.hpp BondPositionServce.hpp BondPricingService.hpp BondConnector.hpp)
add_executable(fall2016_9815_hw06 ${SOURCE_FILES})