#include "widget.h"
#include "ui_widget.h"

#include "doublespinboxdelegate.h"
#include <QStandardItemModel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mModelA = new QStandardItemModel(this);
    mModelB = new QStandardItemModel(this);
    mModelR = new QStandardItemModel(this);

    ui->tableViewA->setModel(mModelA);
    ui->tableViewB->setModel(mModelB);
    ui->tableViewR->setModel(mModelR);

    ui->tableViewA->setItemDelegate(new DoubleSpinBoxDelegate(this));
    ui->tableViewB->setItemDelegate(new DoubleSpinBoxDelegate(this));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_multiplicarPushButton_clicked()
{
    mModelR->clear();
    const int rowCountA = mModelA->rowCount();
    const int rowCountB = mModelB->rowCount();
    const int colCountB = mModelB->columnCount();
    mModelR->setRowCount(rowCountA);
    mModelR->setColumnCount(colCountB);
    double suma;
    for(int ix = 0; ix<rowCountA;ix++){
        for(int jx = 0; jx<colCountB;jx++){
            suma = 0.0;
            for(int kx = 0;kx<rowCountB;kx++){
                const double aij = getValueAt(mModelA, ix, kx);
                const double bij = getValueAt(mModelB, kx, jx);
                const double ab = aij * bij;
                suma += ab;
            }
            appendTo(mModelR,suma);
        }
    }
}

void Widget::on_SalirPushButton_clicked()
{
    close();
}

void Widget::on_numeroDeColumnasSpinBoxA_valueChanged(int arg1)
{

    mModelA->setColumnCount(arg1);
    ui->numeroDeColumnasSpinBoxB->setValue(arg1);
}

void Widget::on_numeroDeFilasSpinBoxA_valueChanged(int arg1)
{
    mModelA->setRowCount(arg1);
    mModelR->setRowCount(arg1);
}

void Widget::on_numeroDeFilasSpinBoxB_valueChanged(int arg1)
{
    mModelB->setRowCount(arg1);
    ui->numeroDeColumnasSpinBoxA->setValue(arg1);
}

void Widget::on_numeroDeColumnasSpinBoxB_valueChanged(int arg1)
{
    mModelB->setColumnCount(arg1);
    mModelR->setColumnCount(arg1);
}

double Widget::getValueAt(QStandardItemModel *model, int ix, int jx) const
{
    if(!model->item(ix,jx)){
        return 0.0;
    }
    return model->item(ix,jx)->text().toDouble();
}

void Widget::appendTo(QStandardItemModel *model, double value) const
{
    const int rowCount = model->rowCount();
    const int colCount = model->columnCount();
    for(int ix=0;ix<rowCount;ix++){
        for(int jx=0;jx<colCount;jx++){
            if(model->item(ix,jx)){
                model->setItem(ix,jx,new QStandardItem(QString::number(value)));
                return;
            }
        }
    }
}
