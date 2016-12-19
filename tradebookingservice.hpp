/**
 * tradebookingservice.hpp
 * Defines the data types and Service for trade booking.
 *
 * @author Breman Thuraisingham
 */
#ifndef TRADEBOOKINGSERVICE_HPP
#define TRADEBOOKINGSERVICE_HPP

#include <string>
#include <vector>
#include "soa.hpp"
//#include "Global_variables_functions.hpp"

// Trade sides
enum Side { BUY, SELL };

/**
 * Trade object with a price, side, and quantity on a particular book.
 * Type T is the product type.
 */
template<typename T>
class Trade
{

public:

  // ctor for a trade
  Trade(const T &_product, string _tradeId, string _book, long _quantity, Side _side);
    // Dummy Trade ctor
    Trade(){};

  // Get the product
  const T& GetProduct() const;

  // Get the trade ID
  const string& GetTradeId() const;

  // Get the book
  const string& GetBook() const;

  // Get the quantity
  long GetQuantity() const;

  // Get the side
  Side GetSide() const;

private:
  T product;
  string tradeId;
  string book;
  long quantity;
  Side side;

};

/**
 * Trade Booking Service to book trades to a particular book.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class TradeBookingService : public Service<string,Trade <T> >
{

public:

  // Book the trade
  //void BookTrade(const Trade<T> &trade) = 0;
    virtual void BookTrade(Trade<T> &trade) = 0;

};

template<typename T>
Trade<T>::Trade(const T &_product, string _tradeId, string _book, long _quantity, Side _side) :
  product(_product)
{
  tradeId = _tradeId;
  book = _book;
  quantity = _quantity;
  side = _side;
}

template<typename T>
const T& Trade<T>::GetProduct() const
{
  return product;
}

template<typename T>
const string& Trade<T>::GetTradeId() const
{
  return tradeId;
}

template<typename T>
const string& Trade<T>::GetBook() const
{
  return book;
}

template<typename T>
long Trade<T>::GetQuantity() const
{
  return quantity;
}

template<typename T>
Side Trade<T>::GetSide() const
{
  return side;
}


#endif
