#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string.h>
#include <QSerialPort>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    float pos_X;
    float pos_Y;
    float pos_Z;
    float pos_theo;
    float pos_theo1;
    float Pmesure;
    float capteur1;
    float capteur2;
    float capteur3;
    float capteur4;
    void graphic_window();
    void fonction_mesures();
    void ip();

private slots:
    //void on_pushButton_clicked(); //pour transfère de data entre différentes windows


    void on_actionPlacement_auto_triggered();

    void on_actionPlacement_manuel_triggered();

    void on_actionMesures_triggered();

    void on_actionConfiguration_R_seau_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void updateRGB(QString);
    void on_pushButton_5_clicked();

    void on_pushButton_61_clicked();

    void on_pushButton_62_clicked();

    void on_pushButton_63_clicked();

    void on_pushButton_64_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_68_clicked();

    void on_pushButton_3_clicked();

private:

    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QStandardItemModel *csvModel;
};
#endif // MAINWINDOW_H
