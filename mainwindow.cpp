/* mainwindow.cpp
 *
 * mainwindow:n lähdekooditiedosto
 * toteuttaa otsikkotiedostossa määritellyt
 * asiat. Tässä on toteutettu graafisenkäyttöliittymän
 * rakenne, sekä kaikkien siirtojen näkyminen.
 * Tiedossa toteutetaan pelilaudan päivittyminen,
 * mahdollisten siirtojen näkyminen,
 * ruudun klikkaaminen,
 * infotekstin näkyminen,
 * sekä pelin resetoiminen ja lopettaminen.
 *
 * Ohjelman kirjoittaja
 * Nimi: Teemu Ruonakoski
 * Opiskelijanumero: 152116224
 * Käyttäjätunnus: tcteru
 * E-Mail: teemu.ruonakoski@tuni.fi
 *
 * */

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      game_(),
      selectedCoord_(NULL_COORD)
{
    setupUi();
    game_.start_game();
    updateBoard();
    updateInfoText();
}

MainWindow::~MainWindow()
{
    // Laudan tyhjennys:
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            delete boardSquares_[row][col];
        }
    }
}

// Funktio graafisen käyttöliittymän luomiselle.
void MainWindow::setupUi()
{
    // Ikkunan ominaisuuksien asettaminen:
    setWindowTitle("Chess Game");
    resize(600, 650);

    // Luo keskeinen widget ja pääasettelu:
    centralWidget_ = new QWidget(this);
    setCentralWidget(centralWidget_);
    mainLayout_ = new QGridLayout(centralWidget_);

    // Luodaan painikkeet:
    resetButton_ = new QPushButton("Reset", this);
    quitButton_ = new QPushButton("Quit", this);

    // Yhdistetään painettavat nappulat:
    connect(resetButton_, &QPushButton::clicked, this, &MainWindow::resetGame);
    connect(quitButton_, &QPushButton::clicked, this, &MainWindow::quitGame);

    // Luo yläasettelu painikkeille ja infotekstille:
    QHBoxLayout* topLayout = new QHBoxLayout();

    // Lisätään painikkeen ja infoteksti yläasetteluun:
    topLayout->addWidget(resetButton_);

    // Luodaan infoteksti:
    infoLabel_ = new QLabel("White's turn", this);
    QFont font = infoLabel_->font();
    font.setPointSize(14);
    infoLabel_->setFont(font);
    infoLabel_->setAlignment(Qt::AlignCenter);
    topLayout->addWidget(infoLabel_);

    topLayout->addWidget(quitButton_);

    // Lisätään yläasettelu pääasetteluun:
    mainLayout_->addLayout(topLayout, 0, 0, 1, 3);

    // Luodaan shakkilaudan asettelu:
    boardLayout_ = new QGridLayout();
    boardLayout_->setSpacing(0);
    mainLayout_->addLayout(boardLayout_, 1, 0, 1, 3);

    // Luodaan laudan ruudut:
    boardSquares_.resize(8);
    for (int row = 0; row < 8; ++row)
    {
        boardSquares_[row].resize(8);
        for (int col = 0; col < 8; ++col)
        {
            QPushButton* square = new QPushButton();
            square->setFixedSize(64, 64);
            square->setIconSize(QSize(60, 60));

            // Yhdistetään painike, painikkeen käsittelijään:
            connect(square, &QPushButton::clicked, [this, row, col]()
            {
                handleSquareClick(row, col);
            });

            boardSquares_[row][col] = square;
            boardLayout_->addWidget(square, row, col);
        }
    }

    // Lisätään pelilaudan venytys ikkunaan:
    mainLayout_->setRowStretch(1, 10);
}

// Funktio pelilaudan päivittämiselle.
void MainWindow::updateBoard()
{
    // Päivitetään ruudut:
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Coord coord = {row, col};
            shared_ptr<ChessPiece> piece
            = game_.get_board().get_piece_at(coord);

            // Määritellään ruudun väri:
            ChessColor squareColor = ((row + col) % 2 == 0) ? BLACK : WHITE;

            // Asetetaan taustaväri:
            QString bgColor = squareColor == WHITE ? "#FFFFFF" : "#000000";
            boardSquares_[row][col]
            ->setStyleSheet(QString("background-color: %1;").arg(bgColor));

            // Haetaan nappulan reitti:
            QString imagePath = getPieceImagePath(piece, squareColor);

            // Ladataan kuva:
            QPixmap pixmap;
            pixmap.load(imagePath);

            // Lisätään painike:
            boardSquares_[row][col]->setIcon(QIcon(pixmap));
        }
    }
}

// Ruutujen tarkistaminen.
QString MainWindow::getPieceImagePath(shared_ptr<ChessPiece> piece,
                                      ChessColor squareColor)
{
    if (piece == nullptr)
    {
        // Tyhjä ruutu:
        return QString(":pieces/empty-%1.png").arg(squareColor
                                                   == WHITE ? "wt" : "bl");
    }
    else
    {
        // Ruutu, jossa on nappula:
        QString pieceColor = piece->get_color() == WHITE ? "wt" : "bl";
        QString pieceName = QString::fromStdString(piece->get_name());
        QString sqColor = squareColor == WHITE ? "wt" : "bl";

        QString path = QString(":pieces/%1-%2-on-%3.png").arg(pieceColor,
                                                              pieceName,
                                                              sqColor);

        return path;
    }
}

// Funktio ruutujen klikkaukselle.
void MainWindow::handleSquareClick(int row, int col)
{

    // Tarkistetaan, onko peli päättynyt:
    if (game_.get_game_state() != IN_PROGRESS)
    {
        return;
    }

    Coord clickedCoord = {row, col};

    // Jos nappulaa ei ole valittu:
    if (selectedCoord_ == NULL_COORD)
    {
        shared_ptr<ChessPiece> piece
        = game_.get_board().get_piece_at(clickedCoord);

        // Tarkistetaan, kumman vuoro on, ja onko nappulaa painettu:
        if (piece != nullptr && piece->get_color()
            == game_.get_current_turn())
        {
            selectedCoord_ = clickedCoord;

            // Korostetaan sallitut liikkeet:
            set<Coord> validMoves
            = piece->get_allowed_moves(game_.get_board());
            highlightValidMoves(validMoves);
        }
    }
    // Jos nappula on jo valittu:
    else
    {
        shared_ptr<ChessPiece> selectedPiece
        = game_.get_board().get_piece_at(selectedCoord_);

        // Tarkisteaan saadaanko liikkua valittuun ruutuun:
        set<Coord> validMoves
        = selectedPiece->get_allowed_moves(game_.get_board());

        if (validMoves.find(clickedCoord) != validMoves.end())
        {
            // Tehdään siirto:
            game_.make_move(selectedPiece, clickedCoord);

            // Päivitetään lauta:
            updateBoard();
            updateInfoText();
        }

        // Tyhjennetään valintojen korostukset:
        selectedCoord_ = NULL_COORD;
        clearHighlights();
    }
}

// Funktio korostuksille.
void MainWindow::highlightValidMoves(const set<Coord>& validMoves)
{
    // Korostetaan valittu nappula:
    ChessColor selectedSquareColor
    = ((selectedCoord_.row + selectedCoord_.col) % 2 == 0) ? BLACK : WHITE;
    QString bgColor = selectedSquareColor == WHITE ? "#FFFFFF" : "#000000";
    boardSquares_[selectedCoord_.row][selectedCoord_.col]->setStyleSheet(
    QString("background-color: %1; border: 3px solid red;").arg(bgColor)
    );

    // Korostetaan sallitut siirrot:
    for (const Coord& coord : validMoves)
    {
        ChessColor squareColor
        = ((coord.row + coord.col) % 2 == 0) ? BLACK : WHITE;
        QString bgColor = squareColor == WHITE ? "#FFFFFF" : "#000000";
        boardSquares_[coord.row][coord.col]->setStyleSheet(
        QString("background-color: %1; border: 3px solid red;").arg(bgColor)
        );
    }
}

// Funktio korostusten tyhjentämiselle.
void MainWindow::clearHighlights()
{
    // Tyhjennetään korostukset:
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessColor squareColor = ((row + col) % 2 == 0) ? BLACK : WHITE;
            QString bgColor = squareColor == WHITE ? "#FFFFFF" : "#000000";
            boardSquares_[row][col]->setStyleSheet(
                QString("background-color: %1;").arg(bgColor)
            );
        }
    }
}

// Funktio infotekstille.
void MainWindow::updateInfoText()
{
    // Päivitetään infoteksti:
    switch (game_.get_game_state())
    {
        case IN_PROGRESS:
            infoLabel_->setText(
                game_.get_current_turn()
                == WHITE ? "White's turn" : "Black's turn"
            );
            break;
        case WHITE_WIN:
            infoLabel_->setText("White won!");
            break;
        case BLACK_WIN:
            infoLabel_->setText("Black won!");
            break;
    }
}

// Funktio peli resetoimiselle.
void MainWindow::resetGame()
{
    // Luodaan uusi peli:
    game_ = Chess();
    game_.start_game();
    selectedCoord_ = NULL_COORD;

    // Päivitetään UI:
    updateBoard();
    updateInfoText();
}

// Funktio pelin lopettamiselle.
void MainWindow::quitGame()
{
    // Lopetetaan peli:
    QApplication::quit();
}
