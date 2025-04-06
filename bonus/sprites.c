#include "cub3d.h"


// pour (chaque sprite) {
//     1. calcul distance au joueur

//     1.2 trier les sprites par distance (pour éviter suraffichage)

//     2. coordonnées relatives entre joueur et sprite
//     // double spriteX = sprite[spriteOrder[i]].x - posX;
//     //  double spriteY = sprite[spriteOrder[i]].y - posY;

//     3. calcul de inverse de la matrice de caméra
//     // double invDet = 1.0 / (planeX * dirY - dirX * planeY);
//     3.2 coordonnées transformées dans espace de la caméra
//     //  double transformX = invDet * (dirY * spriteX - dirX * spriteY);
//     //  double transformY = invDet * (-planeY * spriteX + planeX * spriteY);
//     3.3 pos horizontale du sprite a ecran (colonne centrale du sprite ?)
//     //  int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

//     4. calcul hauteur du sprite projeté

//     5. calcul largeur du sprite projeté

//     6. rendu pixel par pixel comme les murs
//     // if (transformY > 0 && transformY < z_buffer[col])
//     // {
//     //     // le sprite est plus proche que le mur : on dessine
//     // }
//     // else
//     // {
//     //     // le mur est devant, on ne dessine pas ce pixel
//     // }

// }

// 2 Ko
// (ce qui est commenté sur le fichier si c'est des formules ca vient de son article, le reste c'est moi qui ai rajouté)