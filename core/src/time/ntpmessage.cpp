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
#include "ntpmessage.h"
#include "i2pptime.h"
#include "random.h"

#include <math.h>
#include <cstdlib>

using namespace i2pp::core;

const quint32 NtpMessage::_secondsTo1970 = 2208988800U;
const quint32 NtpMessage::_lastSecondEpoch = quint32(pow(2,31));
const quint32 NtpMessage::_lastFirstEpoch = quint32(pow(2,32))-1;

bool bRandInit = false;

NtpMessage::NtpMessage()
{
    _leapIndicator = 0;
    _version = 3;
    _mode = 3;
    _stratum = 0;
    _pollInterval = 0;
    _precision = 0;
    _rootDelay = 0.0;
    _rootDispersion = 0.0;
    _referenceIdentifier = QByteArray((int)4,(byte)0);
    _referenceTime = _lastSecondEpoch + 1;
    _originateTime = _referenceTime;
    _recieveTime = _referenceTime;
    nowUTC(_transmitTime);
}

NtpMessage::NtpMessage(const QByteArray& ba)
{
    _leapIndicator = (byte) ((ba[0] >> 6) & 0x3);
    _version = (byte) ((ba[0] >> 3) & 0x7);
    _mode = (byte) (ba[0] & 0x7);
    _stratum = unsignedByteToShort(ba[1]);
    _pollInterval = ba[2];
    _precision = ba[3];
    _rootDelay = (ba[4] * 256.0) +
                  unsignedByteToShort(ba[5]) +
                  (unsignedByteToShort(ba[6]) / 256.0) +
                  (unsignedByteToShort(ba[7]) / 65536.0);
    _rootDelay = (unsignedByteToShort(ba[8]) * 256.0) +
                         unsignedByteToShort(ba[9]) +
                         (unsignedByteToShort(ba[10]) / 256.0) +
                         (unsignedByteToShort(ba[11]) / 65536.0);
    _referenceIdentifier[0] = ba[12];
    _referenceIdentifier[1] = ba[13];
    _referenceIdentifier[2] = ba[14];
    _referenceIdentifier[3] = ba[15];
    _referenceTime = decodeTimestamp(ba, 16);
    _originateTime = decodeTimestamp(ba, 24);
    _recieveTime = decodeTimestamp(ba, 32);
    _transmitTime = decodeTimestamp(ba, 40);
}

bool NtpMessage::operator==(const NtpMessage& other) const
{
    if (_leapIndicator == other._leapIndicator &&
        _version == other._version &&
        _mode == other._mode &&
        _stratum == other._stratum &&
        _pollInterval == other._pollInterval &&
        _precision == other._precision &&
        _rootDelay == other._rootDelay &&
        fabs(_rootDispersion - other._rootDispersion) < 0.0001 &&
        _referenceIdentifier == other._referenceIdentifier &&
        fabs(_referenceTime - other._referenceTime) < 0.0001 &&
        fabs(_originateTime - other._originateTime) < 0.0001 &&
        fabs(_recieveTime - other._recieveTime) < 0.0001 &&
        fabs(_transmitTime - other._transmitTime) < 0.0001)
        return true;
  return false;
}

//static
void NtpMessage::nowUTC(double& time)
{
    time = _secondsTo1970 + Time::milliSeconds() / 1000.0;
}

//static
QDateTime NtpMessage::maxDate()
{
    quint64 max = quint64(_lastFirstEpoch) + _lastSecondEpoch;
    return QDateTime::fromTime_t(max - _secondsTo1970);
}

//static
short NtpMessage::unsignedByteToShort(byte b)
{
    if((b & 0x80)==0x80)
        return (short) (128 + (b & 0x7f));
    else
        return (short) b;
}

QByteArray NtpMessage::toByteArray()
{
    QByteArray ba(int(48),(byte)0);
    ba[0] = (byte) (_leapIndicator << 6 | _version << 3 | _mode);
    ba[1] = (byte) _stratum;
    ba[2] = (byte) _pollInterval;
    ba[3] = (byte) _precision;

    // root delay is a signed 16.16-bit FP
    qint16 l = (qint16) (_rootDelay * 65536.0);
    ba[4] = (byte) ((l >> 24) & 0xFF);
    ba[5] = (byte) ((l >> 16) & 0xFF);
    ba[6] = (byte) ((l >> 8) & 0xFF);
    ba[7] = (byte) (l & 0xFF);

    // root dispersion is an unsigned 16.16-bit FP
    quint16 ul = (quint16) (_rootDispersion * 65536.0);
    ba[8] = (byte) ((ul >> 24) & 0xFF);
    ba[9] = (byte) ((ul >> 16) & 0xFF);
    ba[10] = (byte) ((ul >> 8) & 0xFF);
    ba[11] = (byte) (ul & 0xFF);

    ba[12] = _referenceIdentifier[0];
    ba[13] = _referenceIdentifier[1];
    ba[14] = _referenceIdentifier[2];
    ba[15] = _referenceIdentifier[3];

    encodeTimestamp(ba, 16, _referenceTime);
    encodeTimestamp(ba, 24, _originateTime);
    encodeTimestamp(ba, 32, _recieveTime);
    encodeTimestamp(ba, 40, _transmitTime);
    return ba;
}

void NtpMessage::encodeTimestamp(QByteArray& ba, int startIndex, const double& ts)
{
    double timeStamp = ts;
    //if we are later than 2036, then we assume it's second epoch
    if (timeStamp > _lastFirstEpoch)
        timeStamp -= _lastFirstEpoch;
    Q_ASSERT(timeStamp >= 0.0 && timeStamp <= _lastFirstEpoch);
    // Converts a double into a 64-bit fixed point
    for(int i=0; i<8; i++)
    {
        // 2^24, 2^16, 2^8, .. 2^-32
        double base = pow(2, (3-i)*8);
        // Capture byte value
        ba[startIndex+i] = (byte) (timeStamp / base);
        // Subtract captured value from remaining total
        timeStamp = timeStamp - (double) (unsignedByteToShort(ba[startIndex+i]) * base);
    }
    // From RFC 2030: It is advisable to fill the non-significant
    // low order bits of the timestamp with a random, unbiased
    // bitstring, both to avoid systematic roundoff errors and as
    // a means of loop detection and replay detection.
    // the below should be sufficient for our needs
    QByteArray randbyte = Random().getBytes(1);
    if (ba.size() == 1)
        ba[startIndex+7] = (byte) randbyte[0];
}

double NtpMessage::decodeTimestamp(const QByteArray& ba, int startIndex)
{
    double r = 0.0;
    for(int i=0; i<8; i++)
    {
         r += unsignedByteToShort(ba[startIndex+i]) * pow(2, (3-i)*8);
    }
    //let's see if we are in second epoch
    if (r <= _lastSecondEpoch)
        r += _lastFirstEpoch;
    Q_ASSERT(r > _lastSecondEpoch && r <= (quint64(_lastSecondEpoch) + quint64(_lastFirstEpoch)));
    return r;
}
