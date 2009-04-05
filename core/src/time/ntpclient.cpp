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

using namespace i2pp::core;

//static
quint64 NtpClient::currentTime(QStringList servers)
{
    if (servers.size() <= 0)
        return 0;
    //randomize the server list if there are more than one
    if (servers.size() != 1)
    {
        QStringList loc;
    }
    return 0;
}

//static
quint64 NtpClient::currentTime(QString server)
{
    return 0;
}
