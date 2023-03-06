#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include "matrix.cpp"
#include "Main.h"


void logo()
{
	std::wcout << "   ___  ___      _        _        _____ _                 _____ _               _               " << std::endl;
	std::wcout << "   |  \\/  |     | |      (_)      /  __ \\ |               /  __ \\ |             | |              " << std::endl;
	std::wcout << "   | .  . | __ _| |_ _ __ ___  __ | /  \\/ | __ _ ___ ___  | /  \\/ |__   ___  ___| | _____ _ __   " << std::endl;
	std::wcout << "   | |\\/| |/ _` | __| '__| \\ \\/ / | |   | |/ _` / __/ __| | |   | '_ \\ / _ \\/ __| |/ / _ \\ '__|  " << std::endl;
	std::wcout << "   | |  | | (_| | |_| |  | |>  <  | \\__/\\ | (_| \\__ \\__ \\ | \\__/\\ | | |  __/ (__|   <  __/ |     " << std::endl;
	std::wcout << "   \\_|  |_/\\__,_|\\__|_|  |_/_/\\_\\ \\_____/_|\\__,_|___/___/ \\_____/_| |_|\\___|\\___|_|\\_\\___|_|     " << std::endl;
	std::wcout << std::endl << L"Помощь - help" << std::endl;
}
void help()
{
	std::wcout << L"Доступные комманды:" << std::endl << std::endl;
	std::wcout << L"help - отобразить это меню" << std::endl;
	std::wcout << L"exit - выйти" << std::endl;
	std::wcout << L"create - создать матрицу" << std::endl;
	std::wcout << L"view - отобразить текущую матрицу" << std::endl;
}
std::wstring requestCommand()
{

	std::wcout << L"Команда:";
	std::wstring input;
	std::getline(std::wcin, input);
	return input;
}
void ClearConsole()
{
	std::wcout << "\x1B[2J\x1B[H";//clear console escape
}
Matrix createMatrix()
{
	ClearConsole();
	bool valid = false;
	while (!valid)
	{
		std::wcout << L"Укажите размер квадратной матрицы (back - назад): ";
		std::wstring input;
		std::getline(std::wcin, input);
		if (input == L"back")
		{
			return new Matrix();
		}
		try {
			int size = stoi(input);
			valid = true;
		}
		catch (const std::invalid_argument& ia)
		{
			std::wcout << L"Это неправильный размер" << std::endl;
		}
	}
	return new Matrix();
}

int main()
{
	Matrix matrix;
	auto mode = _setmode(_fileno(stdout), _O_U16TEXT);
	mode = _setmode(_fileno(stdin), _O_U16TEXT);
	mode = _setmode(_fileno(stderr), _O_U16TEXT);
	logo();
	while (true)
	{
		std::wstring command = requestCommand();
		//switch str
		if (command == L"help")
		{
			help();
		}
		else if (command == L"exit")
		{
			exit(0);
		}
		else if (command == L"create")
		{
			matrix = createMatrix();
			ClearConsole();
			logo();
		}
		else {
			ClearConsole();
			logo();
			std::wcout << L"Команда не найдена" << std::endl;
		}
	}
}