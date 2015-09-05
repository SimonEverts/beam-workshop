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

#include "lut.h"

#include <QAtomicInt>
#include <QDebug>

Lut::Lut (void) :
    m_red (NULL),
    m_green (NULL),
    m_blue (NULL),
    m_ref (NULL)
{

}

Lut::Lut (int depth) :
    m_depth (depth)
{
    int size = 1 << depth;

    m_red = new int [size];
    m_green = new int [size];
    m_blue = new int [size];

    memset (m_red, 0, sizeof (int) * size);
    memset (m_green, 0, sizeof (int) * size);
    memset (m_blue, 0, sizeof (int) * size);

    m_ref = new QAtomicInt();
    m_ref->ref();
}

Lut::Lut (const Lut& lut)
{
    m_depth = lut.m_depth;

    m_red = lut.m_red;
    m_green = lut.m_green;
    m_blue = lut.m_blue;

    m_ref = lut.m_ref;
    m_ref->ref();
}

Lut::~Lut (void)
{
    if (!m_ref)
        return;

    if (!m_ref->deref())
    {
        if (m_red)
            delete[] m_red;
        m_red = NULL;

        if (m_green)
            delete[] m_green;
        m_green = NULL;

        if (m_blue)
            delete[] m_blue;
        m_blue = NULL;

        delete m_ref;
        m_ref = NULL;
    }
}

Lut& Lut::operator= (const Lut& lut)
{
    if (&lut != this && m_ref)
    {
        if (!m_ref->deref())
        {
            if (m_red)
                delete[] m_red;
            m_red = NULL;

            if (m_green)
                delete[] m_green;
            m_green = NULL;

            if (m_blue)
                delete[] m_blue;
            m_blue = NULL;

            delete m_ref;
            m_ref = NULL;
        }
    }

    if (lut.m_ref)
    {
        m_depth = lut.m_depth;

        m_red = lut.m_red;
        m_green = lut.m_green;
        m_blue = lut.m_blue;

        m_ref = lut.m_ref;
        m_ref->ref();
    }

    return *this;
}
