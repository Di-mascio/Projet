#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"
#include "iostream"
#include <QHostAddress>
#include <QHostInfo>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QTcpSocket>
#include <QFile>
#include <QDebug>
#include <QtWidgets>
#include <QTextStream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available){
        // open and configure the serialport
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }else{
        // give error message if not available
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(3);
    ui->tableView->setModel(csvModel);


    QFile file("/home/maxime/Documents/Projet/SERVER/demande.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {

        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            QList<QStandardItem *> standardItemsList;
            for (QString item : line.split(","))
            {
                standardItemsList.append(new QStandardItem(item));
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
        file.close();

    }
}

MainWindow::~MainWindow()
{
    if(arduino->isOpen()){
        arduino->close();
    }

    delete ui;
}


/*void MainWindow::on_pushButton_clicked() // pour transfère de data entre différentes windows
{
    QString testText = "test";
    s=new secwindow(this);
    s->show();
    s->text(testText);
    QString test2Text;
    test2Text = "Hello World !";
    ui->label4->setText(test2Text);
    s->text(test2Text);
}*/


void MainWindow::on_actionPlacement_auto_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionPlacement_manuel_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionMesures_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionConfiguration_R_seau_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::graphic_window()
{
    ui->label->setStyleSheet(QString::fromUtf8("background-color: rgb(144, 28, 58);"));
    ui->label2->setStyleSheet(QString::fromUtf8("background-color: rgb(197, 29, 74);"));
    QPixmap pix("/home/maxime/Images/1200px-Raspberry_Pi_logo.svg.png");
    ui->label3->setPixmap(pix);
}

void MainWindow::fonction_mesures()
{
    pos_X = 12.1, pos_Y = 13.1, pos_Z = 14.1, capteur1 = 1.1, capteur2 = 2.1, capteur3 = 3.1, capteur4 = 4.1, pos_theo = 8.1, pos_theo1 = 9.1, Pmesure = 10.8;
    QString string, string2, string3, string4, string5, string6, string7, string8, string9, string10;

    string.sprintf("pos X (mm) = %f", pos_X);
    string2.sprintf("pos Y (mm) = %f", pos_Y);
    string3.sprintf("pos Z (mm) = %f", pos_Z);
    string4.sprintf("capteur 1 (N) = %f", capteur1);
    string5.sprintf("capteur 2 (N) = %f", capteur2);
    string6.sprintf("capteur 3 (N) = %f", capteur3);
    string7.sprintf("capteur 4 (N) = %f", capteur4);
    string8.sprintf("XGtheo (N)  = %f", pos_theo);
    string9.sprintf("YGtheo (N)  = %f", pos_theo1);
    string10.sprintf("Pmesuré (N)  = %f", Pmesure);

    QFont f("Ubuntu Mono", 12, QFont::Bold);

    ui->label_11->setFont(f);
    ui->label_11->setText(string);
    ui->label_12->setFont(f);
    ui->label_12->setText(string2);
    ui->label_13->setFont(f);
    ui->label_13->setText(string3);
    ui->label_14->setFont(f);
    ui->label_14->setText(string4);
    ui->label_15->setFont(f);
    ui->label_15->setText(string5);
    ui->label_16->setFont(f);
    ui->label_16->setText(string6);
    ui->label_17->setFont(f);
    ui->label_17->setText(string7);
    ui->label_18->setFont(f);
    ui->label_18->setText(string8);
    ui->label_19->setFont(f);
    ui->label_19->setText(string9);
    ui->label_20->setFont(f);
    ui->label_20->setText(string10);
}

void MainWindow::ip()
{
    QString localhostname =  QHostInfo::localHostName();
    QString localhostIP, localMacAddress, localNetmask;
    QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             localhostIP = address.toString();
    }

    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
        foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
            if (entry.ip().toString() == localhostIP) {
                localMacAddress = networkInterface.hardwareAddress();
                break;
            }
        }
    }

    ui->label_23->setText(localhostname);
    ui->label_5->setText(localhostIP);
    ui->label_8->setText(localMacAddress);
}

void MainWindow::on_pushButton_clicked()
{
    QTcpSocket* sock = new QTcpSocket(this);

    sock->connectToHost("192.168.1.39", 80);

    bool connected = sock->waitForConnected(30000);

    if (!connected)
    {
        sock->abort();
        ui->label_9->setText("Test Non Fonctionnel");
    }else
    {
        ui->label_9->setText("Test Fonctionnel");
    }


    sock->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QFile file("send.txt");

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // On choisit le codec correspondant au jeu de caractères que l'on souhaite ; ici, UTF-8
    flux.setCodec("UTF-8");
    // Écriture des différentes lignes dans le fichier
    flux << "Bonjour,\n" << "Nous sommes le " << 1 << " Juin " << 2021 << "\n";
}

void MainWindow::updateRGB(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}

void MainWindow::on_pushButton_61_clicked()
{
    //Increment a 1
    MainWindow::updateRGB(QString("1"));
    qDebug() << "1";
}


void MainWindow::on_pushButton_62_clicked()
{
    //Increment a 10
    MainWindow::updateRGB(QString("2"));
    qDebug() << "10";
}


void MainWindow::on_pushButton_63_clicked()
{
    //Increment a 100
    MainWindow::updateRGB(QString("3"));
    qDebug() << "100";
}


void MainWindow::on_pushButton_64_clicked()
{
    //Increment a 1000
    MainWindow::updateRGB(QString("4"));
    qDebug() << "1000";
}

void MainWindow::on_pushButton_5_clicked()
{
    //X+
    MainWindow::updateRGB(QString("x"));
    qDebug() << "x";
}

void MainWindow::on_pushButton_11_clicked()
{
    //X-
    MainWindow::updateRGB(QString("X"));
    qDebug() << "X";
}

void MainWindow::on_pushButton_6_clicked()
{
    //Y+
    MainWindow::updateRGB(QString("y"));
    qDebug() << "y";
}

void MainWindow::on_pushButton_12_clicked()
{
    //Y-
    MainWindow::updateRGB(QString("Y"));
    qDebug() << "Y";
}

void MainWindow::on_pushButton_7_clicked()
{
    //Z+
    MainWindow::updateRGB(QString("z"));
    qDebug() << "z";
}

void MainWindow::on_pushButton_13_clicked()
{
    //Z+
    MainWindow::updateRGB(QString("Z"));
    qDebug() << "Z";
}


void MainWindow::on_pushButton_10_clicked()
{
    //tare a vide
    MainWindow::updateRGB(QString("0"));
    qDebug() << "0";
}


void MainWindow::on_pushButton_9_clicked()
{
    //tare connue
    MainWindow::updateRGB(QString("c"));
    qDebug() << "c";
}


void MainWindow::on_pushButton_8_clicked()
{
    //tare plateau ~
    MainWindow::updateRGB(QString("v"));
    qDebug() << "v";
}


void MainWindow::on_pushButton_68_clicked()
{
    //Stop mesures
    MainWindow::updateRGB(QString("S"));
    qDebug() << "S";
}

void MainWindow::delete_record()
{

    // Open FIle pointers
    fstream fin, fout;

    // Open the existing file
    fin.open("/home/maxime/Téléchargements/build-activite-fichier-csv-Desktop_Qt_5_15_2_GCC_64bit-Debug/bin/data.csv", ios::in);

    // Create a new file to store the non-deleted data
    //fout.open("/home/maxime/Téléchargements/build-activite-fichier-csv-Desktop_Qt_5_15_2_GCC_64bit-Debug/bin/data.csv", ios::out);

    int rollnum, roll1, marks, count = 0, i;
    char sub;
    int index, new_marks;
    string line, word;
    vector<string> row;

    // Get the roll number
    // to decide the data to be deleted
    cout << "Enter the roll number "
         << "of the record to be deleted: ";
    cin >> rollnum;
    roll1 = 0;

    string data;
    while (std::getline(fin, line))
    {
        roll1++;
        if( roll1 != rollnum){
            data = data + line + '\n';

        }

    }



    // Close the pointers
    fin.close();


    // removing the existing file
    //remove("/home/maxime/Téléchargements/build-activite-fichier-csv-Desktop_Qt_5_15_2_GCC_64bit-Debug/bin/data.csv");

    // renaming the new file with the existing file name
   //rename("/home/maxime/Téléchargements/build-activite-fichier-csv-Desktop_Qt_5_15_2_GCC_64bit-Debug/bin/dataaaaa.csv", "/home/maxime/Téléchargements/build-activite-fichier-csv-Desktop_Qt_5_15_2_GCC_64bit-Debug/bin/data.csv");

    fout.open("/home/maxime/Téléchargements/build-activite-fichier-csv-Desktop_Qt_5_15_2_GCC_64bit-Debug/bin/data.csv", ios::out);
    fout.write( data.c_str() , data.length() );
    fout.close();
            qDebug() << data.c_str();
}


