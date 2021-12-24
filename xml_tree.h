/*
 * parse_tree.h
 *
 *  Created on: Dec 15, 2021
 *      Author: Kyrillos
 */

#ifndef XML_TREE_H_
#define XML_TREE_H_



#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <cctype>
#include "node.h"

std::string removeSpaces(const std::string &s);
std::vector<attribute> trim_attributes(std::string attr_string);
void parse_tree(Node *root, std::string xml_string);


#endif /* XML_TREE_H_ */
