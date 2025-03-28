#include "Visiontollbox.h"
#include "ui_Visiontollbox.h"

Visiontollbox::Visiontollbox(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Visiontollbox)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);
    log("Initialized Visiontollbox");

    connect(ui->btnLoad, &QPushButton::clicked, this, &Visiontollbox::onLoadImage);
    connect(ui->btnSave, &QPushButton::clicked, this, &Visiontollbox::onSaveImage);
    connect(ui->btnEdit, &QPushButton::clicked, this, &Visiontollbox::onSwitchToEditor);
    connect(ui->btnBack, &QPushButton::clicked, this, &Visiontollbox::onBackToViewer);
    connect(ui->btnGrayscale, &QPushButton::clicked, this, &Visiontollbox::onGrayscaleClicked);
    connect(ui->btnOriginal, &QPushButton::clicked, this, &Visiontollbox::orinImage);
}

Visiontollbox::~Visiontollbox()
{
    delete ui;
}

void Visiontollbox::onLoadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        currentImage = cv::imread(fileName.toStdString());
        if (currentImage.empty()) {
            log("Failed to load image");
            QMessageBox::warning(this, "Error", "Could not load image.");
            return;
        }
        originalImage = currentImage.clone();
        updateViewerImage();
        log("Image loaded: " + fileName);
    }
}

void Visiontollbox::onSaveImage()
{
    if (currentImage.empty()) {
        log("No image to save.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPG (*.jpg)");
    if (!fileName.isEmpty()) {
        cv::imwrite(fileName.toStdString(), currentImage);
        log("Image saved: " + fileName);
    }
}

void Visiontollbox::onSwitchToEditor()
{
    ui->stackedWidget->setCurrentWidget(ui->editorPage);
    updateEditorImage();
    log("Switched to editor page");
}

void Visiontollbox::onBackToViewer()
{
    ui->stackedWidget->setCurrentWidget(ui->viewerPage);
    updateViewerImage();
    log("Returned to viewer page");
}

void Visiontollbox::updateViewerImage()
{
    if (currentImage.empty()) return;

    QImage qimg = cvMatToQImage(currentImage);
    ui->imgLabel->setPixmap(QPixmap::fromImage(qimg).scaled(
        ui->imgLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Visiontollbox::updateEditorImage()
{
    if (currentImage.empty()) return;

    QImage qimg = cvMatToQImage(currentImage);
    ui->imgEditLabel->setPixmap(QPixmap::fromImage(qimg).scaled(
        ui->imgEditLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QImage Visiontollbox::cvMatToQImage(const cv::Mat& mat)
{
    if (mat.type() == CV_8UC3)
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_BGR888).copy();
    else if (mat.type() == CV_8UC1)
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8).copy();
    return QImage();
}

void Visiontollbox::log(const QString& text)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->textEdit->append(QString("[%1] %2").arg(timestamp, text));
}

void Visiontollbox::onGrayscaleClicked()
{
    if (currentImage.empty()) return;

    cv::Mat gray;
    cv::cvtColor(currentImage, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray, currentImage, cv::COLOR_GRAY2BGR);
    updateEditorImage();
    log("Grayscale filter applied");
}

void Visiontollbox::orinImage()
{
    if (originalImage.empty()) {
        log("No original image to restore.");
        return;
    }

    currentImage = originalImage.clone();  // 원본으로 복원
    updateEditorImage();                   // 에디터 화면 갱신
    log("Image restored to original.");
}

