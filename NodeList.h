/* 
 * File:   NodeList.h
 * Author: Aser
 *
 * Created on November 2, 2014, 5:04 PM
 */

#ifndef NODELIST_H
#define	NODELIST_H

#include "Node.h"

#include <string>
#include <iostream>
using namespace std;

class NodeList {
private:
    Node* head;
    Node* tail;
public:
    NodeList();
    NodeList(const NodeList& orig);
    virtual ~NodeList();
    
    Node* findNode(int nodeID);
    Node* insertNode(int nodeID);
    void findOrInsertNodeAndResistor (int nodeID, int nodeID2, string name, float resistance);
    bool findResistor(string name);
    Resistor* findResistorPrint(string name);
    bool changeResistance (string name, float resistance);
    bool deleteResistor (string name, int &numberSet);
    bool deleteAllResistors();
    void printAllResistors();
    void printNodeAll();
    void previousSetNodes(int* &list, int &sizePrevSetNodes);
    bool solve();
};

#endif	/* NODELIST_H */

