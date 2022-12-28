#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QtWidgets/qlabel.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QFile>
#include <random>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadWidgets();

    loadImages();

    //shuffle button
    connect(ui->shuffle,SIGNAL(released()),this,SLOT(shuffle()));
    //reset button
    connect(ui->reset,SIGNAL(released()),this,SLOT(reset()));
    //quit button
    connect(ui->quit,SIGNAL(released()),this,SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::loadWidgets(){

    //pointer holds grid layout

    QGridLayout *layout = ui->gridLayout;

    QLabel *label;



    //increment through grid

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 13; j++){

            //new label

            QLabel *label = new QLabel(this);



            layout->addWidget(label,i,j);



        }
    }


}//endloadWidgets()


void MainWindow::loadImages(){

    //array holding the addresses of the images (see cards.qrc)

    QString images[52];



    //generate the image paths

    for(int i = 0; i < 13; i++){

        images[i] = QString::fromStdString(":medium/spades_" + std::to_string(i+1) + ".png");

        images[i+13] = QString::fromStdString(":medium/diamond_" + std::to_string(i+1) + ".png");

        images[i+26] = QString::fromStdString(":medium/clubs_" + std::to_string(i+1) + ".png");

        images[i+39] = QString::fromStdString(":medium/hearts_" + std::to_string(i+1) + ".png");
    }


    //count will increment through the images array

    int count = 0;


    //i and j represent row and columns of the grid layout
    for (int i = 0; i < ui->gridLayout->rowCount(); i++){
        for (int j = 0; j < ui->gridLayout->columnCount(); j++){


          //pixmap stores image inside of QLabel
          QPixmap pixmapTarget = QPixmap(images[count]);
          pixmapTarget = pixmapTarget.scaled(50, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);

          //obtain QLabel from QGridLayout
          QLayoutItem* item = ui->gridLayout->itemAtPosition(i,j);
          QWidget* widget = item->widget();
          QLabel* label = dynamic_cast<QLabel*>(widget);

          label->setPixmap(pixmapTarget);


          //increment

          count++;

        }


    }





}//end loadImages()


void MainWindow::shuffle(){

    //randomize number of swaps

    int numberOfSwaps = numberGen(80,200);

    for(int i = 0; i < numberOfSwaps; i++)
        swap();



}






void MainWindow::swap(){

    //generate 4 numbers representing two cards that should be swapped

    int x1 = numberGen(0,3);

    int y1 = numberGen(0,12);

    int x2 = numberGen(0,3);

    int y2 = numberGen(0,12);


    //obtain grid layout

    QGridLayout *grid = ui->gridLayout;

    //obtain card 1

    QLayoutItem* item = grid->itemAtPosition(x1,y1);


    //obtain card 2

    QLayoutItem* item2 = grid->itemAtPosition(x2,y2);

    //clear cards

    grid->removeItem(item);
    grid->removeItem(item2);

    //convert to QLabel

    QWidget* widget2 = item2->widget();
    QLabel* label2 = dynamic_cast<QLabel*>(widget2);

    QWidget* widget = item->widget();
    QLabel* label = dynamic_cast<QLabel*>(widget);

    //switch

    grid->addWidget(label2,x1,y1);
    grid->addWidget(label,x2,y2);


}//end shuffle()

int MainWindow::numberGen(int lower, int upper){

    //create a random number generator

    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();

    std::default_random_engine myRandomEngine(seed);

    //bounds defined by the user

    std::uniform_int_distribution<int> unifIntDist(lower, upper);

    int number = unifIntDist(myRandomEngine);



    return number;

}//end numberGen()



void MainWindow::reset(){

    //iterates through the grid and wipes everything

    QGridLayout *grid = ui->gridLayout;

    for (int i = 0; i < ui->gridLayout->rowCount(); i++){
        for (int j = 0; j < ui->gridLayout->columnCount(); j++){

            QLayoutItem* item = grid->itemAtPosition(i,j);

            grid->removeItem(item);


        }
    }


    //reloads widgets and images

    loadWidgets();
    loadImages();



}//end reset()



void MainWindow::quit(){

    //quits out of the application
    QApplication::quit();


}//end quit()
