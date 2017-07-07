#include "inputrectanglesize.h"
#include "ui_inputrectanglesize.h"

InputRectangleSize::InputRectangleSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputRectangleSize)
{
    ui->setupUi(this);
}

InputRectangleSize::~InputRectangleSize()
{
    delete ui;
}

void InputRectangleSize::setMaximumSizes(int Hsize, int Wsize) //Height size and Width size
{
    ui->horizontalSlider->setMaximum(Hsize);
    ui->horizontalSlider_2->setMaximum(Wsize);
}

void InputRectangleSize::inputSize(QSize *s)
{
    this->size = s;
}

void InputRectangleSize::on_buttonBox_accepted()
{
    this->size->setHeight(ui->horizontalSlider->value());
    this->size->setWidth(ui->horizontalSlider_2->value());
}
