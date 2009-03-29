/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#include "pc.h"
#include "context.h"

#include <QSettings>

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

QString Context::name()
{
  return _name;
}

void Context::init(const QString& name)
{
  _name = name;
  QSettings::Format format = QSettings::NativeFormat;
#ifdef WIN32 //on windows, we don't want to store into registry...
  format = QSettings::IniFormat;
#endif
  QSettings localSettings(format, QSettings::UserScope,"i2pp","context_"+name);
  QFileInfo fi(localSettings.fileName());
  QString filepath = fi.absoluteDir().absolutePath() + QDir::separator() + fi.baseName () + QDir::separator() + "router." + fi.completeSuffix();
  _settings = new QSettings(filepath, format);
}
