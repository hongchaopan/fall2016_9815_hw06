//
// Created by Hongchao Pan on 12/16/16.
//

#ifndef BONDTRADEPOSITIONSERVICE_HPP
#define BONDTRADEPOSITIONSERVICE_HPP

#include "positionservice.hpp"
//#include "products.hpp"
#include "BondTradeRiskService.hpp"
//#include "Global_variables_functions.hpp"


class BondPositionListener : public ServiceListener<Position<Bond>>{
//private:
public:
    BondTradeRiskService *bondrisk_service;
    BondPositionListener(){
        cout<<"Bond position listener ctor\n";
        bondrisk_service=BondTradeRiskService::create_instance();
        cout<<"Getting the bond risk service\n";
    }

    //BondPositionListener(){}


public:

    // Create Bond position service listener by using singleton
    static BondPositionListener *create_instance(){
        cout<<"Instance of Bond position listener\n";
        static BondPositionListener instance;
        return &instance;
    }



    void ProcessAdd(Position<Bond> &data) override {
        cout<<"ProcessAdd in BondPositionListener has been called.\n";
        bondrisk_service->AddPosition(data);

    }

    void ProcessRemove(Position<Bond> &data) override {
        cout<<"ProcessRemove in BondPositionListener has been called.\n";
        // Not yet fully implemented

    }

    void ProcessUpdate(Position<Bond> &data) override {
        cout<<"ProcessUpdate in BondPositionListener has been called.\n";
        // Not yet fully implemented
    }


};



//template <typename T>
// Trade<Bond>
class BondTradePositionService:public PositionService<Bond>{
//private:
public:
    // Add position listener in the constructor of the position service
    BondTradePositionService() {
        cout<<"Bond trade position service ctor\n";
        BondPositionListener* _listener=BondPositionListener::create_instance();
        AddListener(_listener);
    }
    //Trade<Bond> trade; // Dummy trade
    vector<ServiceListener<Position<Bond>> *> Listeners;
    //Position<Bond> dummy_position;

public:
//    Position<Bond> &GetData(string key) override {
//        cout<<"GetData in Bond Position service has been called\n";
//
//        return bond_positions[key];
//    }

    // Create an instance of BondTradePostionService by using singleton
    static BondTradePositionService* create_instance(){
        cout<<"Instance of Bond trade position service\n";
        static BondTradePositionService instance;
        return &instance;
    }


    void AddTrade(Trade<Bond> &trade)  {
        cout<<"Adding Trade in the BondTradePositionService has been called\n";
//        map<string, Trade<Bond>>::iterator itr=trades_all.begin();
//        // Check
//        for(;itr!=trades_all.end();++itr){
//            // Get bond ID and book
//            string bondID=itr->second.GetProduct().GetProductId();
//            string book=itr->second.GetBook();
//
//            if(bond_positions.count(bondID)){
//                if(bond_positions[bondID].positions.count(book)){
//                    bond_positions[bondID].positions[book]+=itr->second.GetQuantity();
//
//                }
//                else{
//                    bond_positions[bondID].positions[book]=itr->second.GetQuantity();
//                }
//            }
//            else{
//                // New bond
//                Position<Bond> new_bond_pos(itr->second.GetProduct());
//                bond_positions[bondID]=new_bond_pos;
//            }
//
//        }

    }

    void OnMessage(Position<Bond> &data) override {
        cout<<"Flow in the Bond position service\n";
        for(auto listener: Listeners){

            listener->ProcessAdd(data);
        }

    }

    void AddListener(ServiceListener<Position<Bond>> *listener) override {
        Listeners.push_back(listener);
        cout<<"Add a listener to the BondTradeBookingService.\n";

    }

    const vector<ServiceListener<Position<Bond>> *> &GetListeners() const override {
        return Listeners;
    }


};




#endif //FALL2016_9815_HW06_BONDTRADEPOSITIONSERVICE_HPP
