#include <iostream>
//#include "BondTradeServiceListener.hpp"

//#include "BondTradeConnector.hpp"
//#include "BondTradePositionService.hpp"
//#include "BondPricingService.hpp"
//#include "BondTradeServiceListener.hpp"
//#include "BondPositionListener.hpp"
//#include "BondTradeConnector.hpp"
//#include "soa.hpp"
//#include "products.hpp"

#include "BondTradeBookingService.hpp"
//#include "BondTradePositionService.hpp"
//#include "BondTradeRiskService.hpp"


#include "Global_variables_functions.hpp"


#include "DataGenerator.hpp"

#include "BondPricingService.hpp"

#include "BondMarketDataService.hpp"

#include "BondInquiryService.hpp"

int main() {

    // Test the workflow

//    // Generate trades
    Generate_Trade();
//
    // Initialize global variables
    initialize_global_variables();
//
    ofstream file("booked_risk.txt");
    ofstream file2("price_record.txt");
    ofstream file3("executed_order.txt");    // Contained the executed order
    ofstream file_inquiry("inquiries_record.txt");
    ofstream file_stream("streaming_record.txt");

    ofstream file_allinq("allinquiries.txt");
    ofstream file_hist_stream("streaming.txt");
    ofstream file_exe("executions.txt");
    ofstream file_risk("risk.txt");

//    // Flow data
    BondTradeConnector::create_instance()->FlowTradeData();


    // Generate price.txt
//    int N=int(1e6);
//    Generate_price(N);
//
//    // Generate makadata.txt
//    Generate_MarketData(N);

//    // Generate inquries.txt
//    Generate_inquiry_data();

    // File contains price data

    BondPricingServiceConnector::create_instance()->FlowPriceData();


    // Flow date to market data service
    cout<<"Flow market data to bond market data service\n";
    BondMarketDataConnector::create_instance()->FlowMarketData();

    cout<<"Flow inquiries data to bond inquiry service\n";
    BondInquiryServiceConnector::create_insatnce()->FlowInquiryData();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}