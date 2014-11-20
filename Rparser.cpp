/*
 * File:   Parser.cpp
 * Author: eldamaty
 *
 * Created on September 23, 2014, 10:14 AM
 */

#include "NodeList.h"


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Node.h"
#include "Resistor.h"

#define MIN_NODE_NUMBER 0
#define MAX_NODE_NUMBER 5000

Node** nodeArray;
Resistor** resistorArray;
int nodeMax, resistorsMax, resistorLocation, nodeLocation, resistorArrayPos;

using namespace std;

//The following functions will be used to print the error messages.
void argumentfail(){
    cout<<"Error: invalid argument\n";
}

void negativeres(){
    cout<<"Error: negative resistance\n";
}

void invalidRange(int x){
    cout<<"Error: node " << x << " is out of permitted range " << MIN_NODE_NUMBER << "-" << nodeMax << "\n";
}

void cannotBeAll (){
    cout<<"Error: resistor name cannot be the keyword \"all\"\n";
}

void sameNode (int nodeNum){
    cout<<"Error: both terminals of resistor connect to node "<<nodeNum<<"\n";
}

void tooManyArgs(){
    cout<<"Error: too many arguments\n";
}

void tooFewArgs(){
    cout<<"Error: too few arguments\n";
}

void maxValRange(){
    cout<<"Error: maxVal arguments must be greater than 0\n";
}

//The following functions will be used for most of the error checking 

//This function is used to check the name, making sure that the user actually entered a name

bool checkNamePrint(NodeList* &list, string name, bool fail,bool search){
    if(!fail){
        if (name == "all"){
            return true;
        }
        if (search){
            bool found = list->findResistor(name);
            if(!found){
                cout<<"Error: resistor "<<name<<" not found\n";
                return false;
            }
            else return true;
        }
    }
    else{
        tooFewArgs();
        return false;
    }
    return false;
}

//makes sure a name is entered and that it isn't all and it matches a name in the array
 bool checkName(NodeList* &list, string name, bool fail, bool search){
    if (!fail){
        if (name == "all"){
            cannotBeAll();
            return false;
        }
        if (search){
            bool found = list->findResistor(name);
            if(!found){
                cout<<"Error: resistor "<<name<<" not found\n";
                return false;
            }
            else return true;
        }
        else{
            bool found = list->findResistor(name);
            if(found){
                cout<<"Error: resistor "<<name<<" already exists\n";
                return false;
            }
            else return true;
        }
        
    }
    else{
        tooFewArgs();
        return false;
    }
}

//makes sure resistance is greater than zero
bool checkResistance(int resistance, bool fail, char peek){  
    if(fail){
            if(resistance==0) argumentfail();
            else tooFewArgs();
            return false;
    }
    else{
        if (resistance<0 && peek==' '){
            negativeres();
            return false;
        }
        else if(resistance<0 && peek!=' '){
            argumentfail();
            return false;
        }
        else return true;
    }
}

bool checkResistanceModify(int resistance, bool fail, char peek, bool eof){   
    if(fail&&!eof){
            if(resistance==0) argumentfail();
            else tooFewArgs();
            return false;
    }
    
    else{
        
        if (resistance<0){
            negativeres();
            return false;
        }
        
        else return true;
        
    }
}

//checks one node to make sure it is an integer and within the valid range
bool checkOneNode (int num1, int num2, bool fail, bool eof){

    if(fail){
        if(eof){
           return true;
        }
        else{
            argumentfail();
            return false;
        }
    }
    else{
        tooManyArgs();
        return false;
    }
    
}

//will look for the node to see if it exists, if not it will create a new one, then resistor will be added to both nodes
bool checkNodesInsertRes (NodeList* &list, string name, float resistance, int node1, int node2, bool fail, bool eof){
    if (fail){
        if(eof){
            if(node1==node2){
                sameNode(node1);
                return false;
            }
            else{
                //check to see if nodes exist, if not create them
                list->findOrInsertNodeAndResistor(node1, node2, name, resistance);
            }
        }
        else{
            argumentfail();
            return false;
        }
    }
    else{
        if(node1==node2){
            sameNode(node1);
            return false;
        }
        else{
            tooManyArgs();
            return false;
        }
    }
}


bool modifyRes(NodeList* &list, string name, float resistance){
    Resistor* res = list->findResistorPrint(name);
    float originalResistance = res->getResistance();
    list->changeResistance(name, resistance);
    cout<<"Modified: resistor "<<name<<" from "<<originalResistance<<" Ohms"<<" to "<<resistance<< " Ohms"<<endl;
    
}

void solve(NodeList* &list){
    bool done = list->solve();
}

//main function
int Rparser() {
    NodeList* list = new NodeList();//
    int numberSet=0;
    //used to make sure the floats are displayed to two decimal places
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    
    //will be used later
    string line, command, name, extras;
    float resistance;
    int nodeid1, nodeid2;
    
    cout<<"> ";
    getline(cin, line);

    while (!cin.eof()){

        stringstream linestream (line);
        linestream >> command;

        //The following list of ifs are used to determine what command is given, and then proceeds to evaluate the command and test for errors
        //Should it match none, it will print an invalid command
        //If user enters ^D, then the programs exits
        
        //the basic format is read one thing, then check for errors, then move on to the next, if it cant read then too few args
        //some error checking is sometimes done here instead of in above functions for simplicity
        
        if(command == "insertR"){
            int other;
            bool keepGoing=true;
            bool search=false;
            
            linestream >> name;
            keepGoing=checkName(list, name, linestream.fail(),search);

            if (keepGoing){
                linestream >> resistance;
                keepGoing=checkResistance(resistance, linestream.fail(), linestream.peek());
            }

            if (keepGoing){
               
                linestream >> nodeid1;
                if (linestream.fail()){
                    if(linestream.eof()){
                        tooFewArgs();
                        keepGoing=false;
                    }
                    else{
                        argumentfail();
                        keepGoing=false;
                    }
                }
                else{
                    linestream.clear();
                    linestream >> nodeid2;
                    if (linestream.fail()){
                        if(linestream.eof()){
                            tooFewArgs();
                            keepGoing=false;
                        }
                        else{
                            argumentfail();
                            keepGoing=false;
                        }
                    }
                }
                
                
                linestream.clear();
                if(keepGoing){
                    linestream >> other;
                    //will look for nodes, make a new one if it doesn't exist then add the resistor
                    keepGoing=checkNodesInsertRes(list, name, resistance, nodeid1, nodeid2, linestream.fail(), linestream.eof());
                    cout<<"Inserted: resistor "<<name<<" "<<resistance<<" Ohms "<<nodeid1<<" -> "<<nodeid2<<endl;
                }
                
            }

            if (keepGoing){
                if (linestream.peek()!= 32 && linestream.peek()>0){
                    argumentfail();
                }
                else{
                    linestream >> extras;
                    if (!linestream.fail()){
                        tooManyArgs();
                        keepGoing=false;
                    }
                    else{
                        //adds the resistor to the two nodes and makes a resistor in the array if successful
                        
                        
                    }
                }

            }

        }
        else if (command == "modifyR"){

            int previousRes;
            bool keepGoing=true;
            bool search=true;
            
            linestream >> name;
            keepGoing=checkName(list, name, linestream.fail(),search);

            if (keepGoing){
                linestream >> resistance;
                keepGoing=checkResistanceModify(resistance, linestream.fail(),linestream.peek(),linestream.eof());
            }

            if (keepGoing){
                if(linestream.peek()!=32 && linestream.peek()>0){
                    argumentfail();
                }
                else {
                    linestream>>extras;
                    if (!linestream.fail()){
                        tooManyArgs();
                        keepGoing=false;
                    }
                    else{
                        //modifys the resistance of a resistor
                        bool modified=modifyRes(list, name, resistance);
                        //cout<<"Modified: resistor "<<name<<" from "<<previousR<<" Ohms"<<" to "<<resistance<< " Ohms"<<endl;
                    }
                }

            }
        }
        else if (command == "printR"){
            bool keepGoing=true;
            bool search=true;
            
            linestream >> name;
            keepGoing=checkNamePrint(list, name, linestream.fail(),search);
            
            if (keepGoing){
                linestream >> extras;
                if (!linestream.fail()){
                    tooManyArgs();
                    keepGoing=false;
                }
                else{
                    cout<<"Print:\n";
                    if (name=="all"){
                        list->printAllResistors();
                    }
                    else{
                        Resistor* resToPrint = list->findResistorPrint(name);
                        resToPrint->print();
                    }
                }
            }
        }
        else if (command == "printNode"){
            bool keepGoing=true;
            bool printAll=true;
            int num,num2;
            linestream >> num;
            if(linestream.fail()){
                linestream.clear();
                linestream >> name;
                if(linestream.fail()){
                    tooFewArgs();
                    keepGoing=false;
                }
                else keepGoing=true;
            }
            else{
                printAll=false;
                linestream >> num2;
                keepGoing=checkOneNode(num,num2,linestream.fail(),linestream.eof());
            }

            if (keepGoing){
                cout<<"Print:\n";
                if(printAll){
                    list->printNodeAll();
                }
                else{
                    Node* temp = list->findNode(num);
                    if(temp!=NULL){
                        temp->print(num);
                    }
                }
            }
        }
        else if (command == "deleteR"){
            bool keepGoing=true;
            bool search=true;
            linestream >> name;

            if (name=="all"){
                list->deleteAllResistors();
                //numberSet=0;
                cout<<"Deleted: all resistors\n";
            }
            else{
                keepGoing=checkName(list, name, linestream.fail(),search);

                if (keepGoing){
                    linestream >> extras;
                    if (!linestream.fail()){
                        tooManyArgs();
                        keepGoing=false;
                    }
                    else{
                        //delete specified resistor
                        bool deleted=list->deleteResistor(name, numberSet);
                        if(deleted){
                            cout<<"Deleted: resistor "<<name<<endl;
                        }
                    }
                }
            }
        }
        else if (command=="setV"){
            int nodeID;
            float volts;
            linestream >> nodeID;
            linestream >> volts;
            
            Node* nodeToSet=list->findNode(nodeID);
            if(nodeToSet != NULL){
                nodeToSet->setVoltage(volts);
            }
            else{
                nodeToSet=list->insertNode(nodeID);
                nodeToSet->setVoltage(volts);
            }
            numberSet++;
            cout<<"Set: node "<<nodeID<<" to "<<volts<<" Volts\n";
        }
        else if (command=="unsetV"){
            int nodeID;
            linestream >> nodeID;
            
            Node* nodeToSet=list->findNode(nodeID);
            if(nodeToSet != NULL){
                nodeToSet->unSetVoltage(0.0);   
                numberSet--;
            }
            cout<<"Unset: the solver will determine the voltage of node "<<nodeID<<endl;
        }
        else if (command=="solve"){
            if(numberSet>0){
                solve(list);
            }
            else{
                cout<<"Error: no nodes have their voltage set\n";
            }
        }
        else{
            cout<<"Error: invalid command"<<"\n";
        }
        
        cout<<"> ";
        linestream.clear();
        getline(cin, line);
    }
    //cout<<"exiting\n";
    delete list;
    return 0;
}


