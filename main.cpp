#include <iostream>
#include "BondTradeBookingService.hpp"
#include "Global_variables_functions.hpp"
#include "DataGenerator.hpp"
#include "BondPricingService.hpp"
#include "BondMarketDataService.hpp"
#include "BondInquiryService.hpp"

#include <numeric>
#include <ctime>
#include <chrono>

int main() {

    // Add timer
    std::chrono::time_point<std::chrono::system_clock> start, end;
    // Start record time
    cout<<"Start computing and recording time.\n";
    start = std::chrono::system_clock::now();

    // Generate trades
    Generate_Trade();

    // Initialize global variables
    initialize_global_variables();

    ofstream file("booked_risk.txt");
    ofstream file2("price_record.txt");
    ofstream file3("executed_order.txt");    // Contained the executed order
    ofstream file_inquiry("inquiries_record.txt");
    ofstream file_stream("streaming_record.txt");

    ofstream file_allinq("allinquiries.txt");
    ofstream file_hist_stream("streaming.txt");
    ofstream file_exe("executions.txt");
    ofstream file_risk("risk.txt");

    // Flow data
    cout<<"Flow trade data to bond trade booking service\n";
    BondTradeConnector::create_instance()->FlowTradeData();


    // Generate price.txt
    int N=int(1e6);
    Generate_price(N);

    // Generate makadata.txt
    Generate_MarketData(N);

    // Generate inquries.txt
    Generate_inquiry_data();

    // File contains price data

    BondPricingServiceConnector::create_instance()->FlowPriceData();


    // Flow date to market data service
    cout<<"Flow market data to bond market data service\n";
    BondMarketDataConnector::create_instance()->FlowMarketData();

    cout<<"Flow inquiries data to bond inquiry service\n";
    BondInquiryServiceConnector::create_insatnce()->FlowInquiryData();


    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";


    return 0;
}