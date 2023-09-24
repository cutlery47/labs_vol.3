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

    Matrix matrix(5);

    while (quit == false) {
        mainMenu();

        std::cin >> option;

        switch(option)
        {
            case 1:
            {
                matrix.setSize();
                matrix.setValues();
                break;
            }
            case 2:
            {
                number det = matrix.det();
                std::cout << "Determinant = " << det <<std::endl;
                break;
            }
            case 3:
            {
                matrix.transpose();
                break;
            }
            case 4:
            {
                int rank = matrix.rank();
                std::cout << "Rank = " << rank << std::endl;
                break;
            }
            case 5:
            {
                matrix.print();
                break;
            }
            case 6:
            {
                quit = true;
                break;
            }
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
