//
// Created by okkul on 24/03/24.
//

#include "DataLoader.h"
#include <QFile>

DataLoader::DataLoader() {}

QJsonArray DataLoader::loadJsonData() {
    const QString path = "./Data/CarteJson.json";
    QFile file(path);
    QJsonArray dataArray;

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Impossible d'ouvrir le fichier JSON.");
        return dataArray;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    dataArray = doc.array();

    return dataArray;
}