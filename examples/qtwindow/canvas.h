#ifndef CANVAS_H
#define CANVAS_H

#include <memory>
#include <vector>

#include <QImage>
#include <QTimer>
#include <QWidget>

namespace Ui
{
class Canvas;
}

class DualBuffer
{
  public:
    DualBuffer(const QSize& size, QImage::Format format)
        : bufferContainer_(2)
        , currentlyAvailable_(0)
    {
        bufferContainer_[0] = QImage(size, format);
        bufferContainer_[1] = QImage(size, format);
    }

    void resize(const QSize& size, QImage::Format format)
    {
        bufferContainer_[0] = QImage(size, format);
        bufferContainer_[1] = QImage(size, format);
    }

    QImage& getForRendering()
    {
        int previouslyAvailable = currentlyAvailable_;
        currentlyAvailable_     = (currentlyAvailable_ + 1) % 2;

        return bufferContainer_[previouslyAvailable];
    }

    QImage& getForDisplaying()
    {
        return bufferContainer_[currentlyAvailable_];
    }

  private:
    std::vector<QImage> bufferContainer_;
    int currentlyAvailable_;
};

class Canvas : public QWidget
{
    Q_OBJECT

  public:
    explicit Canvas(QWidget* parent = 0);

    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);
    virtual ~Canvas();

  public slots:
    void updateLoop();

  private:
    Ui::Canvas* ui_;
    QTimer* timer_;
    DualBuffer buffer_;
    double time_;
    const QImage::Format bufferFormat_ = QImage::Format_RGB888;
};

#endif // CANVAS_H
