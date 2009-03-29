/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#include "pc.h"
#include "context.h"

#include <QSettings>
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/fileappender.h"
#include "log4cxx/patternlayout.h"

using namespace i2pp::core;

Context::Context()
{
  init("default");
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
  _directory = fi.absoluteDir().absolutePath() + QDir::separator() + fi.baseName () + QDir::separator();
  //make sure that the directory exists
  QDir(_directory).mkpath(_directory);
  QString filepath = _directory + "router." + fi.completeSuffix();
  _settings = new QSettings(filepath, format);

  //loggin initialisation
  initLogger();
}

void Context::initLogger()
{
  //todo: adapte to be configurable through property file!
  static bool bBasicConfigured = false;
  static QMap<QString,QString> contextRootLoggers;
  if (!bBasicConfigured)
  {
    log4cxx::BasicConfigurator::configure(); //make sure log4cxx root logger has some basic initialisation
    bBasicConfigured = true;
  }

  if (!contextRootLoggers.contains(_name))
  {
    //now configure the context specific root logger
    log4cxx::LoggerPtr logger=log4cxx::Logger::getLogger(QString(_name).toStdString());
    //we don't want to rely on the root logger for appenders/levels!
    logger->setAdditivity(false);
    //for starters, let's to debug level logging
    logger->setLevel(log4cxx::Level::DEBUG);
    //create layout
    //log4cxx::PatternLayoutPtr layout(new log4cxx::PatternLayout("%-4r [%t] %-5p %c %x - %m%n"));
    log4cxx::PatternLayoutPtr layout(new log4cxx::PatternLayout("%d [%t] %-5p %c %x - %m%n"));
    //create fileappender. filename should be static (or member variable), as when it's not, this created exception...
    contextRootLoggers[_name] = _directory + "router.log";
    log4cxx::FileAppenderPtr appender(new log4cxx::FileAppender(layout,contextRootLoggers[_name].toStdString(),true));
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

QSettings* Context::settings()
{
  return _settings;
}

log4cxx::LoggerPtr Context::logger(QString name)
{
  //getting logger, prepending the context name
  if (name.isEmpty())
    return log4cxx::Logger::getLogger(QString(_name).toStdString());
  else
    return log4cxx::Logger::getLogger(QString(_name+"."+name).toStdString());
}
