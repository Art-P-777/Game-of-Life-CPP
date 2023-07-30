#include <iostream>
#include <random>

using namespace std;

class GameOfLife {
private:
	//приват будет отвечать за изменение поля игры

	// приватные переменныe
	static const size_t heigth = 162, width = 42;// плюсовать 2 из-за границ поля игры
	char alive = '@', err = '!', dead = ' ';
	char arr[width][heigth];

	// рандомайзер используемый в конструкторе \ использовать только в rand_alive_char
	bool rand_alive_bool(const size_t probality) {
		size_t random = rand() % 100;

		if (random <= probality) { return true; }
		else { return false; }
	}

	char rand_alive_char(const size_t probality) {
		if (rand_alive_bool(probality)) {
			return alive;
		}
		else {
			return dead;
		}
	}

	size_t check_alive_neigbours(const size_t i1, const size_t i2) {
		size_t alive_neigbours = 0;

		for (int j1 = -1; j1 < 2; j1++) {
			for (int j2 = 1; j2 > -2; j2--) {
				if ( !( (j1 == 0 && j2 == 0) || (arr[i1][i2] == err) ) ) {
					if (arr[i1+j1][i2+j2] == alive) {
						alive_neigbours++;
					}
				}
			}
		}

		return alive_neigbours;
	}

public:
	GameOfLife() {
		// заполнение пустотой
		for (int i1 = 0; i1 < width; i1++) {
			for (int i2 = 0; i2 < heigth; i2++) {
				arr[i1][i2] = dead;
			}
		}

		// граница поля игры
		for (int i = 0; i < width; i++) {
			if (i == 0 || i == width - 1) {
				for (int i1 = 0; i1 < heigth; i1++) {
					arr[i][i1] = err;
				}
			}
			else {
				arr[i][0] = err;
				arr[i][heigth - 1] = err;
			}
		}

		// рандомайзер для появления живых клеток
		srand(time(NULL));
		for (int i1 = 1; i1 < width - 1; i1++) {
			for (int i2 = 1; i2 < heigth - 1; i2++) {
				arr[i1][i2] = rand_alive_char(1);
			}
		}
	}// конец конструктора

	void update_grid() {
		for (int i1 = 1; i1 < width - 1; i1++) {
			for (int i2 = 1; i2 < heigth - 1; i2++) {
				size_t alive_neigbours = check_alive_neigbours(i1, i2);

				if (arr[i1][i2] == alive && (alive_neigbours < 2 || alive_neigbours > 3)) {
					arr[i1][i2] = dead;
				}
				else if (arr[i1][i2] == dead && alive_neigbours == 3) {
					arr[i1][i2] = alive;
				}
			}
		}
	}

	void cout_grid() {
		system("cls");
		for (int i1 = 1; i1 < width - 1; i1++) {
			for (int i2 = 1; i2 < heigth - 1; i2++) {
				cout << arr[i1][i2];
			}
			cout << endl;
		}
	}
	

};

int main(){
	setlocale(LC_ALL, "RU");

	GameOfLife x;

	while (true) {
		x.cout_grid();
		x.update_grid();
	}
	
	return 0;
}