#include <iostream>
#include "BondServiceListener.hpp"
#include "BondTradeBookingService.hpp"
#include "BondPositionServce.hpp"
#include "BondPricingService.hpp"





int main() {

    // Test the workflow
    // Create Bond
    // 2Y US T-Bond
    date maturityDate(2018,Dec,5);
    Bond b1("ABCDE01W",CUSIP,"T",3.25,maturityDate);

    Trade<Bond> T1(b1,"T1ID","BOOK",1000,BUY);



    std::cout << "Hello, World!" << std::endl;
    return 0;
}