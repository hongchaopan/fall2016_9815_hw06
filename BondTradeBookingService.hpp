//
// Created by Hongchao Pan on 12/2/16.
//
// Derived the BondTradeBookingService from tradebookingservice

#ifndef BONDTRADEBOOKINGSERVICE_HPP
#define BONDTRADEBOOKINGSERVICE_HPP

#include "tradebookingservice.hpp"
#include "products.hpp"
#include "BondTradePositionService.hpp"

/**
 *
 * Trade Booking Service to book trades to a particular book.
 * Keyed on product identifier.
 * Type T is the product type.
 */

// Bond trade service listener
class BondTradeServiceListener: public ServiceListener<Trade<Bond>>{
//private:
public:
    BondTradePositionService *position_service=nullptr;
    BondTradeServiceListener(){
        cout<<"Bond trade service listener constructor\n";
        position_service=BondTradePositionService::create_instance();
    }

public:
    //map<string, Position<Bond>> bond_positions;
//    BondTradePositionService position_service;
//    BondTradeServiceListener(){
//        cout<<"Bond trade service listener constructor\n";
//    }

    // Crete instance of ServiceListener by using singleton
    static BondTradeServiceListener* create_instance(){
        cout<<"Instance of Bond trade service listener\n";
        static BondTradeServiceListener instance;
        return &instance;
    }

    void ProcessAdd(Trade<Bond> &data) override {
        cout<<"ProcessAdd in BondTradeServiceListener\n";
        // Get the CUSIP ID
        string cusip_id=data.GetProduct().GetProductId();
        // Get the side and quantity
        long quantity=0; // Default quantity is 0
        if(data.GetSide()==BUY){
            quantity=data.GetQuantity();
        }
        if(data.GetSide()==SELL){
            quantity=-data.GetQuantity();
        }
        // Add position
        cout<<"Add data to bond positions(map)\n";
        bond_positions[cusip_id].AddPosition(data.GetBook(), quantity);
        cout<<"Bond position (map) is good\n";
        position_service->OnMessage(bond_positions[cusip_id]);
//        position_service.OnMessage(bond_positions[cusip_id]);

    }

    void ProcessRemove(Trade<Bond> &data) override {
        cout<<"ProcessRemove hasn't been implemented."<<endl;
    }

    void ProcessUpdate(Trade<Bond> &data) override {
        cout<<"ProcessUpdate hasn't been implemented."<<endl;

    }

};

//template <typename T>
// Trade<Bond>
class BondTradeBookingService: public TradeBookingService<Bond>{
//private:
public:
    //Trade<Bond> trade; // Dummy trade
    vector<ServiceListener<Trade<Bond>> *> Listeners;

    BondTradeBookingService(){
        // Add a listener when initial the BondTradeBookingService
        cout<<"Create bond service listener\n";
        BondTradeServiceListener* _listener=BondTradeServiceListener::create_instance();
        AddListener(_listener);
    }

public:
    //map<string, Trade<Bond>> trades_all;

//    BondTradeBookingService(){
//        cout<<"Bond trade booking service ctor\n";
//
//    }
//    //BondTradeBookingService bondtrade_service;


    // Crete an instance of BondTradeBookingService by using singleton
    static BondTradeBookingService* create_instance(){
        cout<<"Instance of Bond trade booking service\n";
        static BondTradeBookingService instance;
        return &instance;
    }

//    Trade<Bond> &GetData(string key) override {
//        cout<<"GetData function in BondTradeBookingService\n";
//        return trades_all[key];   // Return the data through the key
//    }

    void OnMessage(Trade<Bond> &data) override {

        // Book trade through OnMessage
        cout<<"OnMessage in Bond trade booking service has been called.\n";

        BookTrade(data);

    }

    void AddListener(ServiceListener<Trade<Bond>> *listener) override {
        Listeners.push_back(listener);
        cout<<"Add a listener to the BondTradeBookingService.\n";
    }

    const vector<ServiceListener<Trade<Bond>> *> &GetListeners() const override {
        return Listeners;
    }

    void BookTrade(Trade<Bond>& trade) override {
        //cout<<"BookTrade in Bond trade booking service\n";
        for(auto listener: Listeners){
            cout<<"BookTrade in Book trade service\n";
            listener->ProcessAdd(trade);

        }
    }
};


// Bond trade service connector: flow data to the service
//template <typename V>
// Change to specific Trade<Bond>
class BondTradeConnector:public Connector<Trade<Bond>>{
//private:
public:
    BondTradeBookingService *bondtrade_service=nullptr;
    BondTradeConnector(){
        cout<<"Bond Trade connector constructor\n";
        bondtrade_service=BondTradeBookingService::create_instance();
        cout<<"Bond Trade connector constructor and create an instance of Bond trade booking service\n";
    }

public:
//    BondTradeConnector(){
//        cout<<"Bond trade connector ctor\n";
//    }
//    BondTradeBookingService &bondtrade_service;
//
//    BondTradeServiceListener* _listener=BondTradeServiceListener::create_instance();
//    bondtrade_service.AddListener(_listener);
//    //bondtrade_service.AddListener(_listener);

    // Create instance of BondTradeConnector by using singleton
    static BondTradeConnector* create_instance(){
        cout<<"Instance of Bond trade connector\n";
        static BondTradeConnector instance;
        return &instance;
    }

    // Don't use this method to flow date
    void Publish(Trade<Bond> &data){
        //bondtrade_service->OnMessage(data);
        cout<<"Publish in connector\n";

    }

    void FlowTradeData(){
        // Flow the Trade date to BondTradeBookingService
        cout<<"Flow data from the input file\n"; // Dummy function, check the workflow

        ifstream file("trades.txt");
        // Delimiter is ","

        string line;
        string cusip, cusip_type, ticker, coupon, tradeID, book, quantity, _side;
        getline(file, line); // Skip the line

        vector<date> MaturityDates=Generate_MaturityDate();
        int index=0;
        cout<<"Start Parsing the trades.txt file\n";
        while(getline(file,line)){
            vector<string> inputs=parse_line(line);

            tie(cusip, cusip_type, ticker, coupon, tradeID, book, quantity, _side)=make_tuple(
                    inputs[0],inputs[1],inputs[2],inputs[3],inputs[4],inputs[5],inputs[6],inputs[7]
            );

            BondIdType bondidtype=(cusip_type=="CUSIP" ? CUSIP: ISIN);

            Side side=(_side=="BUY" ? BUY:SELL);

            // use std::stol converge string to int
            // use std::stof converge string to float
            Bond bond(cusip,bondidtype,ticker,stof(coupon),MaturityDates[index]);
            //cout<<"Bond coupon: "<<bond.GetCoupon()<<endl;
            index+=1;
            Trade<Bond> trade(bond,tradeID,book,stol(quantity),side);
            //cout<<"Created a trade and send to bond trade service\n";
            // Add the trade to trades_all
            cout<<"Pass trade to trades_all\n";
            trades_all.insert(make_pair(tradeID,trade));
            cout<<"Pass trade tp trades_all successful\n";

            bondtrade_service->OnMessage(trade);
            //bondtrade_service.OnMessage(trade);
            cout<<"trade has been sent to the bond trade service\n";

        }

    }

};









#endif //FALL2016_9815_HW06_BONDTRADEBOOKINGSERVICE_HPP
