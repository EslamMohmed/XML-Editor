#include "mainwindow.h"
#include "extra.h"
#include<string>


/*****************************************************
 * ******************check errors*********************
 * **************************************************/
vector<pair<string,int>>detecterrors(vector<string> xml_data) {
    vector<pair<string,int>>errors;
    stack <string>  tag_stack;
    string tag="";

    for(size_t i=0;i < xml_data.size();i++) {
        // pushing in the stack
        if (xml_data[i][0] == '<' && xml_data[i][1] != '!' && xml_data[i][1] != '?' && xml_data[i][1] != '/') {
            int j =1;    // to cut the chars of the tag
            tag ="";
            while (xml_data[i][j] != ' '&& xml_data[i][j] != '>') {
                tag += xml_data[i][j];
                j++;
            }
            tag_stack.push(tag);
        }
        //poping from the stack
        else if (xml_data[i][0] == '<' && xml_data[i][1] == '/') {
            int j =2;
            tag ="";
            while (xml_data[i][j] != ' ' && xml_data[i][j] != '>') {
                tag += xml_data[i][j];
                j++;
            }
            if(!tag_stack.empty()){
                if (tag_stack.top() == tag) {
                    tag_stack.pop();
                }
                else{
                    errors.push_back({tag,i});
                    tag_stack.pop();

                }
            }
        }
    }

    /*
      <usere>
           <aboud>
                <id></id>
            </abdou>

      */
    int k =xml_data.size();
    if(!tag_stack.empty()){
        errors.push_back({tag_stack.top(),k} );
        k++;
        tag_stack.pop();
    }
    return errors;
}


/*****************************************************
 * ******************correct errors*******************
 * **************************************************/


string correcterrors(vector<string> xml_data){
    stack <string>  tag_stack;
    string output="";
    string tag="";
    for(size_t i=0;i < xml_data.size();i++) {
        // pushing in the stack
        if (xml_data[i][0] == '<' && xml_data[i][1] != '!' && xml_data[i][1] != '?' && xml_data[i][1] != '/') {
            int j =1;    // to cut the chars of the tag
            tag ="";
            output += xml_data[i];
            while (xml_data[i][j] != ' '&& xml_data[i][j] != '>') {
                tag += xml_data[i][j];
                j++;
            }
            tag_stack.push(tag);
        }
        //poping from the stack
        else if (xml_data[i][0] == '<' && xml_data[i][1] == '/') {
            int j =2;
            tag ="";
            while (xml_data[i][j] != ' ' && xml_data[i][j] != '>') {
                tag += xml_data[i][j];
                j++;
            }
            if(!tag_stack.empty()){
                if (tag_stack.top() == tag) {
                    output += xml_data[i];
                    tag_stack.pop();
                }
                else{
                    output+="</"+tag_stack.top()+">";
                    tag_stack.pop();
                }
            }
        }
        //to show the text
        else {
            output+=xml_data[i];
        }
    }

    if(!tag_stack.empty()){
        output+="</"+tag_stack.top()+">";
        tag_stack.pop();
    }
    return output;
}

/*****************************************************
 * *********************minifying*********************
 * **************************************************/

string Minify(string s) {
    /// Stores the output XML text.
    string minified;
    bool newline = false;

    for(int i=0; i<s.length(); i++) {
        /// Deleting spaces and taps
        if(s[i] == '\n' || s[i] == '\t') {
            newline=true;
            continue;
        }

        /// Deleting unnecessary spaces.
        if(newline) {
            if(s[i] == ' ') {continue;}
            else            {newline=false;}
        }

        /// If we encountered a char other than newlines and taps, add it to the output text.
        minified.append(1, s.at(i));
    }
    /// return the minified XML.
    return minified;
}

vector<string>string_to_vector(string line) {
    vector<string> xml;
    line=Minify(line);
    string temp;
    int new_i = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '<' && (line[i + 1] != '!' && line[i + 1] != '?')) {
            new_i = line.find('>', i);
            temp = line.substr(i, new_i + 1 - i);
            xml.push_back(temp);
            i = new_i - 1;
        }
        else if (line[i] == '>' && i != line.length() - 1 && line[i + 1] != '<') {
            new_i = line.find('<', i);
            temp =line.substr(i + 1, line.length() - i);
            for (int j = 0; j < temp.length(); j++) {
                if (temp[j] == ' ') {
                    if (temp[j] == ' ') {
                        if (j == 0) {
                            temp.erase(j, 1);
                            j--;
                        }
                        else if (j == temp.length() - 1) {
                            temp.erase(j, 1);
                            j = temp.length() - 2;
                        }
                    }
                }
            }
            if (new_i == -1 && !temp.empty()) {
                xml.push_back(temp);
                i = line.length();
            }
            else {
                temp =line.substr(i + 1, new_i - 1 - i);
                for (int j = 0; j < temp.length(); j++) {
                    if (temp[j] == ' ') {
                        if (j == 0) {
                            temp.erase(j, 1);
                            j--;
                        }
                        else if (j == temp.length() - 1) {
                            temp.erase(j, 1);
                            j = temp.length() - 2;
                        }
                    }
                }
                if (!temp.empty()) {
                    xml.push_back(temp);
                }
                i = new_i - 1;
            }
        }
    }
    return xml;
}



/*****************************************************
 * *********************formatting********************
 * **************************************************/

bool findChar(char x, string y) {
    for (int i = 0; i < y.length(); i++) {
        if (y[i] == x) {
            return 1;
        }
    }
    return 0;
}

string format(vector<string> t) {
    string str="";
    int ind = 0;
    int openflag = 0;
    int closeflag = 0;

    for (int i = 0; i < t.size(); i++) {
        if(t[i]=="") continue;
        if (t[i][0] == '<' && (t[i][1] == '?' || t[i][1] == '!')) {
            // cout << t[i] << endl;		//print output
            str=str+t[i]+"\n";
        }
        else if (t[i][0] == '<' && !findChar('/', t[i])) {
            openflag++;
            closeflag = 0;
            if (openflag > 1) {
                ind++;
            }
            for (int j = 0; j < ind; j++) {
                //     cout << "\t";		//print tab
                str+="    ";
            }
            //  cout << t[i] << endl;	//print output
            str=str+t[i]+"\n";

        }
        else if (t[i][0] == '<' && t[i][1] == '/') {
            closeflag++;
            openflag = 0;
            if (closeflag > 1) {
                ind--;
            }
            for (int j = 0; j < ind; j++) {
                //  cout << "\t";		//print tab
                str+="    ";
            }
            //  cout << t[i] << endl;	//print output
            str=str+t[i]+"\n";

        }
        else if (t[i][0] == '<' && findChar('/', t[i])) {
            openflag++;
            closeflag = 0;
            if (openflag > 1) {
                ind++;
            }
            for (int j = 0; j < ind; j++) {
                //  cout << "\t";		//print tab
                str+="    ";
            }
            //  cout << t[i] << endl;	//print output
            str=str+t[i]+"\n";
            closeflag++;
            openflag = 0;
            if (closeflag > 1) {
                ind--;
            }
        }

        else {
            for (int j = 0; j < ind; j++) {
                // cout << "\t";		//print tab
                str+="    ";
            }
            //  cout << t[i] << endl;	//print output
            str=str+t[i]+"\n";

        }
    }
    return str;
}



/*****************************************************
 * **********************compression******************
 * **************************************************/
vector<int> compression(string s1)
{
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    output_code.push_back(table[p]);
    return output_code;
}

/*****************************************************
 * ********************decompression******************
 * **************************************************/

string decompression(vector<int> op)
{
    string out = "";
    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = op[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
    cout << s;
    int count = 256;
    for (int i = 0; i < op.size() -1 ; i++) {
        n = op[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }
        out += s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
    return out;
}

/*****************************************************
 * ********************xml to json********************
 * **************************************************/

int XML_TO_JSON(Node *root, int level, string *input, vector<Node *> children_data_arr)
{

    if (root->get_name() == COMMENT_TAG || root->get_name() == "XML,TAG")
    {
        return 0;
    }

    // Copying Root children
    vector<Node *> children = root->get_children();

    map<string, vector<Node *>> children_data_map;
    map<string, int> children_data_wait;
    int remaining_children = 0;

    if (children.size())
    {
        for (auto child : children)
        {
            // if the the child wasnt a comment or xml tag
            // we put them in the map to trace them
            if (child->get_name() != COMMENT_TAG && root->get_name() != "XML,TAG")
            {
                children_data_map[child->get_name()].push_back(child);
                children_data_wait[child->get_name()] = 1;
            }
        }
    }


    for (int i = 0; i < level + 1; i++)
    {
        *input += "    ";
    }

    // if its the beginng of the xml
    if (root->get_name() == "XML")
    {
        // print the first "{" in the json

        *input += "{\n";
    }
    else
    {
        // if t wasn`t the first line and it has children we print its name and [{\n
        if (children.size() || root->get_attr().size())
        {
            if (children_data_arr.size() > 1)
            {
                if (root == children_data_arr.front())
                {
                    //printing<< "root name": [{
                    *input += "\"" + root->get_name() + "\": [{\n";
                }
                else
                {
                    *input += "{\n";
                }
            }
            else // if it has no children or attributes
            {
                *input += "\"" + root->get_name() + "\": {\n";
            }


            //  printing attributes

            if (root->get_attr().size())
            {
                for (auto attr : root->get_attr())
                {
                    //printing white spaces to represent levels
                    for (int i = 0; i < level + 2; i++)
                    {
                        *input += "    ";
                    }



                     // adding attribute key highlighted and its value
                     //  printing "@attribute key" : "value"


                    *input += "\"@" + attr.key + "\": " + "\"" + attr.value + "\"";

                    //if there are no attributes print new line

                    if (attr.key == root->get_attr().back().key && attr.value == root->get_attr().back().value && root->get_data().empty() && children.empty())
                    {
                        *input += "\n";
                    }
                    //else printing "," and newline to continue printing attributes
                    else
                    {
                        *input += ",\n";
                    }
                }

                if (!root->get_data().empty())
                {
                    size_t index = 0;
                    while (true)
                    {

                        index = root->get_data().find("\"", index);

                        //if it doesn`t have "
                        if (index == string::npos)
                            break;

                        string data = root->get_data();
                        //remove " and adding \" instead
                        data.replace(index, index + 1, "\\\"");
                        root->set_data(data);
                        index += 2;
                    }
                    for (int i = 0; i < level + 2; i++)
                    {
                        *input += "    ";
                    }
                    *input += "\"title\": \"" + root->get_data() + "\"\n";
                    for (int i = 0; i < level + 1; i++)
                    {
                        *input += "    ";
                    }
                    *input += "}";
                }
            }
        }


        else
        {
            size_t index = 0;
            while (true)
            {
                index = root->get_data().find("\"", index);
                if (index == std::string::npos)
                    break;
                std::string data = root->get_data();
                data.replace(index, index + 1, "\\\"");
                root->set_data(data);
                index += 2;
            }
            if (children_data_arr.size() > 1)
            {
                if (root == children_data_arr.front())
                {
                    *input += "\"" + root->get_name() + "\": [" + "\"" + root->get_data() + "\"";
                }
                else
                {
                    *input += "\"" + root->get_data() + "\"";
                }
            }
            else
            {
                *input += "\"" + root->get_name() + "\": " + "\"" + root->get_data() + "\"";
            }
        }
    }



    for (int i = 0; i < children.size(); i++)
    {
        if (children[i]->get_name() != COMMENT_TAG)
        {
            if (children_data_wait[children[i]->get_name()] == 0)
            {
                continue;
            }


            // calculating the total number of children this root have


            int remaning_children = std::accumulate(children_data_wait.begin(), children_data_wait.end(), 0, [](int value, const std::map<std::string, int>::value_type &p)
                    { return value + p.second; });
            for (auto child : children_data_map[children[i]->get_name()])
            {
                int status_check = XML_TO_JSON(child, level + 1, input, children_data_map[children[i]->get_name()]);
                if (status_check)
                {
                    if ((remaning_children == 1 && child == children_data_map[children[i]->get_name()].back()) || children.size() == 1)
                    {
                        *input += "\n";
                    }
                    else
                    {
                        *input += ",\n";
                    }
                }
            }
            children_data_wait[children[i]->get_name()] = 0;
        }
    }

    if (root->get_name() == "XML")
    {
        *input += "}";
    }
    else
    {
        if (root->get_data().empty())
        {

            for (int i = 0; i < level + 1; i++)
            {
                *input += "    ";
            }
            if (children_data_arr.size() > 1 && children_data_arr.back() == root)
            {
                *input += "}]";
            }
            else
            {
                *input += "}";
            }
        }
        else
        {
            if (children_data_arr.size() > 1 && children_data_arr.back() == root)
            {
                *input += "]";
            }
        }
    }
    return 1;
}




