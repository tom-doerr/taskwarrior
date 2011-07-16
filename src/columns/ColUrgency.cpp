////////////////////////////////////////////////////////////////////////////////
// taskwarrior - a command line task list manager.
//
// Copyright 2006 - 2011, Paul Beckingham, Federico Hernandez.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the
//
//     Free Software Foundation, Inc.,
//     51 Franklin Street, Fifth Floor,
//     Boston, MA
//     02110-1301
//     USA
//
////////////////////////////////////////////////////////////////////////////////

#define L10N                                           // Localization complete.

#include <Context.h>
#include <ColUrgency.h>
#include <text.h>
#include <i18n.h>

extern Context context;

////////////////////////////////////////////////////////////////////////////////
ColumnUrgency::ColumnUrgency ()
{
  _name  = "urgency";
  _type  = "number";
  _style = "real";
  _label = STRING_COLUMN_LABEL_URGENCY;

  _styles.push_back ("real");
  _styles.push_back ("integer");

  _examples.push_back ("4.6");
  _examples.push_back ("4");
}

////////////////////////////////////////////////////////////////////////////////
ColumnUrgency::~ColumnUrgency ()
{
}

////////////////////////////////////////////////////////////////////////////////
// Set the minimum and maximum widths for the value.
void ColumnUrgency::measure (Task& task, int& minimum, int& maximum)
{
  if (_style == "default" ||
      _style == "real")
  {
    minimum = maximum = format (task.urgency (), 4, 3).length ();
  }
  else if (_style == "integer")
  {
    minimum = maximum = format ((int)task.urgency ()).length ();
  }

  else
    throw format (STRING_COLUMN_BAD_FORMAT, _name, _style);
}

////////////////////////////////////////////////////////////////////////////////
void ColumnUrgency::render (
  std::vector <std::string>& lines,
  Task& task,
  int width,
  Color& color)
{
  if (_style == "default" ||
      _style == "real")
  {
    lines.push_back (
      color.colorize (
        rightJustify (
          format (task.urgency (), 4, 3), width)));
  }
  else if (_style == "integer")
  {
    lines.push_back (
      color.colorize (
        rightJustify (
          format ((int)task.urgency ()), width)));
  }
}

////////////////////////////////////////////////////////////////////////////////
