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
#include "random.h"

#include "botan/auto_rng.h"


using namespace i2pp::core;

Random::Random(Context* pContext)
{
    init(pContext);
}

Random::~Random()
{
    if (_prng)
        delete _prng;
}

Random::Random(const Random& other)
{
    UNUSED_PARAMETER(other);
}

Random&  Random::operator = (const Random& other)
{
    UNUSED_PARAMETER(other);
    return *this;
}


void Random::init(Context* pContext)
{
    _ctx = pContext;
    if (_ctx == NULL)
        _ctx = Context::globalContext();
    _logger = _ctx->logger("Random");

    _logger->info("Starting to initialise Randomizer");

    _prng = 0;
    try
    {
        _prng = new Botan::AutoSeeded_RNG();
    }
    catch(...)
    {

    }
    logInitFinished();


}

void Random::logInitFinished()
{
    if (_prng == 0)
    {
        _logger->fatal("Unable to initialise Randomizer from Botan Library!");
    }
    else
    {
        _logger->info("Randomizer initialised with %1", _prng->name().c_str());
        #if defined(BOTAN_HAS_X931_RNG)
            #if defined(BOTAN_HAS_HMAC_RNG)
                _logger->info("Randomizer is using HMAC_RNG");
            #elif defined(BOTAN_HAS_RANDPOOL)
                _logger->info("Randomizer is using Randpool");
            #endif
        #endif

        QString strEntropies = "Randomizer uses the following entropies:";
        #if defined(BOTAN_HAS_TIMER_HARDWARE)
            strEntropies += " [Hardware_Timer]";
        #endif
        #if defined(BOTAN_HAS_TIMER_POSIX)
            strEntropies += " [POSIX_Timer]";
        #endif
        #if defined(BOTAN_HAS_TIMER_UNIX)
            strEntropies += " [Unix_Timer]";
        #endif
        #if defined(BOTAN_HAS_TIMER_WIN32)
            strEntropies += " [Win32_Timer]";
        #endif
        #if defined(BOTAN_HAS_ENTROPY_SRC_DEVICE)
            strEntropies += " [/dev/random] [/dev/srandom] [/dev/uandom]";
        #endif
        #if defined(BOTAN_HAS_ENTROPY_SRC_EGD)
            strEntropies += " [/var/run/egd-pool] [/dev/egd-pool]";
        #endif
        #if defined(BOTAN_HAS_ENTROPY_SRC_CAPI)
            strEntropies += " [Win32_CAPI_EntropySource]";
        #endif
        #if defined(BOTAN_HAS_ENTROPY_SRC_FTW)
            strEntropies += " [/proc]";
        #endif
        #if defined(BOTAN_HAS_ENTROPY_SRC_WIN32)
            strEntropies += " [Win32_EntropySource]";
        #endif
        #if defined(BOTAN_HAS_ENTROPY_SRC_BEOS)
            strEntropies += " [BeOS_EntropySource]";
        #endif
        #if defined(BOTAN_HAS_ENTROPY_SRC_UNIX)
            strEntropies += " [/bin] [/sbin] [/usr/bin] [/usr/sbin]";
        #endif
        _logger->info(strEntropies);
   }

}

bool Random::getBytes(QByteArray& ba)
{
    if (ba.size() <= 0)
        return false;

    if (_prng)
    {
        QMutexLocker locker(&_mutex);
        try
        {
            _prng->randomize(reinterpret_cast<unsigned char*>(ba.data()), ba.size());
        }
        catch (...)
        {
            QString strMessage = QString("An error occured while trying to generate %1 random bytes. Exception thrown by baton library").arg(ba.size());
            _logger->error(strMessage);
            return false;
        }
    }
    else
    {
        QString strMessage = QString("An error occured while trying to generate %1 random bytes. Randomizer not initialised.").arg(ba.size());
        _logger->error(strMessage);
        return false;
    }
    QString strMessage = QString("%1 random bytes successfully generated.").arg(ba.size());
    _logger->debug(strMessage);
    return true;
}

QByteArray Random::getBytes(unsigned int size)
{
    QByteArray ba(size,char(0));
    if (getBytes(ba))
        return ba;
    return QByteArray(0,char(0));
}

bool Random::getByte(char& b)
{
    if (_prng)
    {
        QMutexLocker locker(&_mutex);
        try
        {
            b = _prng->next_byte();
        }
        catch (...)
        {
            QString strMessage = QString("An error occured while trying to generate one random byte. Exception thrown by baton library");
            _logger->error(strMessage);
            return false;
        }
    }
    else
    {
        QString strMessage = QString("An error occured while trying to generate one random byte. Randomizer not initialized.");
        _logger->error(strMessage);
        return false;
    }
    QString strMessage = QString("one random byte successfully generated.");
    _logger->debug(strMessage);
    return true;
}
