//
// Created by okkul on 28/03/24.
//

#ifndef UNTITLED5_DECKVIEW_H
#define UNTITLED5_DECKVIEW_H


#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include "DataLoader.h"

class DeckView : public QWidget {
    Q_OBJECT

public:
    DeckView(QWidget *parent = nullptr);


private:
    QJsonArray cartesLoader;
};


#endif //UNTITLED5_DECKVIEW_H
