#include "videowidget.h"

#include <QPaintEvent>
#include <QDebug>




VideoWidget::VideoWidget(QWidget* parent): QWidget(parent), hasImage_(false)
{
  setAutoFillBackground(false);
  setAttribute(Qt::WA_NoSystemBackground, true);
  setAttribute(Qt::WA_PaintOnScreen, true);

  QPalette palette = this->palette();
  palette.setColor(QPalette::Background, Qt::black);
  setPalette(palette);

  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}
VideoWidget::~VideoWidget()
{}


void VideoWidget::inputImage(std::unique_ptr<uchar[]> input,
                             QImage &image)
{
  Q_ASSERT(input);
  drawMutex_.lock();
  input_ = std::move(input);
  currentImage_ = image;
  drawMutex_.unlock();

  hasImage_ = true;
  update();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  qDebug() << "Painting image";

  if(!hasImage_)
    qWarning() << "no Image received";

  if(hasImage_)
  {
    drawMutex_.lock();
    Q_ASSERT(input_);
    currentImage_.save("testikuva.jpg");
    painter.drawImage(currentImage_.rect(), currentImage_);
    drawMutex_.unlock();
  }
  else
    painter.fillRect(event->rect(), QBrush(QColor(100,100,0)));
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
  QWidget::resizeEvent(event);
  QSize size = currentImage_.size();
  size.scale(QWidget::size().boundedTo(size), Qt::KeepAspectRatio);

  targetRect_ = QRect(QPoint(0, 0), size);
  targetRect_.moveCenter(rect().center());
}