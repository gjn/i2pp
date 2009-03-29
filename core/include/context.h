/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
#ifndef I2PP_CORE_CONTEXT_H
#define I2PP_CORE_CONTEXT_H

/*
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
  the default constructor (and the name is, very originally, 'default').
  There is a constructor to specify a desired name for the context.

  As the context is THE central part of i2pp, it's important
  that a context instance is created as early as possible
  in an application, and deleted at the very end.

  It's possible to have more than one context in one process/application.
  This is especially helpful for developement and debugging, to have
  several routers up and running, talking to each other; but is not
  limited to this usage.
  To avoid mixing different contexts interfering with each other, it's
  important to name every context differently.
*/

class QSettings;

#include "log4cxx/logger.h"

namespace i2pp {
  namespace core {

class Context {
  public:
    // creates a context with name 'default'
    Context();
    // creates a context with the given name
    Context(const QString& name);
    //the destructor
    virtual ~Context();
    //name of the context
    QString name();
    //directory location of the context (where to store context specific things)
    QString directory();

    /*
      configuration of the context, see QSettings configuration on how to get and
      set settings.
      Please note that the location of the file is fixed after construction. The
      format on Linux system is *.conf, on windows *.ini. To configure the context,
      make sure that the appropriate file is installed/located in the context directory.
      (see above for the directory of the context)
     */
    QSettings* settings();

    /*
      Get the context logger. To any logger name given, the context name will be appended,
      so loggers are unique to their context. The looger(s) are configured with a
      configuration file inside the context's directory. For this, the PropertyConfigurator of log4cxx
      is extended so that in the configuration file, the context name does not have to
      be included.
      Also, make sure to always get the logger from the context, and NOT to use
      log4cxx::Logger::getLogger(...). Once you have the logger, use the log4cxx MACRO's to
      log whatever you want (see log4cxx documentation on the macros)
      context.logger("my.logger.here")
      LOG4CXX_DEBUG(logger, "The number is: " << i);
    */
    log4cxx::LoggerPtr logger(QString name);

  private:
    void init(const QString& name);
    void initLogger();

  protected:

    QString _name; //name of the context
    QString _directory; //directory of the context (contains trailing separator)

    QSettings* _settings; //settings used to read/write settings. It's also used to get the context path
};

}
}

#endif // I2PP_CORE_CONTEXT_H
