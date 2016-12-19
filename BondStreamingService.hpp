//
// Created by Hongchao Pan on 12/18/16.
//

#ifndef FALL2016_9815_HW06_BONDSTREAMINGSERVICE_HPP
#define FALL2016_9815_HW06_BONDSTREAMINGSERVICE_HPP

#include "streamingservice.hpp"
#include "Global_variables_functions.hpp"
#include "historicaldataservice.hpp"

class BondStreamingService : public StreamingService<Bond>{
public:
    //HistoricalDataService *hist_service;

    BondStreamingService(){
        cout<<"Bond streamming service ctor\n";
        //hist_service=HistoricalDataService::create_instance();
    }

    // Create instance of BondStreamingService by using singleton
    static BondStreamingService *create_instance(){
        cout<<"Instance of BondStreamingService\n";
        static BondStreamingService instance;
        return &instance;
    }



    void OnMessage(PriceStream<Bond> &data) override {
        //cout<<"OnMessage in price streaming service\n";
        //cout<<"Using PublishPrice function instead of OnMessage\n";
        hist_service->StreamingOutput(data);

        string cusip=data.GetProduct().GetProductId();
        double bid_price=data.GetBidOrder().GetPrice();
        double ask_price=data.GetOfferOrder().GetPrice();
        long quantity_bid=data.GetBidOrder().GetVisibleQuantity();
        long quantity_ask=data.GetOfferOrder().GetVisibleQuantity();

        ofstream file2;
        file2.open("streaming_record.txt",std::ofstream::app);  // Append
        file2<<"cusip, bid price, bid quantity, ask price, ask quantity\n";
        file2<<cusip<<","<<bid_price<<","<<quantity_bid<<","<<ask_price<<","<<quantity_ask<<endl;
        file2.close();

    }

    void AddListener(ServiceListener<PriceStream<Bond>> *listener) override {
        //Service::AddListener(listener);
    }

    const vector<ServiceListener<PriceStream<Bond>> *> &GetListeners() const override {
        //return Service::GetListeners();
    }

    void PublishPrice(const PriceStream<Bond> &priceStream) override {
        string cusip=priceStream.GetProduct().GetProductId();
        double bid_price=priceStream.GetBidOrder().GetPrice();
        double ask_price=priceStream.GetOfferOrder().GetPrice();
        long quantity_bid=priceStream.GetBidOrder().GetVisibleQuantity();
        long quantity_ask=priceStream.GetOfferOrder().GetVisibleQuantity();

        ofstream file2;
        file2.open("streaming_record.txt",std::ofstream::app);  // Append
        file2<<"cusip, bid price, bid quantity, ask price, ask quantity\n";
        file2<<cusip<<","<<bid_price<<","<<quantity_bid<<","<<ask_price<<","<<quantity_ask<<endl;
        file2.close();


    }


};



#endif //FALL2016_9815_HW06_BONDSTREAMINGSERVICE_HPP
