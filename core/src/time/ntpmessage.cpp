#include "pc.h"
#include "ntpmessage.h"

using namespace i2pp::core;

const double NtpMessage::_secondsTo1970 =
    QDateTime::fromString("19000101000000","yyyyMMddhhmmss")
    .secsTo(QDateTime::fromString("19700101000000","yyyyMMddhhmmss"));

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
  _referenceTime = 0.0;
  _originateTime = 0.0;
  _recieveTime = 0.0;
  _transmitTime = now();
}

NtpMessage::NtpMessage(const QByteArray& ba)
{
  //todo: parse the byte array
}

//static
double NtpMessage::now()
{
  QDateTime current = QDateTime::currentDateTime();
  //toTime_t also converts to UTC
  return _secondsTo1970 + current.toTime_t() + current.time().msec()/1000.0;
}

QByteArray NtpMessage::toByteArray()
{
  QByteArray ba(int(48),(byte)0);
  ba[0] = (byte) (_leapIndicator << 6 | _version << 3 | _mode);
  ba[1] = (byte) _stratum;
  ba[2] = (byte) _pollInterval;
  ba[3] = (byte) _precision;

  // root delay is a signed 16.16-bit FP
  int l = (int) (_rootDelay * sizeof(int));
  ba[4] = (byte) ((l >> 24) & 0xFF);
  ba[5] = (byte) ((l >> 16) & 0xFF);
  ba[6] = (byte) ((l >> 8) & 0xFF);
  ba[7] = (byte) (l & 0xFF);

  /*
  // root dispersion is an unsigned 16.16-bit FP, in Java there are no
  // unsigned primitive types, so we use a long which is 64-bits
  long ul = (long) (rootDispersion * 65536.0);
  p[8] = (byte) ((ul >> 24) & 0xFF);
  p[9] = (byte) ((ul >> 16) & 0xFF);
  p[10] = (byte) ((ul >> 8) & 0xFF);
  p[11] = (byte) (ul & 0xFF);

  p[12] = referenceIdentifier[0];
  p[13] = referenceIdentifier[1];
  p[14] = referenceIdentifier[2];
  p[15] = referenceIdentifier[3];

  encodeTimestamp(p, 16, referenceTimestamp);
  encodeTimestamp(p, 24, originateTimestamp);
  encodeTimestamp(p, 32, receiveTimestamp);
  encodeTimestamp(p, 40, transmitTimestamp);
*/
  return ba;
}
