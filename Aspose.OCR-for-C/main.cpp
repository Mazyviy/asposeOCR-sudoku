#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <aspose_ocr.h>
#include <vector>

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

int main() {
	std::vector<std::vector<int>> board(9, std::vector<int>(9));
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
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
    std::cout << std::endl << std::endl;

    SolutionSudoku sol;
    sol.solution(board, 0, 0);

    for (auto i = 0; i < 9; ++i) {
        for (auto j = 0; j < 9; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}