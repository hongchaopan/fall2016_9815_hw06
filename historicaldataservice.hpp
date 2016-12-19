/**
 * historicaldataservice.hpp
 * historicaldataservice.hpp
 *
 * @author Breman Thuraisingham
 * Defines the data types and Service for historical data.
 *
 * @author Breman Thuraisingham
 */
#ifndef HISTORICAL_DATA_SERVICE_HPP
#define HISTORICAL_DATA_SERVICE_HPP

#include "soa.hpp"
//#include "Global_variables_functions.hpp"
#include "inquiryservice.hpp"
#include "streamingservice.hpp"
#include "executionservice.hpp"
#include "riskservice.hpp"
/**
 * Service for processing and persisting historical data to a persistent store.
 * Keyed on some persistent key.
 * Type T is the data type to persist.
 */
//template<typename T>
//class HistoricalDataService : Service<string,T>
//{
//
//public:
//
//  // Persist data to a store
//  void PersistData(string persistKey, const T& data) = 0;
//
//};


class HistoricalDataService : Service<string,Bond>
{

public:
    // Create an instance of historical data service by using singleton
    static HistoricalDataService *create_instance(){
        cout<<"Instance of historical data service\n";

        static HistoricalDataService instance;
        return &instance;
    }

    // Persist data to a store
    void PersistData(string persistKey, const Bond& data){
        cout<<"PersistData\n";
    }


    void OnMessage(Bond &data) override {
        cout<<"OnMessage\n";

    }

    void AddListener(ServiceListener<Bond> *listener) override {
        //Service::AddListener(listener);
    }

    const vector<ServiceListener<Bond> *> &GetListeners() const override {
        //return Service::GetListeners();
    }


    void InquiryOutput(Inquiry<Bond> &data){
        string cusip=data.GetProduct().GetProductId();
        double price=data.GetPrice();
        string inq_id=data.GetInquiryId();
        long quantity=data.GetQuantity();

        ofstream file;
        file.open("allinquiries.txt",std::ofstream::app);   // Append
        file<<"cusip, inquiry id, inquiry price, inquiry quantity\n";
        file<<cusip<<","<<inq_id<<","<<price<<","<<quantity<<endl;
        file.close();

    }

    void StreamingOutput(PriceStream<Bond> &data){

        string cusip=data.GetProduct().GetProductId();
        double bid_price=data.GetBidOrder().GetPrice();
        double ask_price=data.GetOfferOrder().GetPrice();
        long quantity_bid=data.GetBidOrder().GetVisibleQuantity();
        long quantity_ask=data.GetOfferOrder().GetVisibleQuantity();

        ofstream file2;
        file2.open("streaming.txt",std::ofstream::app);  // Append
        file2<<"cusip, bid price, bid quantity, ask price, ask quantity\n";
        file2<<cusip<<","<<bid_price<<","<<quantity_bid<<","<<ask_price<<","<<quantity_ask<<endl;
        file2.close();
    }

    void ExecutionOutput(const ExecutionOrder<Bond> &order, Market market) {
        //ExecutionService::ExecuteOrder(order, market);
        // Write the order into a file
        //cout<<"ExecuteOrder in bond execution service\n";
        ofstream file;
        file.open("executions.txt",std::ofstream::app); // Append

        file<<"Executing an order with following information\n";

        file<<"cusip, orderid, price, visibleQuantity\n";

        string cusip=order.GetProduct().GetProductId();
        string orderid=order.GetOrderId();
        double price=order.GetPrice();
        double visibleQuantity=order.GetVisibleQuantity();
        file<<cusip<<","<<orderid<<","<<price<<","<<visibleQuantity<<endl;
        file.close();
    }

    void RiskOutput(Position<Bond> &position) {
        cout<<"AddPosition in the bond risk service\n";
        string cusip=position.GetProduct().GetProductId();
        long _position=position.GetAggregatePosition();
        ofstream file;
        file.open("risk.txt",std::ofstream::app);

        file<<"Booked risk with follow information\n";
        file<<"cusip, aggregate position\n";
        file<< cusip<<","<<_position<<endl;
        file.close();

    }

};




#endif
