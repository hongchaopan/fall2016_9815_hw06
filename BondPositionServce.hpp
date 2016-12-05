//
// Created by hongchao on 12/5/16.
//

#ifndef BONDPOSITIONSERVCE_HPP
#define BONDPOSITIONSERVCE_HPP

#include "positionservice.hpp"



template <typename T>
class BondPositionService:public PositionService<T>{
public:
    void AddTrade(const Trade<T> &trade) override {

    }

    Position<T> &GetData(string key) override {
        return <#initializer#>;
    }

    void OnMessage(Position<T> &data) override {

    }

    void AddListener(ServiceListener<Position<T>> *listener) override {

    }

    const vector<ServiceListener<Position<T>> *> &GetListeners() const override {
        return <#initializer#>;
    }

};




#endif // BONDPOSITIONSERVCE_HPP
