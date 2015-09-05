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

#include "imagereader_generic.h"

#include <QImage>
#include <QImageReader>

#include <QElapsedTimer>
#include <QDebug>

class ImageReader_generic_p
{
public:
    ImageReader_generic_p() {
        m_random = qrand();
    }

    void openImage (QString imagePath);

    Image loadThumbnail (void);
    Image loadPreview (void);
    Image loadMaster (void);
private:
    QImageReader m_imageReader;

    int m_random;
};


void ImageReader_generic_p::openImage (QString imagePath)
{
    m_imageReader.setFileName( imagePath );
}

Image ImageReader_generic_p::loadThumbnail ()
{
    if (!m_imageReader.canRead())
        return Image();

    m_imageReader.setQuality(25);

    QSize image_size = m_imageReader.size();

    int scale = 1;
    while ((image_size.width() >> scale) > 480)
        scale++;

    QSize scaled_size( image_size.width() / scale,
                       image_size.height() / scale);

    m_imageReader.setScaledSize ( scaled_size);

    QImage image = m_imageReader.read();

    return Image::fromQImage( image );
}

Image ImageReader_generic_p::loadPreview ()
{
    if (!m_imageReader.canRead())
        return Image();

    m_imageReader.setQuality(100);

    QSize image_size = m_imageReader.size();

    m_imageReader.setScaledSize ( image_size);

    QImage image = m_imageReader.read();

    return Image::fromQImage( image );
}

Image ImageReader_generic_p::loadMaster ()
{
    return loadPreview();
}

ImageReader_generic::ImageReader_generic (QObject *parent)
{
    p = new ImageReader_generic_p();
}

ImageReader_generic::~ImageReader_generic()
{
    delete p;
}

void ImageReader_generic::openImage (QString imagePath)
{
    p->openImage(imagePath);
}

Image ImageReader_generic::loadThumbnail()
{
    return p->loadThumbnail();
}

Image ImageReader_generic::loadPreview()
{
    return p->loadPreview();
}

Image ImageReader_generic::loadMaster()
{
    return p->loadMaster();
}

QMap <QString, QVariant> ImageReader_generic::loadInfo (void)
{
    return QMap <QString, QVariant> ();
}

QStringList ImageReader_generic::supportedFormats (void)
{
    QStringList filter;

    QList <QByteArray> supported_formats = QImageReader::supportedImageFormats();

    for (int i=0; i<supported_formats.size(); i++)
        filter << supported_formats.at(i);

    return filter;
}
