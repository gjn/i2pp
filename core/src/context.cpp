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
#include "context.h"
#include "log4qt/ttcclayout.h"
#include "log4qt/fileappender.h"

#include <QSettings>

namespace i2pp {
    namespace core {

        class ContextGlobals
        {
            public:
                ContextGlobals()
                {
                    _format = QSettings::NativeFormat;
#ifdef WIN32 //on windows, native is in registry...we don't want that
                    _format = QSettings::IniFormat;
#endif
                    QSettings localSettings(_format, QSettings::UserScope,"i2pp","dummy");
                    QFileInfo fi(localSettings.fileName());
                    QString directory = fi.absoluteDir().absolutePath() + QDir::separator() +
                                        fi.baseName () + QDir::separator();
                    _confSuffix = fi.completeSuffix();
                    QDir curDir = QDir(directory);
                    curDir.cdUp();
                    _rootDirectory = curDir.absolutePath() + QDir::separator();
                    curDir.mkpath(_rootDirectory);
                    _globalSettings = new QSettings(_rootDirectory + "router." + _confSuffix, _format);
                }

                ~ContextGlobals()
                {
                    delete _globalSettings;
                }

                QSettings::Format _format;
                QString _rootDirectory;
                QString _confSuffix;
                QSettings* _globalSettings;
                QMap<QString,int> _contextRootLoggers;
                QMap<QString,int> _contextCounter;
        };
    }
}

using namespace i2pp::core;

//create the globals during initialisation
static ContextGlobals g_globals;

Context::Context()
{
    init("global");
}

Context::Context(const QString& name)
{
    init(name);
}

Context::~Context()
{
    --(g_globals._contextCounter[_name]);
    if (g_globals._contextCounter[_name] <= 0)
        g_globals._contextCounter.remove(_name);
    delete _settings;
    _settings = NULL;
}

void Context::init(const QString& name)
{
    _name = name;
    //set context directory
    _directory = g_globals._rootDirectory + "context_" + name + QDir::separator();
    //init the loggers as early as possible, so we have it
    initLogger();

    if (g_globals._contextCounter.contains(name))
    {
        ++g_globals._contextCounter[name];
        QString strMessage=QString("Context with the name %1 is at least created twice!"
                           " This will most likely result in conflicts and undefined"
                           " behaviour!").arg(_name);
        _logger->error(strMessage);
    }
    else
        g_globals._contextCounter[name] = 1;

    QDir curDir = QDir(_directory);
    curDir.mkpath(_directory);
    QString filepath = _directory + "router." + g_globals._confSuffix;
    _settings = new QSettings(filepath, g_globals._format);
}

void Context::initLogger()
{
    ///@todo initialisation is very basic now. extend to configure with input file
    if (!g_globals._contextRootLoggers.contains(_name))
    {
        g_globals._contextRootLoggers[_name] = 1;
        //create layout
        Log4Qt::TTCCLayout* layout = new Log4Qt::TTCCLayout();
        //create file appender
        Log4Qt::FileAppender* appender = new Log4Qt::FileAppender(layout,
                                                                  _directory + "router.log",
                                                                  true);
        appender->setName("FileAppender");
        appender->activateOptions();
        //create logger
        _logger = Log4Qt::Logger::logger(_name);
        _logger->setAdditivity(false);
        //for starters, let's log at debug level
        _logger->setLevel(Log4Qt::Level(Log4Qt::Level::DEBUG_INT));
        _logger->addAppender(appender);
    }
    else
    {
        _logger = Log4Qt::Logger::logger(_name);
    }
}

QString Context::name() const
{
    return _name;
}

QString Context::directory() const
{
    return _directory;
}

QVariant Context::getSetting(const QString& key, const QVariant& defaultValue) const
{
    //make sure global settings has it
    if (!g_globals._globalSettings->contains(key))
        g_globals._globalSettings->setValue(key,defaultValue);
    //get from router, if not, get from global settings
    if (_settings->contains(key))
        return _settings->value(key, defaultValue);
    else
        return g_globals._globalSettings->value(key, defaultValue);
}

void Context::setSetting(const QString & key, const QVariant & value)
{
    _settings->setValue(key, value);
}

Log4Qt::Logger* Context::logger(QString name)
{
    //getting logger, prepending the context name
    if (name.isEmpty())
      return Log4Qt::Logger::logger(_name);
    else
      return Log4Qt::Logger::logger(QString(_name+"::"+name));
}
