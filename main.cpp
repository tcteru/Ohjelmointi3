/* Shakki
 *
 * Kuvaus:
 * Ohjelma toteuttaa Shakki-pelin.
 * Shakissa pelaajat tekevät vuorotellen siirtoja
 * oman värisillä pelinappuloillaan,
 * tavoitteena hyökätä toisen pelaajan kuninkaan kimppuun
 * ja suojella omaa kuningastaan.
 * Pohjakoodissa toteutettu shakki on yksinkertaistus
 * shakin virallisista säännöistä.
 * Suurimpana erona pohjakoodin shakissa on voittoehto.
 * Normaalisti kuningas tulee saada shakkimattiin eli tilanteeseen,
 * jossa se ei voi enää liikkua mihinkään tulematta syödyksi.
 * Pohjakoodin shakissa pelin voittaa yksinkertaisesti
 * syömällä toisen pelaajan kuninkaan.
 * Tässä versiossa ei myöskään ole tasapelejä.
 * Ohjelmassa on pohjakoodin kommentteja, jotka on kirjoitettu
 * englanniksi. Nämä on säilytetty ennallaan tiedostoissa,
 * joita ei ole muokattu.
 * Omat kommentit on kirjoitettu suomeksi.
 *
 * Ohjelman kirjoittaja
 * Nimi: Teemu Ruonakoski
 * Opiskelijanumero: 152116224
 * Käyttäjätunnus: tcteru
 * E-Mail: teemu.ruonakoski@tuni.fi
 * Palautteen kieli: fi
 *
 * */

/* Tiedoston alkukommentti
 *
 * Tämän tiedoston ainoat muutokset pohjakoodiin,
 * ovat nämä kommentit.
 *
 * */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
