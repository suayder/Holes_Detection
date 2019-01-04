#ifndef INPUTRECTANGLESIZE_H
#define INPUTRECTANGLESIZE_H

#include <QDialog>

namespace Ui {
class InputRectangleSize;
}

class InputRectangleSize : public QDialog
{
    Q_OBJECT

public:
    explicit InputRectangleSize(QWidget *parent = 0);
    ~InputRectangleSize();
    void setMaximumSizes(int, int);
    void inputSize(QSize*);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::InputRectangleSize *ui;
    QSize *size;
};

#endif // INPUTRECTANGLESIZE_H
