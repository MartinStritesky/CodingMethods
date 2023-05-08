#ifndef WIDGET_H
#define WIDGET_H

#include "qgraphicsscene.h"
#include "main.h"

#include <QWidget>
#include <QtCore>
#include <QtGui>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

struct SymbolProb; // declaration of struct SymbolProp to use it in this file.

class Widget : public QWidget
{
    Q_OBJECT

public:
    //! Widget class constructor.
    Widget(QWidget *parent = nullptr);
    //!  Widget class destructor.
    ~Widget();
    //! A method used to draw binary tree inside QGraphicsScene with QGraphicsItemLines.
    void drawBinaryTree(SymbolProb alp[], int size, int scene);
    //! A method used to transfer all alphabet information to QWidget panel.
    void addAlphabet(SymbolProb alp[],SymbolProb alp2[], int size,  double entrophy, double avgWordLength, double avgWordLengthHuff, double avgInfoQty, double infoQty[]);

private:
    Ui::Widget *ui;
    QGraphicsScene * scene;  // Declaration of a Scene used to draw Shannon-Fano tree.
    QGraphicsScene * scene2;  // Declaration of a Scene used to draw Huffmann tree.
};
#endif // WIDGET_H
