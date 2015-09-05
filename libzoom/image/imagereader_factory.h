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

#ifndef IMAGEREADER_FACTOTY_H
#define IMAGEREADER_FACTOTY_H

#include "imagereader.h"

class ImageReaderFactory
{
public:
    explicit ImageReaderFactory(void);
    virtual ~ImageReaderFactory (void);

    ImageReader* imageReaderFromFormat (QString format);

    QStringList supportedSuffixes (void);

private:
    QList <ImageReader*> m_imageReaders;
};

#endif // IMAGEREADER_FACTOTY_H
