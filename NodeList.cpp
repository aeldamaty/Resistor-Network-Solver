/* 
 * File:   NodeList.cpp
 * Author: Aser
 * 
 * Created on November 2, 2014, 5:04 PM
 */

#include "NodeList.h"
#include "ResistorList.h"
#include "Node.h"
#include "Resistor.h"
#include <cmath>
#define MIN_ITERATION_CHANGE 0.0001

NodeList::NodeList() {
    head=NULL;
}

NodeList::NodeList(const NodeList& orig) {
}

NodeList::~NodeList() {
    //deletes the head which calls the destructor for node which deletes next
    delete head;
}

//will find a node and return a pointer to it
Node* NodeList::findNode(int nodeID){
    Node* ptr;
    if(head==NULL) return NULL;
    else{
        ptr=head;
        while(ptr!=NULL){
            if(ptr->nodeID==nodeID)break;
            ptr=ptr->next;
        }
        return ptr;
    }
}

//will insert a node given a nodeid and return a pointer to it
Node* NodeList::insertNode(int nodeID){
    Node* ptr;
    //if head is null, list is empty and it inserts the node at the beginning
    if(head==NULL){
        head=new Node(nodeID);
        //tail=head;
        return head;
    }
    else{
        //everything in the else block is used to properly insert the node in the correct location based on ascending order
        ptr=head;
        bool done=false;

        while(ptr->next != NULL && !done){
            if(nodeID < head->nodeID){
                Node* temp = head;
                head = new Node (nodeID);
                head->next=temp;
                done=true;
                return head;
            }
            else if(nodeID > ptr->nodeID && nodeID < ptr->next->nodeID){
                Node* temp = ptr->next;
                ptr->next = new Node (nodeID);
                ptr->next->next = temp;
                done=true;
                return ptr->next;
            }
            ptr=ptr->next;
        }
        if(!done){
            ptr=head;
            while(ptr->next!=NULL) ptr=ptr->next;
            ptr->next = new Node(nodeID);
            return ptr->next;
        }
    }
}

//will find a node or insert a new one if it cant
void NodeList::findOrInsertNodeAndResistor(int nodeID1, int nodeID2, string name, float resistance){
    //this stores the nodeid so we can use it later, it then reverses the order of the nodeids if the first is higher than the second
    int nodeID1_=nodeID1;
    int nodeID2_=nodeID2;
    if(nodeID1>nodeID2){
        int temp = nodeID2;
        nodeID2=nodeID1;
        nodeID1=temp;
    }
    bool found=false;
    //if list is empty insert at the beginning 
    Node* ptr;
    if(head==NULL){
        head = new Node(nodeID1);
        head->next = new Node(nodeID2);
        //tail = head->next;
        head->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
        head->next->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
        head->numRes++;
        head->next->numRes++;
    }
    else{
        //insert each node in the correct position 
        ptr=head;
        while(ptr!=NULL){
            //cout<<"in while\n";
            if(ptr->nodeID == nodeID1){
                found=true;
                break;
            }
            ptr=ptr->next;
        }
        
        if(found){
            ptr->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
            ptr->numRes++;
        }
        else{
            ptr=head;
            bool done=false;
            
            while(ptr->next != NULL && !done){
                if(nodeID1 < head->nodeID){
                    Node* temp = head;
                    head = new Node (nodeID1);
                    head->next=temp;
                    head->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
                    head->numRes++;
                    done=true;
                }
                else if(nodeID1 > ptr->nodeID && nodeID1 < ptr->next->nodeID){
                    Node* temp = ptr->next;
                    ptr->next = new Node (nodeID1);
                    ptr->next->next = temp;
                    ptr->next->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
                    ptr->next->numRes++;
                    done=true;
                }
                ptr=ptr->next;
            }
            if(!done){
                ptr=head;
                while(ptr->next!=NULL) ptr=ptr->next;
                ptr->next = new Node(nodeID1);
                ptr->next->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
                ptr->next->numRes++;
            }
        }
        
        //for the second node
        found=false;
        ptr=head;
        while(ptr!=NULL){
            //cout<<"in while\n";
            if(ptr->nodeID == nodeID2){
                found=true;
                break;
            }
            ptr=ptr->next;
        }
        
        if(found){
            ptr->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
            ptr->numRes++;
        }
        else{
            ptr=head;
            bool done=false;
            
            while(ptr->next != NULL && !done){
                if(nodeID2 < head->nodeID){
                    Node* temp = head;
                    head = new Node (nodeID2);
                    head->next=temp;
                    head->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
                    head->numRes++;
                    done=true;
                }
                else if(nodeID2 > ptr->nodeID && nodeID2 < ptr->next->nodeID){
                    Node* temp = ptr->next;
                    ptr->next = new Node (nodeID2);
                    ptr->next->next = temp;
                    ptr->next->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
                    ptr->next->numRes++;
                    done=true;
                }
                ptr=ptr->next;
            }
            if(!done){
                ptr=head;
                while(ptr->next!=NULL) ptr=ptr->next;
                ptr->next = new Node(nodeID2);
                ptr->next->resistors->insertResistor(name, resistance, nodeID1_, nodeID2_);
                ptr->next->numRes++;
            }
        }
    }
}

//finds a resistor and returns true if it found it
bool NodeList::findResistor(string name){
    
    bool found=false;
    Node* ptr;
    
    if(head==NULL) return false;
    else{
        ptr=head;
        while(ptr!=NULL){
            if(ptr->resistors->findRes(name)!= NULL){
                found=true;
                break;
            }
            ptr=ptr->next;
        }
        return found;
    }
}

//finds a resistor and returns a pointer to it, used for print
Resistor* NodeList::findResistorPrint(string name){
    Node* ptr;
    
    if(head==NULL) return NULL;
    else{
        ptr=head;
        while(ptr!=NULL){
            if(ptr->resistors->findRes(name)!= NULL){
                return ptr->resistors->findRes(name);
                break;
            }
            ptr=ptr->next;
        }
    }
}

//changes resistance, returns true if successful
bool NodeList::changeResistance (string name, float resistance){
    bool changed=false;
    Node* ptr;
    Resistor* resPtr;
    
    if(head==NULL) return false;
    else{
        ptr=head;
        while(ptr!=NULL){
            resPtr = ptr->resistors->findRes(name);
            if(resPtr!=NULL){
                resPtr->setResistance(resistance);
                changed=true;
            }
            ptr=ptr->next;
        }
    } 
    return changed;
    
}

//deletes resistor, returns true if successful
bool NodeList::deleteResistor (string name, int &numberSet){
    bool deleted=false;
    bool checkThisNode=false;
    Node* ptr;
    Node* helperPtr;
    
    if(head==NULL) return false;
    else{
        ptr=head;
        helperPtr=head;
        Resistor* resPtr;
        while(ptr!=NULL){
            checkThisNode=false;
            resPtr=ptr->resistors->findRes(name);
            if(resPtr != NULL){
                ptr->resistors->deleteResistor(resPtr);
                ptr->numRes--;
                deleted=true;
            }
            helperPtr=ptr;
            ptr=ptr->next; 
        }
        return deleted;
    }
}

//deletes all resistors
bool NodeList::deleteAllResistors(){
    Node* ptr;
    Node* helperPtr;
    
    if(head==NULL) return true;
    else{
        
        
        ptr=head;
        while(ptr!=NULL){
            delete ptr->resistors;
            ptr->resistors = new ResistorList();
            ptr->numRes=0;
            ptr=ptr->next;
        }
    }
}

//prints all resistors
void NodeList::printAllResistors(){
    Node* ptr;
    
    if (head==NULL) return;
    else{
        ptr=head;
        while(ptr!=NULL){
            ptr->resistors->printAllResistors();
            ptr=ptr->next;
        }
    }
}

//prints all nodes
void NodeList::printNodeAll(){
    Node* ptr;
    
    if(head==NULL) return;
    else{
        ptr=head;
        while(ptr!=NULL){
            if(ptr->numRes==0){
                ptr=ptr->next;
            }
            else{
                ptr->print(ptr->nodeID);
                ptr=ptr->next;
            }
        }
    }
}

//used to solve
bool NodeList::solve(){
    bool done=false;
    //cout<<"Solve:\n";
    int* surroundingNodes;
    float* voltagesAroundNode;
    float* resistances;
    bool wentInOnce=false;
    
    while(!done){
        wentInOnce=false;
        done=true;
        float toMult1DenomSum=0;
        float toMult2Sum=0;
        Node* ptr=head;
        Node* helper;
        while(ptr!=NULL){
            float previousNodeV=ptr->voltage;
            if(!ptr->voltageSet){
                surroundingNodes = new int[ptr->numRes];
                voltagesAroundNode = new float[ptr->numRes];
                resistances = new float[ptr->numRes];
                bool gotIt = ptr->resistors->getSurroundingNodesAndRes(ptr->nodeID, surroundingNodes, resistances);
                if(gotIt){
                    wentInOnce=true;
                    for(int i=0;i<ptr->numRes;i++){
                        helper=findNode(surroundingNodes[i]);
                        if(helper!=NULL){
                            voltagesAroundNode[i]=helper->voltage;
                        }
                    }
                    for(int i=0;i<ptr->numRes;i++){
                        toMult1DenomSum=toMult1DenomSum + (1/resistances[i]);
                        toMult2Sum=toMult2Sum + (voltagesAroundNode[i]/resistances[i]);
                    }
                    ptr->voltage=(1/toMult1DenomSum)*(toMult2Sum);
                    float newNodeV=ptr->voltage;
                    if(fabs(newNodeV-previousNodeV)>MIN_ITERATION_CHANGE) done=false;
                }
                
                ptr=ptr->next;
                toMult1DenomSum=0;
                toMult2Sum=0;
                delete surroundingNodes;
                delete voltagesAroundNode;
                delete resistances;
                
            }
            else{
                ptr=ptr->next;
            }
            
        }
    }
    if(wentInOnce){
        cout<<"Solve:\n";
        Node* ptr=head;
        while(ptr!=NULL){
            bool print = ptr->resistors->ifSurroundingNodes(ptr->nodeID);
            if(print) cout<<" Node "<<ptr->nodeID<<": "<<ptr->voltage<<" V\n";
            if(!ptr->voltageSet)ptr->voltage=0.0;
            ptr=ptr->next;
        }
    }
    else{
        cout<<"Error: no nodes have their voltage set\n";
    }
    return true;
}