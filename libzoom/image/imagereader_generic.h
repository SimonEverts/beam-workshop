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

#ifndef IMAGELOADER_GENERIC_H
#define IMAGELOADER_GENERIC_H

#include "imagereader.h"

class ImageReader_generic_p;

class ImageReader_generic : public ImageReader
{
public:
    explicit ImageReader_generic (QObject *parent = 0);
    virtual ~ImageReader_generic (void);

    void openImage (QString imagePath);

    Image loadThumbnail (void);
    Image loadPreview (void);
    Image loadMaster (void);

    QMap <QString, QVariant> loadInfo (void);

    QStringList supportedFormats (void);

private:
    ImageReader_generic_p* p;
};

#endif // IMAGELOADER_GENERIC_H
