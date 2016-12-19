//
// Created by Hongchao Pan on 12/5/16.
//

#ifndef BONDPRICINGSERVICE_HPP
#define BONDPRICINGSERVICE_HPP

#include "pricingservice.hpp"
#include "Global_variables_functions.hpp"
#include "BondAlgoStreamingService.hpp"



//template <typename T>
class BondPricingService:public PricingService<Bond>{
public:
    vector<ServiceListener<Price<Bond>> *> Listeners;

    BondAlgoStreamingService *algo_stream_service;
    BondPricingService(){
        cout<<"Bond pricing service ctor\n";

        algo_stream_service=BondAlgoStreamingService::create_instance();    // Connector to BondAlgoStreamingService
    }

    // Create instance of bond pricing service through singleton
    static BondPricingService *create_instance(){
        static BondPricingService instance;
        return &instance;
    }



public:
//    Price<Bond> &GetData(string key) override {
//       return Price<Bond>;
//    }

    void OnMessage(Price<Bond> &data) override {

        algo_stream_service->OnMessage(data);   // Flow data to BondAlgoStreamingService

        //cout<<"OnMessage in the Bond pricing service has been called.\n";
        string cusip=data.GetProduct().GetProductId();
        double mid_price=data.GetMid();
        double bs_spread=data.GetBidOfferSpread();
        ofstream file;
        file.open("price_record.txt",std::ofstream::app);
        file<<"cusip, mid price, bid/ask offer spread\n";
        file<<cusip<<","<<mid_price<<","<<bs_spread<<endl;
        file.close();

        //cout<<"Mid price is: "<<mid_price<<endl;
        //cout<<"Bid ask spread is: "<<bs_spread<<endl;

    }

    void AddListener(ServiceListener<Price<Bond>> *listener) override {
        Listeners.push_back(listener);


    }

    const vector<ServiceListener<Price<Bond>> *> &GetListeners() const override {
        return Listeners;
    }

};


class BondPricingServiceConnector : public Connector<Price<Bond>>{
public:

    static BondPricingServiceConnector *create_instance(){
        cout<<"Instance of Bond pricing service connector\n";
        static BondPricingServiceConnector instance;
        return &instance;

    }

    BondPricingService *pricing_service;
    BondPricingServiceConnector(){
        cout<<"Bond pricing service connector ctor\n";
        pricing_service=BondPricingService::create_instance();
        //BondPricingService pricing_service;
    }

//    BondPricingService *pricing_service= new BondPricingService;

    void FlowPriceData(){
        cout<<"Flow data\n";

        ifstream file("prices.txt");
        // Delimiter ","

        string line;
        string cusip, mid, bs_offer;
        // Skip header
        getline(file,line);

        //while(getline(file,line)) // For whole file
        cout<<"Recording price: in order to save time and space, flowing 1st 1000 lines in prices.txt\n";
        for(int i=0; i<1000; ++i)

        {
            getline(file,line);
            //cout<<"Parse file\n";
            vector<string> inputs=parse_line(line);

            tie(cusip,mid,bs_offer)=make_tuple(inputs[0],inputs[1],inputs[2]);
            //cout<<cusip<<","<<mid<<","<<bs_offer<<endl;

            //cout<<bonds_all[cusip].GetCoupon()<<endl;
            Bond& bond=bonds_all[cusip];

            double mid_price=fraction_to_double(mid);
            double bs_spread=fraction_to_double(bs_offer);

            //cout<<mid_price<<","<<bs_spread<<endl;

            Price<Bond> price_bond(bond,mid_price,bs_spread);
            //cout<<"Send Price<Bond> to pricing service\n";
            //BondPricingService pricing_service;
            pricing_service->OnMessage(price_bond);
            //price_obj.OnMessage(price_bond);
            //cout<<"Send Price<Bond> to pricing service successful\n";
        }
    }


    void Publish(Price<Bond> &data) override {
        cout<<"Using FlowPriceData instead of publish\n";

    }


};





#endif // BONDPRICINGSERVICE_HPP
