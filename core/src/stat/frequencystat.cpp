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
#include "frequencystat.h"

using namespace i2pp::core;

//private default constructor
FrequencyStat::FrequencyStat()
{
    d = new FrequencyStatData();
}

FrequencyStat::FrequencyStat(QString name, QString description,
                             QString group, QList<qint64> periods)
{
    d = new FrequencyStatData();
    d->_statName = name;
    d->_description = description;
    d->_groupName = group;
    foreach (qint64 period, periods)
        d->_frequencies << Frequency(period);
}

FrequencyStat::FrequencyStat(const FrequencyStat& other) : d(other.d)
{
}

QString FrequencyStat::getName() const
{
    return d->_statName;
}

QString FrequencyStat::getGroupName() const
{
    return d->_groupName;
}

QString FrequencyStat::getDescription() const
{
    return d->_description;
}

QList<qint64> FrequencyStat::getPeriods() const
{
    QList<qint64> retval;
    foreach (Frequency freq, d->_frequencies)
        retval << freq.getPeriod();
    return retval;
}

bool FrequencyStat::getFrequency(qint64 period, Frequency& freq) const
{
    foreach (Frequency myfreq, d->_frequencies)
    {
        if (myfreq.getPeriod() == period)
        {
            freq = myfreq;
            return true;
        }
    }
    return false;
}

void FrequencyStat::eventOccured()
{
    foreach (Frequency freq, d->_frequencies)
        freq.eventOccured();
}

