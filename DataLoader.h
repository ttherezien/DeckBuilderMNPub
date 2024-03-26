//
// Created by okkul on 24/03/24.
//

#ifndef UNTITLED5_DATALOADER_H
#define UNTITLED5_DATALOADER_H


#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class DataLoader {
public:
    DataLoader();

    // Méthode pour charger les données à partir d'un fichier JSON
    QJsonArray loadJsonData();
};



#endif //UNTITLED5_DATALOADER_H
