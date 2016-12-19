//
// Created by Hongchao Pan on 12/17/16.
//

#ifndef FALL2016_9815_HW06_GLOBAL_VARIABLES_FUNCTIONS_HPP
#define FALL2016_9815_HW06_GLOBAL_VARIABLES_FUNCTIONS_HPP

#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <tuple>
#include "boost/algorithm/string.hpp"      // boost::split
#include "boost/date_time/gregorian/gregorian.hpp"
//#include "soa.hpp"
#include "products.hpp"
#include "positionservice.hpp"
#include "tradebookingservice.hpp"  // Trade
#include <map>
#include <utility>  // std::pair
#include "historicaldataservice.hpp"

using namespace std;
using namespace boost::gregorian;

HistoricalDataService *hist_service=HistoricalDataService::create_instance();


//enum Side { BUY, SELL };    // tradebookingservice.hpp

//enum BondIdType { CUSIP, ISIN };
//
//enum DayCountConvention { THIRTY_THREE_SIXTY, ACT_THREE_SIXTY };
//enum PaymentFrequency { QUARTERLY, SEMI_ANNUAL, ANNUAL };
//enum FloatingIndex { LIBOR, EURIBOR };
//enum FloatingIndexTenor { TENOR_1M, TENOR_3M, TENOR_6M, TENOR_12M };
//enum Currency { USD, EUR, GBP };
//enum SwapType { STANDARD, FORWARD, IMM, MAC, BASIS };
//enum SwapLegType { OUTRIGHT, CURVE, FLY };
//
//enum ProductType { IRSWAP, BOND };


// Create a global bond_positions
//map<string, Position<Bond>> bond_positions;

//template <typename T>
//class Trade;


// Trade sides
//enum Side { BUY, SELL };

//template <typename T>
//class Trade;

// Create a global Trade
map<string, Trade<Bond>> trades_all;

map<string, Bond> bonds_all;
map<string, Position<Bond>> bond_positions;


// Parse line function by using boost
vector<string> parse_line(string &line){
    vector<string> res;
    boost::split(res,line,boost::is_any_of(","));
    return res;
}

// Generate Maturity Dates

vector<date> Generate_MaturityDate(){
    cout<<"Generate Maturity Dates\n";
    vector<date> MaturityDate;
    for(int i=0; i<6; ++i){
        date maturityDate2(2018,Dec,17); // 2Y
        date maturityDate3(2019,Dec,17); // 3Y
        date maturityDate5(2021,Dec,17); // 5Y
        date maturityDate7(2023,Dec,17); // 7Y
        date maturityDate10(2026,Dec,17); // 10Y
        date maturityDate30(2046,Dec,17); // 30Y

        MaturityDate.push_back(maturityDate2);
        MaturityDate.push_back(maturityDate3);
        MaturityDate.push_back(maturityDate5);
        MaturityDate.push_back(maturityDate7);
        MaturityDate.push_back(maturityDate10);
        MaturityDate.push_back(maturityDate30);

    }
    return MaturityDate;
}





void initialize_global_variables(){
    cout<<"Initialize global variables\n";
    // Check whether the initial variables are empty
    if(bonds_all.size()==0 && bond_positions.size()==0){
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

        vector<date> MaturityDates=Generate_MaturityDate();

        vector<Bond> bonds;
        cout<<"Create bonds\n";
        for(int i=0; i<6;++i){
            //cout<<"Create bonds\n";
            bonds.push_back(Bond(cusips[i],CUSIP,"T",0.0,MaturityDates[i]));
        };
        //cout<<bonds[0].GetTicker()<<endl;

        for(int i=0; i<6; ++i){
            //cout<<"Assign bonds to bonds_all(map)\n";

//            std::pair<string, Bond> bond_pair;
//            cout<<"Pair\n";
//            bond_pair=make_pair(cusips[i],bonds[i]);
            //cout<<"Make pair\n";
            //bonds_all.insert(bond_pair);

            bonds_all.insert(make_pair(cusips[i],bonds[i]));
            //bonds_all[cusips[i]]=bonds[i];

            // Create Position<Bond> for bond_positions
            //cout<<"Create bond_pos\n";
            Position<Bond> bond_pos(bonds[i]);
            //cout<<"Initialize the bond_pos\n";
            bond_pos.init_position();   // Initialize the positions
            //cout<<"Assign bond_pos to bond_positions\n";
            //bond_positions[cusips[i]]=bond_pos;
            bond_positions.insert(make_pair(cusips[i],bond_pos));

        }
        cout<<"Initialize global variables successful\n";
    }





}

double fraction_to_double(string str){
    // Convert the fraction notation to double
    // Find "-"
    size_t index=str.find_first_of('-');

    double price=stod(str.substr(0,index)); // Get 99/100/101

    int dig2=stoi(str.substr(index+1,2));   // Get 2nd digit

    // Get the last digit 4 or "+"

    char last=str[str.size()-1];
    if(last=='+'){
        last='4'; // Convert "+" to 4
    }
    int dig3=last-'0';  // Convert to integer

    price+=(dig2*8+dig3)*1.0/256;

    return price;

}




#endif //FALL2016_9815_HW06_GLOBAL_VARIABLES_FUNCTIONS_HPP
