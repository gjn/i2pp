/*  this file is part of i2pp
    Copyright (C)2009 Gilbert Jeiziner

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#include "pc.h"
#include "ntpclient.h"
#include "ntpmessage.h"
#include "random.h"
#include "systemtime.h"

#include <QUdpSocket>

using namespace i2pp::core;

//static
qint32 NtpClient::currentOffset(QStringList servers)
{
    Log4Qt::Logger* logger = Context::globalContext()->logger("NtpClient");

    if (servers.size() <= 0)
    {
        logger->warn("Ntp Client failed because no servers are provided.");
        return 0;
    }
    //randomize the server list if there are more than one
    if (servers.size() > 1)
    {
        int nSize = servers.size();
        Random* random = Context::globalContext()->random();
        for (int i=0; i < nSize; i++)
        {
            quint32 randomNr;
            if (random->getUInt32(randomNr, 0, nSize - i - 1))
                servers.swap(i, i + randomNr);
        }
    }
    for (int i = 0; i < servers.size(); i++)
    {
        quint64 curr = currentOffset(servers.at(i));
        if (curr > 0)
            return curr;
    }
    return 0;
}

//static
qint32 NtpClient::currentOffset(QString server)
{
    Log4Qt::Logger* logger = Context::globalContext()->logger("NtpClient");
    QString strMessage = QString("Trying to get time offset from server %1.").arg(server);
    logger->debug(strMessage);

    QUdpSocket udpSocket;
    udpSocket.connectToHost(server, 123);
    if (!udpSocket.waitForConnected())
    {
        QString strMessage = QString("Failed to connect to server %1.").arg(server);
        logger->warn(strMessage);
        return 0;
    }
    NtpMessage sendMessage;
    QByteArray sendArray = sendMessage.toByteArray();

    if (udpSocket.write(sendArray) != sendArray.size())
    {
        udpSocket.disconnectFromHost();
        if (udpSocket.state() != QAbstractSocket::UnconnectedState)
            udpSocket.waitForDisconnected();
        QString strMessage = QString("Failed to send udp datagram to server %1.").arg(server);
        logger->warn(strMessage);
        return 0;
    }

    while (udpSocket.bytesAvailable() < sendArray.size())
    {
        if (!udpSocket.waitForReadyRead())
        {
            udpSocket.disconnectFromHost();
            if (udpSocket.state() != QAbstractSocket::UnconnectedState)
                udpSocket.waitForDisconnected();
            QString strMessage = QString("Failed to recieve udp datagram from server %1.").arg(server);
            logger->warn(strMessage);
            return 0;
        }
    }

    QByteArray recievedArray = udpSocket.read(sendArray.size());
    if (recievedArray.size() != sendArray.size())
    {
        udpSocket.disconnectFromHost();
        if (udpSocket.state() != QAbstractSocket::UnconnectedState)
            udpSocket.waitForDisconnected();
        QString strMessage = QString("Failed to recieve correct number of bytes from server %1.").arg(server);
        logger->warn(strMessage);
        return 0;
    }
    //get recieve time as fast as possible
    double destinationTime = (SystemTime::milliSeconds()/1000.0) + NtpMessage::_secondsTo1970;

    udpSocket.disconnectFromHost();
    if (udpSocket.state() != QAbstractSocket::UnconnectedState)
        udpSocket.waitForDisconnected();

    NtpMessage recMessage(recievedArray);
    if ((recMessage._stratum < 1) || (recMessage._stratum > 15))
    {
        QString strMessage = QString("Stratum of server %1 is in unacceptable range (%2).").arg(server).arg(recMessage._stratum);
        logger->warn(strMessage);
        return 0;
    }

    qint32 retval = qint32(((recMessage._recieveTime - recMessage._originateTime) + (recMessage._transmitTime - destinationTime)) * 500.0);

    strMessage = QString("Time offset determined from server %1 is %2 ms").arg(server).arg(retval);
    logger->info(strMessage);
    return retval;
}
