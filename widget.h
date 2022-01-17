#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }

class QStandardItemModel;
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_multiplicarPushButton_clicked();
    void on_SalirPushButton_clicked();
    void on_numeroDeColumnasSpinBoxA_valueChanged(int arg1);
    void on_numeroDeFilasSpinBoxA_valueChanged(int arg1);
    void on_numeroDeFilasSpinBoxB_valueChanged(int arg1);
    void on_numeroDeColumnasSpinBoxB_valueChanged(int arg1);

private:
    double getValueAt(QStandardItemModel *model, int ix, int jx)const;
    void appendTo(QStandardItemModel *model,double value)const;

    Ui::Widget *ui;

    QStandardItemModel *mModelA;
    QStandardItemModel *mModelB;
    QStandardItemModel *mModelR;
};
#endif // WIDGET_H
