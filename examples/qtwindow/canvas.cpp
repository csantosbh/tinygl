#include <iostream>

#include <QResizeEvent>
#include <QPainter>

#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::Canvas),
    timer_(new QTimer()),
    buffer_(this->size(), bufferFormat_),
    time_(0.0)
{
    ui_->setupUi(this);

    // Disable automatic window clearing
    setAttribute(Qt::WA_OpaquePaintEvent, true);

    // Start update timer
    connect(timer_, SIGNAL(timeout()), this, SLOT(updateLoop()));
    timer_->start(1000.0 * 1.0 / 60.0);

    // Use QT memory management
    timer_->setParent(this);
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    buffer_.resize(event->size(), bufferFormat_);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter qpainter(this);
    qpainter.drawImage(0, 0, buffer_.getForDisplaying());
}

void Canvas::updateLoop()
{
    using namespace std;
    struct Pixel {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    QImage& buffer = buffer_.getForRendering();

    Pixel* ptr = (Pixel*)buffer.bits();
    for(int y = 0; y < buffer.size().height(); ++y) {
        for(int x = 0; x < buffer.size().width(); ++x) {
            float val = cos((float)x/(float)buffer.size().width() * 3.14159/2.0 + time_) * 255.0;
            ptr[y*buffer.size().width() + x] = {(uint8_t)val, 255, 255};
        }
    }

    update();

    time_ += 1.0 / 60.0;
}

Canvas::~Canvas()
{
    delete ui_;
}
