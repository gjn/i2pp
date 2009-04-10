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

#ifndef I2PP_CORE_TIMESTAMPER_H
#define I2PP_CORE_TIMESTAMPER_H

#include "context.h"
#include "log4qt/logger.h"

#include <QThread>
#include <QWaitCondition>
#include <QStringList>

namespace i2pp
{
namespace core
{

/*! Timestamper
    Timestamper thread queries ntp servers in a regualar intervall
    to update the systemtime offset from the ntp time. A signal is
    emitted when a new offset is determined.
*/
class TimeStamper : public QThread
{
    public:
        TimeStamper(Context* pContext);
        virtual ~TimeStamper();

    signals:
        void newOffset(qint32);

    protected:
        TimeStamper(const TimeStamper& other); //disable copy constructor
        TimeStamper&  operator = (const TimeStamper& other); //disable assignement operator

        bool running();
        void stop();
        void updateConfig();

        //called in the thread
        virtual void run();

        //locking and control
        QReadWriteLock _lock;
        QWaitCondition _wait;
        bool _bRun;

        //configuration
        uint _queryFrequenzMS;
        QStringList _serverList;
        bool _disabled;
        uint _concurringServers;

        static uint s_maxVarianceMS;

        //access global objects
        Context* _ctx;
        Log4Qt::Logger* _logger;
};

}
}

#endif // I2PP_CORE_TIMESTAMPER_H
