//
// Created by okkul on 24/03/24.
//

#ifndef UNTITLED5_DECKBUILDER_H
#define UNTITLED5_DECKBUILDER_H


#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonArray>
#include <QLabel>
#include <QCheckBox>


class DeckBuilder : public QWidget {
Q_OBJECT


public:
    DeckBuilder(QWidget *parent = nullptr);
    void loaderDeck();
    QLayout *checkBoxFilter();


signals:
    void retourMenu();

private slots:
    void ajouterCarteAuDeck();
    void enleverCarteDeck();
    void visualiserLaCarteSelectionner(QListWidget *listeCarte);
    void filtrerListeCartes(const QString &text);
    void sauvegarderDeck();
    QLayout * vueInfoDeck();
    void updateStatDeck(QLayout *StatDeck);






private:
    QListWidget *listeCartesDisponibles;
    QListWidget *listeCartesDeck;
    QLineEdit *champInteraction;
    QJsonArray cartes;
    QLabel *labelChampInteraction;
    QPushButton *retour;
    QMap<QString, int> cartesDeck;
    QLayout *StatDeck;



    QCheckBox *checkAir{};
    QCheckBox *checkEau{};
    QCheckBox *checkFeu{};
    QCheckBox *checkPlante{};
    QCheckBox *checkPierre{};
    QCheckBox *checkArcane{};

    QPixmap pixAir;
    QPixmap pixEau;
    QPixmap pixFeu;
    QPixmap pixPlante;
    QPixmap pixPierre;
    QPixmap pixArcane;



};


#endif //UNTITLED5_DECKBUILDER_H
