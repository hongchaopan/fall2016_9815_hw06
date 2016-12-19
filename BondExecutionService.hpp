//
// Created by Hongchao Pan on 12/18/16.
//

#ifndef FALL2016_9815_HW06_BONDEXECUTIONSERVICE_HPP
#define FALL2016_9815_HW06_BONDEXECUTIONSERVICE_HPP

#include "executionservice.hpp"
#include "Global_variables_functions.hpp"

class BondExecutionService : public ExecutionService<Bond>{

public:
    // Create an instance of bond execution service

    static BondExecutionService *create_instance(){
        cout<<"Instance of bond execution service\n";

        static BondExecutionService instance;
        return &instance;


    }
    BondExecutionService(){
        cout<<"Bond execution service ctor\n";
    } //Default ctor


    void ExecuteOrder(const ExecutionOrder<Bond> &order, Market market) override {
        //ExecutionService::ExecuteOrder(order, market);
        // Write the order into a file
        //cout<<"ExecuteOrder in bond execution service\n";
        hist_service->ExecutionOutput(order,market);
        ofstream file;
        file.open("executed_order.txt",std::ofstream::app); // Append

        file<<"Executing an order with following information\n";

        file<<"cusip, orderid, price, visibleQuantity\n";

        string cusip=order.GetProduct().GetProductId();
        string orderid=order.GetOrderId();
        double price=order.GetPrice();
        double visibleQuantity=order.GetVisibleQuantity();
        file<<cusip<<","<<orderid<<","<<price<<","<<visibleQuantity<<endl;
        file.close();
    }

    void OnMessage(ExecutionOrder<Bond> &data) override {
        cout<<"OnMessage in bond execution service\n";

    }

    void AddListener(ServiceListener<ExecutionOrder<Bond>> *listener) override {
        Service::AddListener(listener);
    }

    const vector<ServiceListener<ExecutionOrder<Bond>> *> &GetListeners() const override {
        return Service::GetListeners();
    }


};





#endif //FALL2016_9815_HW06_BONDEXECUTIONSERVICE_HPP
