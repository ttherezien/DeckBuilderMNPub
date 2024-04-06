//
// Created by okkul on 24/03/24.
//

#include "MainWindows.h"
#include "DeckBuilder.h"
#include "DataLoader.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QCheckBox>
#include <QMenuBar>
#include <QStringListModel>
#include <QStandardItem>

DeckBuilder::DeckBuilder(QWidget *parent) : QWidget(parent) {


    this->resize(1000, 800);
    QHBoxLayout *layoutPrincipal = new QHBoxLayout(this);
    QVBoxLayout *layoutListeCartesDisponibles = new QVBoxLayout();
    QVBoxLayout *layoutChampInteraction = new QVBoxLayout();
    QVBoxLayout *layoutListeCartesDeck = new QVBoxLayout();


    // Filtre
    QLayout *Filtre = checkBoxFilter();


    retour = new QPushButton("Retour");
    QLabel *labelListeCartesDisponibles = new QLabel("Cartes disponibles");
    labelChampInteraction = new QLabel("Ajouter/Visualiser carte");
    QLabel *labelListeCartesDeck = new QLabel("Cartes dans le deck");
    QLineEdit *searchBar = new QLineEdit();
    champInteraction = new QLineEdit();
    champInteraction->setReadOnly(true);


    StatDeck = vueInfoDeck();


    QPushButton *boutonAjouter = new QPushButton("Ajouter au deck");
    QPushButton *boutonEnlever = new QPushButton("Enlever du deck");
    QPushButton *boutonSauvegarder = new QPushButton("Sauvegarder le deck");
    QPushButton *boutonCharger = new QPushButton("Charger le deck");






    //Listes
    listeCartesDisponibles = new QListWidget();
    listeCartesDeck = new QListWidget();




    // Ajout des widgets aux layouts

    layoutListeCartesDisponibles->addWidget(labelListeCartesDisponibles);
    layoutListeCartesDisponibles->addLayout(Filtre);
    layoutListeCartesDisponibles->addWidget(searchBar);
    layoutListeCartesDisponibles->addWidget(retour);
    layoutListeCartesDisponibles->addWidget(listeCartesDisponibles);


    layoutChampInteraction->addWidget(labelChampInteraction);
    layoutChampInteraction->addWidget(champInteraction);
    layoutChampInteraction->addWidget(boutonAjouter);
    layoutChampInteraction->addWidget(boutonEnlever);

    layoutListeCartesDeck->addWidget(labelListeCartesDeck);
    layoutListeCartesDeck->addWidget(listeCartesDeck);
    layoutListeCartesDeck->addLayout(StatDeck);
    layoutListeCartesDeck->addWidget(boutonSauvegarder);
    layoutListeCartesDeck->addWidget(boutonCharger);




    // Ajouter les layouts dans le layout principal

    layoutPrincipal->addLayout(layoutListeCartesDisponibles);
    layoutPrincipal->addLayout(layoutChampInteraction);
    layoutPrincipal->addLayout(layoutListeCartesDeck);
    setLayout(layoutPrincipal);






    // Chargement des données initiales

    cartesLoader = DataLoader().loadJsonData();

    for (int i = 0; i < cartesLoader.size(); ++i) {
        QJsonObject obj = cartesLoader[i].toObject();
        QString nomCarte = obj["Nom"].toString();
        listeCartesDisponibles->addItem(nomCarte);
    }




    // Connexion des signaux des filtres aux slots de filtrage

    connect(retour, &QPushButton::clicked, this, [this]() {
        emit retourMenu();
    });
    connect(boutonAjouter, &QPushButton::clicked, this, &DeckBuilder::ajouterCarteAuDeck);
    connect(listeCartesDisponibles, &QListWidget::itemDoubleClicked, this, &DeckBuilder::ajouterCarteAuDeck);
    connect(listeCartesDisponibles, &QListWidget::itemSelectionChanged, this, [this]() {
        this->visualiserLaCarteSelectionner(listeCartesDisponibles);
    });
    connect(listeCartesDeck, &QListWidget::itemClicked, [this]() {
        this->visualiserLaCarteSelectionner(listeCartesDeck);
    });
    connect(listeCartesDeck, &QListWidget::itemSelectionChanged, [this]() {
        this->visualiserLaCarteSelectionner(listeCartesDeck);
    });
    connect(boutonEnlever, &QPushButton::clicked, this, &DeckBuilder::enleverCarteDeck);
    connect(listeCartesDeck, &QListWidget::itemDoubleClicked, this, &DeckBuilder::enleverCarteDeck);
    connect(boutonSauvegarder, &QPushButton::clicked, this, &DeckBuilder::sauvegarderDeck);
    connect(boutonCharger, &QPushButton::clicked, this, &DeckBuilder::loaderDeck);

    // Connexion des signaux des filtres aux slots de filtrage
    connect(searchBar, &QLineEdit::textChanged, this, &DeckBuilder::filtrerListeCartes);
    connect(checkAir, &QCheckBox::stateChanged, this, [=](int state) { filtrerListeCartes(searchBar->text()); });
    connect(checkFeu, &QCheckBox::stateChanged, this, [=](int state) { filtrerListeCartes(searchBar->text()); });
    connect(checkEau, &QCheckBox::stateChanged, this, [=](int state) { filtrerListeCartes(searchBar->text()); });
    connect(checkPlante, &QCheckBox::stateChanged, this, [=](int state) { filtrerListeCartes(searchBar->text()); });
    connect(checkPierre, &QCheckBox::stateChanged, this, [=](int state) { filtrerListeCartes(searchBar->text()); });
    connect(checkArcane, &QCheckBox::stateChanged, this, [=](int state) { filtrerListeCartes(searchBar->text()); });
}


void DeckBuilder::filtrerListeCartes(const QString &text) {
    QJsonArray data = DataLoader().loadJsonData();

    for (int i = 0; i < data.size(); ++i) {
        QJsonObject obj = data[i].toObject();
        QString nomCarte = obj["Nom"].toString();
        bool afficherCarte = false;

        // Vérifier si le nom de la carte contient le texte de recherche
        if (nomCarte.contains(text, Qt::CaseInsensitive)) {
            // Vérifier les conditions pour afficher la carte en fonction de l'élément
            if ((obj["Élément"] == "Air" && checkAir->isChecked()) ||
                (obj["Élément"] == "Feu" && checkFeu->isChecked()) ||
                (obj["Élément"] == "Eau" && checkEau->isChecked()) ||
                (obj["Élément"] == "Végétal" && checkPlante->isChecked()) ||
                (obj["Élément"] == "Minéral" && checkPierre->isChecked()) ||
                (obj["Élément"] == "Arcane" && checkArcane->isChecked())) {
                afficherCarte = true;
            } else if (!checkAir->isChecked() && !checkFeu->isChecked() && !checkEau->isChecked() &&
                       !checkPlante->isChecked() && !checkPierre->isChecked() && !checkArcane->isChecked()) {
                afficherCarte = true;
            }
        }

        // Afficher ou masquer la carte en fonction de la valeur de afficherCarte
        listeCartesDisponibles->item(i)->setHidden(!afficherCarte);
    }
}

void DeckBuilder::enleverCarteDeck() {
    QString carteSelectionnee = champInteraction->text();

    QStringList listeDesCartesDansLeDeck = cartesDeck.keys();

    if (cartesDeck.contains(carteSelectionnee)) {
        if (cartesDeck[carteSelectionnee] > 1) {
            cartesDeck[carteSelectionnee]--;
        } else {
            cartesDeck.remove(carteSelectionnee);
        }
    }

    listeCartesDeck->clear();
    QMap<QString, int>::iterator i;
    for (i = cartesDeck.begin(); i != cartesDeck.end(); ++i) {
        listeCartesDeck->addItem(i.key() + " (" + QString::number(i.value()) + ")");
    }
    updateStatDeck(StatDeck);

}

void DeckBuilder::ajouterCarteAuDeck() {
    QString carteAjoutee = champInteraction->text();
    if (!carteAjoutee.isEmpty()) {
        // Vérifier si la carte a déjà été ajoutée
        if (cartesDeck.contains(carteAjoutee)) {
            // Si la carte a déjà été ajoutée, augmenter son nombre d'occurrences
            if (cartesDeck[carteAjoutee] < 4) {
                cartesDeck[carteAjoutee]++;
            }
        } else {
            // Si la carte n'a pas encore été ajoutée, l'ajouter avec un nombre d'occurrences de 1
            cartesDeck.insert(carteAjoutee, 1);
        }

        // Effacer la liste des cartesLoader dans le deck
        listeCartesDeck->clear();

        // Ajouter chaque carte et son nombre d'occurrences à la liste des cartesLoader dans le deck
        QMap<QString, int>::iterator i;
        for (i = cartesDeck.begin(); i != cartesDeck.end(); ++i) {


            listeCartesDeck->addItem(i.key() + " (" + QString::number(i.value()) + ")");
        }


    }
    updateStatDeck(StatDeck);
}

void DeckBuilder::visualiserLaCarteSelectionner(QListWidget *listeCarte) {
    // il enlever les parenthèses et le nombre d'occurrences
    QString carteSelectionnee = listeCarte->currentItem()->text();
    QStringList parts = carteSelectionnee.split(" (");
    QString nomCarte = parts[0];

    for (int i = 0; i < cartesLoader.size(); ++i) {
        QJsonObject obj = cartesLoader[i].toObject();
        QString nomCarte = obj["Nom"].toString();
        if (nomCarte == parts[0]) {
            QString image = obj["image"].toString();
            labelChampInteraction->setPixmap(QPixmap("./image/" + image));
            champInteraction->setText(parts[0]);
        }
    }


}


void DeckBuilder::sauvegarderDeck() {
    QJsonArray deck;
    QMap<QString, int>::iterator i;
    for (i = cartesDeck.begin(); i != cartesDeck.end(); ++i) {
        QJsonObject carte;
        carte["Nom"] = i.key();
        carte["Quantité"] = i.value();
        deck.append(carte);
    }

    //ouvre un explorateur de fichier pour sauvegarder le deck
    QString cheminFichier = QFileDialog::getSaveFileName(this, "Sauvegarder le deck", QDir::homePath(),
                                                         "Fichiers JSON (*.json)");
    QFile fichier(cheminFichier);
    if (fichier.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(deck);
        fichier.write(doc.toJson());
        fichier.close();
    }

}

void DeckBuilder::loaderDeck() {
    QString cheminFichier = QFileDialog::getOpenFileName(this, "Charger un deck", QDir::homePath(),
                                                         "Fichiers JSON (*.json)");
    QFile fichier(cheminFichier);

    if (fichier.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(fichier.readAll());
        QJsonArray deck = doc.array();
        cartesDeck.clear();
        listeCartesDeck->clear();
        for (int i = 0; i < deck.size(); ++i) {
            QJsonObject carte = deck[i].toObject();
            QString nomCarte = carte["Nom"].toString();
            int quantite = carte["Quantité"].toInt();
            cartesDeck.insert(nomCarte, quantite);
            listeCartesDeck->addItem(nomCarte + " (" + QString::number(quantite) + ")");
        }
        fichier.close();
    }
    updateStatDeck(StatDeck);
}

QLayout *DeckBuilder::checkBoxFilter() {

    QHBoxLayout *Filtre = new QHBoxLayout();

    checkAir = new QCheckBox();
    checkFeu = new QCheckBox();
    checkEau = new QCheckBox();
    checkPlante = new QCheckBox();
    checkPierre = new QCheckBox();
    checkArcane = new QCheckBox();

    QLabel *labelAir = new QLabel();
    QLabel *labelFeu = new QLabel();
    QLabel *labelEau = new QLabel();
    QLabel *labelPlante = new QLabel();
    QLabel *labelPierre = new QLabel();
    QLabel *labelArcane = new QLabel();

    pixAir = QPixmap("./image/air_icon.png");
    pixFeu = QPixmap("./image/fire_icon.png");
    pixEau = QPixmap("./image/water_icon.png");
    pixPlante = QPixmap("./image/vegetal_icon.png");
    pixPierre = QPixmap("./image/mineral_icon.png");
    pixArcane = QPixmap("./image/arcane_icon.png");


    // il faut retrecire les image

    pixAir = pixAir.scaled(25, 25, Qt::KeepAspectRatio);
    pixFeu = pixFeu.scaled(25, 25, Qt::KeepAspectRatio);
    pixEau = pixEau.scaled(25, 25, Qt::KeepAspectRatio);
    pixPlante = pixPlante.scaled(25, 25, Qt::KeepAspectRatio);
    pixPierre = pixPierre.scaled(25, 25, Qt::KeepAspectRatio);
    pixArcane = pixArcane.scaled(25, 25, Qt::KeepAspectRatio);

    labelAir->setPixmap(pixAir);
    labelFeu->setPixmap(pixFeu);
    labelEau->setPixmap(pixEau);
    labelPlante->setPixmap(pixPlante);
    labelPierre->setPixmap(pixPierre);
    labelArcane->setPixmap(pixArcane);

    Filtre->addWidget(checkAir);
    Filtre->addWidget(labelAir);
    Filtre->addWidget(checkFeu);
    Filtre->addWidget(labelFeu);
    Filtre->addWidget(checkEau);
    Filtre->addWidget(labelEau);
    Filtre->addWidget(checkPlante);
    Filtre->addWidget(labelPlante);
    Filtre->addWidget(checkPierre);
    Filtre->addWidget(labelPierre);
    Filtre->addWidget(checkArcane);
    Filtre->addWidget(labelArcane);

    return Filtre;
}

QLayout *DeckBuilder::vueInfoDeck() {


    QLayout *StatDeck = new QVBoxLayout();

    QHBoxLayout *nbrCarteLayout = new QHBoxLayout();
    QHBoxLayout *imageLayout = new QHBoxLayout();

    QPixmap pixTotal("./image/CardDeck.png");


    QLabel *imageTotal = new QLabel();
    QLabel *imageAir = new QLabel();
    QLabel *imageFeu = new QLabel();
    QLabel *imageEau = new QLabel();
    QLabel *imagePlante = new QLabel();
    QLabel *imagePierre = new QLabel();
    QLabel *imageArcane = new QLabel();

    pixTotal = pixTotal.scaled(25, 25, Qt::KeepAspectRatio);


    imageTotal->setPixmap(pixTotal);
    imageAir->setPixmap(pixAir);
    imageFeu->setPixmap(pixFeu);
    imageEau->setPixmap(pixEau);
    imagePlante->setPixmap(pixPlante);
    imagePierre->setPixmap(pixPierre);
    imageArcane->setPixmap(pixArcane);


    QLabel *labelNbCartesTotal = new QLabel(QString::number(cartesDeck.size()));
    QLabel *labelNbCartesAir = new QLabel(QString::number(cartesDeck.size()));
    QLabel *labelNbCartesFeu = new QLabel(QString::number(cartesDeck.size()));
    QLabel *labelNbCartesEau = new QLabel(QString::number(cartesDeck.size()));
    QLabel *labelNbCartesPlante = new QLabel(QString::number(cartesDeck.size()));
    QLabel *labelNbCartesPierre = new QLabel(QString::number(cartesDeck.size()));
    QLabel *labelNbCartesArcane = new QLabel(QString::number(cartesDeck.size()));


    nbrCarteLayout->addWidget(labelNbCartesTotal);
    nbrCarteLayout->addWidget(labelNbCartesAir);
    nbrCarteLayout->addWidget(labelNbCartesFeu);
    nbrCarteLayout->addWidget(labelNbCartesEau);
    nbrCarteLayout->addWidget(labelNbCartesPlante);
    nbrCarteLayout->addWidget(labelNbCartesPierre);
    nbrCarteLayout->addWidget(labelNbCartesArcane);

    imageLayout->addWidget(imageTotal);
    imageLayout->addWidget(imageAir);
    imageLayout->addWidget(imageFeu);
    imageLayout->addWidget(imageEau);
    imageLayout->addWidget(imagePlante);
    imageLayout->addWidget(imagePierre);
    imageLayout->addWidget(imageArcane);

    StatDeck->addItem(nbrCarteLayout);
    StatDeck->addItem(imageLayout);

    listeComposantDeck = new QListWidget();

    StatDeck->addWidget(listeComposantDeck);


    return StatDeck;

}

void DeckBuilder::updateStatDeck(QLayout *StatDeck) {

    QLabel *labelNbCartesTotal = (QLabel *) StatDeck->itemAt(0)->layout()->itemAt(0)->widget();
    QLabel *labelNbCartesAir = (QLabel *) StatDeck->itemAt(0)->layout()->itemAt(1)->widget();
    QLabel *labelNbCartesFeu = (QLabel *) StatDeck->itemAt(0)->layout()->itemAt(2)->widget();
    QLabel *labelNbCartesEau = (QLabel *) StatDeck->itemAt(0)->layout()->itemAt(3)->widget();
    QLabel *labelNbCartesPlante = (QLabel *) StatDeck->itemAt(0)->layout()->itemAt(4)->widget();
    QLabel *labelNbCartesPierre = (QLabel *) StatDeck->itemAt(0)->layout()->itemAt(5)->widget();
    QLabel *labelNbCartesArcane = (QLabel *) StatDeck->itemAt(0)->layout()->itemAt(6)->widget();


    listeComposantDeck->addItem("Arbre (1)");


    int nbrCartes = 0;
    int nbrCartesAir = 0;
    int nbrCartesFeu = 0;
    int nbrCartesEau = 0;
    int nbrCartesPlante = 0;
    int nbrCartesMineral = 0;
    int nbrCartesArcane = 0;

    QMap<QString, int> composants;

    QMap<QString, int>::iterator i;
    for (i = cartesDeck.begin(); i != cartesDeck.end(); ++i) {
        nbrCartes += i.value();
        for (int j = 0; j < cartesLoader.size(); ++j) {
            QJsonObject obj = cartesLoader[j].toObject();
            if (obj["Nom"].toString() == i.key()) {
                if (obj["Élément"] == "Air") {
                    nbrCartesAir += i.value();
                } else if (obj["Élément"] == "Feu") {
                    nbrCartesFeu += i.value();
                } else if (obj["Élément"] == "Eau") {
                    nbrCartesEau += i.value();
                } else if (obj["Élément"] == "Végétal") {
                    nbrCartesPlante += i.value();
                } else if (obj["Élément"] == "Minéral") {
                    nbrCartesMineral += i.value();
                } else if (obj["Élément"] == "Arcane") {
                    nbrCartesArcane += i.value();
                }

                QJsonValue composantsDeLaCarte = obj["Composants"]; //QJsonValue(object, QJsonObject({"Arbre":1,"Flamme":1}))
                QJsonObject objComposants = composantsDeLaCarte.toObject(); //QJsonObject({"Arbre":1,"Flamme":1})
                QStringList keys = objComposants.keys(); //QStringList({"Arbre","Flamme"})
                for (int k = 0; k < keys.size(); ++k) {
                    QString key = keys[k]; //QString("Arbre")
                    int value = objComposants[key].toInt(); //int(1)
                    if (composants.contains(key)) {
                        composants[key] += value * i.value();
                    } else {
                        composants.insert(key, value*i.value());
                    }
                }


            }// les noms sont les mêmes











        }//for
    }

    listeComposantDeck->clear();
    for (i = composants.begin(); i != composants.end(); ++i) {
        listeComposantDeck->addItem(i.key() + " (" + QString::number(i.value()) + ")");
    }




    labelNbCartesTotal->setText(QString::number(nbrCartes));
    labelNbCartesAir->setText(QString::number(nbrCartesAir));
    labelNbCartesFeu->setText(QString::number(nbrCartesFeu));
    labelNbCartesEau->setText(QString::number(nbrCartesEau));
    labelNbCartesPlante->setText(QString::number(nbrCartesPlante));
    labelNbCartesPierre->setText(QString::number(nbrCartesMineral));
    labelNbCartesArcane->setText(QString::number(nbrCartesArcane));




}
