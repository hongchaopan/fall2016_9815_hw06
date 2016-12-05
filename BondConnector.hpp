//
// Created by Hongchao Pan on 12/5/16.
//

#ifndef BONDCONNECTOR_HPP
#define BONDCONNECTOR_HPP

#include "soa.hpp"
#include "BondTradeBookingService.hpp"

template <typename V>
class BondConnector:public Connector<V>{
private:
    BondTradeBookingService<Bond> BSBT;
public:
    void Publish(V &data) override {
        // Not consistent with the OnMessage in BondTradeBookingService
    }
    void Publish(Trade<V> &data){
        BSBT.OnMessage(data);

    }

};

#endif // BONDCONNECTOR_HPP
