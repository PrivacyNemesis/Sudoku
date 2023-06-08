#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int Grille(int tab[9][9], int position) {
  int i, x, y, chiffreValide;
  int Chiffre[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Un tableau avec les chiffres possibles

  if (position == 81) // Grille remplie completement
    return 1;

  x = position / 9;
  y = position % 9;

  for (i = 0; i < 9; i++) {
    Chiffre[tab[i][x]] = 0; // suppression des chiffres de la meme colonne
    Chiffre[tab[y][i]] = 0; // suppression des chiffres de la meme ligne
    Chiffre[tab[(y / 3) * 3 + (i / 3)][(x / 3) * 3 + (i % 3)]] = 0; // suppression des chiffres de les carrés
  }

  // On compte le nombre de résultats restants
  chiffreValide = 0;
  for (i = 1; i <= 9; i++)
    if (Chiffre[i])
      chiffreValide++;

  while (chiffreValide) {

    i = 1 + (rand() % 9); // rand pour des chiffres aleatoire

    if (Chiffre[i] != 0) { // ...parmis les chiffres valides restant
      tab[y][x] = i;

      if (Grille(tab, position + 1)) // Solution valide
        return 1;

      Chiffre[i] = 0;
      chiffreValide--;
      tab[y][x] = 0; // On reinitialise la valeur
    }
  }
  return 0; // Chiffre non valide
}

void nettoyage_Grille(int tab[9][9]) {

  for (int y = 0; y < 9; y++)
    for (int x = 0; x < 9; x++)
      tab[y][x] = 0;
}

void affichage_Grille(int tab[9][9]) { // Printf de la grille
  for (int y = 0; y < 9; y++) {
    for (int x = 0; x < 9; x++) {
      if (x == 3 || x == 6)
        printf("|");
      if (tab[y][x] == 0)
        printf(" ");
      else
        printf("%d", tab[y][x]);
    }

    printf("\n");
    if (y == 2 || y == 5)
      printf("-----------\n");
  }
}

// Fonction principal Sudoku
int main() {
  int tab[9][9];
  srand((int) time(NULL)); // srand pour générer des chiffres aléatoirement a chaque compilation 

  nettoyage_Grille(tab);
  Grille(tab, 0);
  affichage_Grille(tab);

  return 0;
}
