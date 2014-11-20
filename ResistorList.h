/* 
 * File:   ResistorList.h
 * Author: Aser
 *
 * Created on November 2, 2014, 5:03 PM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H

#include "Resistor.h"

class ResistorList {
    friend class NodeList;
private:
    Resistor* head;
    Resistor* tail;
public:
    ResistorList();
    ResistorList(const ResistorList& orig);
    virtual ~ResistorList();
    
    bool insertResistor(string name, float resistance, int nodeID1, int nodeID2);
    Resistor* findRes(string name);
    bool deleteResistor(Resistor* ptr);
    void deleteAllResistors();
    void printAllResistors();
    bool getSurroundingNodesAndRes(int nodeID, int* &surroundingNodes, float* &resistances);
    bool ifSurroundingNodes(int nodeID);

};

#endif	/* RESISTORLIST_H */

