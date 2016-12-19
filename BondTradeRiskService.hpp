//
// Created by Hongchao Pan on 12/16/16.
//

#ifndef FALL2016_9815_HW06_BONDTRADERISKSERVICE_HPP
#define FALL2016_9815_HW06_BONDTRADERISKSERVICE_HPP

#include "riskservice.hpp"
//#include "products.hpp"
//#include "random"
#include "BondTradePositionService.hpp"
#include "Global_variables_functions.hpp"

// create a hash map contains the initial risk
map<string, double> risk_map;
map<string, PV01<Bond>> risk_pv01_map;

class BondTradeRiskService : public RiskService<Bond>{
//private:
public:
    // Create a dummpy PVO1
    //PV01<Bond>* dummy_pv01;
    // No listener needed for BondTradeRiskService

    //vector<ServiceListener<PV01<Bond>> *> Listeners;

    //BondTradeRiskService(){}

    std::default_random_engine re;  // Random engine

public:

    BondTradeRiskService(){
        cout<<"Bond trade risk service ctor\n";
    }

    // Create an instance of BondTradeRiskService by using singleton
    static BondTradeRiskService  *create_instance(){
        cout<<"Instance of bond trade risk service\n";
        static BondTradeRiskService instance;
        return &instance;
    }

    void AddPosition(Position<Bond> &position) override {

        hist_service->RiskOutput(position);

        cout<<"AddPosition in the bond risk service\n";
        string cusip=position.GetProduct().GetProductId();
        long _position=position.GetAggregatePosition();
        ofstream file;
        file.open("booked_risk.txt",std::ofstream::app);

        file<<"Booked risk with follow information\n";
        file<<"cusip, aggregate position\n";
        file<< cusip<<","<<_position<<endl;
        file.close();

    }

    PV01<Bond> &GetBucketedRisk(const BucketedSector<Bond> &sector) override {
        //return <#initializer#>;
    }

    void OnMessage(PV01<Bond> &data) override {

    }

    void AddListener(ServiceListener<PV01<Bond>> *listener) override {
//        Service::AddListener(listener);
    }

    const vector<ServiceListener<PV01<Bond>> *> &GetListeners() const override {
        //return Service::GetListeners();
    }

//        PV01<Bond> default_val;
//
//    void AddPosition(Position<Bond> &position) override {
//        cout<<"Flow in the Bond trade risk service.\n";
//
//        if(risk_map.size()==0 & risk_pv01_map.size()==0 ){
//            // Create initial risk_map by using random generator
//
//            // Random generator for double numbers between [3.0, 4.0]
//            uniform_real_distribution<double> uniD(0.0,1.0);
//
//            // 2Y, 3Y, 5Y, 7Y, 10Y, 30Y cusip
//            // Reference: https://www.treasurydirect.gov/instit/instit.htm
//            string cusips[]={
//                    "912828U40",    // 2Y notes
//                    "912828U73",    // 3Y notes
//                    "912828U65",    // 5Y notes
//                    "912828U57",    // 7Y notes
//                    "912828U24",    // 10Y notes
//                    "912810RU4"     // 30Y bonds
//            };
//
//            cout<<"Create initial risk\n";
//
//            for(int i=0; i<6; ++i){
//
//                risk_map.insert(make_pair(cusips[i],uniD(re)));
//                risk_pv01_map.insert(make_pair(cusips[i],default_val));
//
//            }
//
//            cout<<"Done create the hash maps\n";
//
//        }
//
//        string cusip=position.GetProduct().GetProductId();
//
//        long quantity=position.GetAggregatePosition();
//
//        double new_risk=quantity*risk_map[cusip];
//
//        PV01<Bond> new_pv01(position.GetProduct(),new_risk,quantity);
//        cout<<"Create new pv_01, need to pass to historical data further\n";
//        map<string, Position<Bond>>::iterator itr;
//        itr=bond_positions.begin();
//        for(;itr!=bond_positions.end();++itr){
//
//            // Find the position risk
//            double risk_pos=itr->second.GetAggregatePosition()*risk_map[itr->first];
//            // Create the PV01
//            PV01<Bond> new_pv01(itr->second.GetProduct(),risk_pos,itr->second.GetAggregatePosition());
//
//            //risk_pv01_map[itr->first]=risk_pv01_map[itr->first]+new_pv01;
//
//        }

//    }

//    PV01<Bond> &GetBucketedRisk(const BucketedSector<Bond> &sector)  override {
//        cout<<"GetBuckedRisk in BondTradeRiskService has been called.\n";
//        //return default_val;
//    }

//    PV01<Bond> &GetData(string key) override {
//        cout<<"GetData in RiskService has been called.\n";
//        return risk_pv01_map[key];
//    }
//
//    void OnMessage(PV01<Bond> &data) override {
//        cout<<"OnMessage in risk service, no corresponding listener.\n";
//
//    }
//
//    void AddListener(ServiceListener<PV01<Bond>> *listener) override {
//        cout<<"No listener\n";
//
//    }
//
//    const vector<ServiceListener<PV01<Bond>> *> &GetListeners() const override {
//        cout<<"No listener\n";
//        //return Listeners;
//    }
//



};




#endif //FALL2016_9815_HW06_BONDTRADERISKSERVICE_HPP
