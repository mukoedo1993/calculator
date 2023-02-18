#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<regex>
#include<iostream>
#include<QDebug>
double calcVal = 0.0;
int calcValInt = 0;
bool divTrigger = false;
bool mutliTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool floatPointTrigger = false;
bool isFloat = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        //any time numbuttons pushed down called this function,
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    connect(ui->Plus, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Assign, SIGNAL(released()), this,
            SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
    connect(ui->FloatPoint, SIGNAL(released()), this,
            SLOT(FloatPointPressed()));
    connect(ui->ClearEverything, SIGNAL(released()), this,
            SLOT(ClearEverything()));
    connect(ui->IsFloat,SIGNAL(released()), this,
            SLOT(IsFloat()));
    connect(ui->F1,SIGNAL(released()), this,
            SLOT(F1()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if(isFloat){
    if(floatPointTrigger == false)
    {
     if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
     }
     else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));

        }
    }
    else{
        ui->DisplayError->setText("Dot detected!");
        floatPointTrigger = false;
        std::string ptr(".");
        QString newVal = displayVal + QString::fromStdString(ptr) + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
    }
    else /*not float*/
    {
         if(displayVal.toInt() == 0 ){
            ui->Display->setText(butVal);
         }
         else {
            QString newVal = displayVal + butVal;
            double dblNewVal = newVal.toInt();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));

            }


    }

}
void MainWindow::MathButtonPressed(){
     divTrigger = false;
     mutliTrigger = false;
     addTrigger = false;
     subTrigger = false;
     floatPointTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    calcValInt = displayVal.toInt();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
       { divTrigger = true;
    }else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    { mutliTrigger = true;
 }else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    { addTrigger = true;
 }else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
    { subTrigger = true;
 }else {
      ;
    }
ui->Display->setText("");
}



void MainWindow::EqualButton(){
    double solution = 0.0;
    int solution_int = 0;
    QString displayVal = ui->Display->text();
    //ui->DisplayError->setText("equalbutton here!");
    std::cout << "Equal Button called!";
    if(isFloat){
     double dblDisplayVal = displayVal.toDouble();

     if(addTrigger || subTrigger || mutliTrigger || divTrigger){

        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        } else if(mutliTrigger){
            solution = calcVal * dblDisplayVal;
        } else {
            if(dblDisplayVal == 0 || dblDisplayVal == 0.0){
                ui->DisplayError->setText("Error! Please do not divide by zero(float)! Everything is cleared!");
                ClearEverything();
                return;
            }
            solution = calcVal / dblDisplayVal;
        }
     }
    }
    else/*not float*/ {
         int intDisplayVal = displayVal.toInt();
         std::cout << "intDisplayVal is: " <<intDisplayVal;
         if(addTrigger || subTrigger || mutliTrigger || divTrigger){

            if(addTrigger){
                solution_int = calcValInt + intDisplayVal;
            } else if(subTrigger){
                solution_int = calcValInt - intDisplayVal;
            } else if(mutliTrigger){
                solution_int = calcValInt * intDisplayVal;
            } else {
                if(intDisplayVal == 0 ){
                    ui->DisplayError->setText("Error! Please do not divide by zero(int)! Everything is cleared!");
                    ClearEverything();
                    return;
                }


                solution_int = calcValInt / intDisplayVal;
            }
         }

    }
    if(isFloat){
    ui->Display->setText(QString::number(solution));
    }
    else{
     ui->Display->setText(QString::number(solution_int));
    }
}
void MainWindow::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    std::string temp1("[-]?[0-9.]*");
    if(std::regex_match(displayVal.toStdString(), std::regex(temp1))){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void MainWindow::FloatPointPressed() {
    //QPushButton *button = (QPushButton *)sender();
    if(!isFloat)return;
    floatPointTrigger = true;
    QString displayVal = ui->Display->text();
    std::string reg("[\.]{1}");

    if(std::regex_match(displayVal.toStdString(), std::regex(reg))){
        floatPointTrigger = false;
        ui->DisplayError->setText("Float Point Detected!");
        return;
    }
    else {
        ui->DisplayError->setText("");
    }

}

void MainWindow::ClearEverything() {
    ui->Display->setText("0");

}

void MainWindow::IsFloat() {
    isFloat = (!isFloat);
    if(isFloat){
     ui->DisplayError->setText("Switched to float mode! Everything is cleared!");
      ClearEverything();
    }
    else{

          ui->DisplayError->setText("Switched to integer mode! Everything is cleared!");
           ClearEverything();
    }
}
void MainWindow::F1(){
    ui->DisplayError->setText("New feature might be added in the future! But currently it does nothing");
}

/*
*
*AC, Memory buttons need to be set up carefully...
*/
