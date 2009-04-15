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
#include "clock.h"
#include "time/timestamper.h"
#include "time/systemtime.h"

using namespace i2pp::core;

///if the clock is sqewed by more than 3 days, we are in trouble
const qint64 Clock::MAX_OFFSET = 3 * 24 * 60 * 60 * 1000;
///once set, don't allow changes of more than 10 minutes
const qint64 Clock::MAX_LIVE_OFFSET = 10 * 60 * 1000;
///if the clock sqew changes by less than 1s, ignore it (so we don't slide all over the place)
const qint64 Clock::MIN_OFFSET_CHANGE = 10 * 1000;

Clock::Clock(Context* pContext)
{
    init(pContext);
}

Clock::~Clock()
{
    delete _timeStamper;
}

Clock::Clock(const Clock& other):QObject(NULL)
{
    UNUSED_PARAMETER(other);
}

Clock& Clock::operator = (const Clock& other)
{
    UNUSED_PARAMETER(other);
    return *this;
}

quint64 Clock::now()
{
    return SystemTime::milliSeconds() + offset();
}

void Clock::init(Context* pContext)
{
    _ctx = pContext;
    if (_ctx == NULL)
        _ctx = Context::globalContext();
    _logger = _ctx->logger("Clock");
    _logger->info("Starting to initialise Clock");

    _startedOn = SystemTime::milliSeconds();
    _currentOffset = 0;
    _alreadyChanged = false;
    _statsCreated = false;

    _timeStamper = new TimeStamper(pContext);
    connect(_timeStamper, SIGNAL(newOffset(qint64)), SLOT(offset(qint64)));

    _logger->info("Clock Initialised");
}

//slot
void Clock::offset(qint64 offsetMS)
{
    qint64 delta = offsetMS - offset();
    if ((offsetMS > MAX_OFFSET) || (offsetMS < 0 - MAX_OFFSET))
    {
        _logger->error(QString("Maximum offset shift exceeded [%1], NOT HONORING IT").arg(offsetMS));
        return;
    }
    // only allow substantial modifications before the first 10 minutes
    if (_alreadyChanged && (SystemTime::milliSeconds() - _startedOn > 10 * 60 * 1000))
    {
        if ((delta > MAX_LIVE_OFFSET) || (delta < 0 - MAX_LIVE_OFFSET))
        {
            _logger->error(QString("The clock has already been updated, but you want to change it by "
                                   "%1 to %2? Did something break?").arg(delta).arg(offsetMS));
            return;
        }
    }
    if ((delta < MIN_OFFSET_CHANGE) && (delta > 0 - MIN_OFFSET_CHANGE))
    {
        _logger->debug(QString("Not changing offset since it is only %1ms").arg(delta));
        _alreadyChanged = true;
        return;
    }
    if (_alreadyChanged)
    {
        if (delta > 15*1000)
            _logger->warn(QString("Updating clock offset to %1ms from %2ms").arg(offsetMS).arg(offset()));
        else if (_logger->isInfoEnabled())
            _logger->info(QString("Updating clock offset to %1ms from %2ms").arg(offsetMS).arg(offset()));

        if (!_statsCreated)
        {
            ///@todo : establish stat manager
            //_context.statManager().createRateStat("clock.skew", "How far is the already adjusted clock being skewed?", "Clock", new long[] { 10*60*1000, 3*60*60*1000, 24*60*60*60 });
        }
        _statsCreated = true;
        ///@todo: add rate to the stat manager
        //_context.statManager().addRateData("clock.skew", delta, 0);
    }
    else
    {
        _logger->info(QString("Initializing clock offset to %1ms from %2ms").arg(offsetMS).arg(offset()));
    }
    _alreadyChanged = true;
    _mutex.lockForWrite();
    _currentOffset = offsetMS;
    _mutex.unlock();

    emit offsetChanged(delta);
}

qint64 Clock::offset() const
{
    QReadLocker locker(&_mutex);
    return _currentOffset;
}
