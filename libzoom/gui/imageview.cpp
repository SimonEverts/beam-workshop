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

#include "imageview.h"

#include <QPainter>
#include <QPaintEngine>

#include <QMouseEvent>

#include <QDebug>

ImageView::ImageView(QWidget *parent) :
    QWidget(parent),
    m_zoomFit (false),
    m_zoomFactor (1)
{
    setMouseTracking(true);
}

ImageView::~ImageView (void)
{

}


void ImageView::setImage (QImage image)
{
    m_orig_image = image;

    resizeImage ();

    update();
}

void ImageView::setZoom (bool zoomFit, double factor)
{
    m_zoomFit = zoomFit;
    m_zoomFactor = factor;

    resizeImage();

    update();
}

void ImageView::paintEvent(QPaintEvent *event)
{
    draw ();
}

void ImageView::resizeEvent(QResizeEvent *)
{
    resizeImage();

    update();
}

void ImageView::draw (void)
{
    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_Source);

    QBrush brush (Qt::SolidPattern);
    brush.setColor (Qt::darkGray);

    painter.fillRect(rect(), brush);

    QRect source_rect (m_imageOffset + m_pressOffset, rect().size());

    painter.drawImage (rect(), m_scaled_image, source_rect);
}

void ImageView::resizeImage(void)
{
    QSize orig_image_size = m_orig_image.size();

    double hscale = double(rect().width()) / orig_image_size.width();
    double vscale = double(rect().height()) / orig_image_size.height();

    if (m_zoomFit)
        m_zoomFactor = (hscale < vscale) ? hscale : vscale;

    QSize scaled_image_size;
    scaled_image_size.setWidth( static_cast <int> (m_zoomFactor * orig_image_size.width() ));
    scaled_image_size.setHeight( static_cast <int> (m_zoomFactor * orig_image_size.height() ));

    // TODO Fast on preview
    m_scaled_image = m_orig_image.scaled (scaled_image_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}



void ImageView::mouseMoveEvent ( QMouseEvent * event )
{
    if (event->buttons())
        m_pressOffset = m_pressPos - event->pos();

    // TODO
    if (m_imageOffset.x() + m_pressOffset.x() < 0)
        m_pressOffset.setX( - m_imageOffset.x() );


    update();
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    m_pressPos = event->pos();
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    m_imageOffset += m_pressOffset;
    m_pressOffset.setX(0);
    m_pressOffset.setY(0);
}
