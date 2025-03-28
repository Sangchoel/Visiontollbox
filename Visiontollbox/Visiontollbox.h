#pragma once

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class Visiontollbox; }
QT_END_NAMESPACE

class Visiontollbox : public QMainWindow
{
    Q_OBJECT

public:
    explicit Visiontollbox(QWidget* parent = nullptr);
    ~Visiontollbox();

private slots:
    void onLoadImage();
    void onSaveImage();
    void onSwitchToEditor();
    void onBackToViewer();
    void onGrayscaleClicked();
    void orinImage();

private:
    Ui::Visiontollbox* ui;

    cv::Mat currentImage;
    cv::Mat originalImage;

    void updateViewerImage();
    void updateEditorImage();
    QImage cvMatToQImage(const cv::Mat& mat);
    void log(const QString& text);
};
