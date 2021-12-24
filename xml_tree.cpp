/*
 File Name   : XML_Tree.cpp
 Description : building a tree from an XML file
 Algorithm   : get an xml string
               check of this string if it is consist of
                                                      xml tag <? ?>
                                                      comment tag <!-- --!>
                                                      openting tag <tag>
                                                      empty tag <tag />
                                                      closing tag </ tag>
                if it was an opening tag we make it as a child to the top element in the stack
                and then push him in the stack to be the top element untill its closing come
                so we pop it.

                if it was an empty tag we get the tag name and attributes and make him a child to the
                top element in the stack

                if it is an xml tag or comment tag we get the data from them and make them children
                to the top element in the stack
 */


#include "XML_Tree.h"



/*
 * function to parse XML code line by line
 * analysis the XML file according to its syntix
 * and get the tag , attributes, data , comments
 */

void parse_tree(Node *root, string xml_string)
{
    std::stack<Node *> node_stack; // to store pointers to every node
    node_stack.push(root);//pushing root as the first element

    int xmlTags = 0; // variable used for this tag <? ?>

    std::string tag, attr, data;// to store tag and attributes and data

    std::vector<attribute> attr_vector; //to store attributes

    for (size_t i = 0; i < xml_string.size(); i++)
    {

        /*****************************************
         * the first line
         *  <?   ?>
         *******************************************/
        if (xml_string[i] == '<' && xml_string[i + 1] == '?')
        {

            i += 2;
            for (; xml_string[i] != '?' && xml_string[i + 1] != '>'; i++)//take the data about xml an put iy into data
            {
                data.push_back(xml_string[i]);
            }
            if (!xmlTags)//true in the first time
            {
                //put this data in the root
                node_stack.top()->set_data(data);
                xmlTags++;
            }
            // if it is Not the first time
            else
            {
                Node *temp = new Node("XML,TAG", data);//else put this data in a child
                node_stack.top()->add_child(temp);//make a child to the top element in the stack
            }

            data.clear();
            i += 2;
        }
        /*****************************************
        * comment in xml
        *  <!-- comment  -->
        *******************************************/
        else if (xml_string[i] == '<' && xml_string[i + 1] == '!')
        {
            i += 4;
            for (; xml_string[i] != '-'; i++)
            {
                data.push_back(xml_string[i]);
            }

            Node *temp = new Node(COMMENT_TAG, data);
            data.clear();
            node_stack.top()->add_child(temp);
            i += 2;
        }

        /*****************************************
        * Openning Tag
        *  <tag>
        *******************************************/

        else if (xml_string[i] == '<' && xml_string[i + 1] != '/')
        {
            i++;
            for (; xml_string[i] != '>' && xml_string[i] != ' ' && xml_string[i] != '/'; i++)
            {
                // getting the tag name
                tag.push_back(xml_string[i]);
            }
            /*
             * if there are any attributes in the tag
             */
            if (xml_string[i] == ' ')
            {
                i++;
                for (; xml_string[i] != '>'; i++)
                {
                    //get the attribute
                    attr.push_back(xml_string[i]);
                }
                /*
                 * check if it an empty tag
                 * <a/>
                 * has no data only a tag and attribute without a closing or data
                 */
                if (xml_string[i - 1] == '/')
                {
                    i--;
                }
                attr_vector = trim_attributes(attr);
                attr.clear();
            }
            //put it as a child to the root
            Node *temp = new Node(tag, data, attr_vector);
            node_stack.top()->add_child(temp);

            if (xml_string[i] == '/')
            {
                /*
                 * as empty tag has no data
                 */
                temp->set_data("null");
                i++;
            }

            /*
             * if it isNot an empty tag
             * it will be pushed in the stack till its closing come
             */
            else
            {
                node_stack.push(temp);
            }
            /*
             * clearing tag and attribute value
             */
            tag.clear();
            attr_vector.clear();
        }

        /*
         * if it is a CLOSING TAG
         * </ tag>
         */
        else if (xml_string[i] == '<' && xml_string[i + 1] == '/')
        {
            data = removeSpaces(data);
            node_stack.top()->set_data(data);
            //incrementing i
            i += node_stack.top()->get_name().length() + 2;
            //poping from stack
            node_stack.pop();
            data.clear();
        }
        /*
         * check if it is a data between to tags
         * <opennig tag> data <\closing tag>
         */
        else if (xml_string[i] != '\n' && xml_string[i] != '\r' && xml_string[i] != ' ')
        {
            for (; xml_string[i] != '<'; i++)
            {
                if (xml_string[i] != '\n' && xml_string[i] != '\r')
                {
                    data.push_back(xml_string[i]);
                }
            }
            i--;
        }
    }
}


//to remove all white spaces from the start and the end
string removeSpaces(const string &s)
{
    auto start = s.begin();
    while (start != s.end() && isspace(*start))
    {
        start++;
    }

    auto end = s.end();
    do
    {
        end--;
    } while (distance(start, end) > 0 && isspace(*end));

    return std::string(start, end + 1);
}

/*
 * to get the attribute key and value
 */
vector<attribute> trim_attributes(string attr_string)
{
    attribute attr;
    vector<attribute> attr_vector;
    bool key_ready = 0, value_ready = 0;
    for (size_t i = 0; i < attr_string.length(); i++)
    {
        if (attr_string[i] != ' ')
        {
            if (attr_string[i] == '"')
            {
                i++;
                for (; attr_string[i] != '"'; i++)
                {
                    attr.value.push_back(attr_string[i]);
                }
                key_ready = 1;
            }
            else
            {
                for (; attr_string[i] != '=' && attr_string[i] != ' ' && attr_string[i] != '\n' && attr_string[i] != '\r'; i++)
                {
                    attr.key.push_back(attr_string[i]);
                }
                value_ready = 1;
            }
        }
        if (value_ready && key_ready)
        {
            attr_vector.push_back(attr);
            attr.key.clear();
            attr.value.clear();
            value_ready = 0;
            key_ready = 0;
        }
    }
    return attr_vector;
}
