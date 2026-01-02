/* queen.cpp
 *
 * queen lähdekooditiedosto toteuttaa
 * otsikkotiedostossa määritellyt asiat.
 * Tämä tiedosto toteuttaa kuningatar-nappulan
 * toiminnan shakki-pelissä, sekä lisää
 * kyseisen nappulan pelilaudalle.
 *
 * Ohjelman kirjoittaja
 * Nimi: Teemu Ruonakoski
 * Opiskelijanumero: 152116224
 * Käyttäjätunnus: tcteru
 * E-Mail: teemu.ruonakoski@tuni.fi
 *
 * */

#include "queen.hh"

Queen::Queen(ChessColor color) : ChessPiece(color, QUEEN, "queen"){}

set<Coord> Queen::get_allowed_moves(ChessBoard const& board) const
{
    set<Coord> allowed_moves;
    Coord piece_location = get_position();

    // Tarkistetaan, onko nappula laudalla:
    if (piece_location == NULL_COORD)
    {
        return allowed_moves;
    }

    // Määritellään suunnat:
    const int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
    const int dy[] = {-1, 0, 1, 0, -1, 1, 1, -1};

    // Tarkistetaan suunnat:
    for (int dir = 0; dir < 8; ++dir)
    {
        // Liikutaan määriteltyyn suuntaan,
        // kunnes jokin este tulee vastaan:
        for (int step = 1; step < 8; ++step)
        {
            int new_row = piece_location.row + dy[dir] * step;
            int new_col = piece_location.col + dx[dir] * step;

            // Tarkisteaan, onko nappula vielä laudalla:
            if (new_row < 0 || new_row >= 8 || new_col < 0 || new_col >= 8)
            {
                break;
            }

            Coord target_coord = {new_row, new_col};
            shared_ptr<ChessPiece> target_piece
            = board.get_piece_at(target_coord);

            if (target_piece == nullptr)
            {
                // Kuningatar voi liikkua tyhjään ruutuun:
                allowed_moves.insert(target_coord);
            }
            else if (target_piece->get_color() != get_color())
            {
                // Kuningatar voi napata vastustajan nappulan:
                allowed_moves.insert(target_coord);
                break;
            }
            else
            {
                // Oma nappula tulee vastaan:
                break;
            }
        }
    }

    return allowed_moves;
}
