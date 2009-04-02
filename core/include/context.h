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

#ifndef I2PP_CORE_CONTEXT_H
#define I2PP_CORE_CONTEXT_H

#include "log4qt/logger.h"

#include <QReadWriteLock>

class QSettings;

namespace i2pp
{
namespace core
{

/*! Context
  A context is a single-point of access to comonly used
  components of i2pp. These components include
  - settings
  - logging
  - cryptography
  - ...
  A context is bound to a working directory, where the context's
  settings, keys, identities, netdb and more is stored. The location
  of the working directory is chosen by the context itself, with
  the help of the QSettings class. On linux, the working directory
  is placed under the $HOME/.config/i2pp/context_name directory. On
  windows, the directory is %APPDATA%/i2pp/context_name. Also, the
  settings will be read from this directory.

  The name of the context is chosen automatically upon creation with
  the default constructor (and the name is, very originally, 'global'),
  or you can specify a name.

  @note
  Each context name is unique.

  @note
  As the context is THE central part of i2pp, it's important
  that a context instance is created as early as possible
  in an application, and deleted at the very end. Creation is _NOT_
  done during static initialisation.

  It's possible to have more than one context in one process/application.
  This is especially helpful, but not limited, for developement and debugging,
  to have several routers up and running, talking to each other
*/
class Context {
    public:
        ///provided for conveniencce; gets first created context or creates one
        static Context* globalContext();
        ///get a named instance, created of not already existing
        static Context* instance(const QString& name);

        virtual ~Context();
        ///name of the context
        QString name() const;
        ///directory location of the context
        QString directory() const;

        /*! settings
          settings of the context, see QSettings configuration on how to
          get and set settings.
          Please note that the location of the file is fixed after construction.
          The format on Linux system is *.conf, on windows *.ini. To configure
          the context, make sure that the appropriate file is installed/located
          in the context directory.
        */
        QVariant getSetting(const QString& key,
                            const QVariant& defaultValue = QVariant()) const;
        void setSetting(const QString & key, const QVariant & value);

        /*! logger
          Get the context logger. To any logger name given, the context name
          will be appended, so loggers are unique to their context. The looger(s)
          are configured with a configuration file inside the context's directory.
          For this, the PropertyConfigurator of log4qt is extended so that in the
          configuration file, the context name does not have to be included.
          Also, make sure to always get the logger from the context, and NOT to
          use Log4Qt::Logger::logger(...).
          @code
          context.logger("my.logger.here")
          LOG4QT_DEBUG(logger, "The number is: " << i);
          @endcode
        */
        Log4Qt::Logger* logger(QString name);

    private:
        Context(const QString& name);
        Context(const Context& other); //disable copy constructor
        Context&  operator = (const Context& other); //disable assignement operator

        void init();
        void initLogger();

    protected:
        const QString _name; //name of the context
        const QString _directory; //directory of the context (contains trailing separator)

        QSettings* _settings; //router settings

        Log4Qt::Logger* _logger; //this contexts logger
};

}
}

#endif // I2PP_CORE_CONTEXT_H
