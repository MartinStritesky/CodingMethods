# Coding Methods
Encoding 10 symbol alphabet into binary code with Shannon-Fano´s and Huffman´s algorithms

This application is written in C++ and uses QT framework. 
- QWidget is used to display the app window. 
- QTableWidget contains all data related to 10 symbols
- two instances of QGraphicsScene show binary trees resultign rom Shannon-Fano´s and Huffman´s method of encoding

Initialization of programme is done by setting up 10 symbols and their probability. Sum of probabilities has to be equal to 1.0. Start of encoding is gone by button "Generuj".

Verification of algorithms is made by inspecting binaty trees that should be without unassigned branches and by comparing the code efficiency value which should be always equal of higher for Huffman´s method. 

![Screenshot from 2023-05-08 21-01-26](https://user-images.githubusercontent.com/113254850/236909748-cf75a88b-fa83-4892-818f-0f79705ab666.png)
