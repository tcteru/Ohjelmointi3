/* mainwindow.hh
 *
 * mainwindow-luokka toteuttaa graafisen käyttöliittymän.
 * Tähän otsikkotiedostoon on lisätty tarvittavat kirjastot,
 * sekä tiedostot. Otsikkotiedostossa on lisätty funktioiden
 * kutsut, sekä alustettu kaikki muu tarpeelinen,
 * jotta lähdekooditiedostossa voidaaan täyttää,
 * jo määritellyt funktiot tekemättä lisää alustuksia.
 *
 * Ohjelman kirjoittaja
 * Nimi: Teemu Ruonakoski
 * Opiskelijanumero: 152116224
 * Käyttäjätunnus: tcteru
 * E-Mail: teemu.ruonakoski@tuni.fi
 *
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <set>
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QApplication>
#include "chess.hh"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleSquareClick(int row, int col);
    void resetGame();
    void quitGame();

private:
    Ui::MainWindow *ui;
    void setupUi();
    void updateBoard();
    void updateInfoText();
    void highlightValidMoves(const set<Coord>& validMoves);
    void clearHighlights();
    QString getPieceImagePath(shared_ptr<ChessPiece> piece, ChessColor squareColor);
    Chess game_;
    Coord selectedCoord_ = NULL_COORD;
    QWidget* centralWidget_;
    QGridLayout* mainLayout_;
    QGridLayout* boardLayout_;
    QLabel* infoLabel_;
    QPushButton* resetButton_;
    QPushButton* quitButton_;
    QVector<QVector<QPushButton*>> boardSquares_;
};

#endif // MAINWINDOW_HH
