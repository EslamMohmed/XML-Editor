/*
 * Node.cpp
 *
 *  Created on: Dec 15, 2021
 *      Author: Kyrillos
 */

#include "node.h"
using namespace std;

Node::Node() {
    // TODO Auto-generated constructor stub

}

Node::Node(std::string tag, std::string node_data, std::vector<attribute> node_attr)
    {
        name = tag;
        data = node_data;
        attr = node_attr;
    }
string Node::get_name()
    {
        return name;
    }
    void Node::set_name(std::string node_name)
    {
        name = node_name;
    }
    std::vector<attribute> Node::get_attr()
    {
        return attr;
    }
    void Node::set_attr(std::vector<attribute> node_attr)
    {
        attr = node_attr;
    }
    std::string Node::get_data()
    {
        return data;
    }
    void Node::set_data(std::string node_data)
    {
        data = node_data;
    }
    void Node::add_child(Node *child)
    {
        children.push_back(child);
    }
    Node* Node::pop_child()
    {
        Node *child = children.back();
        children.pop_back();
        return child;
    }
    std::vector<Node *> Node::get_children(){
        return children;
    }


Node::~Node() {
    // TODO Auto-generated destructor stub
}

