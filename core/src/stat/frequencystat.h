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

#ifndef I2PP_CORE_FREQUENCYSTAT_H
#define I2PP_CORE_FREQUENCYSTAT_H

#include "frequency.h"

#include <QSharedDataPointer>

namespace i2pp
{
namespace core
{

class FrequencyStatData;

/*! FrequencyStat
    Manages a frequency stat over several periods

    This class is implicitely shared (in the Qt sense).
    This class is thread-safe.
*/
class FrequencyStat
{
    public:
        FrequencyStat(QString name, QString description,
                      QString group, QList<qint64> periods);
        FrequencyStat(const FrequencyStat& other);

        /** notify all frequencies about a new event */
        void eventOccured();

        QString getName() const;

        QString getGroupName() const;

        QString getDescription() const;

        QList<qint64> getPeriods() const;

        bool getFrequency(qint64 period, Frequency&) const;

   private:
        FrequencyStat();

        QSharedDataPointer<FrequencyStatData> d;
};

class FrequencyStatData : public QSharedData
{
    public:
        FrequencyStatData()
        {
            _statName = "";
            _description = "";
            _groupName = "";
        }

        FrequencyStatData(const FrequencyStatData& other):QSharedData(other)
        ,_statName(other._statName)
        ,_description(other._description)
        ,_groupName(other._groupName)
        ,_frequencies(other._frequencies)
        {
        }

        QString _statName;
        QString _description;
        QString _groupName;
        QList<Frequency> _frequencies;
        mutable QReadWriteLock _lock;
};


}
}

#endif // I2PP_CORE_FREQUENCYSTAT_H
