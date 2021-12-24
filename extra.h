#ifndef EXTRA_H
#define EXTRA_H

#include "mainwindow.h"
#include <QApplication>
#include <QByteArray>
#include <QDebug>
#include<vector>
#include <bits/stdc++.h>
#include "Node.h"
#include <unordered_map>

using namespace std;

struct Match_Pointer{
    int begin;
    int length;
    Match_Pointer(int begin,int length);
};


//detect error and correct
vector<pair<string,int>>detecterrors(vector<string> xml_data);


//correct error
string correcterrors(vector<string> xml_data);


//string format(string t);
vector<string>string_to_vector(string line);
string Minify(string s);
string format(vector<string> t);
bool findChar(char x, string y);



//compression and decompression
QString decompression(QByteArray& compressed);
vector<int> compression(string s1);
string decompression(vector<int> op);

//xml to json

int XML_TO_JSON(Node *root, int level, std::string *input, std::vector<Node *> children_data_arr = std::vector<Node *>());

#endif // EXTRA_H
