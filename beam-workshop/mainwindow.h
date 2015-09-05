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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "image/image.h"
#include "processing/imagemanager.h"

#include "aboutdialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void loadImage (QString imagePath);

private slots:
    void displayImage (Image image);

    void on_actionOpen_triggered();

    void on_brightnessSlider_valueChanged(int value);

    void on_borderDistanceSpinBox_valueChanged(int arg1);

    void on_whiteBackgroundcheckBox_clicked();

    void on_zoomCheckBox_clicked();

    void on_autoCropCheckBox_clicked();

    void on_cropHeaderCheckBox_clicked();

    void on_cropFooterCheckBox_clicked();

    void on_addSongNrCheckBox_clicked();

    void on_saveButton_clicked();

    void on_actionOpslaan_als_triggered();

    void on_gammaSlider_valueChanged(int value);

    void on_gammaSpinBox_valueChanged(double arg1);

    void on_brightnessSpinBox_valueChanged(double arg1);

    void on_openDirButton_clicked();

    void on_songSlider_valueChanged(int value);

    void on_songButton_clicked(bool checked);

    void on_manualButton_clicked(bool checked);

    void on_convertAllButton_clicked();

    void on_actionAbout_triggered();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent ( QDropEvent * event );

private:
    void updateCurrentImage();
    void processDir( QString path, QString relativePath, QStringList& imageFiles, QStringList& imageFilesTargetPath );

    Ui::MainWindow *ui;

    AboutDialog m_aboutDialog;

    ImageManager m_imageManager;

    QStringList m_imageFiles;
    QStringList m_imageTargetPath;

    QString m_sourcePath;
    QString m_targetPath;

    BeamImage m_currentImage;
};

#endif // MAINWINDOW_H
