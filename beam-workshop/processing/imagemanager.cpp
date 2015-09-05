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

#include "imagemanager.h"

#include "image/imagereader_factory.h"
#include "image/imageprocessing.h"

#include <QFileInfo>

#include <QPainter>


ImageManager::ImageManager()
{
}

BeamImage ImageManager::loadImage (QString imagePath) const
{
    ImageReaderFactory image_reader_factory;

    QFileInfo image_file_info (imagePath);

    if (!image_file_info.exists())
        throw std::exception("File not found!");

    BeamImage beamImage (imagePath);

    QString liedNr = songNrFromFilename( imagePath );
    if (liedNr != "")
        beamImage.setLiedNr(liedNr);

    ImageReader* image_reader = image_reader_factory.imageReaderFromFormat(image_file_info.suffix());

    if (!image_reader)
        throw std::exception("Onbekend bestand type!");

    image_reader->openImage( imagePath );

    Image origImage = image_reader->loadMaster().copy();
    beamImage.setImage( origImage );

    return beamImage;
}

Image ImageManager::processImage (const BeamImage& beamImage)
{
    const Image& srcImage = beamImage.image();

    Image process_src_image = preprocessOriginalImage(srcImage,
                                                      m_processSettings.cropHeader,
                                                      m_processSettings.cropFooter,
                                                      m_processSettings.autoCrop);

    QImage canvas = createNewCanvas (m_processSettings.newImageSize,
                                     m_processSettings.whiteBackground);

    int liedNrSize = 0;
    if (m_processSettings.addSongNumber)
        liedNrSize = 60;

    QSize target_frame_size = calculateTargetFrameSize( canvas.size(),
                                                        m_processSettings.borderSize,
                                                        liedNrSize );

    QSize scaled_image_size = calculateScaledImageSize( process_src_image.size(),
                                                        target_frame_size,
                                                        m_processSettings.zoom);


    QImage scaled_image = process_src_image.toQImage().scaled (scaled_image_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    int x_offset = m_processSettings.borderSize;
    int y_offset = m_processSettings.borderSize + liedNrSize;

    QPoint offset ( x_offset + (target_frame_size.width() - scaled_image.size().width()) /2,
                   y_offset + (target_frame_size.height() - scaled_image.size().height()) /2);

    QPainter painter (&canvas);

    QFont font ("Arial");
    font.setPixelSize(40);
    painter.setFont(font);

    if (m_processSettings.addSongNumber)
        painter.drawText (QRect(10, 10, scaled_image.width(), 40), Qt::AlignHCenter, beamImage.liedNr());

    painter.drawImage(offset, scaled_image);

    Lut lut(8);
    ImageProcessing::generateLut(0,
                                 m_processSettings.brightness,
                                 m_processSettings.gamma, 1.0, 1.0, 1.0, lut);

    Image copy_image (canvas.size(), 4, 8);
    Image my_canvas = Image::fromQImage(canvas);
    ImageProcessing::applyLut(&my_canvas, &copy_image, lut);

    return copy_image;
}

QImage ImageManager::createNewCanvas(QSize size, bool white)
{
    QImage canvas (size, QImage::Format_RGB32);

    QPainter painter (&canvas);

    if (white)
        painter.fillRect( canvas.rect(), QColor ("white"));
    else
        painter.fillRect( canvas.rect(), QColor ("black"));

    return canvas;
}

Image ImageManager::preprocessOriginalImage(Image srcImage, bool cropHeader, bool cropFooter, bool autoCrop)
{
    Image* process_src_image = &srcImage;

    Image cropped_image;

    if (cropHeader)
    {
        cropped_image = ImageProcessing::cropHeader_8u(process_src_image, 50);
        process_src_image = &cropped_image;
    }

    if (cropFooter)
    {
        cropped_image = ImageProcessing::cropFooter_8u(process_src_image, 25);
        process_src_image = &cropped_image;
    }

    // Auto crop
    if (autoCrop)
    {
        cropped_image = ImageProcessing::autoCrop_8u(process_src_image);
        process_src_image = &cropped_image;
    }

    return process_src_image->copy();
}

QSize ImageManager::calculateTargetFrameSize(QSize canvasSize, int borderSize, int liedNrSize)
{
    // There is less height if we need to add the song-nr
    QSize image_region_size (canvasSize.width() - (2*borderSize),
                             canvasSize.height() - (2*borderSize) - liedNrSize);

    return image_region_size;
}

QSize ImageManager::calculateScaledImageSize( QSize sourceImageSize, QSize targetFrameSize, bool zoom)
{
    // scale / zoom
    double hscale = double(targetFrameSize.width()) / sourceImageSize.width();
    double vscale = double(targetFrameSize.height()) / sourceImageSize.height();

    double zoom_factor = 1;
    if (zoom)
        zoom_factor = (hscale > vscale) ? hscale : vscale;
    else
        zoom_factor = (hscale < vscale) ? hscale : vscale;      

    QSize scaled_image_size;
    scaled_image_size.setWidth( static_cast <int> (zoom_factor * sourceImageSize.width() ));
    scaled_image_size.setHeight( static_cast <int> (zoom_factor * sourceImageSize.height() ));

    return scaled_image_size;
}

QString ImageManager::songNrFromFilename (QString path) const
{
    QString result;

    QFileInfo imageFile (path);

    QStringList segmentedFileName = imageFile.baseName().split('-', QString::SkipEmptyParts );
    if (segmentedFileName.size() > 5 && segmentedFileName.at(3) == "couplet")
        result = "Lied " + segmentedFileName.at(1) + " : " + segmentedFileName.at(4);

    if (segmentedFileName.size() > 3 && segmentedFileName.at(3) != "couplet" )
        result = "Lied " + segmentedFileName.at(1) + " : " + segmentedFileName.at(3);

    return result;
}
