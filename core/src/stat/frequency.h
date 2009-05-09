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

#ifndef I2PP_CORE_FREQUENCY_H
#define I2PP_CORE_FREQUENCY_H

#include "../time/systemtime.h"
#include <QSharedDataPointer>

namespace i2pp
{
namespace core
{

class FrequencyPrivate;


/*! Frequency
	Manage the calculation of a moving event frequency over a certain period.

    This class is implicitely shared (in the Qt sense) and it is reentrant, but
    NOT thread-safe.
*/
class Frequency
{
    public:
        Frequency(qint64 periodMS);
        Frequency(const Frequency& other);

        /** how long is this frequency averaged over? */
        qint64 getPeriod() const;

        /** when did the last event occur? */
        qint64 getLastEvent() const;

        /**
         * on average over the last $period, after how many milliseconds are events coming in,
         * as calculated during the last event occurrence?
         */
        double getAverageInterval() const;

        /** what is the lowest average interval (aka most frequent) we have seen? */
        double getMinAverageInterval() const;

        /** calculate how many events would occur in a period given the current average */
        double getAverageEventsPerPeriod() const;

        /** calculate how many events would occur in a period given the maximum average */
        double getMaxAverageEventsPerPeriod() const;

        /** over the lifetime of this stat, without any decay or weighting, what was the average interval between events? */
        double getStrictAverageInterval() const;

        /** using the strict average interval, how many events occur within an average period? */
        double getStrictAverageEventsPerPeriod() const;

        /** how many events have occurred within the lifetime of this stat? */
        qint64 getEventCount() const;

        /** Take note that a new event occurred, recalculating all the averages and frequencies */
        void eventOccured();

        /** Recalculate the averages */
        void recalculate();

    private:
        void recalculate(bool eventOccured);

        void setPeriod(qint64 milliseconds);

        QSharedDataPointer<FrequencyPrivate> d;
        friend class FrequencyPrivate;
};


class FrequencyPrivate : public QSharedData
{
    public:
        FrequencyPrivate()
        {
            _avgInterval = 0.0;
            _minAverageInterval = 0.0;
            _period = 0;
            _lastEvent = 0;
            _start = SystemTime::milliSeconds();
            _count = 0;
        }

        FrequencyPrivate(const FrequencyPrivate& other):QSharedData(other)
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

#endif // I2PP_CORE_FREQUENCY_H
