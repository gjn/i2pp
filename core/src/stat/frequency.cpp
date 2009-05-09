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

namespace i2pp {
namespace core {

class FrequencyData : public QSharedData
{
    public:
        FrequencyData()
        {
            _avgInterval = 0.0;
            _minAverageInterval = 0.0;
            _period = 0;
            _lastEvent = 0;
            _start = SystemTime::milliSeconds();
            _count = 0;
        }

        FrequencyData(const FrequencyData& other):QSharedData(other)
        ,_avgInterval(other._avgInterval)
        ,_minAverageInterval(other._minAverageInterval)
        ,_period(other._period)
        ,_lastEvent(other._lastEvent)
        ,_start(other._start)
        ,_count(other._count)
        {
        }

        double _avgInterval;
        double _minAverageInterval;
        qint64 _period;
        qint64 _lastEvent;
        qint64 _start;
        qint64 _count;
};

}
}


using namespace i2pp::core;

Frequency::Frequency(qint64 periodMS) : d(new FrequencyData)
{
    setPeriod(periodMS);
}

Frequency::Frequency(const Frequency& other) : d(other.d)
{
}

Frequency::~Frequency()
{
    // QSharedDataPointer auto deletes
    d = 0;
}

qint64 Frequency::getPeriod() const
{
    return d->_period;
}

qint64 Frequency::getLastEvent() const
{
    return d->_lastEvent;
}

double Frequency::getAverageInterval() const
{
    return d->_avgInterval;
}

double Frequency::getMinAverageInterval() const
{
    return d->_minAverageInterval;
}

double Frequency::getAverageEventsPerPeriod() const
{
    if (d->_avgInterval > 0)
        return d->_period / d->_avgInterval;
    return 0.0;
}

double Frequency::getMaxAverageEventsPerPeriod() const
{
    if (d->_minAverageInterval > 0)
        return d->_period / d->_minAverageInterval;
    return 0.0;
}

double Frequency::getStrictAverageInterval() const
{
   qint64 duration = SystemTime::milliSeconds() - d->_start;
    if (duration <= 0 || d->_count <= 0)
        return 0;
    return double(duration) / d->_count;
}

double Frequency::getStrictAverageEventsPerPeriod() const
{
    double strictAvgInterval = getStrictAverageInterval();
    if (strictAvgInterval > 0.0)
        return d->_period / strictAvgInterval;
    return 0.0;
}

qint64 Frequency::getEventCount() const
{
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
    d->_period = milliseconds;
}

