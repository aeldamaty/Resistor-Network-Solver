#ifndef NODE_H
#define NODE_H

#define MAX_RESISTORS_PER_NODE 5

#include "ResistorList.h"

class Node
{
    friend class NodeList;
private:
    
   int numRes; // number of resistors currently connected
   int nodeID;
   float voltage;
   ResistorList* resistors;
   Node* next;
   bool voltageSet;
   
public:
   Node();
   Node(int nodeID_);
   ~Node();

   //ResistorList getResistors();
   
   // Updates resIDArray to show the resistor in position rIndex in
   // the resistor array is now connected to this node.
   // Returns true if successful
   bool addResistor (int rIndex); 
   bool deleteResistor (int rIndex);
   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void print (int nodeIndex);
   void setVoltage (float voltage_);
   void unSetVoltage (float voltage_);

};

#endif	/* NODE_H */

