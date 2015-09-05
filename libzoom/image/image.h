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

#ifndef IMAGE_H
#define IMAGE_H

#include <QSize>
#include <QImage>

#include <QAtomicInt>

class Image
{
public:
    explicit Image (void);
    Image(QSize size, unsigned int channels, unsigned int depth);
    Image(QSize size, unsigned int channels, unsigned int step, unsigned int depth);
    Image(unsigned char* pixels, QSize size, unsigned int channels, unsigned int step, unsigned int depth);

    Image (const Image& image);

    virtual ~Image (void);

    Image& operator= (const Image& image);

    Image copy (void);

    QImage toQImage (void) const;
    static Image fromQImage (QImage image);

    void clear (void);
    bool isNull (void) const;

    unsigned char* pixels () const {return m_pixels;}
    QSize size () const {return m_size;}
    unsigned int channels () const {return m_channels;}
    unsigned int step () const {return m_step;}
    unsigned int depth () const {return m_depth;}

private:
    unsigned char* m_pixels;
    QAtomicInt* m_ref;

    QSize m_size;
    unsigned int m_channels;
    unsigned int m_step;
    unsigned int m_depth;
};

#endif // IMAGE_H
