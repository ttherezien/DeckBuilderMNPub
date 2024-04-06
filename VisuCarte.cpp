//
// Created by okkul on 25/03/24.
//

#include <QLabel>
#include "VisuCarte.h"
#include "DeckBuilder.h"

VisuCarte::VisuCarte(QWidget *parent) : QWidget(parent){




    mainLayout = new QHBoxLayout(this);

    layout = new QVBoxLayout(this);
    searchBar = new QLineEdit(this);
    retour = new QPushButton("Retour", this);


    DeckBuilder deckBuilder;


    // Créer un QListWidget pour afficher la liste des cartes
    listWidget = new QListWidget(this);
    // Lire le fichier JSON
    QJsonArray array = dataLoader.loadJsonData();

    // Ajouter chaque carte à la QListWidget
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject obj = array[i].toObject();
        QString cardName = obj["Nom"].toString();
        new QListWidgetItem(cardName, listWidget);
    }

    // Ajouter la QListWidget à la fenêtre
    detailsWidget = new QListWidget(this);

    layout->addWidget(retour);
    layout->addWidget(searchBar);
    layout->addWidget(listWidget);


    mainLayout->addLayout(layout);
    mainLayout->addWidget(detailsWidget);

    connect(searchBar, &QLineEdit::textChanged, this, &VisuCarte::filtrerListeCartes);
    connect(listWidget, &QListWidget::itemSelectionChanged, this, [this](){
        QListWidgetItem *item = listWidget->currentItem();
        afficherDetailsCarte(item);
    });
    connect(retour, &QPushButton::clicked, [this](){
        emit retourMenu();
    });

    setLayout(layout);

}

void VisuCarte::filtrerListeCartes(const QString &text) {
    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem *item = listWidget->item(i);
        if (item->text().contains(text, Qt::CaseInsensitive)) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
}

void VisuCarte::afficherDetailsCarte(QListWidgetItem *item) {
    QString cardName = item->text();
    // Lire le fichier JSON


    QJsonArray array = dataLoader.loadJsonData();

    // Trouver la carte correspondante
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject obj = array[i].toObject();
        if (obj["Nom"].toString() == cardName) {


            // Afficher les détails dans le QListWidget
            detailsWidget->clear();

            // Afficher l'image
            QString imagePath = obj["image"].toString();
            QPixmap pixmap("./image/" + imagePath);
            QLabel *imageLabel = new QLabel(this);
            imageLabel->setPixmap(pixmap);

            // Ajuster la taille de l'élément de la liste en fonction de la taille de l'image
            QSize imageSize = pixmap.size();
            QSize itemSize = QSize(imageSize.width()+40, imageSize.height() + 40); // Ajustez la hauteur selon vos besoins
            QListWidgetItem *imageItem = new QListWidgetItem();
            imageItem->setSizeHint(itemSize);

            // Associer le QLabel à l'élément de la liste
            detailsWidget->addItem(imageItem);
            detailsWidget->setItemWidget(imageItem, imageLabel);

            break;
        }
    }

}