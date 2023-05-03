#include <stdio.h>
#include <stdlib.h>


typedef struct sudoku_title{
    char value;
    char possible[10];
} sudoku;

sudoku init(sudoku *grid){

    for(int i = 0; i < 81; i++){               // i parcourt la grille
        (grid + i) -> value = '0';
        for(int j = 0; j < 9; j++){                //j parcourt les cases du tableau possible
            ((grid + i) -> possible)[j] = '1';
        }
        ((grid + i) -> possible)[9] = '\0';

    }
    printf("\n");
    printf("\t SUDOKU \n");

    for(int i = 0; i < 81; i++){
        printf(" | %c", (grid + i) -> value);
        if(i % 9 == 8){
            printf(" |\n\n");
        }
    }
    return *grid;
}

void disp_final(sudoku *grid){
    for(int i = 0; i < 81; i++){
        if((grid + i) -> value == '0'){
            printf(" |  ");
        }
        else{
            printf(" | %c", (grid + i) -> value);
        }
        if(i % 9 == 8){
            printf(" |\n\n");
        }
    }
}

void disp_possible(sudoku *grid){
    int caractere;
    for(int d = 1; d < 10; d++){
        for(int i = 0; i < 81; i++){
            if((grid+i) -> value == d+'0'){          // convertir le int d en char
                caractere = d+'0';
            }
            else if((grid + i) -> value != '0'){
                caractere = '.';
            }
            else if((grid + i) -> value == '0' && ((grid + i) -> possible)[d-1] == '1'){
                caractere = '+';
            }
            else{
                caractere = ' ';
            }
            printf(" | %c", caractere);
            if(i % 9 == 8){
                printf(" |\n\n");
            }
        }
       printf("\n\n");
    }
}

void set_tile_value(sudoku * sudokuCase, char val){
    int value= sudokuCase -> value -'0';         //convertir le char value en int
    sudokuCase->value=val;
    if(value != 0){
        sudokuCase -> possible[value-1] = '1';
    if(val-'0'!=0){
        sudokuCase -> possible[val-'0'-1] = '0';
    }
}
}


void req_start_grid(sudoku *grid){
    char ligne[11];
    for (int i = 1; i <= 9; i++)
    {
      printf ("saisir la %d eme ligne\n", i);
      
      fgets (ligne, 11, stdin);
      printf("%s\n",ligne);
      for (int j = 0; j < 9; j++)
	{
	  if (ligne[j] <= '9' && ligne[j] >= '1')
	    {
	      (grid + (i - 1) * 9 + j )->value = ligne[j];
	      (grid + (i - 1) * 9 + j )->possible[j ] = '0';
	    }
	  
	} 
	
	}
}

int clean_line(sudoku *sudokuLine){
    int modifier = 0;
    char value;
    int valueToInt;
    for(int i = 0; i < 9; i++){
        value = (sudokuLine + i) -> value;
        if(value != '0'){
            valueToInt = value - '0';
            for(int j = 0; j < 9; j++){
                if((sudokuLine + j) -> possible[valueToInt - 1] != '0'){
                    (sudokuLine + j) -> possible[valueToInt - 1] = '0';
                    modifier = 1;
                }
            }
        }
    }
    return modifier;
}

int validate_single_possibility(sudoku *grid){
    int modifier = 0;
    int count;
    int valeurUniquePossible;
    for(int i = 0; i < 81; i++){
        count = 0;
        if((grid + i) -> value == '0'){
            for(int j = 0; j < 9; j++){
                if ((grid + i) -> possible[j] == '1'){
                    count++;
                    valeurUniquePossible = j+1;
                }
            }
            if(count == 1){
                (grid + i) -> value = valeurUniquePossible + '0';
                (grid + i) -> possible[valeurUniquePossible - 1] = '0';
                modifier = 1;
            }
        }
    }
    return modifier;
}

int valid_exist_in_line(sudoku *sudokuline){
  int modifier=0;
  int count=0;
  char vall;
  int valeur,casee;
  for (int v=1;v<10;v++){
      for(int j=0;j<9;j++){
      if((sudokuline+j)->value=='0'&& (sudokuline+j)->possible[v-1]=='1'){
        count++;
        valeur=v;
        vall=v+'0';
        casee=j;
      }}
      if(count==1){
         (sudokuline+casee)->value=vall ;
         (sudokuline+casee)->possible[valeur-1]='0';
         modifier=1;
      }
  }
return modifier;
}

/*le type subset qui est un pointeur vers un pointeur qui pointe sur sudoku(c est
donc un pointeur vers une case codee par *sudoku
il va donc servir a avoir "un tableau de pointeur sur les cases"(sous ensemble de la grille)*/
 typedef sudoku ** subset; 
 /* on a definit le type subset qui remplace le sudoku**(qui est un pointeur vers
un pointeur pointant vers un struct(sudoku)*/

void disp_subset(subset Sousensemble){   /*sousensemble est un tableau des 
subset)*/
    //Permet l'affichage des elements d'un subset
    for(int i = 0; i < 9; i++){
        if(((*(Sousensemble + i)) -> value) == '0'){ 
            printf(" |  ");
        }
        else{
            printf(" | %c", (*(Sousensemble + i)) -> value); /* *(sousensemble+i) est le contenu
           de i eme element du tableau des subset il est donc le pointeur de la i eme case!*/
        }
        if(i%3 == 2){
            printf(" |\n\n");
        }
    }
}

subset get_line_subset(sudoku *grid, int ligne){
    //Creer un subset a partir des 9 elements d'une ligne
    subset Sousensemble = (subset)malloc(sizeof(sudoku*) * 9);
    for(int i = 0; i < 9; i++){
        *(Sousensemble + i) = (grid + (ligne - 1)*9 + i);
    }
    return Sousensemble;
}


subset get_col_subset(sudoku *grid, int colonne){
    //Creer un subset a partir des 9 elements d'une colonne
    subset Sousensemble = (subset)malloc(sizeof(sudoku*) * 9);
    for(int i = 0; i < 9; i++){
        *(Sousensemble + i) = (grid + i*9 + colonne - 1);
    }
    return Sousensemble;
}

subset get_subsq_subset(sudoku *grid, int numero){
    /*Creer un subset a partir des 9 elements d'un carre 3x3 de la grille
    Ici le numero repreente le premier element a entrer dans le sous carre*/
    subset SousEnsemble = (subset)malloc(sizeof(sudoku*) * 9);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            *(SousEnsemble + i*3 + j) = (grid + numero-1 + i*9 + j);
        }
    }
    return SousEnsemble;
}

int clean_subset(subset Sousensemble){
    //Suit le meme principe que clean_line
    int modifier = 0;
    char value;
    int valueToInt;
    for(int i = 0; i < 9; i++){
        value = (*(Sousensemble + i)) -> value;
        if(value != '0'){
            valueToInt = value - '0';
            for(int j = 0; j < 9; j++){
                if((*(Sousensemble + j)) -> possible[valueToInt - 1] != '0'){
                    (*(Sousensemble + j)) -> possible[valueToInt - 1] = '0';
                    modifier = 1;
                }
            }
        }
    }
    return modifier;
}

int valid_exist_in_subset(subset sousensemble){
    //Creer de la meme maniere que valid_exist_in_line
    int modifier = 0;
    int count =0;
    int casee,valeur;
    char vall;
    for (int v=1;v<10;v++){
        for(int j=0;j<9;j++){
	  if((*(sousensemble+j))->value=='0' && (*(sousensemble)+j)->possible[v-1]=='1'){
            count++;
            vall=v+'0';
            casee=j;
            valeur=v;
        }}
        if (count==1){
            (*(sousensemble+casee))->value=vall;
            (*(sousensemble+casee))->possible[valeur-1]='0';
            modifier=1;
        }
        }
    return modifier;
    
}

int clean_grid(subset * ensemble){
    //Applique clean_subset sur les 27 subsets de Ensemble
    int modifier = 0;
    int modifierGeneral = 0;
    for(int i = 0; i < 27; i++){
        modifier =  clean_subset(*(ensemble + i));
        if(modifier){
            modifierGeneral = 1;
        }
    }
    return modifierGeneral;
}

int valid_exist(subset * ensemble){
    //Applique valid_exist_in_subset sur les 27 subsets de Ensemble
    int modifier = 0;
    int modifierGeneral = 0;
    for(int i = 0; i < 27; i++){
        modifier =  valid_exist_in_subset(*(ensemble + i));
        if(modifier){
            modifierGeneral = 1;
        }
    }
    return modifierGeneral;
}


typedef struct affectation {    //le role est de memeoriser l historique des affectations
    sudoku *tile;
    char supposed ;
}affectation;

void set_tile_value2(sudoku * sudokuCase, char val, affectation * history, int * history_index, char supposed){
    int value = sudokuCase -> value - '0';
    sudokuCase -> value = val;
    (history + *history_index) -> tile = sudokuCase; /* il s agit de la case dans laquelle il faudra ecrire
                                                        la prochaine operation(on va changer sa valeur par val)*/
    (history + *history_index) -> supposed = supposed;
    (*history_index)++;                                   
    if(value != 0){
        sudokuCase -> possible[value-1] = '1';
    }
    if(val - '0' != 0){
        sudokuCase -> possible[val - '0' - 1] = '0';
    }

}
int count_possible(char possible[10]){
    //Cette fonction renvoie le nombre de valeurs possibles(c'est une fct intermediaire)
    int count = 0;
    for(int i = 0; i < 9; i++){
        if(possible[i] == '1'){
            count ++;
        }
    }
    return count;
}

int is_grid_valid(sudoku * grid){
    int valid = 1;
    for(int i = 0; i < 81; i++){
        if((grid + i) -> value == '0' && count_possible((grid + i) -> possible) == 0){
            valid = 0;
        }
    }
    return valid;
}

int guess_value(sudoku * grid, affectation * history, int * history_index){
    int supposed_find = 0;
    char value_possible;
    for(int i = 0; i < 81; i++){
        if((grid + i) -> value == '0' && count_possible((grid + i) -> possible) == 2){
            for(int j = 0; j<9; j++){
                if((grid + i) -> possible[j] == '1'){
                    value_possible = j + 1 + '0';
                }
            }
            set_tile_value2(grid + i, value_possible, history, history_index, 1);
            supposed_find = 1;
            break;
        }
    }
    return supposed_find;
}
int valid_exist_in_subset2(subset SousEnsemble, affectation * history, int * history_index){
    //Creer de la meme maniere que valid_exist_in_ligne
    int modifier = 0;
    int valueExist;
    int count;
    int valeurUniquePossique;
    for(int v = 1; v < 10; v++){
        valueExist = 0;
        count = 0;
        for(int i = 0; i < 9; i++){
            if((*(SousEnsemble + i)) -> value == v+'0'){
                valueExist = 1;
            }
            else if((*(SousEnsemble + i)) -> possible[v-1] != '0'){
                count++;
                valeurUniquePossique = i;
            }
        }
        if(valueExist == 0 && count == 1){
            set_tile_value2((*(SousEnsemble + valeurUniquePossique)), v + '0', history, history_index, 0);
            modifier = 1;
        }
    }
    return modifier;
}
int valid_exist2(subset * Ensemble, affectation * history, int * history_index){
    //Applique valid_exist_in_subset sur les 27 subsets de Ensemble
    int modifier = 0;
    int modifierGeneral = 0;
    for(int i = 0; i < 27; i++){
        modifier =  valid_exist_in_subset2(*(Ensemble + i), history, history_index);
        if(modifier){
            modifierGeneral = 1;
        }
    }
    return modifierGeneral;
}
int validate_single_possibility2(sudoku *grid, affectation * history, int * history_index){
    int modifier = 0;
    int count;
    int valeurUniquePossique;
    for(int i = 0; i < 81; i++){
        count = 0;
        if((grid + i) -> value == '0'){
            for(int j = 0; j < 9; j++){
                if ((grid + i) -> possible[j] == '1'){
                    count++;
                    valeurUniquePossique = j+1;
                }
            }
            if(count == 1){
                set_tile_value2(grid + i, valeurUniquePossique + '0', history, history_index, 0);
                modifier = 1;
            }
        }
    }
    return modifier;
}

void reinitialiser_possible(sudoku *sudokuCase){           /* cette fonction intermediare permet de reinitialiser
                                                          le tableau possible d'une case (le remplir par les '1'seulement)*/
    for(int j = 0; j < 9; j++){
            (sudokuCase -> possible)[j] = '1';
        }
        (sudokuCase -> possible)[9] = '\0';
}


void back_play(affectation * history, int * history_index, sudoku * grid, subset * Ensemble){
    int n = (*history_index);
    int value_supposed;
    for(int i = n-1; i >= 0; i--){             // i parcourt le tableau history
        if((history+i) -> supposed == 0){
            (history + i) -> tile -> value = '0';
            (*history_index)--;                          
        }
        else{
            value_supposed = (history + i) -> tile -> value;
            (history + i) -> tile -> value = '0';
            for(int j = 0; j < 81; j++){
                if((grid+j) -> value == '0'){
                    reinitialiser_possible(grid+j);
                }
            }
            clean_grid(Ensemble);           /*elle parcourt toutes les cases de tous les sous ensembles (Ensemble)
                                            et si une case a v comme valeur connue, elle indique qu'elle est impossible
                                             pour les autres cases qui sont dans le meme Ensemble*/

            (history + i) -> tile -> possible[value_supposed - '0' - 1] = '0';

            (*history_index)--;
            guess_value(grid, history, history_index);
            break;
        }
    }
}

 int main(int argc, char*argv[]){
    sudoku *grid = (sudoku *)malloc(81*sizeof(sudoku)); // Allocation de memoire pour la grille du sudoku
    subset * ensemble = malloc(sizeof(subset)*27); // Ensemble est la nouvelle variable qui contiendra tous les 27 subset

 affectation *history = (affectation *)malloc(81*sizeof(affectation));


    init(grid); // Initialisation de la grille 
    (grid+1)->value='2';
    (grid+3)->value='5';
    // req_start_grid(grid);
    disp_final(grid);
    disp_possible(grid);
    //int a=valid_exist_in_line(grid);
    //printf("%d\n",a);
    req_start_grid(grid);
    // Demande a l'utilisateur de definir les valeurs de debut de la grille
    printf("\n");


    // Ajout des 9 subset constitués a partir des 9 lignes de la grille
    for(int i = 0; i < 9; i++){
        *(ensemble + i) = get_line_subset(grid, i+1);
    }

    // Ajout des 9 subset constitués a partir des 9 colonnes de la grille
    for(int i = 9; i < 18; i++){
        *(ensemble + i) = get_col_subset(grid, i-8);
    }

    // Ajout des 9 subset constitués a partir des 9 carrees de 9 elements de la grille
    for(int i = 18; i < 27; i++){
        int numeros[9] = {1, 4, 7, 28, 31, 34, 55, 58, 61}; // les valeurs de debut des 9 carres
        *(ensemble + i) = get_subsq_subset(grid, numeros[i-18]);
    }

    //Affichage de tous les 27 subsets de la grille
    for(int i = 0; i < 27; i++){
        disp_subset(*(ensemble + i));
        printf("\n\n");
    }
    
    int history_index = 0;
    int count = 0;

    //Programme permettant la resolution de la grille comme expliqué dans le sujet
    int modifier[4] = {1, 1, 1, 1};
    while(modifier[0] || modifier[1] || modifier[2] || modifier[3]){
        modifier[0] = clean_grid(ensemble);
        modifier[1] = validate_single_possibility2(grid, history, &history_index);
        modifier[2] = valid_exist2(ensemble, history, &history_index);
        modifier[3] = validate_single_possibility2(grid, history, &history_index);
        
        if(is_grid_valid(grid) == 0){
            back_play(history, &history_index, grid, ensemble);
            if(++count == 5){
                break;                                 
            }
        }

        if(modifier[0] == 0 && modifier[1] == 0 && modifier[2] == 0 && modifier[3]== 0){
            if(guess_value(grid, history, &history_index) == 1){
                modifier[0] = 1;
            }
        }

        disp_final(grid);
        printf("\n\n");
    }

    //Liberation de la memoire
    free(grid);
    return 0;
}

