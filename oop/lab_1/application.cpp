#include "application.h"
#include "matrix.h"


Application::Application()
{
    exec();
}

void Application::exec()
{
    bool quit = false;
    int option = 0;

    //создаем объект класса Matrix - вызываем конструктор
    Matrix matrix;

    while (quit == false) {
        mainMenu();

        std::cin >> option;

        switch(option)
        {
            case(1):
                matrix.setSize();
                matrix.setMatrixValues();
                break;
            case(2):
                number** tmp_matrix;
                number det;
                det = 0;

                //создаем копию матрицы, чтобы проводить операции над копией, а не над исходной матрицей
                tmp_matrix = new number* [matrix.getSize()];
                for (int i = 0; i < matrix.getSize(); ++i) {
                    tmp_matrix[i] = new number[matrix.getSize()];
                }
                matrix.copyMatrix(tmp_matrix);

                //вызываем метод для расчета определителя
                det = matrix.calculateDet(tmp_matrix, matrix.getSize());

                std::cout << "Determinant = " << det <<std::endl;

                break;
            case(3):
                matrix.transposeMatrix();
                break;
            case(4):
                int rank;
                rank = 0;

                //создаем копию матрицы, чтобы проводить операции над копией, а не над исходной матрицей
                tmp_matrix = new number* [matrix.getSize()];
                for (int i = 0; i < matrix.getSize(); ++i) {
                    tmp_matrix[i] = new number[matrix.getSize()];
                }
                matrix.copyMatrix(tmp_matrix);

                rank = matrix.calculateRank();

                std::cout << "Rank = " << rank << std::endl;
                break;
            case(5):
                matrix.printMatrix();
                break;
            case(6):
                quit = true;
        }

    }
}

void Application::mainMenu()
{
    std::cout << "==============================" << std::endl;
    std::cout << "1) Edit matrix data" << std::endl;
    std::cout << "2) Calculate the matrix determinant" << std::endl;
    std::cout << "3) Transpose the matrix" << std::endl;
    std::cout << "4) Calculate the matrix rank" << std::endl;
    std::cout << "5) Matrix output" << std::endl;
    std::cout << "6) Exit" << std::endl;
    std::cout << "==============================" << std::endl;
}



