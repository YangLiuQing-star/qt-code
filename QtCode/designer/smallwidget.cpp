#include "smallwidget.h"

#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>

SmallWidget::SmallWidget(QWidget *parent) : QWidget(parent)
{
    QSpinBox *spin = new QSpinBox(this);
    QSlider *slider = new QSlider(Qt::Horizontal,this);

    //把控件添加到布局中
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(spin);
    layout->addWidget(slider);

    //使用函数指针指定信号函数
    connect(spin,static_cast<void (QSpinBox::*)(int)> (&QSpinBox::valueChanged),slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,spin,&QSpinBox::setValue);
}
