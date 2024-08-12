#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <iostream>
#include <qdebug.h>

#include <QFile>
#include <QFileDialog>
#include <QTextCodec>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QFile file;
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void zoomInSlot();
    void zoomOutSlot();
//signals:
//    void mysignals();

private slots:
    void btnOpen_clicked();
    void btnClose_clicked();
    void btnSave_clicked();
    void comCurrentIndexChanged(int index);
    void TextcursorPositionChanged();
//    void myslots();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
