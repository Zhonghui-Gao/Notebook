#ifndef NBTEXTEDIT_H
#define NBTEXTEDIT_H

#include <QTextEdit>

class NBTextEdit : public QTextEdit
{
public:
    NBTextEdit(QWidget *parent);
protected:
    void wheelEvent(QWheelEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

private:
    bool ctrlKeyPressed = 0;
};

#endif // NBTEXTEDIT_H
