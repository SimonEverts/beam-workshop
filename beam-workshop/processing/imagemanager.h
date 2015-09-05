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

#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QString>
#include <image/image.h>
#include "beamimage.h"

#include "processsettings.h"

class ImageManager
{
public:
    ImageManager();

    BeamImage loadImage (QString imagePath) const;

    Image processImage(const BeamImage& beamImage );

    QImage createNewCanvas(QSize size, bool white);
    Image preprocessOriginalImage(Image srcImage, bool cropHeader, bool cropFooter, bool autoCrop);
    QSize calculateTargetFrameSize(QSize canvasSize, int borderSize, int liedNrSize);
    QSize calculateScaledImageSize(QSize sourceImageSize, QSize targetFrameSize, bool zoom);

    ProcessSettings processSettings() {
        return m_processSettings;
    }

    void setProcessSettings(ProcessSettings processSettings) {
        m_processSettings = processSettings;
    }

    QString songNrFromFilename (QString path) const;

public slots:

signals:

private:
    ProcessSettings m_processSettings;
};

#endif // IMAGEMANAGER_H
