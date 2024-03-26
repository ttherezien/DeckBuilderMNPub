#include "MainWindows.h"
#include "DataLoader.h"
#include "VisuCarte.h"
#include "DeckBuilder.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QListWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

    //this->resize(auto);
    this->resize(1000, 800);

    //this->adjustSize();



    mainLayout = new QVBoxLayout(this);


    button1 = new QPushButton("Nouveau Deck", this);
    button1->setGeometry(50, 50, 100, 30);
    button2 = new QPushButton("Charger Deck", this);
    button2->setGeometry(50, 100, 100, 30);
    button3 = new QPushButton("Voir carte", this);
    button3->setGeometry(50, 150, 100, 30);

    // Ajouter les boutons à la fenêtre sans les mettre dans le layout
    mainLayout->addWidget(button1);
    mainLayout->addWidget(button2);
    mainLayout->addWidget(button3);

    // Connecter les signaux et les slots en utilisant des lambdas
    connect(button1, &QPushButton::clicked, [this]() {
        deckBuilder = new DeckBuilder();
        effacerBouton();
        connect(deckBuilder, &DeckBuilder::retourMenu, this, [this]() {
            deckBuilder->hide();
            button1->show();
            button2->show();
            button3->show();
        });
        mainLayout->addWidget(deckBuilder);

    });
    connect(button2, &QPushButton::clicked, [this]() {
        deckBuilder = new DeckBuilder();
        effacerBouton();
        connect(deckBuilder, &DeckBuilder::retourMenu, this, [this]() {
            deckBuilder->hide();
            button1->show();
            button2->show();
            button3->show();
        });

        mainLayout->addWidget(deckBuilder);
        deckBuilder->loaderDeck();

    });
    connect(button3, &QPushButton::clicked, this, [this]() {
        visuCarte = new VisuCarte();
        effacerBouton();
        connect(visuCarte, &VisuCarte::retourMenu, this, [this]() {
            visuCarte->hide();
            button1->show();
            button2->show();
            button3->show();
        });

        mainLayout->addWidget(visuCarte);

        //afficherListeCartes();
    });
}



void MainWindow::effacerBouton() {
    button1->hide();
    button2->hide();
    button3->hide();

}
