#ifndef SQLEDIT_H
#define SQLEDIT_H

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>

class SQLEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    SQLEdit(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth();
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};

#endif // SQLEDIT_H
