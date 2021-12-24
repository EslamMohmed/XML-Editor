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

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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






