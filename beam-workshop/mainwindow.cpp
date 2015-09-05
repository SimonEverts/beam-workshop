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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QList>
#include <QMessageBox>

#include <QMimeData>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_currentImage("")
{
    ui->setupUi(this);
    ui->mainToolBar->setVisible(false);

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage (QString imagePath)
{
    try
    {
        m_currentImage = m_imageManager.loadImage( imagePath );
        updateCurrentImage();

        ui->statusBar->showMessage(QString("Afbeelding geopend: ") + imagePath, 0);
    }
    catch( const std::exception& e)
    {
        ui->statusBar->showMessage(QString("Fout met openen afbeelding: ") + e.what(), 0);
    }
}

void MainWindow::displayImage(Image image)
{
    ui->imageView->setZoom (true, 1);
    ui->imageView->setImage (image.toQImage() );
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Selecteer afbeelding");

    loadImage( file_path );
}

void MainWindow::on_saveButton_clicked()
{
    QFileInfo image_file_info (m_currentImage.imagePath());

    QDir base_dir = image_file_info.absoluteDir();
    QString base_path = base_dir.absolutePath() + "/export/";
    base_dir.mkpath(base_path);

    QString new_file_path = base_path + "/"  + image_file_info.baseName() + ".jpg";

    int number = 1;
    while (QFileInfo(new_file_path).exists())
    {
        new_file_path = base_path + "/" + image_file_info.baseName() + "_" + QString::number(number) + ".jpg";
        number++;
    }

    Image new_image = m_imageManager.processImage(m_currentImage);
    QImage qt_image = new_image.toQImage();

    qt_image.save(new_file_path, "JPG");

    ui->statusBar->showMessage(QString("Afbeelding opgeslagen als: ") + new_file_path, 0);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
     if (event->mimeData()->hasUrls())
         event->acceptProposedAction();
}

void MainWindow::dropEvent ( QDropEvent * event )
{
    if (event->mimeData()->hasUrls())
    {
        QList< QUrl > url_list = event->mimeData()->urls();

//        if (ui->autoExportCheckBox->checked())
//        {
//            for (auto i= url_list.begin(); i != url_list.end(); i++)
//            {
//                loadImage( i->toLocalFile() );

//                qDebug() << url_list.begin()->toLocalFile();
//            }
//        }
//        else
//        {
            if (url_list.size())
            {
                loadImage( url_list.begin()->toLocalFile() );
                qDebug() << url_list.begin()->toLocalFile();
            }
//        }

         event->acceptProposedAction();
    }
}

void MainWindow::on_actionOpslaan_als_triggered()
{
    QFileInfo image_file_info (m_currentImage.imagePath());
    QDir base_dir = image_file_info.absoluteDir();

    QString file_path = QFileDialog::getSaveFileName(this, "Afbeeldig opslaan", base_dir.absolutePath());

    Image new_image = m_imageManager.processImage(m_currentImage);
    QImage qt_image = new_image.toQImage();

    qt_image.save(file_path);

    ui->statusBar->showMessage(QString("Afbeelding opgeslagen als: ") + file_path, 0);
}

void MainWindow::updateCurrentImage()
{
    Image new_image = m_imageManager.processImage(m_currentImage);
    displayImage (new_image);
}

void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    ui->brightnessSpinBox->setValue (float(value) / 100);

    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.brightness = float(value) / 100;
    m_imageManager.setProcessSettings(processSettings);

    updateCurrentImage();
}

void MainWindow::on_borderDistanceSpinBox_valueChanged(int arg1)
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.borderSize = arg1;
    m_imageManager.setProcessSettings(processSettings);

    updateCurrentImage();
}

void MainWindow::on_whiteBackgroundcheckBox_clicked()
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.whiteBackground = ui->whiteBackgroundcheckBox->isChecked();
    m_imageManager.setProcessSettings(processSettings);

    updateCurrentImage();
}

void MainWindow::on_zoomCheckBox_clicked()
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.zoom = ui->zoomCheckBox->isChecked();
    m_imageManager.setProcessSettings(processSettings);

    updateCurrentImage();
}

void MainWindow::on_autoCropCheckBox_clicked()
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.autoCrop = ui->autoCropCheckBox->isChecked();
    m_imageManager.setProcessSettings(processSettings);

    updateCurrentImage();
}

void MainWindow::on_cropHeaderCheckBox_clicked()
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.cropHeader = ui->cropHeaderCheckBox->isChecked();
    m_imageManager.setProcessSettings(processSettings);

    updateCurrentImage();
}

void MainWindow::on_cropFooterCheckBox_clicked()
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.cropFooter = ui->cropFooterCheckBox->isChecked();
    m_imageManager.setProcessSettings(processSettings);

    updateCurrentImage();
}

void MainWindow::on_addSongNrCheckBox_clicked()
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.addSongNumber = ui->addSongNrCheckBox->isChecked();
    m_imageManager.setProcessSettings(processSettings);

    updateCurrentImage();
}


void MainWindow::on_gammaSlider_valueChanged(int value)
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.gamma = float(value) / 100;
    m_imageManager.setProcessSettings(processSettings);

    ui->gammaSpinBox->setValue( processSettings.gamma );

    updateCurrentImage();
}

void MainWindow::on_gammaSpinBox_valueChanged(double arg1)
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.gamma = arg1;
    m_imageManager.setProcessSettings(processSettings);

    ui->gammaSlider->setValue( arg1 * 100);

    updateCurrentImage();
}

void MainWindow::on_brightnessSpinBox_valueChanged(double arg1)
{
    ProcessSettings processSettings = m_imageManager.processSettings();
    processSettings.brightness = arg1;
    m_imageManager.setProcessSettings(processSettings);

    ui->brightnessSlider->setValue( arg1 * 100);

    updateCurrentImage();
}

void MainWindow::processDir( QString path, QString relativePath, QStringList& imageFiles, QStringList& imageFilesTargetPath )
{
    QDir dir (path);

    QFileInfoList file_list = dir.entryInfoList(QStringList() << "*.png" << "*.bmp" << "*.jpg" << "*.gif");

    for (int i=0; i<file_list.size(); i++)
    {
        QFileInfo file_info = file_list.at(i);

        if (!file_info.exists())
            continue;

        if (!file_info.isFile())
            continue;

        imageFiles.push_back( file_info.absoluteFilePath() );

        imageFilesTargetPath.push_back( relativePath );
    }

    QFileInfoList dir_list = dir.entryInfoList( QStringList(), QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    for (int i=0; i<dir_list.size(); i++)
    {
        QFileInfo dir_info = dir_list.at(i);

        if (!dir_info.exists())
            continue;

        if (!dir_info.isDir())
            continue;

        processDir (dir_info.absoluteFilePath(), relativePath + "/" + dir_info.fileName(), imageFiles, imageFilesTargetPath);
    }
}

void MainWindow::on_openDirButton_clicked()
{
    m_imageFiles.clear();
    m_imageTargetPath.clear();

    QString dir_path = QFileDialog::getExistingDirectory(this, "Selecteer een directory met liederen", QDir::homePath());

    if (dir_path.isEmpty())
    {
        QMessageBox::critical( this, "Selecteer een directory met liederen!", "Selecteer een directory met liederen!");
        return;
    }

    QDir dir (dir_path);
    if (!dir.exists())
    {
        QMessageBox::critical( this, "Directory bestaat niet!", "Directory bestaat niet!");
        return;
    }


    m_sourcePath = dir.absolutePath();
    m_targetPath = m_sourcePath + "_converted" + "/";

    processDir (dir.absolutePath(), "./", m_imageFiles, m_imageTargetPath);

    ui->imagesFoundLabel->setText("Liederen gevonden: " + QString::number(m_imageFiles.count()));

    ui->songSlider->setMaximum(m_imageFiles.count());
    ui->songSlider->setEnabled( m_imageFiles.count() );

    if (m_imageFiles.count())
        loadImage(m_imageFiles.first());
}

void MainWindow::on_songSlider_valueChanged(int value)
{
    if (value < m_imageFiles.count())
        loadImage(m_imageFiles.at(value));
}

void MainWindow::on_songButton_clicked(bool checked)
{
    if (checked)
    {
        ui->stackedWidget->setCurrentWidget(ui->songPage);
    }
}

void MainWindow::on_manualButton_clicked(bool checked)
{
    if (checked)
    {
        ui->stackedWidget->setCurrentWidget(ui->manualPage);
    }
}

void MainWindow::on_convertAllButton_clicked()
{
    for (int i=0; i<m_imageFiles.size(); i++)
    {
        QApplication::processEvents();
        if (!isVisible())
            continue;

        QFileInfo file_info (m_imageFiles.at(i));

        if (!file_info.exists())
            continue;

        QString liedNr = m_imageManager.songNrFromFilename( file_info.baseName() );

        QDir dir;
        dir.mkpath( m_targetPath + "/" + m_imageTargetPath.at(i));

        qDebug() << file_info.absoluteFilePath();

        BeamImage beamImage = m_imageManager.loadImage( file_info.absoluteFilePath() );
        Image new_image = m_imageManager.processImage(beamImage);

        QImage qt_image = new_image.toQImage();

        qt_image.save( m_targetPath + "/" + m_imageTargetPath.at(i) + "/" + file_info.baseName() + ".jpg" );

        ui->statusBar->showMessage(file_info.baseName() + " is geconverteerd.", 0);

        displayImage(new_image);
    }

    QMessageBox messageBox (QMessageBox::Information, "Liederen geconverteerd",
                            "Liederen geconverteerd naar directory: " + m_targetPath);
    messageBox.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    m_aboutDialog.show();
}
