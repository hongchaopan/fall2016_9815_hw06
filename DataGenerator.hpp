//
// Created by Hongchao Pan on 12/17/16.
//

#ifndef FALL2016_9815_HW06_DATAGENERATOR_HPP
#define FALL2016_9815_HW06_DATAGENERATOR_HPP

#include <fstream>      // Output to file
#include <iostream>
#include <random>       // Random generator
#include <vector>
#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <cstddef>      // size_t


using namespace std;
using namespace boost::gregorian;

// 2Y, 3Y, 5Y, 7Y, 10Y, 30Y cusip
// Reference: https://www.treasurydirect.gov/instit/instit.htm
string cusips[]={
        "912828U40",    // 2Y notes
        "912828U73",    // 3Y notes
        "912828U65",    // 5Y notes
        "912828U57",    // 7Y notes
        "912828U24",    // 10Y notes
        "912810RU4"     // 30Y bonds
};

std::default_random_engine re;  // Random engine

// Random generator for double numbers between [3.0, 4.0]
uniform_real_distribution<double> uniD(3.0,4.0);

// Random generator for int numbers between [1, 3]
uniform_int_distribution<int> uniI(1,3);

void Generate_Trade(){
    // Output the file to csv file
    ofstream file("trades.txt");

    // Syntax of the trades: Two parts: Bonds and Trades
    // Columns: 1-8:
    // cusip, CUSIP, tickerID, coupon, TradeID, TRSY1/2/3, quantity, side
    // tickerID is "T"
    // Set the Maturity date separately


    file<<"cusip, CUSIP, T, Coupon(%), TradeID, TRSY1/2/3, quantity, side\n";
    for(int i=0; i<6; ++i){
        // 60 trades
        for(int j=i*10; j<(i+1)*10; ++j){
            file<<cusips[i]<<","<<"CUSIP"<<","<<"T"<<",";
            file<<uniD(re)<<","<<"T"<<j+1<<","<<"TRSY"<<uniI(re)<<","<<uniI(re)*(1e6)<<",";
            file<<(uniI(re)%2==1 ? "BUY":"SELL")<<endl;
        }
    }
    file.close();


}

string rand_to_fraction(int num){
    // Convert a int number to fraction notation
    int num1=num/256;
    int num2=num%256;
    int num3=num2/8;
    int num4=num2%8;

    string str1, str2, str3;
    str1=to_string(99+num1)+"-";
    str2 = std::to_string(num3);
    str3 = std::to_string(num4);

    if (num3 < 10) str2 = "0" + str2;
    if (num4 == 4)	str3 = "+";
    return str1 + str2 + str3;

}





void Generate_price(int N){
    // N: total size of prices

    ofstream file("prices.txt");
    cout<<"Create prices.txt"<<endl;

    file<<"cusip, mid, b/s offer"<<endl;
    for(int i=0; i<N-1; ++i){
        for(int j=0; j<6; ++j){
            file<<cusips[j]<<",";

            // Get the mid price
            int mid=rand()%(256*2-8)+4;
            file<<rand_to_fraction(mid)<<",";

            // Get the bid ask spread
            int osc=(rand()%3+2);

            string bs_offer="0-00";
            if(osc==4){
                bs_offer+="+";
            }
            else{
                bs_offer+=to_string(osc);
            }
            file<<bs_offer<<endl;

        }

    }
    cout<<"Creating prices.txt successful\n";
}

void Generate_MarketData(int N){
    // N: total size of order book

    ofstream file("marketdata.txt");
    file<<"cusip, bid1, quantity1, bid2, quantity2, bid3, quantity3, bid4, quantity4, bid5, quantity5"<<",";
    file<<"ask1, quantityS1, ask2, quantityS2, ask3, quantityS3, ask4, quantityS4, ask5, quantityS5\n";

    for(int i=0; i<N; ++i){
        for(int j=0; j<6; ++j){

            file<<cusips[j]<<",";

            // bid price and quantity

            int mid = rand() % (256 * 2 + 1);

            int bid=mid-1;

            for(int k=0; k<5;++k){

                // Output 5 bid price and quantity
                int quantity=int(1e6)*(k+1);
                file<<rand_to_fraction(bid)<<","<<quantity<<",";
                bid-=1;

            }
            int ask=mid+1;
            for(int k=0; k<5; ++k){
                // Output 5 ask price and quantity

                int quantity=int(1e6)*(k+1);

                file<<rand_to_fraction(ask)<<","<<quantity<<",";
                ask+=1;
            }

            file<<endl;

        }

    }

}


void Generate_inquiry_data(){
    ofstream file("inquiries.txt");

    file<<"cusip, price, side, quantity, state\n";

    for(int i=0; i<10; ++i){
        for(int j=0; j<6; ++j){
            file<<cusips[j]<<","<<"100"<<",";   // Price as 100

            // Get side by random generator
            // uniI(1,3)
            if(uniI(re)%2==0){
                file<<"BUY"<<",";
            }
            else{
                file<<"SELL"<<",";
            }
            file<<10000*(i+1)<<","<<"RECEIVED"<<endl;

        }


    }


}


#endif //FALL2016_9815_HW06_DATAGENERATOR_HPP
