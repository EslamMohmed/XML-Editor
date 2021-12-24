/*
 * Node.h
 *
 *  Created on: Dec 15, 2021
 *      Author: Kyrillos
 */

#ifndef NODE_H_
#define NODE_H_

#include<vector>
#include<iostream>
using namespace std;

#define COMMENT_TAG "xml,comment"
#define XML_TAG_s "XML,TAG"
typedef struct
{
    std::string name;
    int start_index;
} tag;


typedef struct
{
    std::string key;
    std::string value;
} attribute;


class Node {
private:
    std::string name;//to store tag name
    std::string data;// to store data
    std::vector<attribute> attr; // to store attributes
    std::vector<Node *> children; // to store children

public:
    Node();
    Node(std::string tag, std::string node_data, std::vector<attribute> node_attr = vector<attribute>());
    std::string get_name();
    void set_name(std::string node_name);
    std::vector<attribute> get_attr();
    void set_attr(std::vector<attribute> node_attr);
    std::string get_data();
    void set_data(std::string node_data);
    void add_child(Node *child);
    Node *pop_child();
    std::vector<Node *> get_children();
    virtual ~Node();
};

#endif /* NODE_H_ */
