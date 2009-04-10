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
#include "timestamper.h"

using namespace i2pp::core;

uint TimeStamper::s_maxVarianceMS = 10*1000; //if servers differ more than 10 seconds, we have a problem

TimeStamper::TimeStamper(Context* pContext)
{
    setObjectName("TimeStamper");
    Q_ASSERT(pContext);
    _ctx = pContext;
    _logger = _ctx->logger("TimeStamper");
    _bRun = true;
    //let's try to start it here
    start(LowestPriority);
}

TimeStamper::~TimeStamper()
{
    stop();
    //wakeup
    _wait.wakeAll();
    //wait until finished
    wait();

    _logger->debug("timestamper deconstructed...yeah");
}

TimeStamper::TimeStamper(const TimeStamper& other)
{
    UNUSED_PARAMETER(other);
}

TimeStamper&  TimeStamper::operator = (const TimeStamper& other)
{
    UNUSED_PARAMETER(other);
    return *this;
}

void TimeStamper::updateConfig()
{
    QStringList defaultServers;
    defaultServers << "0.pool.ntp.org" << "1.pool.ntp.org" << "2.pool.ntp.org";
    QWriteLocker locker(&_lock);
    //default is every 5 minutes
    _queryFrequenzMS = _ctx->getSetting("TimeStamper/QueryFrequency",
                                        uint(5*60*1000))
                                        .toUInt();
    _serverList = _ctx->getSetting("TimeStamper/ServerList",
                                   QVariant(defaultServers))
                                   .toStringList();
    _disabled = _ctx->getSetting("TimeStamper/Disabled",false).toBool();
    _concurringServers = _ctx->getSetting("TimeStamp/ConcurringServers",
                                          uint(3))
                                         .toUInt();
}

bool TimeStamper::running()
{
    QReadLocker locker(&_lock);
    return _bRun;
}

void TimeStamper::stop()
{
    QWriteLocker locker(&_lock);
    _bRun = false;
}

void TimeStamper::run()
{
    while (running())
    {
        updateConfig();
        _lock.lockForRead();
        if (!_disabled)
        {
            //now do something here
            _logger->debug("timestamper is doing something...yeah");
        }
        //_lock must be locked before calling this!
        _wait.wait(&_lock, _queryFrequenzMS);
        _lock.unlock();
    }
    _logger->debug("thread is ending right now...yeah");
}
