//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU Lesser General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU Lesser General Public License for more details.

// Copyright (c) Petr Bena 2018

#include <QStringList>
#include <QCoreApplication>
#include <QTimer>
#include "relaybot.h"

#ifdef __linux__
#include <unistd.h>
#endif

#define DAEMONIZE_SUCCESS 0
#define DAEMONIZE_FORKED  1
#define DAEMONIZE_FAILED  2
#define EDAEMONIZEFAILED    -1
#define EUNHANDLEDEXCEPTION -2
#define EPIDMKER            -3

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc < 4)
    {
        qWarning("You need to provide 3 parameters: nick network/#channnel network2/#channel");
        return 1;
    }

    QString net1 = argv[2];
    QString net2 = argv[3];

    if (!net1.contains("/") || !net2.contains("/"))
    {
        qWarning("Invalid format");
        return 2;
    }

    QStringList inputs = net1.split("/");
    RelayBot* relay_bot = new RelayBot();
    relay_bot->Network1 = inputs[0];
    relay_bot->Channel1 = inputs[1];
    relay_bot->Nick = argv[1];
    inputs = net2.split("/");
    relay_bot->Network2 = inputs[0];
    relay_bot->Channel2 = inputs[1];
    QTimer::singleShot(0, relay_bot, SLOT(Main()));
    return a.exec();
}
