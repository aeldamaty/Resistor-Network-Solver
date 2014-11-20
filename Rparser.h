/* 
 * File:   Rparser.h
 * Author: eldamaty
 *
 * Created on October 7, 2014, 10:32 AM
 */

#ifndef RPARSER_H
#define	RPARSER_H

#endif	/* RPARSER_H */

//Node** nodeArray;
//Resistor** resistorArray;
//int nodeMax, resistorsMax, resistorLocation, nodeLocation;
using namespace std;

#include <string>
#include <iostream>
#include "NodeList.h"

void argumentfail();
void negativeres();
void invalidRange();
void cannotBeAll();
void sameNode(int nodeNum);
void tooManyArgs();
void tooFewArgs();

//int checkNameDelete(string name);
bool checkNamePrint(NodeList &list, string name, bool fail,bool search);
bool checkName (NodeList &list, string name, bool fail, bool search);
bool checkResistance(int resistance, bool fail, char peek);
bool checkResistanceModify(float resistance, bool fail, char peek, bool eof);
bool checkOneNode (int num1, int num2, bool fail, bool eof);
bool checkNodesInsertRes (NodeList, string name, float resistance, int node1, int node2, bool fail, bool eof);
bool modifyRes(NodeList &list, string name, float resistance);
void solve(NodeList &list);

int Rparser (); 