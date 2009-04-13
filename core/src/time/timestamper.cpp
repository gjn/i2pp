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

#include "random.h"
#include "ntpclient.h"
#include "clock.h"

using namespace i2pp::core;

const qint64 TimeStamper::MAX_VARIANCE_MS = 10*1000; //if servers differ more than 10 seconds, we have a problem

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
    //stopping the thread
    stop();
    //wakeup
    _wait.wakeAll();
    //wait until finished
    wait();
    _logger->trace("timestamper deconstructed...yeah");
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

bool TimeStamper::enabled()
{
    QReadLocker locker(&_lock);
    return !_disabled;
}

void TimeStamper::stop()
{
    QWriteLocker locker(&_lock);
    _bRun = false;
}

void TimeStamper::run()
{
    sleep(1); //wait one second

    _logger->info("Starting up TimeStamper");
    while (running())
    {
        //possibly configuration changed during runtime
        updateConfig();

        //get values and have them locally
        _lock.lockForRead();
        QStringList servers = _serverList;
        quint32 randomizedOffset = 0;
        _ctx->random()->getUInt32(randomizedOffset, 0, _queryFrequenzMS);
        uint sleepTime = _queryFrequenzMS + randomizedOffset;
        _lock.unlock();

        //do the stuff
        if (enabled())
        {
            if (_logger->isDebugEnabled())
            {
                QString strMsg = QString("Querying servers ") + servers.join(",");
                _logger->debug(strMsg);
            }
            qint64 offset;
            if (queryOffset(offset, servers))
            {
                _logger->info(QString("Timestamper is emitting new offset of %1 ms.").arg(offset));
                emit newOffset(offset);
            }
            else
                sleepTime = 30*1000;
        }
        else
        {
            _logger->info("Timestamper is disabled!");
        }
        _lock.lockForRead();
        _wait.wait(&_lock, sleepTime);
        _lock.unlock();
    }
    _logger->info("TimeStamper stopped.");
}

bool TimeStamper::queryOffset(qint64& offset, const QStringList& servers)
{
    QList<qint64> found;
    qint64 expectedDelta = 0;
    _lock.lockForRead();
    uint numServers = _concurringServers;
    _lock.unlock();

    for (uint i = 0; i < numServers; i++)
    {
        //let's see if the want the thread to be stopped (probably from the outside)
        if (!running())
        {
            _logger->debug("Querying NTP servers aborted.");
            return false;
        }
        sleep(10); //wait at least 10 seconds between each concurring server
        if (!running())
        {
            _logger->debug("Querying NTP servers aborted.");
            return false;
        }
        if (NtpClient::currentOffset(offset, servers))
        {
            qint64 delta = offset - _ctx->clock()->offset();
            found.append(delta);
            if (i == 0)
            {
                if (qAbs(delta) < MAX_VARIANCE_MS)
                {
                    _logger->info(QString("A single SNTP offset query (%1) was within the tolerance").arg(offset));
                    break; //we are happy when we are within the tolerance
                }
                else
                    expectedDelta = delta;
            }
            else
            {
                if (qAbs(delta - expectedDelta) >= MAX_VARIANCE_MS)
                {
                    if (_logger->isErrorEnabled())
                    {
                        QString strMessage = QString("SNTP client variance"
                                                     "exceeded at query %1."
                                                     " Expected %2ms and found %3ms."
                                                     " All found so far:")
                                             .arg(i)
                                             .arg(expectedDelta)
                                             .arg(delta);
                        for (int j = 0; j < found.size(); j++)
                        {
                            strMessage += QString(" %1ms").arg(found[j]);
                        }
                        strMessage += QString(".");
                        _logger->error(strMessage);
                    }
                    return false;
                }
            }
        }
    }
    if (found.size() <= 0)
    {
        _logger->error("Unable to reach any of the NTP servers. Is the Network connected?");
        return false;
    }
    if (_logger->isDebugEnabled())
    {
        QString strMessage = "Found offsets:";
        for (int j = 0; j < found.size(); j++)
        {
            strMessage += QString(" %1ms").arg(found[j]);
        }
        strMessage += QString(".");
        _logger->debug(strMessage);
    }
    return true;
}
