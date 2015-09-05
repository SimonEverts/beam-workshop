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

#include "imagereader_factory.h"

#include <QFileInfo>
#include <QDebug>

#include <QElapsedTimer>

#include "imagereader_generic.h"

#ifdef LIBRAW_ENABLED
    #include "imagereader_raw.h"
#endif

ImageReaderFactory::ImageReaderFactory(void)
{
    m_imageReaders.append( new ImageReader_generic() );

#ifdef LIBRAW_ENABLED
    m_imageReaders.append( new ImageReader_raw() );
#endif
}

ImageReaderFactory::~ImageReaderFactory ()
{
    while (m_imageReaders.size())
    {
        delete m_imageReaders.first();
        m_imageReaders.removeFirst();
    }
}


ImageReader* ImageReaderFactory::imageReaderFromFormat (QString format)
{
    ImageReader* result = NULL;

    for (int i=0; i < m_imageReaders.size(); i++)
    {
        QStringList supported_formats = m_imageReaders.at(i)->supportedFormats();
        if (supported_formats.contains( format.toLower() ))
            result = m_imageReaders.at(i);
    }

    return result;
}

QStringList ImageReaderFactory::supportedSuffixes (void)
{
    QStringList result;

    for (int i=0; i < m_imageReaders.size(); i++)
    {
        QStringList supported_formats = m_imageReaders.at(i)->supportedFormats();

        for (int j=0; j < supported_formats.size(); j++)
            result << QString("*.") + supported_formats.at(j);
    }

    return result;
}
