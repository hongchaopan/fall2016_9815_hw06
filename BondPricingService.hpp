//
// Created by Hongchao Pan on 12/5/16.
//

#ifndef BONDPRICINGSERVICE_HPP
#define BONDPRICINGSERVICE_HPP

#include "pricingservice.hpp"

template <typename T>
class BondPricingService:public PricingService<T>{
public:
    Price<T> &GetData(string key) override {
        return <#initializer#>;
    }

    void OnMessage(Price<T> &data) override {

    }

    void AddListener(ServiceListener<Price<T>> *listener) override {

    }

    const vector<ServiceListener<Price<T>> *> &GetListeners() const override {
        return <#initializer#>;
    }

};


#endif // BONDPRICINGSERVICE_HPP
