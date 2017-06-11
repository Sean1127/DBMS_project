#include "linenumberarea.h"

LineNumberArea::LineNumberArea(SQLEdit *editor) : QWidget(editor)
{
    SQLEditor = editor;
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    SQLEditor->lineNumberAreaPaintEvent(event);
}
