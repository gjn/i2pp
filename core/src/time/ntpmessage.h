#ifndef I2PP_CORE_NTPMESSAGE_H
#define I2PP_CORE_NTPMESSAGE_H

namespace i2pp {
  namespace core {

class NtpMessage
{
public:
  typedef unsigned char byte;

  NtpMessage();
  NtpMessage(const QByteArray&);

  QByteArray toByteArray();

protected:
  //is the timeoffset (as seconds) from 1900-01-01 00:00:00 to 1970-01-01 00:00:00
  static const double _secondsTo1970;
  static double now(); //get's now as seconds from 1900-01-01 00:00:00 in UTC

  void encodeTimestamp(QByteArray& ba, int startIndex, double timeStamp);

  byte _leapIndicator;
  byte _version;
  byte _mode;
  short _stratum;
  byte _pollInterval;
  byte _precision;
  double _rootDelay;
  double _rootDispersion;
  QByteArray _referenceIdentifier;
  //all tims are as seconds from 01.01.1900 00:00:00
  double _referenceTime;
  double _originateTime;
  double _recieveTime;
  double _transmitTime;
};

}
}

#endif // NTPMESSAGE_H
