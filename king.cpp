/* king.cpp
 *
 * king.cpp toteuttaa otsikkotiedostossa
 * määritellyt asiat. Otsikkotiedostossa
 * kaikki tarpeellinen oli jo
 * määritelty, joten siihen ei ole
 * tehty mitään muutoksia.
 * Tämä tiedosto toteuttaa kuninkaan
 * toiminnan shakki-pelissä, sekä
 * lisää kyseisen nappulan pelilaudalle.
 *
 * Ohjelman kirjoittaja
 * Nimi: Teemu Ruonakoski
 * Opiskelijanumero: 152116224
 * Käyttäjätunnus: tcteru
 * E-Mail: teemu.ruonakoski@tuni.fi
 *
 * */

#include "king.hh"

King::King(ChessColor color) : ChessPiece(color, KING, "king"){}

set<Coord> King::get_allowed_moves(ChessBoard const& board) const
{
    set<Coord> allowed_moves;
    Coord piece_location = get_position();

    // Tarkistetaan, onko nappula laudalla:
    if (piece_location == NULL_COORD)
    {
        return allowed_moves;
    }

    // Määritellään suunnat:
    const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
    const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

    // Tarkistetaan suunnat:
    for (int dir = 0; dir < 8; ++dir)
    {
        int new_row = piece_location.row + dy[dir];
        int new_col = piece_location.col + dx[dir];

        // Tarkistetaan, onko nappula vielä laudalla:
        if (new_row < 0 || new_row >= 8 || new_col < 0 || new_col >= 8)
        {
            continue;
        }

        Coord target_coord = {new_row, new_col};
        shared_ptr<ChessPiece> target_piece
        = board.get_piece_at(target_coord);

        if (target_piece == nullptr)
        {
            // Kuningas voi liikkua tyhjään ruutuun:
            allowed_moves.insert(target_coord);
        }
        else if (target_piece->get_color() != get_color())
        {
            // Kuningas voi napata vastustajan nappulan:
            allowed_moves.insert(target_coord);
        }
    }

    return allowed_moves;
}
