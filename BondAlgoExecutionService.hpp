//
// Created by Hongchao Pan on 12/18/16.
//

#ifndef FALL2016_9815_HW06_BONDALGOEXECUTIONSERVICE_HPP
#define FALL2016_9815_HW06_BONDALGOEXECUTIONSERVICE_HPP

#include "BondExecutionService.hpp"
#include "Global_variables_functions.hpp"



class BondAlgoExecutionService : public Service<string, OrderBook<Bond>> {
public:
    // Create an instance of bond algo execution service by using singleton

    BondExecutionService *execution_service;
    BondAlgoExecutionService(){
        //cout<<"Bond algo execution service ctor\n";

        execution_service=BondExecutionService::create_instance();
    }


    static BondAlgoExecutionService* create_instance() {
        cout<<"Instance of bond algo execution service\n";
        static BondAlgoExecutionService instance;
        return &instance;
    }


    void OnMessage(OrderBook<Bond> &data) override {
        //cout<<"OnMessage in bond algo execution service\n";

        bool bid = false;    // Assume the data is ask
        int order_id = 1;
        bid = !bid;

        // Gather information for executable order
        Bond bond = data.GetProduct();
        PricingSide side;
        string orderid;
        OrderType ordertype;
        double price, visibleQuantity;
        double hiddenQuantity = 0.0;
        string parentOrderId = "";
        bool isChildOrder = false;

        string cusip;

        orderid = to_string(order_id++);
        cusip = bond.GetProductId();
        long position = bond_positions[cusip].GetAggregatePosition();
        // use Market order in default;
        ordertype = OrderType::MARKET;

        // alternating between BID and OFFER
        if (bid) {
            side = BID;
            const Order & bid_order = data.GetBidStack()[0];
            price = bid_order.GetPrice();
            visibleQuantity = bid_order.GetQuantity();
            if (visibleQuantity > position){
                visibleQuantity = position;
            }

        }
        else {
            side = OFFER;
            const Order & offer_order = data.GetOfferStack()[0];
            price = offer_order.GetPrice();
            visibleQuantity = offer_order.GetQuantity();
        }

        ExecutionOrder<Bond> new_order(bond, side, orderid, ordertype, price, visibleQuantity,
                                   hiddenQuantity, parentOrderId, isChildOrder);
        //execution_service->OnMessage(new_order);
        execution_service->ExecuteOrder(new_order, Market::CME);

    }

    void AddListener(ServiceListener<OrderBook<Bond>> *listener) override {
        //Service::AddListener(listener);
    }

    const vector<ServiceListener<OrderBook<Bond>> *> &GetListeners() const override {
        //return Service::GetListeners();
    }


};




#endif //FALL2016_9815_HW06_BONDALGOEXECUTIONSERVICE_HPP
