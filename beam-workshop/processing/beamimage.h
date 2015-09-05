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

#ifndef BEAMIMAGE_H
#define BEAMIMAGE_H

#include <image/image.h>

class BeamImage
{
public:
    BeamImage(QString imagePath);

    QString imagePath() const { return m_imagePath; }

    QString liedNr(void) const { return m_liedNr; }
    void setLiedNr (QString liedNr) {
        m_liedNr = liedNr;
    }

    Image image(void) const {return m_image;}
    void setImage (Image image) {
        m_image = image;
    }

signals:

public slots:

private:
    QString m_imagePath;
    QString m_liedNr;

    Image m_image;
};

#endif // BEAMIMAGE_H
