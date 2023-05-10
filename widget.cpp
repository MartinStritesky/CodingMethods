#include "widget.h"
#include "ui_widget.h"
#include "main.h"

#include <iostream>
#include <QGraphicsRectItem>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);  // setting the UI in QWidget constructor

    scene = new QGraphicsScene(this); // initialization of new Scene
    scene2 = new QGraphicsScene(this); // initialization of another Scene
    ui->graphicsView->setScene(scene);  // assigning the scene into graphicsView
    ui->graphicsView_2->setScene(scene2);  // assigning the scene2 into graphicsView2
    ui->graphicsView->setRenderHints(QPainter::Antialiasing); // turning antialiasing On
    ui->graphicsView_2->setRenderHints(QPainter::Antialiasing); // turning antialiasing On
}

Widget::~Widget()
{
    delete ui;
}

/*!
 * \brief Widget::addAlphabet  A method used to transfer all alphabet information to QWidget panel.
 * \param alpShFan  Array of struct representing alphabet for Shannon Fano method.
 * \param alpHuff  Array of struct representing alphabet for Huffman's method.
 * \param size
 * \param entrophy Entrophy of information given by chosen alphabet
 * \param avgWordLength  Average code word length for code generated by Shannon Fano´s method.
 * \param avgWordLengthHuff Average code word length for code generated by Huffman´s method.
 * \param avgInfoQty  Average information quantity given by chosen alphabet
 * \param infoQty Information quantity given by each symbol.
 */
void Widget::addAlphabet(SymbolProb alp[],int size, double *entrophy, double *avgWordLengthSF, double *avgWordLengthHuff, double *avgInfoQty){
    for(int i = 0; i < size; i++) {
        // Filling the QTableWidget with data
        ui->tableWidget->setItem(i,1, new QTableWidgetItem(QString::number(alp[i].prob, 'f', 2)));
        ui->tableWidget->setItem(i,3, new QTableWidgetItem(QString::fromStdString(alp[i].codeSF)));
        ui->tableWidget->setItem(i,4, new QTableWidgetItem(QString::fromStdString(alp[i].codeHuff)));
        ui->tableWidget->setItem(i,2, new QTableWidgetItem(QString::number(alp[i].infoQty, 'f', 2)));
        ui->tableWidget->setItem(i,5, new QTableWidgetItem(QString::fromStdString(alp[i].codeSecured)));
        // Filling labels with data
        ui->lblCodeEff->setText(QString::number((100 *  *entrophy / *avgWordLengthSF), 'f', 2));
        ui->lblCodeEffHuff->setText(QString::number((100 * *entrophy / *avgWordLengthHuff), 'f', 2));
        ui->lblWordLength->setText(QString::number(*(avgWordLengthSF), 'f', 2));
        ui->lblWordLengthHuff->setText(QString::number(*(avgWordLengthHuff), 'f', 2));
        ui->lblQtyInf->setText(QString::number(*avgInfoQty,'f',2));

        // Filling both QGraphicsScene with binary trees
        std::string wordSF[10];
        wordSF[i] = alp[i].codeSF;

        std::string wordHuff[10];
        wordHuff[i] = alp[i].codeHuff;

        drawBinaryTree(wordSF, 10,1);
        drawBinaryTree(wordHuff, 10,2);
    }
}

/*!
 * \brief Widget::drawBinaryTree A method used to draw binary tree inside QGraphicsScene with QGraphicsItemLines.
 * \param alp    SymbolProb struct object containing symbols, probabilities and code words.
 * \param size
 * \param sc  Selector between scenes, "1" for scene and "2" for scene2.
 */
void Widget::drawBinaryTree(std::string word[], int size, int sc){

    QVector<QGraphicsLineItem*> lines; // Initiating QVector of LineItems.

    int x0 = 0; // Starting x position, coordinate of first point for the line
    int y0 = 0; // Starting y position, coordinate of first point for the line
    int x1 = 0; // Starting x position, coordinate of second point for the line
    int y1 = 0; // Starting y position, coordinate of second point for the line
    int gap = 30; // Gap between levels
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(Qt::darkGreen));  // setting Qpen for drawing lines


    for(int i=0; i<size; i++) {

        int k = 1;   // counter for progressively shortening gap values when levels go higher in the tree
        // Traverse the code word and draw lines accordingly
        for(int j=0; j< word[i].length(); j++) {
            if(word[i][j]  == '0') {
                x1 = x0 - 6*gap/k;  // setting the second line point (x goes to left)
                y1 = y0 - 1.4*gap;
                if(j == word[i].length()-1){  // if this is the last line to draw, shorten it further to accommodate the displayed code label
                    x1 += 15;
                    y1 += 10;
                    QGraphicsTextItem* text = new QGraphicsTextItem(QString::fromStdString("(" +word[i]+ ")"));
                    text->setPos(x1-5-10*j,y1-25);
                    if (sc == 1)scene->addItem(text);
                    else if (sc == 2)scene2->addItem(text);
                }

            } else {
                x1 = x0 + 6*gap/k;   // setting the second line point (x goes to right)
                y1 = y0 - 1.4*gap;
                if(j == word[i].length()-1){ // if this is the last line to draw, shorten it further to accommodate the displayed code label
                    x1 -= 15;
                    y1 += 10;
                    QGraphicsTextItem* text = new QGraphicsTextItem(QString::fromStdString("(" + word[i] + ")"));  // when on the last level for this branch, add text with code word
                    text->setPos(x1-30+3*j,y1-25);
                    if (sc == 1)scene->addItem(text);
                    else if (sc == 2)scene2->addItem(text);  // selector between scenes (ShannonFano vs Huffman)
                }
            }

            QGraphicsLineItem* Line = (new QGraphicsLineItem(x0, y0, x1, y1));  // creating new line with current coordinates
            Line->setPen(pen);
            lines.push_back(Line);  // adding it to the QVector
            x0 = x1;    // setting coordinates for next iteration (next place in code word)
            y0 = y1;
            k++;  // the higher level, the bigger divider value for x coordinate gap
        }

        x0 = 0;  // resetting the coordinate between code words
        y0 = 0;
    }
    // Add all the line items to the scene
    for(int i=0; i<lines.size(); i++) {
        if (sc == 1) scene->addItem(lines[i]);
        else if (sc == 2) scene2->addItem(lines[i]); // selector between scenes (ShannonFano vs Huffman)
    }

}

//void Widget::on_pushButton_clicked()
//{
//    Widget w;
//    double newProb[10];
//    for (int i = 0; i < 10; i++){
//        newProb[i] = ui->tableWidget->item(i, 1)->text().toDouble();
//    }
//    ui->label->setText("BLA");
//    changeProb(newProb, &w);

//    update();
//    repaint();
//}




