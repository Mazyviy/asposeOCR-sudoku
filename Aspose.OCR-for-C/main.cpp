#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <aspose_ocr.h>
#include <vector>
#include <Windows.h>
#include <map>
#include <fstream>
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;

class SolutionSudoku {
private:
    bool isValid(std::vector<std::vector<int>>& board, int row, int col, int number)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (board[row][j] == number)
            {
                return false;
            }
        }

        for (int i = 0; i < 9; ++i)
        {
            if (board[i][col] == number)
            {
                return false;
            }
        }

        int sRow = row - row % 3;
        int sCol = col - col % 3;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i + sRow][j + sCol] == number)
                {
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool solution(std::vector<std::vector<int>>& board, int row, int col)
    {
        if (row == 8 && col == 9)
        {
            return true;
        }

        if (col == 9)
        {
            row++;
            col = 0;
        }

        if (board[row][col] != 0)
        {
            return solution(board, row, col + 1);
        }

        for (size_t number = 1; number <= board.size(); ++number)
        {
            if (isValid(board, row, col, number))
            {
                board[row][col] = number;
                if (solution(board, row, col + 1))
                {
                    return true;
                }
            }
            board[row][col] = 0;
        }
        return false;
    }
};

int SpecifyAllowedCharactersWithinRectangle(int x, int y, int w, int h) {
	std::string image_path = "1.png";

	custom_preprocessing_filters filters_;
	filters_.filter_1 = OCR_IMG_PREPROCESS_RESIZE(523, 930);
    filters_.filter_2 = OCR_IMG_PREPROCESS_THRESHOLD(87);
	filters_.filter_3 = OCR_IMG_PREPROCESS_DILATE;
	asposeocr_preprocess_page_and_save(image_path.c_str(), "2.png", filters_);
	image_path = "2.png";

	const size_t len = 4096;
	wchar_t buffer[len] = { 0 };

	size_t size = aspose::ocr::page_rect_abc(image_path.c_str(), buffer, len, x, y, w, h,
		L" 123456789");

	return _wtoi(buffer);
}

string currentDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y.%m.%d_%H-%M", now);
    return buffer;
}

int main() {
    Sleep(4000);

    keybd_event(VK_CONTROL, 0x1E, 0, 0);
    keybd_event(VK_SNAPSHOT, 0x1E, 0, 0);
    keybd_event(VK_SNAPSHOT, 0x1E, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0x1E, KEYEVENTF_KEYUP, 0);
    Sleep(1000);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(1000);
    string str1 = "copy D:\\Documents\\ShareX\\Screenshots\\2022-09\\"+
        currentDateTime()+ ".png D:\\Downloads\\Aspose.OCR-for-C-master\\Aspose.OCR-for-C";
    string str2 = "rename " + currentDateTime() + ".png 1.png";
    system(str1.c_str());
    system(str2.c_str());

    std::vector<std::vector<int>> board(9, std::vector<int>(9));
	std::vector<std::vector<int>> boardZero(9, std::vector<int>(9));
	const int w = 52, h = 52;//const int w = 45, h = 45;
	int i1 = 0, j1 = 0;

    for (auto y = 135; y < 621; y += h) {
        for (auto x = 26; x < 512; x += w) {
			board[i1][j1] = SpecifyAllowedCharactersWithinRectangle(x, y, w, h);
			x += 2;
			j1++;
		}
		j1 = 0;
		i1++;
		y += 2;
	}

    for (auto i = 0; i < 9; ++i) {
        for (auto j = 0; j < 9; ++j) {
            boardZero[i][j] = board[i][j];
        }
    }

	SolutionSudoku sol;
	sol.solution(board, 0, 0);

	for (auto i = 0; i < 9; ++i) {
		for (auto j = 0; j < 9; ++j) {
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}

	cout << "Window click\n";
	Sleep(3000);

	POINT cursor_first;
	GetCursorPos(&cursor_first);

	map<int, int> key{
		{1, VK_NUMPAD1},
		{2, VK_NUMPAD2},
		{3, VK_NUMPAD3},
		{4, VK_NUMPAD4},
		{5, VK_NUMPAD5},
		{6, VK_NUMPAD6},
		{7, VK_NUMPAD7},
		{8, VK_NUMPAD8},
		{9, VK_NUMPAD9},
	};

	i1 = 0, j1 = 0;
	for (auto y = 0; y < 468; y += h) {
		for (auto x = 0; x < 468; x += w) {
			if (boardZero[i1][j1] == 0) {
				mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE,
					65535 * (cursor_first.x + x) / GetSystemMetrics(SM_CXSCREEN),
					65535 * (cursor_first.y + y) / GetSystemMetrics(SM_CYSCREEN), 0, 0);

				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

				keybd_event(key[board[i1][j1]], 0x1E, 0, 0);
				keybd_event(key[board[i1][j1]], 0x1E, KEYEVENTF_KEYUP, 0);
				Sleep(400);
			}
			x += 2;
			j1++;
		}
		j1 = 0;
		i1++;
		y += 2;
	}

	std::string file_name = "1.png";
	remove(file_name.c_str());
	file_name = "2.png";
	remove(file_name.c_str());
}