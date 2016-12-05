//
// Created by Hongchao Pan on 12/2/16.
//
// Derived the BondTradeBookingService from tradebookingservice

#ifndef BONDTRADEBOOKINGSERVICE_HPP
#define BONDTRADEBOOKINGSERVICE_HPP

#include "tradebookingservice.hpp"
#include "products.hpp"
/**
 * Trade Booking Service to book trades to a particular book.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template <typename T>
class BondTradeBookingService: public TradeBookingService<T>{
private:
    Trade<T> trade; // Dummy trade
    vector<ServiceListener<Trade<T>> *> Listeners;
public:
    Trade<T> &GetData(string key) override {
        return trade;
    }

    void OnMessage(Trade<T> &data) override {
        // Dummy method, output the workflow
        cout<<"Bood trade booking service has been called.\n";
    }

    void AddListener(ServiceListener<Trade<T>> *listener) override {
        Listeners.push_back(listener);
        cout<<"Add a listener to the BondTradeBookingService.\n";
    }

    const vector<ServiceListener<Trade<T>> *> &GetListeners() const override {
        return Listeners;
    }

    void BookTrade(const Trade<T> &trade) override {

    }
};






#endif //FALL2016_9815_HW06_BONDTRADEBOOKINGSERVICE_HPP
