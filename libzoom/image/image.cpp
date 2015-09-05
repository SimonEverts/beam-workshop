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

#include "image.h"

#include <cstring>

#include <QDebug>

Image::Image (void) :
    m_pixels (NULL),
    m_ref (NULL),
    m_size (0,0),
    m_channels (0),
    m_step (0),
    m_depth (0)
{
}

Image::Image(QSize size, unsigned int channels, unsigned int depth) :
    m_size (size),
    m_channels (channels),
    m_depth (depth)
{
    m_step = size.width() * channels * depth/8;

    m_pixels = new unsigned char [size_t(size.height()) * m_step];

    m_ref = new QAtomicInt();
    m_ref->ref();
}

Image::Image(QSize size, unsigned int channels, unsigned int step, unsigned int depth) :
    m_size (size),
    m_channels (channels),
    m_step (step),
    m_depth (depth)
{
    m_pixels = new unsigned char [size_t(size.height()) * step];

    m_ref = new QAtomicInt();
    m_ref->ref();
}

Image::Image(unsigned char* pixels, QSize size, unsigned int channels, unsigned int step, unsigned int depth) :
    m_pixels (pixels),
    m_ref (NULL),
    m_size (size),
    m_channels (channels),
    m_step (step),
    m_depth (depth)
{
}

Image::Image (const Image& image) :
    m_size (image.size()),
    m_channels (image.channels()),
    m_step (image.step()),
    m_depth (image.depth())
{
    m_pixels = image.pixels();
    m_ref = image.m_ref;
    if (m_ref)
        m_ref->ref();
}

Image::~Image (void)
{
    if (!m_ref)
        return;

    if (m_pixels && !m_ref->deref())
    {
        delete[] m_pixels;
        m_pixels = 0;

        delete m_ref;
    }
}

void Image::clear (void)
{
    if (m_pixels && !m_ref->deref())
    {
        delete[] m_pixels;
        delete m_ref;
    }

    m_pixels = 0;
    m_ref = 0;
}

Image& Image::operator= (const Image& image)
{
    if (&image != this)
    {
        if (m_pixels && !m_ref->deref())
        {
            delete[] m_pixels;
            delete m_ref;
        }
    }

    m_size = image.size();
    m_channels = image.channels();
    m_step = image.step();
    m_depth = image.depth();

    m_pixels = image.m_pixels;
    m_ref = image.m_ref;

    if (m_ref)
        m_ref->ref();

    return *this;
}

Image Image::copy (void)
{
    Image image (m_size, m_channels, m_step, m_depth);

    memcpy (image.pixels(), m_pixels, size_t(m_size.height()) * m_step);
    return image;
}

QImage Image::toQImage () const
{
    QImage image;

    if (m_channels == 3)
        image = QImage (m_pixels, m_size.width(), m_size.height(), m_step, QImage::Format_RGB888).copy();

    if (m_channels == 4)
        image = QImage (m_pixels, m_size.width(), m_size.height(), m_step, QImage::Format_RGB32).copy();

    return image;
}

Image Image::fromQImage (QImage image)
{
    int channels = 0;
    int depth = 0;

    switch (image.format()) {
        case QImage::Format_RGB32: {
            channels = 4;
            depth = 8;
        }; break;
        case QImage::Format_ARGB32: {
            channels = 4;
            depth = 8;
        }; break;
        case QImage::Format_RGB888: {
            channels = 3;
            depth = 8;
        }; break;
        default:
        {
            qCritical("Image format not supported!");
            return Image();
        }
    }

    if (!channels || !depth)
        return Image();

    Image result (image.size(),channels, depth);

    memcpy (result.pixels(), image.bits(), size_t(result.size().height()) * result.step());

    return result;
}

bool Image::isNull (void) const
{
    return (m_pixels == NULL) || (m_size.width() == 0) || (m_size.height() == 0);
}

