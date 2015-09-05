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

#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>

class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = 0);
    virtual ~ImageView (void);

    void setImage (QImage image);

    void setZoom (bool zoomFit, double factor);

    QImage scaledImage (void) {return m_scaled_image;}

protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);

    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:

public slots:


private:
    void draw (void);
    void resizeImage (void);

    QImage m_orig_image;
    QImage m_scaled_image;

    bool m_zoomFit;
    double m_zoomFactor;

    QPoint m_pressPos;
    QPoint m_pressOffset;

    QPoint m_imageOffset;
};

#endif // IMAGEVIEW_H
