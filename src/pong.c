// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>

void printPlayField(int playerOneRocket, int playerTwoRocket, int xBall, int yBall, int playerOneScore, int playerTwoScore) { //rocksmar: Эта функция отвечает за отрисовку игрового поля
    /* Перебираем каждое значение ширины, для каждого значения высоты сверху вниз
    */
    for (int height = 0; height < 25; height++) { 
        for (int width = 0; width < 80; width++) {
	    if (height == 0 && width == 20) { //в нужных местах вместо границы поля отрисовываем счет игроков
	    	printf("%d", playerOneScore);
	    } else if (height == yBall && width == xBall) { // если мы на высоте где должен быть мяч то рисуем его
                printf("\033[31m@\033[0m");
	    }
	    else if (width == 40){ //В середине рисуем разделитель игрового поля на половину первого игрока и половину второго игрока
	        printf("\033[33m|\033[0m");
	    } else if (height == 0 && width == 60) {
	        printf("%d", playerTwoScore);
	    } else if (height == 0 || height == 24) { // если мы на высоте верхней или нижней границы поля то рисуем границу
                printf("\033[32m-\033[0m");
            } else if (((height == playerOneRocket || height ==  playerOneRocket + 1 || // если мы оказались на той высоте где должна быть ракетка первого игрока и мы на ширине где должна быть ракетка первого игрока то рисуем её
                         height == playerOneRocket - 1) &&
                        width == 0) ||
                       ((height == playerTwoRocket || height == playerTwoRocket + 1 || height == // тоже самое для второй ракеткт
                             playerTwoRocket - 1) &&
                        width == 79)) {
                printf("\033[34m#\033[0m");
            }  else {
                printf(" ");
            }
        }
        printf("\n"); 
    }
}
int playerOneTurn(char key, int currentPosition) { //venitati: функция обрабатывает ввод первого игрока с клавиш "a или z"
        if (key == 'a') { // если введеная клавиша - "а" 
            if (currentPosition > 2) { // то проверяем можно ли поднять ракетку выше, чтобы она не уперлась в границу поля
                currentPosition--; // если удовлетворяет условие, то поднимаем 
            }
            } else if (key == 'z') { // если введеная клавиша "z" то
            if (currentPosition < 22) { // то проверяем можно ли опустить ракетку ниже
                currentPosition++; // если удовлетворяет условие, то опускаем
            }
    }
        return currentPosition; // Функция возвращает координаты первой ракетки
}
int playerTwoTurn(char key, int currentPosition) { // функция обрабатывает ввод второго игрока с клавиш "k или m"
        if (key == 'k') { // тоже самое, что описанно выше в функции "playerOneTurn" только правая ракетка
            if (currentPosition > 2) {
                currentPosition--;
            }
            } else if (key == 'm') {
            if (currentPosition < 22) {
                currentPosition++;
            }
    }
        return currentPosition; //Функция возвращает координаты второй ракетки
}


int main() { 
    printf("Добро пожаловать в игру Пинг-Понг\n Управление Левая ракетка: A/Z Вверх/вниз, Правая ракетка: K/M Вверх/вниз\n Пропуск хода: Пробел \n Выйти из игры: Ctrl + C\nИгру начинает Левая ракетка, для того чтобы появилось поле начните двигать ракетку.\n");
    int playerOneRocket = 12; //Базовая позиция двух ракеток в начале игры(по середине)
    int playerTwoRocket = 12; 
    int xBall = 1;
    int yBall = 12;
    int playerOneScore = 0;
    int playerTwoScore = 0;
    char xDirection = 'R'; //Переменные для хранения направления мяча по соответсвующей координате.
    char yDirection = '-';
    while (playerOneScore <= 21 || playerTwoScore <= 21) {
    	  printPlayField(playerOneRocket, playerTwoRocket, xBall, yBall, playerOneScore, playerTwoScore);
	  if (playerOneScore == 21) {
            printf("Игрок 1 выйграл!/n");
            break;
        } else if (playerTwoScore == 21) {
            printf("Игрок 2 выйграл!/n");
            break;
        }
	char key;
	key = getchar(); // Используем getchar из стандартного модуля stdin для того чтобы записать введенный символ в переменную
	if (key == 'a' || key == 'z') { // Если символ A или Z то мы управляем первой ракеткой, также if принимает ПРОБЕЛ(Для пропуска хода)  
        playerOneRocket = playerOneTurn(key, playerOneRocket); // Если условие истинно то передаем нажатую клавишу функции, которая двигает первую ракетку
    }
	else if (key == 'k' || key == 'm' || key == ' ') { //то же самое используем для второй ракетки
        playerTwoRocket = playerTwoTurn(key, playerTwoRocket); //передаем функции нажатую клавишу
    } else {continue;}

	// сначала двигаем мяч
	if (yBall == 1){
		yDirection='D';
	}
	if (yBall == 23) {
		yDirection='U';
	}
	if (yDirection == 'U'){
		yBall-=1;
	} 
	if (yDirection == 'D'){
		yBall+=1;
	}
	if (xDirection == 'R'){
		xBall+=1;
	}
	if (xDirection == 'L'){
		xBall-=1;
	}

	// потом проверяем столкновения
    if (xBall <= 1 && (yBall==playerOneRocket || yBall==playerOneRocket+1 || yBall==playerOneRocket-1)) { 
		if (yBall==playerOneRocket) {
			xDirection='R';
			yDirection='-';
		} else if (yBall==playerOneRocket+1) {
			xDirection='R';
			yDirection='D';
		} else if (yBall == playerOneRocket-1) {
			xDirection='R';
			yDirection='U';
		}
	} else if (xBall <= 0) { 
		playerTwoScore++;
		playerOneRocket = 12; 
    	playerTwoRocket = 12;
    	xBall = 79; 
    	yBall = 12;
		xDirection='L'; 
        yDirection='-';
		continue;
	}

    if (xBall >= 79 && (yBall==playerTwoRocket || yBall==playerTwoRocket+1 || yBall==playerTwoRocket-1)) { 
		if (yBall==playerTwoRocket) {
			xDirection='L';
			yDirection='-';
		} else if (yBall==playerTwoRocket+1) {
			xDirection='L';
			yDirection='D';
		} else if (yBall == playerTwoRocket-1) {
			xDirection='L';
			yDirection='U';
		}
	} else if (xBall >= 80) {
		playerOneScore++;
		playerOneRocket = 12;
		playerTwoRocket = 12;
		xBall = 1;
		yBall = 12;
		xDirection='R';
		yDirection='-';
		continue;
    }
 }
return 0;
}
