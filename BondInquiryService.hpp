//
// Created by Hongchao Pan on 12/18/16.
//

#ifndef FALL2016_9815_HW06_BONDINQUIRYSERVICE_HPP
#define FALL2016_9815_HW06_BONDINQUIRYSERVICE_HPP

#include "inquiryservice.hpp"
#include "Global_variables_functions.hpp"
#include "historicaldataservice.hpp"

class BondInquiryService : public InquiryService<Bond>{
public:
    //HistoricalDataService *hist_service;
    BondInquiryService(){
        cout<<"bond inquiry service ctor\n";
        //hist_service=HistoricalDataService::create_instance();
    }

    static BondInquiryService *create_instance(){
        cout<<"Instance of bond inquiry service\n";
        static BondInquiryService instance;
        return &instance;

    }


    void SendQuote(const string &inquiryId, double price) override {
        //InquiryService::SendQuote(inquiryId, price);
    }

    void RejectInquiry(const string &inquiryId) override {
        //InquiryService::RejectInquiry(inquiryId);
    }

    void OnMessage(Inquiry<Bond> &data) override {
        string cusip=data.GetProduct().GetProductId();
        double price=data.GetPrice();
        string inq_id=data.GetInquiryId();
        long quantity=data.GetQuantity();

        hist_service->InquiryOutput(data);

        ofstream file;
        file.open("inquiries_record.txt",std::ofstream::app);   // Append
        file<<"cusip, inquiry id, inquiry price, inquiry quantity\n";
        file<<cusip<<","<<inq_id<<","<<price<<","<<quantity<<endl;
        file.close();

    }

    void AddListener(ServiceListener<Inquiry<Bond>> *listener) override {
        //Service::AddListener(listener);
    }

    const vector<ServiceListener<Inquiry<Bond>> *> &GetListeners() const override {
     //   return Service::GetListeners();
    }


};

class BondInquiryServiceConnector : public Connector<Inquiry<Bond>>{
public:

    BondInquiryService *inquiry_service;
    BondInquiryServiceConnector(){
        inquiry_service=BondInquiryService::create_instance();
    }

    static BondInquiryServiceConnector *create_insatnce(){
        static BondInquiryServiceConnector instance;
        return &instance;
    }


    void Publish(Inquiry<Bond> &data) override {
        cout<<"Using FlowInquiryData instead of Publish\n";

    }

    void FlowInquiryData(){
        cout<<"Flow inquiry data to bond inquiry service\n";

        ifstream file("inquiries.txt");
        string line;
        getline(file, line);    // Skip header

        static int inq_id=1;    // initial inquiry id

        string cusip, _price, _side, _quantity, _state;
        Side side;
        double price;
        long quantity;
        InquiryState state;

        while(getline(file,line)){

            vector<string> inputs=parse_line(line);

            tie(cusip, _price, _side, _quantity, _state)=make_tuple(
                    inputs[0],inputs[1],inputs[2],inputs[3],inputs[4]
            );

            Bond& bond=bonds_all[cusip];

            if(_side=="BUY"){
                side=BUY;
            }
            if(_side=="SELL"){
                side=SELL;
            }

            quantity=stol(_quantity);
            price=fraction_to_double(_price);

            if(_state=="RECEIVED"){
                state=QUOTED;
            }
            string inquiry_id=to_string(inq_id);
            Inquiry<Bond> inquiry_bond(inquiry_id,bond,side,quantity,price,state);
            inq_id+=1;

            inquiry_service->OnMessage(inquiry_bond);

        }






    }


};




#endif //FALL2016_9815_HW06_BONDINQUIRYSERVICE_HPP
