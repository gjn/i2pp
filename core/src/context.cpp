#include "pc.h"
#include "context.h"

using namespace i2pp::core;

Context::Context()
{
  _name = "default";
}

Context::Context(const QString& name)
{
  _name = name;
}
