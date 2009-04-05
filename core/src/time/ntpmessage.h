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

#include <QDateTime>

namespace i2pp
{
namespace core
{

/*! NtpMessage
    Simple wrapper to represent an NtpMessage.
    @warning
    This class stops working after at about the 26th of February 2104. We achieve
    this by following the RFC2030 recommendation in that we assume if the most
    significant bit of the time value is not set, we are in the second epoch.

    Basically, this is a copy of Java implementation in i2p
*/
class NtpMessage
{
    public:
        typedef char byte;
        NtpMessage();
        NtpMessage(const QByteArray&);
        bool operator==(const NtpMessage& other) const;

        QByteArray toByteArray();

        ///is the timeoffset (as seconds) from 1900-01-01 00:00:00 to 1970-01-01 00:00:00
        static const quint32 _secondsTo1970;
        ///returns the maximum date the current implementation is supporting
        static QDateTime maxDate();

        void encodeTimestamp(QByteArray& ba, int startIndex, const double& timeStamp);
        double decodeTimestamp(const QByteArray& ba, int startIndex);
    protected:
        static const quint32 _lastSecondEpoch; //32 bit int with bits 011111...1111
        static const quint32 _lastFirstEpoch; //32 bit int with 1111111...1111
        //get's now as seconds from 1900-01-01 00:00:00 in UTC
        static void nowUTC(double&);
        static short unsignedByteToShort(byte b);


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
        double _referenceTime;
        double _originateTime;
        double _recieveTime;
        double _transmitTime;
};

}
}

#endif // NTPMESSAGE_H
