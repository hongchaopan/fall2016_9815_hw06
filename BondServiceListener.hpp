//
// Created by Hongchao Pan on 12/5/16.
//
// Derived Bond service listener from service listener

#ifndef BONDSERVICELISTENER_HPP
#define BONDSERVICELISTENER_HPP

#include "soa.hpp"

template <typename V>
class BondServiceListener:public ServiceListener<V>{
public:

    void ProcessAdd(V &data) override {

    }

    void ProcessRemove(V &data) override {
        cout<<"ProcessRemove hasn't been implemented."<<endl;
    }

    void ProcessUpdate(V &data) override {
        cout<<"ProcessUpdate hasn't been implemented."<<endl;

    }

};



#endif // BONDSERVICELISTENER_HPP
