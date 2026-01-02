/* bishop.cpp
 *
 * bishop.cpp, toteuttaa otsikkotiedostossa
 * määritellyt asiat. Otsikkotiedostoon ei ole
 * tehty muutoksia, sillä siinä kaikki tarpeellinen
 * oli jo määritelty. Tässä tiedossa on lisätty
 * lähetin toiminta shakki-peliin, sekä
 * lisätty kyseinen nappula pelilaudalle.
 *
 * Ohjelman kirjoittaja
 * Nimi: Teemu Ruonakoski
 * Opiskelijanumero: 152116224
 * Käyttäjätunnus: tcteru
 * E-Mail: teemu.ruonakoski@tuni.fi
 *
 * */

#include "bishop.hh"

Bishop::Bishop(ChessColor color) : ChessPiece(color, BISHOP, "bishop"){}

set<Coord> Bishop::get_allowed_moves(ChessBoard const& board) const
{
    set<Coord> allowed_moves;
    Coord piece_location = get_position();

    // Tarkistetaan, onko nappula laudalla:
    if (piece_location == NULL_COORD)
    {
        return allowed_moves;
    }

    // Määritellään suunnnat:
    const int dx[] = {1, 1, -1, -1};
    const int dy[] = {-1, 1, 1, -1};

    // Tarkistetaan suunnat:
    for (int dir = 0; dir < 4; ++dir)
    {
        // Liikutaan määriteltyyn suuntaan,
        // kunnes jokin este tulee vastaan:
        for (int step = 1; step < 8; ++step)
        {
            int new_row = piece_location.row + dy[dir] * step;
            int new_col = piece_location.col + dx[dir] * step;

            // Tarkistetaan, onko nappula vielä laudalla:
            if (new_row < 0 || new_row >= 8 || new_col < 0 || new_col >= 8)
            {
                break;
            }

            Coord target_coord = {new_row, new_col};
            shared_ptr<ChessPiece> target_piece
            = board.get_piece_at(target_coord);

            if (target_piece == nullptr)
            {
                // Lähetti voi liikkua tyhjään ruutuun:
                allowed_moves.insert(target_coord);
            }
            else if (target_piece->get_color() != get_color())
            {
                // Lähetti voi napata vastustajan nappulan:
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
