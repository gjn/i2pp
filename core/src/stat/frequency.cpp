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
#include "frequency.h"

using namespace i2pp::core;

//private default constructor
Frequency::Frequency()
{
    d = new FrequencyData();
}

Frequency::Frequency(qint64 periodMS)
{
    d = new FrequencyData();
    setPeriod(periodMS);
}

Frequency::Frequency(const Frequency& other) : d(other.d)
{
}

qint64 Frequency::getPeriod() const
{
    QReadLocker locker(&d->_lock);
    return d->_period;
}

qint64 Frequency::getLastEvent() const
{
    QReadLocker locker(&d->_lock);
    return d->_lastEvent;
}

double Frequency::getAverageInterval() const
{
    QReadLocker locker(&d->_lock);
    return d->_avgInterval;
}

double Frequency::getMinAverageInterval() const
{
    QReadLocker locker(&d->_lock);
    return d->_minAverageInterval;
}

double Frequency::getAverageEventsPerPeriod() const
{
    QReadLocker locker(&d->_lock);
    if (d->_avgInterval > 0)
        return d->_period / d->_avgInterval;
    return 0.0;
}

double Frequency::getMaxAverageEventsPerPeriod() const
{
    QReadLocker locker(&d->_lock);
    if (d->_minAverageInterval > 0)
        return d->_period / d->_minAverageInterval;
    return 0.0;
}

double Frequency::getStrictAverageInterval() const
{
    QReadLocker locker(&d->_lock);
    qint64 duration = SystemTime::milliSeconds() - d->_start;
    if (duration <= 0 || d->_count <= 0)
        return 0;
    return double(duration) / d->_count;
}

double Frequency::getStrictAverageEventsPerPeriod() const
{
    double strictAvgInterval = getStrictAverageInterval();
    QReadLocker locker(&d->_lock);
    if (strictAvgInterval > 0.0)
        return d->_period / strictAvgInterval;
    return 0.0;
}

qint64 Frequency::getEventCount() const
{
    QReadLocker locker(&d->_lock);
    return d->_count;
}

void Frequency::eventOccured()
{
    recalculate(true);
}

void Frequency::recalculate()
{
    recalculate(false);
}

///////////////////private functions
void Frequency::recalculate(bool eventOccured)
{
    QWriteLocker locker(&d->_lock);
    qint64 now = SystemTime::milliSeconds();
    qint64 interval = now - d->_lastEvent;
    if (interval >= d->_period)
        interval = d->_period - 1;
    else if (interval <= 0)
        interval = 1;

    double newWeight = (interval / double(d->_period));
    double oldWeight = 1 - newWeight;

    double oldInterval = d->_avgInterval * oldWeight;
    double newInterval = interval * newWeight;
    d->_avgInterval = oldInterval + newInterval;

    if ((d->_avgInterval < d->_minAverageInterval) ||
        (d->_minAverageInterval <= 0))
        d->_minAverageInterval = d->_avgInterval;

    if (eventOccured)
    {
        d->_lastEvent = now;
        d->_count++;
    }
}

void Frequency::setPeriod(qint64 milliseconds)
{
    QWriteLocker locker(&d->_lock);
    d->_period = milliseconds;
}

