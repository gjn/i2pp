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

    QString name();
  private:
    void init(const QString& name);

  protected:

    QString _name; //name of the context

    QSettings* _settings; //settings used to read/write settings. It's also used to get the context path
};

}
}

#endif // I2PP_CORE_CONTEXT_H
