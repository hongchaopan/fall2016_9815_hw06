//
// Created by Hongchao Pan on 12/19/16.
//

#ifndef FALL2016_9815_HW06_BONDALGOSTREAMINGSERVICE_HPP
#define FALL2016_9815_HW06_BONDALGOSTREAMINGSERVICE_HPP

#include "BondStreamingService.hpp"
#include "Global_variables_functions.hpp"
#include "pricingservice.hpp"

class BondAlgoStreamingService :public Service<string, Price<Bond>>{
public:
    BondStreamingService *streaming_service;
    BondAlgoStreamingService(){
        cout<<"bond algo streaming service ctor\n";
        streaming_service=BondStreamingService::create_instance();
    }

    // Create instance of bond lago streaming service
    static BondAlgoStreamingService *create_instance(){
        cout<<"Instance of bond algo streaming service\n";
        static BondAlgoStreamingService instance;
        return &instance;
    }


    void OnMessage(Price<Bond> &data) override {

        // Get the price data from BondPricingService
        string cusip=data.GetProduct().GetProductId();
        double mid_price=data.GetMid();
        double bs_spread=data.GetBidOfferSpread();

        double bid=mid_price-0.5*bs_spread;
        double ask=mid_price+0.5*bs_spread;
        long visibleQuantity=1000;
        long hiddenQuantity=0;
        PricingSide side_bid=BID;
        PricingSide side_ask=OFFER;
        static int k=1;
        // Create PriceStreamOrder
        PriceStreamOrder bidStreamOrder(bid,visibleQuantity*k,hiddenQuantity,side_bid);
        PriceStreamOrder askStreamOrder(ask,visibleQuantity*k,hiddenQuantity,side_ask);
        k+=1;

        // Create PriceStream
        Bond& bond=bonds_all[cusip];
        PriceStream<Bond> price_stream(bond,bidStreamOrder,askStreamOrder);

        streaming_service->PublishPrice(price_stream);
        //streaming_service->OnMessage(price_stream);

    }

    void AddListener(ServiceListener<Price<Bond>> *listener) override {
        Service::AddListener(listener);
    }

    const vector<ServiceListener<Price<Bond>> *> &GetListeners() const override {
        return Service::GetListeners();
    }


};




#endif //FALL2016_9815_HW06_BONDALGOSTREAMINGSERVICE_HPP
