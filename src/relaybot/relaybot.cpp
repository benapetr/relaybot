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
    libirc::ServerAddress network_address_1(this->Network1);
    network_address_1.SetNick(this->Nick);
    this->Channel1 = network_address_1.GetSuffix();
    libirc::ServerAddress network_address_2(this->Network2);
    network_address_2.SetNick(this->Nick);
    this->Channel2 = network_address_2.GetSuffix();

    Log("Connecting to " + network_address_1.GetHost());
    this->net1 = new libircclient::Network(network_address_1, network_address_1.GetHost());
    this->net1->SetDefaultUsername("Relay Bot");
    this->net1->Connect();

    Log("Connecting to " + network_address_2.GetHost());
    this->net2 = new libircclient::Network(network_address_2, network_address_2.GetHost());
    this->net2->SetDefaultUsername("Relay Bot");
    this->net2->Connect();

    connect(this->net1, SIGNAL(Event_PRIVMSG(libircclient::Parser*)), this, SLOT(text1(libircclient::Parser*)));
    connect(this->net2, SIGNAL(Event_PRIVMSG(libircclient::Parser*)), this, SLOT(text2(libircclient::Parser*)));
    connect(this->net1, SIGNAL(Event_CTCP(libircclient::Parser*,QString,QString)), this, SLOT(mis1(libircclient::Parser*,QString, QString)));
    connect(this->net2, SIGNAL(Event_CTCP(libircclient::Parser*,QString,QString)), this, SLOT(mis2(libircclient::Parser*,QString, QString)));
}

void RelayBot::text1(libircclient::Parser *px)
{
    this->net2->SendMessage("<" + px->GetSourceUserInfo()->GetNick() + "@" + this->net1->GetNetworkName() + "> " + px->GetText(), px->GetParameterLine());
}

void RelayBot::text2(libircclient::Parser *px)
{
    this->net1->SendMessage("<" + px->GetSourceUserInfo()->GetNick() + "@" + this->net2->GetNetworkName() + "> " + px->GetText(), px->GetParameterLine());
}

void RelayBot::mis1(libircclient::Parser *px, QString type, QString pars)
{
    if (type == "ACTION")
        this->net2->SendMessage("* " + px->GetSourceUserInfo()->GetNick() + "@" + this->net1->GetNetworkName() + " " + pars, px->GetParameterLine());
}

void RelayBot::mis2(libircclient::Parser *px, QString type, QString pars)
{
    if (type == "ACTION")
        this->net1->SendMessage("* " + px->GetSourceUserInfo()->GetNick() + "@" + this->net2->GetNetworkName() + " " + pars, px->GetParameterLine());
}
