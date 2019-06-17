#ifndef DIALOGTOPUP10_H
#define DIALOGTOPUP10_H

#include <QDialog>

namespace Ui {
class Dialogtopup10;
}

class Dialogtopup10 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogtopup10(QWidget *parent = nullptr);
    ~Dialogtopup10();

private:
    Ui::Dialogtopup10 *ui;
};

#endif // DIALOGTOPUP10_H
