//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU Lesser General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU Lesser General Public License for more details.

// Copyright (c) Petr Bena 2018

#ifndef RELAYBOT_H
#define RELAYBOT_H

#include <QObject>
#include "../libirc/libircclient/network.h"

class RelayBot : public QObject
{
        Q_OBJECT
    public:
        RelayBot();
        void Log(QString text);
        QString Network1;
        QString Network2;
        QString Channel1;
        QString Channel2;
        QString Nick;

    public slots:
        void Main();
        void text1(libircclient::Parser *px);
        void text2(libircclient::Parser *px);
        void mis1(libircclient::Parser *px, QString type, QString pars);
        void mis2(libircclient::Parser *px, QString type, QString pars);

    protected:
        libircclient::Network *net1;
        libircclient::Network *net2;
};

#endif // RELAYBOT_H
