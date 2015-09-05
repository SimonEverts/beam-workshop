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

#ifndef PROCESSSETTINGS_H
#define PROCESSSETTINGS_H

#include <QSize>

class ProcessSettings
{
public:
    ProcessSettings(void);

    QSize newImageSize;
    bool whiteBackground;
    bool zoom;
    bool cropHeader;
    bool cropFooter;
    bool autoCrop;
    int borderSize;
    bool addSongNumber;
    float brightness;
    float gamma;
};


#endif // PROCESSSETTINGS_H
