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
#ifndef I2PP_CORE_NTPCLIENT_H
#define I2PP_CORE_NTPCLIENT_H

namespace i2pp
{
namespace core
{

/*! NtpClient
    Simple NtpClient that gets current time from given time servers
    and returns an time offset in milliseconds of the current time
    versus the ntp time.
    It tries a list of servers and returns after the first server
    responded.
    @warning
    This class stops working after at about the 7th of February 2036.
    See NtpMessage class for details.
*/
class NtpClient
{
    public:
        ///returns current ntp time in milliseconds since january 1970 UTC
        ///return 0 if no time from server could be retrieved (no connection, no servers specified)
        static quint64 currentTime(QStringList servers);

    private:
        static quint64 currentTime(QString server);

};

}
}

#endif // NTPCLIENT_H
