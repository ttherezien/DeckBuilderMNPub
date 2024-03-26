//
// Created by okkul on 25/03/24.
//

#ifndef UNTITLED5_VISUCARTE_H
#define UNTITLED5_VISUCARTE_H


#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include "DataLoader.h"

class VisuCarte : public QWidget {
Q_OBJECT

public:
    VisuCarte(QWidget *parent = nullptr);

signals:
    void retourMenu();

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *layout;
    QLineEdit *searchBar;
    QPushButton *retour;
    QListWidget *listWidget;
    QListWidget *detailsWidget;
    QJsonArray cartes;
    DataLoader dataLoader;


    void filtrerListeCartes(const QString &text);

    void afficherDetailsCarte(QListWidgetItem *item);
};


#endif //UNTITLED5_VISUCARTE_H
