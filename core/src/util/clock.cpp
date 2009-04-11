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
}

Clock::Clock(const Clock& other)
{
    UNUSED_PARAMETER(other);
}

Clock& Clock::operator = (const Clock& other)
{
    UNUSED_PARAMETER(other);
    return *this;
}


void Clock::init(Context* pContext)
{
    _ctx = pContext;
    if (_ctx == NULL)
        _ctx = Context::globalContext();
    _logger = _ctx->logger("Clock");
    _logger->info("Starting to initialise Clock");

    _startedOn = SystemTime::milliSeconds();
    _timeStamper = new TimeStamper(pContext);

    connect(_timeStamper, SIGNAL(newOffset(qint64)), SLOT(setOffset(qint64)));

    _currentOffset = 0;
    _alreadyChanged = false;
    _statsCreated = false;

    _logger->info("Clock Initialised");
}

//slote
void Clock::setOffset(qint64 offset)
{
    QWriteLocker locker(&_mutex);
    _currentOffset = offset;
}
