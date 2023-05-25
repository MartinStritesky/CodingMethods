#ifndef WIDGET_H
#define WIDGET_H

#include "qgraphicsscene.h"


#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QPushButton>


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
    void drawBinaryTree(std::string[], int size, int sc);
    //! A method used to transfer all alphabet information to QWidget panel.
    void addAlphabet(SymbolProb alp[],int size,  double *entrophy, double *avgWordLengthSF, double *avgWordLengthHuff, double *avgInfoQty);
    void getAlp(SymbolProb alp[]);


private slots:
     void on_pushButton_clicked();


 private:
    Ui::Widget *ui;
    QGraphicsScene * scene;  // Declaration of a Scene used to draw Shannon-Fano tree.
    QGraphicsScene * scene2;  // Declaration of a Scene used to draw Huffmann tree.


};
#endif // WIDGET_H
