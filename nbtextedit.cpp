#include "nbtextedit.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QWheelEvent>

NBTextEdit::NBTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

void NBTextEdit::wheelEvent(QWheelEvent *e)
{
    if(ctrlKeyPressed == 1){
        if(e->angleDelta().y() > 0){
            zoomIn();
        }else if (e->angleDelta().y() < 0) {
            zoomOut();
        }
        e->accept();
    }else{
        QTextEdit::wheelEvent(e);
    }
}

void NBTextEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control){
        ctrlKeyPressed = 1;
    }
    QTextEdit::keyPressEvent(e);
}

void NBTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control){
        ctrlKeyPressed = 0;
    }
    QTextEdit::keyReleaseEvent(e);
}



