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
#include "random.h"
#include "clock.h"

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
                    _globalContext = NULL;
                }

                ~ContextGlobals()
                {
                    delete _globalSettings;
                    foreach(Context* pContext, _instances)
                    {
                        delete pContext;
                    }
                }

                QSettings::Format _format;
                QString _rootDirectory;
                QString _confSuffix;
                QSettings* _globalSettings;
                QMap<QString,Context*> _instances;
                Context* _globalContext;
        };
    }
}

using namespace i2pp::core;

//create the globals during initialisation
ContextGlobals* g_globals = NULL;

ContextProvider::ContextProvider()
{
    if (g_globals == NULL)
        g_globals = new ContextGlobals();
}

ContextProvider::~ContextProvider()
{
    if (g_globals)
        delete g_globals;
    g_globals = NULL;
}

Context* Context::globalContext()
{
    if (g_globals == NULL)
        return NULL;

    if (g_globals->_globalContext)
        return g_globals->_globalContext;
    return instance("");
}

Context* Context::instance(const QString& name)
{
    if (g_globals == NULL)
        return NULL;

    QString lname = name;
    if (lname.isEmpty())
        lname = "global";
    if (!g_globals->_instances.contains(lname))
        new Context(lname);
    return g_globals->_instances[lname];
}

Context::Context(const QString& name):
        _name(name)
        ,_directory(g_globals?g_globals->_rootDirectory + "context_" + name + QDir::separator():"")
{
    if (g_globals != NULL)
    {
        if (g_globals->_globalContext == NULL)
            g_globals->_globalContext = this;
        g_globals->_instances[name] = this;

        init();
    }
}

Context::Context(const Context& other)
{
    UNUSED_PARAMETER(other);
}

Context& Context::operator =(const Context& other)
{
    UNUSED_PARAMETER(other);
    return *this;
}

Context::~Context()
{
    delete _clock;
    _clock = NULL;

    delete _random;
    _random = NULL;

    delete _settings;
    _settings = NULL;
}

void Context::init()
{
    if (g_globals == NULL)
        return;

    //init the loggers as early as possible, so we have it
    initLogger();

    _logger->info("Starting to initialise core::Context as '%1'", _name);

    QDir curDir = QDir(_directory);
    curDir.mkpath(_directory);
    QString filepath = _directory + "router." + g_globals->_confSuffix;
    _settings = new QSettings(filepath, g_globals->_format);

    _random = new Random(this);

    _clock = new Clock(this);

    _logger->info("End of initialisation core::Context with name '%1'", _name);
}

void Context::initLogger()
{
    ///@todo initialisation is very basic now. extend to configure with input file
    //create layout
    Log4Qt::TTCCLayout* layout = new Log4Qt::TTCCLayout();
    layout->setDateFormat("ISO8601");
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
    _logger->setLevel(Log4Qt::Level(Log4Qt::Level::TRACE_INT));
    _logger->addAppender(appender);
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
    if (g_globals == NULL)
        return QVariant();

    //make sure global settings has it
    if (!g_globals->_globalSettings->contains(key))
        g_globals->_globalSettings->setValue(key,defaultValue);
    //get from router, if not, get from global settings
    if (_settings->contains(key))
        return _settings->value(key, defaultValue);
    else
        return g_globals->_globalSettings->value(key, defaultValue);
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

Random* Context::random()
{
    return _random;
}

Clock* Context::clock()
{
    return _clock;
}
