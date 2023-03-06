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

	std::wcout << L"Комманда:";
	std::wstring input;
	std::getline(std::wcin, input);
	return input;
}

int main()
{
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
		else std::wcout << L"Комманда не найдена" << std::endl;
	}
}