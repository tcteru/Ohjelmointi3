/* queen
 *
 * queen-luokka toteuttaa kunigatar-
 * nappulan toiminnan. Muuten tähän
 * otsikko tiedostoon ei ole tehty
 * muutoksia, mutta yksi
 * include lisätty.
 *
 * Ohjelman kirjoittaja
 * Nimi: Teemu Ruonakoski
 * Opiskelijanumero: 152116224
 * Käyttäjätunnus: tcteru
 * E-Mail: teemu.ruonakoski@tuni.fi
 *
 * */

#ifndef QUEEN_HH
#define QUEEN_HH

#include "rook.hh" //Annettu pohjakoodissa?
#include "chesspiece.hh" //AINOA LISÄYS

/**
 * @brief The Queen class
 * The queen moves any number of squares vertically, horizontally, or diagonally
 * through unoccupied squares. The queen captures by moving to the square occupied
 * by an enemy piece.
 */
class Queen : public ChessPiece
{
public:
    Queen(ChessColor col);
    virtual ~Queen() = default;

    virtual set<Coord> get_allowed_moves(ChessBoard const& board) const override;

private:

};

#endif // QUEEN_HH
