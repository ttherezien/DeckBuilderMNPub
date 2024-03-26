//
// Created by okkul on 23/03/24.
//

#ifndef UNTITLED5_MAINWINDOWS_H
#define UNTITLED5_MAINWINDOWS_H
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QListWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "DataLoader.h"
#include "DeckBuilder.h"
#include "VisuCarte.h"

class MainWindow : public QWidget {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:

    void effacerBouton();

private:
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    DeckBuilder *deckBuilder;
    VisuCarte *visuCarte;
    QVBoxLayout *mainLayout;

};

#endif //UNTITLED5_MAINWINDOWS_H
