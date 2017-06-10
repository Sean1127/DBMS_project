#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "sqledit.h"

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(SQLEdit *editor);

    QSize sizeHint() const override {
        return QSize(SQLEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    SQLEdit *SQLEditor;
};

#endif // LINENUMBERAREA_H
