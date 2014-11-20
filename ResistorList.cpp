/* 
 * File:   ResistorList.cpp
 * Author: Aser
 * 
 * Created on November 2, 2014, 5:03 PM
 */

#include "ResistorList.h"

ResistorList::ResistorList() {
    head=NULL;
    tail=NULL;
}

ResistorList::ResistorList(const ResistorList& orig) {
}

//destroys the resistorlist
ResistorList::~ResistorList() {
    if(head!=NULL){
        Resistor* helper=head;
        while(head != NULL){
            head=head->next;
            delete helper;
            helper=head;
        }
    }
}

bool ResistorList::insertResistor(string name, float resistance, int nodeID1, int nodeID2){
    if (head == NULL){
        head = new Resistor(name, resistance, nodeID1, nodeID2);
        tail=head;
    }
    else{
        tail->next = new Resistor(name, resistance, nodeID1, nodeID2);
        tail=tail->next;
    }
}

//returns pointer to resistor if it finds one otherwise null is returned
Resistor* ResistorList::findRes(string name){
    Resistor* ptr;
    bool found=false;
    
    if (head==NULL) return NULL;
    else{
        ptr=head;
        while(ptr!=NULL){
            if(ptr->name == name){
                found=true;
                break;
            }
            ptr=ptr->next;
        }
        if(found) return ptr;
        else return NULL;
    }
}

//deletes one resistor
bool ResistorList::deleteResistor(Resistor* ptrDelete){
    if(ptrDelete==head){
        head=head->next;
        delete ptrDelete;
    }
    else{
        Resistor* helperPtr=head;
        while(helperPtr->next != ptrDelete) helperPtr=helperPtr->next;
        helperPtr->next=ptrDelete->next;
        if(helperPtr->next==NULL) tail=helperPtr;
        delete ptrDelete;
    }
    
}

//deletes all resistors
void ResistorList::deleteAllResistors(){
    if (head==NULL) return;
    else{
        delete head;
        tail=NULL;
    }
}

//prints all resistors
void ResistorList::printAllResistors(){
    Resistor* ptr;
    
    if(head==NULL) return;
    else{
        ptr=head;
        while(ptr!=NULL){
            ptr->print();
            ptr=ptr->next;
        }
    }
}

//gets surrounding nodes, used for solve
bool ResistorList::getSurroundingNodesAndRes(int nodeID, int* &surroundingNodes, float* &resistances){
    bool wentIn=false;
    int counter=0;
    Resistor* ptr;
    ptr=head;
    while(ptr!=NULL){
        if(ptr->endpointNodeIDs[0]==nodeID) surroundingNodes[counter]=ptr->endpointNodeIDs[1];
        else surroundingNodes[counter]=ptr->endpointNodeIDs[0];
        resistances[counter]=ptr->resistance;
        counter++;
        ptr=ptr->next;
        wentIn=true;
    }
    return wentIn;
}

bool ResistorList::ifSurroundingNodes(int nodeID){
    bool wentIn=false;
    int counter=0;
    Resistor* ptr;
    ptr=head;
    if(ptr!=NULL) wentIn=true;
    return wentIn;
    
}