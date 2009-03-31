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

using namespace i2pp::core;

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
    delete _settings;
    _settings = NULL;
}

void Context::init(const QString& name)
{
    _name = name;
    QSettings::Format format = QSettings::NativeFormat;
#ifdef WIN32 //on windows, native is in registry...we don't want that
    format = QSettings::IniFormat;
#endif
    QSettings localSettings(format, QSettings::UserScope,"i2pp","context_"+name);
    QFileInfo fi(localSettings.fileName());
    _directory = fi.absoluteDir().absolutePath() + QDir::separator() +
                 fi.baseName () + QDir::separator();
    //make sure that the directory exists
    QDir curDir = QDir(_directory);
    curDir.mkpath(_directory);
    curDir.cdUp();
    QString filepath = _directory + "router." + fi.completeSuffix();
    _settings = new QSettings(filepath, format);

    _globalSettings = new QSettings(curDir.absolutePath() + QDir::separator() +
                                    "router." + fi.completeSuffix(), format);
    //loggin initialisation
    initLogger();
}

void Context::initLogger()
{
    ///@todo initialisation is very basic now. extend to configure with input file
    static QMap<QString,QString> contextRootLoggers;
    if (!contextRootLoggers.contains(_name))
    {
        contextRootLoggers[_name] = _directory + "router.log";
        //create layout
        Log4Qt::TTCCLayout* layout = new Log4Qt::TTCCLayout();
        //create file appender
        Log4Qt::FileAppender* appender = new Log4Qt::FileAppender(layout,
                                                                  contextRootLoggers[_name],
                                                                  true);
        appender->activateOptions();
        //create logger
        Log4Qt::Logger* logger = Log4Qt::Logger::logger(_name);
        logger->setAdditivity(false);
        //for starters, let's debug level logging
        logger->setLevel(Log4Qt::Level(Log4Qt::Level::DEBUG_INT));
        logger->addAppender(appender);
    }
}

QString Context::name()
{
    return _name;
}

QString Context::directory()
{
    return _directory;
}

QVariant Context::getSetting(const QString& key,
                             const QVariant& defaultValue) const
{
    //make sure global settings has it
    if (!_globalSettings->contains(key))
        _globalSettings->setValue(key,defaultValue);
    //get from router, if not, get from global settings
    if (_settings->contains(key))
        return _settings->value(key, defaultValue);
    else
        return _globalSettings->value(key, defaultValue);
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
