//
// Created by Hongchao Pan on 12/18/16.
//

#ifndef FALL2016_9815_HW06_BONDMARKETDATASERVICE_HPP
#define FALL2016_9815_HW06_BONDMARKETDATASERVICE_HPP

#include "marketdataservice.hpp"
#include "Global_variables_functions.hpp"
#include "BondAlgoExecutionService.hpp"

class BondMarketDataServiceListener: public ServiceListener<OrderBook<Bond>>{
public:

    BondAlgoExecutionService * algo_exe_service;

    BondMarketDataServiceListener(){
        algo_exe_service=BondAlgoExecutionService::create_instance();

    }

    // Create an instance of Bond market data service listener to flow date to bond algo execution service
    static BondMarketDataServiceListener *create_instance(){
        cout<<"Instance of bond market data service listener\n";
        static BondMarketDataServiceListener instance;
        return &instance;

    }



    void ProcessAdd(OrderBook<Bond> &data) override {
        //cout<<"OnMessage in bond market data service\n";
        algo_exe_service->OnMessage(data);

    }

    void ProcessRemove(OrderBook<Bond> &data) override {

    }

    void ProcessUpdate(OrderBook<Bond> &data) override {

    }


};


class BondMarketDataService : public MarketDataService<Bond>{
public:

    vector<ServiceListener<OrderBook<Bond>> *> Listeners;
    BondMarketDataServiceListener *algo_listener=BondMarketDataServiceListener::create_instance();
    BondMarketDataService(){
        cout<<"Bond market data service ctor\n";
        // Add listeners

        //AddListener(*HistoricalDataServiceListener::get_instance());
        //AddListener(*BondAlgoExecutionServiceListener::get_instance());
        //AddListener(*BondMarketDataServiceListener::create_instance());
        //BondMarketDataServiceListener *listener=BondMarketDataServiceListener::create_instance();
        //AddListener(listener);


    }

    // Create an instance of Bond market data service by using singleton
    static BondMarketDataService *create_instance(){
        //cout<<"Instance of bond market data service\n";
        static BondMarketDataService instance;
        return &instance;

    }




public:
    const BidOffer &GetBestBidOffer(const string &productId) override {
        //return <#initializer#>;
    }

    const OrderBook<Bond> &AggregateDepth(const string &productId) override {
        //return <#initializer#>;
    }

    void OnMessage(OrderBook<Bond> &data) override {
        //cout<<"OnMessage in bond market data service\n";
//        for(auto listener : Listeners){
//            cout<<"Listener\n";
//            listener->ProcessAdd(data);
//
//        }

        algo_listener->ProcessAdd(data);
    }

    void AddListener(ServiceListener<OrderBook<Bond>> *listener) override {
        cout<<"AddListener in bond market data service\n";

    }

    const vector<ServiceListener<OrderBook<Bond>> *> &GetListeners() const override {
        //return Listeners;
    }


};

class BondMarketDataConnector: public Connector<OrderBook<Bond>>{
public:

    // Create instance of Bond market data connector

    static BondMarketDataConnector *create_instance(){
        cout<<"Instance of Bond market data connector\n";

        static BondMarketDataConnector instance;
        return &instance;

    }

    BondMarketDataService *market_service;

    BondMarketDataConnector(){
        cout<<"Bond Market data connector ctor\n";
        market_service=BondMarketDataService::create_instance();
    }

    void FlowMarketData(){
        cout<<"Flow market data by using Bond market data connector\n";

        ifstream file("marketdata.txt");

        string line;
        getline(file, line);    // Skip the header

        string cusip;
        double bid_price, ask_price;
        long bid_quantity,ask_quantity;
        vector<Order> bid_all, ask_all;
        PricingSide pricing_side;
        cout<<"Execute order: in order to save time, only execute first 1000 orders in marketdata.txt file\n";

        //while(getline(file, line))    // For execute whole file

        for(int i=0; i<1000; ++i)
        {

            getline(file, line);
            //cout<<"Parse a line\n";
            vector<string> inputs=parse_line(line);

            cusip=inputs[0];

            // Get the bid information
            //cout<<"Get the bid information\n";
            int index_pointer=1;
            for(int i=0; i<5; ++i){
                bid_price=fraction_to_double(inputs[index_pointer++]);
                bid_quantity=stol(inputs[index_pointer++]);
                // Price, quantity
                pricing_side=BID;

                Order bid_order(bid_price,bid_quantity,pricing_side);

                bid_all.push_back(bid_order);

            }

            // Get the ask information
            //cout<<"Get the ask information\n";
            //int index_pointer=1;
            for(int i=0; i<5; ++i){
                ask_price=fraction_to_double(inputs[index_pointer++]);
                ask_quantity=stol(inputs[index_pointer++]);
                // Price, quantity
                pricing_side=OFFER;

                Order ask_order(ask_price,ask_quantity,pricing_side);

                ask_all.push_back(ask_order);

            }

            Bond& bond=bonds_all[cusip];    // Get the bond

            OrderBook<Bond> new_order_book(bond,bid_all,ask_all);
            //cout<<"Send order book to market service\n";
            market_service->OnMessage(new_order_book);
            //cout<<"Sent order book to market service successful\n";

        }

    }



    void Publish(OrderBook<Bond> &data) override {
        cout<<"Using FlowMarketData instead of Publish\n";

    }


};




#endif //FALL2016_9815_HW06_BONDMARKETDATASERVICE_HPP
