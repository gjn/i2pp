/*
 Copyright (C) 2009  Gilbert Jeiziner
 Licensed under GNU GPL v2.
 http://www.gnu.org/licenses/gpl.html
 See LICENSE for license details.
*/
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
