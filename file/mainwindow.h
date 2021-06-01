#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string.h>

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

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
