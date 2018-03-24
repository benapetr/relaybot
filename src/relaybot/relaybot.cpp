//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU Lesser General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU Lesser General Public License for more details.

// Copyright (c) Petr Bena 2018

#include <iostream>
#include "../libirc/libircclient/parser.h"
#include "../libirc/libirc/serveraddress.h"
#include "relaybot.h"

RelayBot::RelayBot()
{
    this->net1 = nullptr;
    this->net2 = nullptr;
}

void RelayBot::Log(QString text)
{
    std::cout << text.toStdString() << std::endl;
}

void RelayBot::Main()
{
    Log("Connecting to " + this->Network1);
    libirc::ServerAddress network_address_1(this->Network1, false, 6667, this->Nick);
    this->net1 = new libircclient::Network(network_address_1, this->Network1);
    //connect(this->net1, SIGNAL(Event_RawIncoming(QByteArray)), this, SLOT(DebugIn(QByteArray)));
    connect(this->net1, SIGNAL(Event_ISUPPORT(libircclient::Parser*)), this, SLOT(Finished_Join1(libircclient::Parser*)));
    this->net1->Connect();
    connect(this->net1, SIGNAL(Event_PRIVMSG(libircclient::Parser*)), this, SLOT(text1(libircclient::Parser*)));
    Log("Connecting to " + this->Network2);
    libirc::ServerAddress network_address_2(this->Network2, false, 6667, this->Nick);
    this->net2 = new libircclient::Network(network_address_2, this->Network2);
    connect(this->net2, SIGNAL(Event_ISUPPORT(libircclient::Parser*)), this, SLOT(Finished_Join2(libircclient::Parser*)));
    this->net2->Connect();
    connect(this->net2, SIGNAL(Event_PRIVMSG(libircclient::Parser*)), this, SLOT(text2(libircclient::Parser*)));
}

void RelayBot::Finished_Join1(libircclient::Parser *parser)
{
    this->net1->RequestJoin(this->Channel1);
}

void RelayBot::Finished_Join2(libircclient::Parser *parser)
{
    this->net2->RequestJoin(this->Channel2);
}

void RelayBot::DebugIn(QByteArray data)
{
    Log(QString(data));
}

void RelayBot::DebugOut(QByteArray data)
{
    Log(QString(data));
}

void RelayBot::text1(libircclient::Parser *px)
{
    this->net2->SendMessage("<" + px->GetSourceUserInfo()->GetNick() + "@" + this->net2->GetNetworkName() + "> " + px->GetText(), px->GetParameterLine());
}

void RelayBot::text2(libircclient::Parser *px)
{
    this->net1->SendMessage("<" + px->GetSourceUserInfo()->GetNick() + "@" + this->net1->GetNetworkName() + "> " + px->GetText(), px->GetParameterLine());
}
