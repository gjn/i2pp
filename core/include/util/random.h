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

#ifndef I2PP_CORE_RANDOM_H
#define I2PP_CORE_RANDOM_H

#include <QByteArray>

namespace i2pp
{
namespace core
{

/*! Random class for i2pp
  Use this class when you need prng somewhere in i2pp.
  As of now, it uses the AutoSeedRandomGenerator of
  crypto++ to genererate randomized bytes...but that
  might change in the future.

  @note
  We make sure that these functions are thread-safe
*/

class Random
{
public:
    /*! betting a number of random bytes
      @param ba, this bytearray will be filled with random data.
      @return false if an error occurs during generation, bytearray remains untouched.
      @note It's adviced to check the return value
      @note Zero sized byte array will remains untouched.
    */
    static bool getBytes(QByteArray& ba);
};

}
}

#endif
