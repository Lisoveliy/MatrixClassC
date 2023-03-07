#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <fstream>
#include "Matrix.cpp"

namespace UI {
	void Logo()
	{
		std::wcout << "   ___  ___      _        _        _____ _                 _____ _               _               " << std::endl;
		std::wcout << "   |  \\/  |     | |      (_)      /  __ \\ |               /  __ \\ |             | |              " << std::endl;
		std::wcout << "   | .  . | __ _| |_ _ __ ___  __ | /  \\/ | __ _ ___ ___  | /  \\/ |__   ___  ___| | _____ _ __   " << std::endl;
		std::wcout << "   | |\\/| |/ _` | __| '__| \\ \\/ / | |   | |/ _` / __/ __| | |   | '_ \\ / _ \\/ __| |/ / _ \\ '__|  " << std::endl;
		std::wcout << "   | |  | | (_| | |_| |  | |>  <  | \\__/\\ | (_| \\__ \\__ \\ | \\__/\\ | | |  __/ (__|   <  __/ |     " << std::endl;
		std::wcout << "   \\_|  |_/\\__,_|\\__|_|  |_/_/\\_\\ \\_____/_|\\__,_|___/___/ \\_____/_| |_|\\___|\\___|_|\\_\\___|_|     " << std::endl;
	}
	void Help()
	{
		std::wcout << L"Доступные комманды:" << std::endl << std::endl;
		std::wcout << L"help - отобразить это меню" << std::endl;
		std::wcout << L"exit - выйти" << std::endl;
		std::wcout << L"create - создать матрицу" << std::endl;
		std::wcout << L"create rand - создать матрицу с случайными числами" << std::endl;
		std::wcout << L"create rand int - создать матрицу с случайными целыми числами" << std::endl;
		std::wcout << L"view - отобразить текущую матрицу" << std::endl;
		std::wcout << L"write - записать матрицу в файл" << std::endl << std::endl;
		std::wcout << L"Действия над матрицей: " << std::endl << std::endl;
		std::wcout << L"det - посчитать определитель матрицы" << std::endl;
		std::wcout << L"trans view - вывести транспонированную матрицу" << std::endl;
		std::wcout << L"trans ptr - записать транспонированную матрицу" << std::endl;
		std::wcout << L"reverse view - вывести обратную матрицу" << std::endl;
		std::wcout << L"reverse ptr - записать обратную матрицу" << std::endl;
		std::wcout << L"clear - очистить матрицу до нулевой" << std::endl;
	}
	void ClearConsole()
	{
		std::wcout << "\x1B[2J\x1B[H";//clear console escape
	}
	std::wstring RequestCommand()
	{

		std::wcout << L"Команда:";
		std::wstring input;
		std::getline(std::wcin, input);
		return input;
	}
}
namespace Commands {
	Matrix CreateRandMatrix(Matrix* prev, bool isInt)
	{
		UI::ClearConsole();
		UI::Logo();
		while (true)
		{
			std::wcout << L"Укажите размер квадратной матрицы (back - назад): ";
			std::wstring input;
			std::getline(std::wcin, input);
			if (input == L"back")
			{
				return prev;
			}
			std::wcout << L"Укажите нижнюю границу случайных значений матрицы (back - назад): ";
			std::wstring input2;
			std::getline(std::wcin, input2);
			if (input2 == L"back")
			{
				return prev;
			}
			std::wcout << L"Укажите верхнюю границу случайных значений матрицы (back - назад): ";
			std::wstring input3;
			std::getline(std::wcin, input3);
			if (input3 == L"back")
			{
				return prev;
			}
			try {
				int size = stoi(input);
				if (size < 1)
				{
					throw new std::invalid_argument("recieved zero or negative number");
				}
				int down = stoi(input2);
				int up = stoi(input3);
				double** elements = new double* [size];
				srand(time(NULL));
				for (int i = 0; i < size; i++)
				{
					elements[i] = new double[size];
					for (int i2 = 0; i2 < size; i2++)
					{
						double element;
						if (isInt) {
							element = down + rand() % (up - down + 1);
						}
						else
							element = down + rand() % (up - down + 1) + ((double)10/rand());
						elements[i][i2] = element;
					}
				}
				return new Matrix(size, elements);
			}
			catch (const std::invalid_argument&)
			{
				std::wcout << L"Это неверные значения!" << std::endl;
			}
		}
	}
	Matrix CreateMatrix(Matrix* prev)
	{
		UI::ClearConsole();
		UI::Logo();
		while (true)
		{
			std::wcout << L"Укажите размер квадратной матрицы (back - назад): ";
			std::wstring input;
			std::getline(std::wcin, input);
			if (input == L"back")
			{
				return prev;
			}
			try {
				int size = stoi(input);
				double** elements = new double* [size];
				if (size < 1)
				{
					throw new std::invalid_argument("recieved zero or negative number");
				}
				for (int i = 0; i < size; i++)
				{
					elements[i] = new double[size];
					for (int i2 = 0; i2 < size; i2++) {
						std::wcout << L"Введите значения " << i + 1 << L" столбца(" << i2 + 1 << L")(Через Enter(или вернуться назад через back)):" << std::endl;
						std::wstring input;
						std::getline(std::wcin, input);
						try {
							double num = stoi(input);
							elements[i][i2] = num;
						}
						catch (const std::invalid_argument&)
						{
							if (input == L"back")
							{
								return prev;
							}
							std::wcout << L"Неверное число" << std::endl;
							i2--;
						}
					}
				}
				return new Matrix(size, elements);
			}
			catch (...)
			{
				std::wcout << L"Это неправильный размер" << std::endl;
			}
		}
	}
}

int main()
{
	Matrix* matrixptr = new Matrix();
	auto mode = _setmode(_fileno(stdout), _O_U16TEXT);
	mode = _setmode(_fileno(stdin), _O_U16TEXT);
	mode = _setmode(_fileno(stderr), _O_U16TEXT);
	UI::Logo();
	UI::Help();
	while (true)
	{
		std::wstring command = UI::RequestCommand();
		//switch str
		if (command == L"help")
		{
			UI::ClearConsole();
			UI::Logo();
			UI::Help();
		}
		else if (command == L"exit")
		{
			exit(0);
		}
		else if (command == L"create")
		{
			matrixptr = new Matrix(Commands::CreateMatrix(matrixptr));
			//auto oldaddr = matrixptr;
			//auto newaddr = matrixptr;
			UI::ClearConsole();
			//std::wcout << oldaddr << std::endl << newaddr << std::endl;
			UI::Logo();
		}
		else if (command == L"create rand")
		{
			matrixptr = new Matrix(Commands::CreateRandMatrix(matrixptr, false));
			//auto oldaddr = matrixptr;
			//auto newaddr = matrixptr;
			UI::ClearConsole();
			//std::wcout << oldaddr << std::endl << newaddr << std::endl;
			UI::Logo();
		}
		else if (command == L"create rand int")
		{
			matrixptr = new Matrix(Commands::CreateRandMatrix(matrixptr, true));
			//auto oldaddr = matrixptr;
			//auto newaddr = matrixptr;
			UI::ClearConsole();
			//std::wcout << oldaddr << std::endl << newaddr << std::endl;
			UI::Logo();
		}
		else if (command == L"view")
		{
			UI::ClearConsole();
			UI::Logo();
			std::wcout << L"Текущая матрица: " << std::endl;
			matrixptr->View();
			std::wcout << L"Размерность: " << matrixptr->getDegree() << "x" << matrixptr->getDegree() << std::endl;
		}
		else if (command == L"clear")
		{
			UI::ClearConsole();
			UI::Logo();
			int degree = matrixptr->getDegree();
			double** elements = new double* [degree];
			for (int i = 0; i < degree; i++)
			{
				elements[i] = new double [degree];
				for (int i2 = 0; i2 < degree; i2++)
				{
					elements[i][i2] = 0;
				}
			}
			matrixptr->setElements(elements);
			std::wcout << L"Матрица очищена!" << std::endl;
		}
		else if (command == L"det")
		{
			UI::ClearConsole();
			UI::Logo();
			double det = matrixptr->Det();
			std::wcout << L"Определитель матрицы равен: " << det << std::endl;
		}
		else if (command == L"trans view")
		{
			UI::ClearConsole();
			UI::Logo();
			std::wcout << L"Транспонированная матрица: " << std::endl;
			Matrix trans = matrixptr->Transponse();
			trans.View();
			std::wcout << L"Размерность: " << trans.getDegree() << "x" << trans.getDegree() << std::endl;
		}
		else if (command == L"trans ptr")
		{
			UI::ClearConsole();
			UI::Logo();
			matrixptr = new Matrix(matrixptr->Transponse());
			std::wcout << L"Матрица была транспонированна и перезаписана!" << std::endl;
		}
		else if (command == L"reverse view")
		{
			UI::ClearConsole();
			UI::Logo();
			std::wcout << L"Обратная матрица: " << std::endl;
			Matrix clone = new Matrix(matrixptr);
			clone.Inverse();
			clone.View();
			std::wcout << L"Размерность: " << clone.getDegree() << "x" << clone.getDegree() << std::endl;
		}
		else if (command == L"reverse ptr")
		{
			UI::ClearConsole();
			UI::Logo();
			matrixptr->Inverse();
			std::wcout << L"Матрица стала обратной и была перезаписана!" << std::endl;
		}
		else if (command == L"write")
		{
			std::wofstream out("matrix.txt");
			std::wstreambuf* coutbuf = std::wcout.rdbuf();
			std::wcout.rdbuf(out.rdbuf());
			matrixptr->View();
			out.close();
			std::wcout.rdbuf(coutbuf);
			std::wcout << L"Запись выполнена!" << std::endl;
		}
		else {
			UI::ClearConsole();
			UI::Logo();
			std::wcout << L"Команда не найдена\nhelp для просмотра доступных комманд" << std::endl;
		}
	}
}