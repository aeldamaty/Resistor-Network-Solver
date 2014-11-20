using namespace std;
#include <string>
#include <iostream>
#include <iomanip>
#include "Resistor.h"

//constructor for resistors
Resistor::Resistor(string name_,float resistance_, int nodeID1, int nodeID2){
    name=name_;
    resistance=resistance_;
    endpointNodeIDs[0]=nodeID1;
    endpointNodeIDs[1]=nodeID2;
    next=NULL;
}

Resistor::~Resistor(){
}

string Resistor::getName() const{
    return name;
}
float Resistor::getResistance() const{
    return resistance;
}

//returns node id
int Resistor::getNode(int node)const{
}
//returns resistance
void Resistor::setResistance (float resistance_){
    resistance=resistance_;
}
        
// prints resistor
void Resistor::print (){
    cout<<left<<setw(20)<<name<<" "<<right<<setw(8)<<resistance<<" Ohms "<<endpointNodeIDs[0]<<"->"<<endpointNodeIDs[1]<<endl;
}
