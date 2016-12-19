/**
 * positionservice.hpp
 * Defines the data types and Service for positions.
 *
 * @author Breman Thuraisingham
 */
#ifndef POSITION_SERVICE_HPP
#define POSITION_SERVICE_HPP

#include <string>
#include <map>
#include "soa.hpp"
//#include "tradebookingservice.hpp"
#include "assert.h"

using namespace std;

/**
 * Position class in a particular book.
 * Type T is the product type.
 */
template<typename T>
class Position
{

public:

    Position(){}
  // ctor for a position
  Position(const T &_product);

  // Get the product
  const T& GetProduct() const;

  // Get the position quantity
  long GetPosition(string &book);

  // Get the aggregate position
  long GetAggregatePosition();

    // Add a function to add the postion to the positions in the Position class
    void AddPosition(string _id, long _amount);

    // Create initial positions value through book (TRSY1/2/3)
    void init_position();


    map<string,long> positions;
private:
  T product;
  //map<string,long> positions;

};

/**
 * Position Service to manage positions across multiple books and secruties.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PositionService : public Service<string,Position <T> >
{

public:

  // Add a trade to the service
    // No need this function
  //virtual void AddTrade(Trade<T> &trade) = 0;

};

template<typename T>
Position<T>::Position(const T &_product) :
  product(_product)
{
}

template<typename T>
const T& Position<T>::GetProduct() const
{
  return product;
}

template<typename T>
long Position<T>::GetPosition(string &book)
{
  return positions[book];
}

template<typename T>
long Position<T>::GetAggregatePosition() {
    // implementation of GetAggregatePosition
    long res = 0;
    string str = "TRSY";    // For TRSY1, TRSY2, TRSY3
    for (int i = 1; i <= 3; i++) {
        string key = str + std::to_string(i);
        res += positions.at(key);
    }
    return res;

}

// Add a function to add the postion to the positions in the Position class
template <typename T>
void Position<T>::AddPosition(string _id, long _amount) {
    cout<<"AddPosition in Position<Bond> has been called\n";

    // Add a new postion
    assert(positions.find(_id)!=positions.end());
    positions[_id]+=_amount;

}

template <typename T>
void Position<T>::init_position() {
    //cout<<"Initial position of Position<Bond>\n";
    positions["TRSY1"]=long(1e6);
    positions["TRSY2"]=long(1e6);
    positions["TRSY3"]=long(1e6);


}



#endif
