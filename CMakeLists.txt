cmake_minimum_required(VERSION 3.6)
project(fall2016_9815_hw06)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/usr/local/boost")


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
        main.cpp
        BondTradeBookingService.hpp
        BondTradeRiskService.hpp
        BondTradePositionService.hpp

        BondPricingService.hpp

        DataGenerator.hpp Global_variables_functions.hpp BondMarketDataService.hpp BondExecutionService.hpp BondAlgoExecutionService.hpp BondStreamingService.hpp BondInquiryService.hpp BondAlgoStreamingService.hpp)
add_executable(fall2016_9815_hw06 ${SOURCE_FILES})