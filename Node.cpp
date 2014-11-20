using namespace std;
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Node.h"
#include "Rparser.h"
#include "Resistor.h"


//constructor for node
Node::Node(){
    numRes=0;
    voltage=0;
    resistors = new ResistorList();
    voltageSet=false;
}

//constructing using nodeid
Node::Node(int nodeID_){
    numRes=0;
    nodeID=nodeID_;
    voltage=0;
    resistors = new ResistorList();
    next=NULL;
    voltageSet=false;
}

Node::~Node(){
    //deletes resistor list and next
    delete resistors;
    delete next;
}


// Updates resIDArray to show the resistor in position rIndex in
   // the resistor array is now connected to this node.
   // Returns true if successful
bool Node::addResistor (int rIndex){
    //cout<<"in add resistor\n";
    numRes++;
    bool done=false;
    bool success=false;
    int counter=0;
    
    return success;
} 

bool Node::deleteResistor (int rIndex){
    
}

   // prints the whole node
   // nodeIndex is the position of this node in the node array.
void Node::print (int nodeIndex){
    
    cout<<"Connections at node "<<nodeIndex<<": "<<numRes<<" resistor(s)\n";
    resistors->printAllResistors();
    
    
}

void Node::setVoltage(float voltage_){
    voltage=voltage_;
    voltageSet=true;
}

void Node::unSetVoltage(float voltage_){
    voltage=voltage_;
    voltageSet=false;
}