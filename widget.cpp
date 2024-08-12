#include "widget.h"
#include "ui_widget.h"

#include <QKeySequence>
#include <QMessageBox>
#include <QShortcut>

#define path "E:/qtproject/"

Widget::Widget(QWidget *parent):QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->widgetBottom->setLayout(ui->horizontalLayout_2);

    QShortcut *shortcutOpen = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")),this);
    QShortcut *shortcutSave = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")),this);
    QShortcut *shortcutZoomIn = new QShortcut(QKeySequence(tr("Ctrl+Shift+=", "File|ZoomIn")),this);
    QShortcut *shortcutZoomOut = new QShortcut(QKeySequence(tr("Ctrl+Shift+-", "File|ZoomOut")),this);


    QObject::connect(shortcutOpen, &QShortcut::activated, this, [=](){
        btnOpen_clicked();
    });

    QObject::connect(shortcutSave, &QShortcut::activated, this, [=](){
        btnSave_clicked();
    });

    QObject::connect(shortcutZoomIn, &QShortcut::activated, this, [=](){
        int ZoomInRange = 1;
        ui->textEdit->zoomIn(ZoomInRange++);
    });

    QObject::connect(shortcutZoomOut, &QShortcut::activated, this, [=](){
        int ZoomOutRange = 1;
        ui->textEdit->zoomOut(ZoomOutRange++);
    });

    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comCurrentIndexChanged(int)));

    QObject::connect(ui->btnOpen, SIGNAL(clicked()), this, SLOT(btnOpen_clicked()));
    QObject::connect(ui->btnClose,SIGNAL(clicked()), this, SLOT(btnClose_clicked()));
    QObject::connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(btnSave_clicked()));

    QObject::connect(ui->textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(TextcursorPositionChanged()));
}

void Widget::btnOpen_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open file"), path, tr("Text (*.txt)"));
    ui->textEdit->clear();

    file.setFileName(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug() << " open failed" ;
    }
    this->setWindowTitle(filename);
    QTextStream in(&file);
    in.setCodec(ui->comboBox->currentText().toStdString().c_str());
    while(!in.atEnd()){
        QString context = in.readLine();
        ui->textEdit->append(context);
    }
}

void Widget::btnSave_clicked()
{
    if(!file.isOpen()){
        QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        path,
                                                        tr("Text file (*.txt)"));

        file.setFileName(filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug()<<"save failed";
        }
        this->setWindowTitle(filename);
    }
    QTextStream out(&file);
    out.setCodec(ui->comboBox->currentText().toStdString().c_str());
    QString context = ui->textEdit->toPlainText();
    out << context;
}

void Widget::btnClose_clicked()
{
    int ret = QMessageBox::warning(this,
                                   tr("notebook notice:"),
                                   tr("文档已经被修改\n"
                                      "是否保存修改?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
        case QMessageBox::Save:
            btnSave_clicked();
            break;
        case QMessageBox::Discard:
            ui->textEdit->clear();
            if(file.isOpen()){
                file.close();
                this->setWindowTitle("notebook");
            }
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
}

void Widget::comCurrentIndexChanged(int index)
{
    ui->textEdit->clear();
    if(file.isOpen()){
        QTextStream in(&file);
        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
        file.seek(0);
        while(!in.atEnd()){
            QString context = in.readLine();
            ui->textEdit->append(context);
        }
    }
}

void Widget::TextcursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QString blockNum = QString::number(cursor.blockNumber() + 1);
    QString columNum = QString::number(cursor.columnNumber() + 1);
    const QString labelText = "行" + blockNum + "," + "列" + columNum;
    ui->labelPosition->setText(labelText);

    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection ext;

    ext.cursor = cursor;

    QBrush qBrush(Qt::lightGray);
    ext.format.setBackground(qBrush);
    ext.format.setProperty(QTextFormat::FullWidthSelection,true);
    ext.format.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    //    ext.format.setFontUnderline(true);
    extraSelections.append(ext);
    ui->textEdit->setExtraSelections(extraSelections);
}

void Widget::zoomInSlot()
{
    ui->textEdit->zoomIn(1);
}

void Widget::zoomOutSlot()
{
    ui->textEdit->zoomOut(1);
}


Widget::~Widget()
{
    delete ui;
};


