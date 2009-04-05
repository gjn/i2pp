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

using namespace i2pp::core;

Random::Random()
{
    init(NULL);
}

Random::Random(Context* pContext)
{
    init(pContext);
}

Random::~Random()
{
    if (_prng)
        delete _prng;
}

void Random::init(Context* pContext)
{
    _ctx = pContext;
    if (_ctx == NULL)
        _ctx = Context::globalContext();
    _logger = _ctx->logger("Random");
    _prng = new CryptoPP::AutoSeededRandomPool();
}

bool Random::getBytes(QByteArray& ba)
{
    if (ba.size() <= 0)
        return false;

    QMutexLocker locker(&_mutex);
    try
    {
        _prng->GenerateBlock( (byte*) ba.data(), ba.size());
    }
    catch (...)
    {
        QString strMessage = QString("An error occured while trying to generate %1 random bytes. Exception thrown by crypto++ library").arg(ba.size());
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

bool Random::integer(quint32& result, quint32 start, quint32 end)
{
    QMutexLocker locker(&_mutex);
    try
    {
        result = _prng->GenerateWord32(start, end);
    }
    catch (...)
    {
        QString strMessage = QString("An error occured while trying to generate a random 32 bit integer. Exception thrown by crypto++ library");
        _logger->error(strMessage);
        return false;
    }
    QString strMessage = QString("%1 random 32 bit integer generated.").arg(result);
    _logger->debug(strMessage);
    return true;
}
