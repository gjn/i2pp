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
#ifndef I2PP_CORE_NTPMESSAGE_H
#define I2PP_CORE_NTPMESSAGE_H

namespace i2pp
{
namespace core
{

class NtpMessage
{
    public:
        typedef unsigned char byte;

        NtpMessage();
        NtpMessage(const QByteArray&);

        QByteArray toByteArray();

        ///is the timeoffset (as seconds) from 1900-01-01 00:00:00 to 1970-01-01 00:00:00
        static const quint32 _secondsTo1970;
    protected:
        struct ntpTime
        {
            ntpTime() {_seconds = 0; _fractional = 0;}
            quint32 _seconds;
            quint32 _fractional;
        };
        //get's now as seconds from 1900-01-01 00:00:00 in UTC
        static void nowUTC(ntpTime&);

        void encodeTimestamp(QByteArray& ba, int startIndex, ntpTime& timeStamp);

        byte _leapIndicator;
        byte _version;
        byte _mode;
        short _stratum;
        byte _pollInterval;
        byte _precision;
        double _rootDelay;
        double _rootDispersion;
        QByteArray _referenceIdentifier;
        //all times are as seconds from 01.01.1900 00:00:00
        ntpTime _referenceTime;
        ntpTime _originateTime;
        ntpTime _recieveTime;
        ntpTime _transmitTime;
};

}
}

#endif // NTPMESSAGE_H
