/****
    libzoom - Library for processing images
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

#ifndef IMAGEREADER_H
#define IMAGEREADER_H


#include <QStringList>

#include <QMap>
#include <QVariant>

#include "image.h"

class ImageReader
{
public:

    virtual void openImage (QString imagePath) = 0;

    virtual Image loadThumbnail (void) = 0;
    virtual Image loadPreview (void) = 0;
    virtual Image loadMaster (void) = 0;

    virtual QMap <QString, QVariant> loadInfo (void) = 0;

    virtual QStringList supportedFormats (void) = 0;
};


#endif // IMAGEREADER_H
