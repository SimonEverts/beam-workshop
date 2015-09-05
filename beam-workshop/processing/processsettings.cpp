/****
    BeamWorkshop - Tool to processing images for presentations
    Copyright (C) 2015  Simon Everts

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include "processsettings.h"

ProcessSettings::ProcessSettings(void) :
    newImageSize(QSize(1280, 924)),
    whiteBackground(true),
    zoom(false),
    cropHeader(true),
    cropFooter(false),
    autoCrop(true),
    borderSize(10),
    addSongNumber(true),
    brightness(1.0),
    gamma(1)
{

}

