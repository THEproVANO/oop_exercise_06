#include<iostream>
#include<algorithm>
#include<locale.h>
#include"Pentagon.h"
#include"Queue.h"
#include"Allocator.h"

void Menu1() {
    std::cout << "1. Add figure in queue\n";
    std::cout << "2. Delete figure from queue\n";
    std::cout << "3. Output figure\n";
    std::cout << "4. Output all figures\n";
    std::cout << "5. Add figure by index\n";
    std::cout << "Input the number of function: ";
}

void DeleteMenu() {
    std::cout << "1. Delete the top element\n";
    std::cout << "2. Delete figure by index\n";
    std::cout << "Input the number of function: ";
}

void PrintMenu() {
    std::cout << "1. Output the top element\n";
    std::cout << "2. Output the last element\n";
    std::cout << "Input the number of function: ";
}

int main()
{
    containers::Queue<Pentagon<int>, allocators::my_allocator<Pentagon<int>, 1000>> MyQueue;

	Pentagon<int> TempPentagon;

	while (true) {
		Menu1();
        int n, m;
		size_t ind;
		std::cin >> n;
        switch (n)
        {
		case 1:
			TempPentagon.Read(std::cin);
			TempPentagon.Print(std::cout);
            MyQueue.push(TempPentagon);
			break;
		case 2:
			DeleteMenu();
			std::cin >> m;
			switch (m) {
			case 1:
                if (MyQueue.length() == 0)
                {
                    std::cout << "Empty queue.\n";
                    break;
                }
                MyQueue.pop();
				break;
			case 2:
                if (MyQueue.length() == 0)
                {
                    std::cout << "Empty queue.\n";
                    break;
                }
                std::cout << "Input the index for deleating: ";
				std::cin >> ind;
                MyQueue.delete_by_index(ind);
				break;
			default:
				break;
			}
			break;
		case 3:
			PrintMenu();
			std::cin >> m;
			switch (m) {
			case 1:
                if (MyQueue.length() == 0)
                {
                    std::cout << "Empty queue.\n";
                    break;
                }
                MyQueue.top().Print(std::cout);
				std::cout << std::endl;
				break;
			case 2:
                if (MyQueue.length() == 0)
                {
                    std::cout << "Empty queue.\n";
                    break;
                }
                MyQueue.bottom().Print(std::cout);
				std::cout << std::endl;
				break;
			default:
				break;
			}
			break;
		case 4:
            if (MyQueue.length() == 0)
            {
                std::cout << "Empty queue\n";
                break;
            }
            std::for_each(MyQueue.begin(), MyQueue.end(), [](Pentagon<int>& X) { X.Print(std::cout); std::cout << std::endl; });
			break;
		case 5:
            std::cout << "Input the index\n";
			std::cin >> ind;
            if (ind >= MyQueue.length())
            {
                std::cout << "Index is out of bounders.\n";
                break;
            }
            std::cout << "Input the coordinates of pentagon\n";
			TempPentagon.Read(std::cin);
            MyQueue.insert_by_index(ind, TempPentagon);
			break;
		default:
			return 0;
		}
        std::cout << "\n\n\n";
	}
	return 0;
}
