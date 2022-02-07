#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "extra.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>
#include "node.h"
#include "xml_tree.h"
#include <QTextStream>
#include <QDir>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QFile mytempfile("out.txt");
QFile myfile("myfile.txt");
QString text = "";
QString s="";

void MainWindow::on_openButton_clicked()
{
    ui->input_text->clear();
    ui->output_text->clear();

    QFile input_file(QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("XML File (*.xml) ;;TextFile (*.txt)")));
    s=input_file.fileName();
    input_file.open(QIODevice::ReadOnly |QIODevice::Text);
    QTextStream stream(&input_file);
    text= stream.readAll();
    myfile.remove();
    mytempfile.resize(0);
    input_file.copy("myfile.txt");
    QFile myfile("myfile.txt");
    ui->input_text->setPlainText(text);
    ui->input_text->setLineWrapMode(QPlainTextEdit::NoWrap);
    ui->output_text->setPlainText(text);
    ui->output_text->setLineWrapMode(QPlainTextEdit::NoWrap);
    input_file.close();
}

void MainWindow::on_SaveButton_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Address Book"), "",
                                                    tr("XML (*.xml);;TEXT (*.txt;;JSON (*.json))"));
    QFile output_file(fileName);
    output_file.open(QIODevice::ReadWrite|QIODevice::Text);
    QString text=ui->output_text->toPlainText();
    output_file.write(text.toUtf8());
    output_file.close();
}

void MainWindow::on_Resetbutton_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::on_ExitButton_clicked()
{
    qApp->quit();
}
void MainWindow::on_minifyButton_clicked()
{
    //7tet el 7aga elly fe texteditor goa el var "text"
    QString textt =ui->input_text->toPlainText();
    string tss=textt.toStdString();
    string Result=Minify(tss);
    QString str = QString::fromStdString(Result);
    //show
    ui->output_text->setPlainText(str);
}

void MainWindow::on_checkbutton_clicked()
{
    QString textt =ui->input_text->toPlainText();
    string tss=textt.toStdString();
    vector<pair<string,int>> Result=detecterrors(string_to_vector(tss));

    string result_string;
    for(size_t i=0;i<Result.size();i++)
    {
        result_string.append("error in tag \"");
        result_string.append(Result[i].first);
        result_string.append("\" error in line ");
        result_string.append(to_string(Result[i].second));
        result_string.append( " \n");

    }
    QString str = QString::fromStdString(result_string);
    //show
    ui->output_text->setPlainText(str);
}

void MainWindow::on_correctBtutton_clicked()
{
    QString text =ui->input_text->toPlainText();
    string strr=text.toStdString();
    string Result=correcterrors(string_to_vector(strr));
    Result=format(string_to_vector(Result));
    QString str = QString::fromStdString(Result);
    //show
    ui->output_text->setPlainText(str);
}


void MainWindow::on_FormatButton_clicked()
{
    QString text =ui->input_text->toPlainText();

    string ts=text.toStdString();

    string Result=format(string_to_vector(ts));

    //string to qstring
    QString str = QString::fromStdString(Result);
    //show
    ui->output_text->setPlainText(str);
}


void MainWindow::on_CompressionButton_clicked()
{
    QString text =ui->input_text->toPlainText();

    string ts=text.toStdString();

    vector<int> Result = compression(ts);
    QString str;
    for(auto c:Result)
        str.append(QString:: fromStdString(to_string(c)));

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Address Book"), "",
                                                    tr("COMP (*.comp);;All Files ()"));
    QFile newDoc(fileName);
    if(newDoc.open(QIODevice::WriteOnly)) {
        QTextStream out(&newDoc);
        out<<str;
        newDoc.flush();
    }

    newDoc.close();
    ui->output_text->setPlainText(str);
}

void MainWindow::on_DecompressionButton_clicked()
{
    QString text =ui->input_text->toPlainText();
    string ts=text.toStdString();
    vector<int> Result = compression(ts);
    QString decompressed = QString::fromStdString(decompression(Result));
    ui->output_text->setPlainText(decompressed);
}

void MainWindow::on_XmlToJson_clicked()
{
    std::string xml_string=ui->input_text->toPlainText().toStdString();
    Node *root = new Node("XML", "");
    parse_tree(root, xml_string);
    std::string out = "";
    XML_TO_JSON(root, -1, &out);
    ui->output_text->setPlainText(QString::fromStdString(out));
}


void MainWindow::on_graph_clicked()
{
    std::string xml_string=ui->input_text->toPlainText().toStdString();
    Node *root = new Node("XML", "");
    parse_tree(root, xml_string);
    root = root->children[0];
    vector<User> users;
    for(int i =0;i<root->children.size();i++){
        User temp_user;
        Node* user_node= root->children[i];
        for(int j=0;j<user_node->children.size();j++){
            Node* user_data = user_node->children[j];
            if(user_data->name == "name")
                temp_user.name = user_data->data;
            else if(user_data->name == "id")
                temp_user.id = stoi(user_data->data);
            else if(user_data->name == "followers")
            {
                for(uint k=0;k<user_data->children.size();k++){
                    int temp_id = stoi(user_data->children[k]->children[0]->data);
                    temp_user.followers.push_back(temp_id);
                }
            }
        }
        users.push_back(temp_user);
    }
    graph* graph1=new graph();
    for(int i=0;i<users.size();i++){
        graph1->add_vertex();
        for(int j=0;j<users[i].followers.size();j++){
            graph1->add_edge(users[i].id,users[i].followers[j]);
        }
    }
    QString temp_out;
    for(int i=1;i<graph1->numVertices;i++){

        for(int j=1;j<graph1->numVertices;j++){
            temp_out +=QString::number(graph1->vertArr[i][j]) + "    ";
        }
        temp_out+='\n';
    }
    ui->output_text->setPlainText(temp_out);
    //show dot file
    string result = "digraph Graph {\n\n";
    for(const auto &user : users)
    {
        result += "\t" + to_string(user.id) + " -> {";
        for(size_t i = 0; i < user.followers.size(); i++)
        {
            if(i)
                result += " ,";
            result += to_string(user.followers[i]);
        }
        result += "}\n";
    }
    result += "}\n\n";
    QFile file("C:\\Users\\EGYPT\\OneDrive\\Desktop\\graph.dot");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream out(&file);
    QString text = QString::fromStdString(result);
    out << text;
    file.flush();
    file.close();
    QProcess process;
    process.start("dot -Tpng -O graph.dot", QStringList() << "C:\\Users\\EGYPT\\OneDrive\\Desktop");

}

void MainWindow::on_showgraph_clicked()
{
    ui->label->show();
    QPixmap mypix("C:\\Users\\EGYPT\\OneDrive\\Desktop\\graph.dot.png");
    ui->label->setPixmap(mypix);
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->hide();
}
