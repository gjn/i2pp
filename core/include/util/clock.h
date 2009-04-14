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

#ifndef I2PP_CORE_CLOCK_H
#define I2PP_CORE_CLOCK_H

#include "context.h"
#include "log4qt/logger.h"

namespace i2pp
{
namespace core
{

class TimeStamper;

/*! Clock class for i2pp
  The clock in i2pp is responsible to have the same time-reference
  across the i2p network. It's composed of the system time with
  an applied offset calculated by querying NTP servers on a regular
  interval.
*/

class Clock : public QObject
{
friend class Context;
friend class TimeStamper;

Q_OBJECT

public:
    virtual ~Clock();

    quint64 now();

signals:
    void offsetChanged(qint64 delta);

protected slots:
    void offset(qint64 offsetMS);

protected:
    Clock(Context* pContext);
    Clock(const Clock& other); //disable copy constructor
    Clock&  operator = (const Clock& other); //disable assignement operator

    void init(Context* pContext);

    qint64 offset() const;

    Context* _ctx; //reference
    Log4Qt::Logger* _logger;
    TimeStamper* _timeStamper;

    mutable QReadWriteLock _mutex;

    qint64 _currentOffset; //current offset to the computes system time
    bool _alreadyChanged; //was the offset set once?
    bool _statsCreated;
    quint64 _startedOn;

    static const qint64 MAX_OFFSET;
    static const qint64 MAX_LIVE_OFFSET;
    static const qint64 MIN_OFFSET_CHANGE;

};

}
}

#endif
