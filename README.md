# fall2016_9815_hw06 (Final Project)
## Hongchao Pan
## Team 16

<li> Notes: This is the final project of cpp part of MTH9815 (fall2016)</li>

### Compile instructions
<li> Please make sure install boost before compiling!</li>
<li> Compile method: g++ -std=c++11 -I <path_to_boost> main.cpp -o main_test</li>
<li> Then run the execute file as: ./main_test</li>
<li> Total running time is around 75-90 seconds (mostly on generating millions data)</li>

###Files 
<li>Input files(generated)</li>

<table>
   <tr>
   <td>trades.txt</td>
   </tr>
   <tr>
   <td>prices.txt</td>
   </tr>
   <tr>
   <td>marketdata.txt</td>
   </tr>
   <tr>
   <td>inquiries.txt</td>
   </tr>
   </table>

<li> Output files</li>
<table>
   <tr>
   <td>From Services</td>
   <td>From HistoricalDataService</td>
   </tr>
   <tr>
   <td>booked_risk.txt</td>
   <td>risk.txt</td>
   </tr>
   <tr>
   <td>inquiries_record.txt</td>
   <td>allinquiries.txt</td>
   </tr>
   <tr>
   <td>streaming_record.txt</td>
   <td>streaming.txt</td>
   </tr>
   <tr>
   <td>executed_order.txt</td>
   <td>execution.txt</td>
   </tr>
   </table>


###Documentation
<li> c++ IDE: Clion</li>
<li> Add a function, called "AddPosition(string _id, long _quantity)" to the class Position in the given
positionservice.hpp file</li>

<li> Adjust the BookTrade to be non-const in the tradebookingserice.hpp and derived classes.</li>

<li> Adjust the GetBucketRisk function from const to virtual</li>

<li> GetData function in soa.hpp never has been used, thereby avoid implementation of this method.</li>

<li> CUSIPs reference: https://www.treasurydirect.gov/instit/instit.htm

<li> Using uniform_real_distribution<double> uniD(3.0,4.0) to generate double numbers between 3 and 4 to be 
the coupon of a bond</li>

<li> Write a parse function by using boost::split</li>

<li> Move listener to the corresponding hpp file to avoid include conflict.</li>

<li> Define a new function called FlowData() to send all trades to the Bond trade booking service instead of using 
Publish function one by one.</li>

<li> Move positions in positionservice.hpp to be public</li>

<li> Add a default constructor of PV01<Bond>

<li> Create initial values of positions in positionservice.hpp through key (TRSY1/2/3) with value 1e6</li>

<li> Initialize the global variables through initialize_global_variables</li>

<li> Pricing branch use object instead of singleton</li>

<li> Implment the functions of services in the soa.hpp file to avoid duplicate implementation.</li>

<li> Implement the historical data service in the given historicaldataservice.hpp</li>

<li> Constructor must be defined before create an instance of sigleton</li>

<li> Execution branch: executed order has been written to a file called "executed_order.txt" contains the cusip of 
the bond, orderid, price, visibleQuantity of the executable order</li>

<li> BondTradeBooking branch: write aggregate position and cusip of the bonds to a file called "booked_risk"</li>

<li> Inquiry branch: write cusip, inquiry id, inquiry price and inquiry quantity to a file called "inquiries_record.txt"</li>

<li> Move all the output file to the historicalservice.hpp</li>

<li> Generate an instance of historicalservice by using singleton and created as a global varialbes in the 
 Global_variables_functions.hpp file</li>
