#include <iostream>
#include "MyVector.h"
#include <conio.h>

int GetButton(int& PositionArrow)
{
    int but = _getch();
    //if (but == )
    //return but;

    if (but == 224)
    {
        but = _getch();
        if (but == 72)
            PositionArrow--;
        if (but == 80)
            PositionArrow++;
        PositionArrow = (PositionArrow + 15) % 15;
        return -1;
    }

    else if (but == 13)
        return PositionArrow;
}

void testMyVector()
{
    MyVector<int> a;
    system("cls");
    string menuArr[] = {"0) Back in menu..........",
                        "1) Add...................",
                        "2) Add back..............",
                        "3) Add front.............",
                        "4) Delete................",
                        "5) Delete back...........",
                        "6) Delete front..........",
                        "7) Sort \"Timsort\"........",
                        "8) Sort \"BubbleSort\".....",
                        "9) Random mix............",
                        "10) Random fill..........",
                        "11) Check for sorted.....",
                        "12) Size vector..........",
                        "13) Size memory..........",
                        "14) Clear vector........."};
    string arrow = "<---";
    int positionArrow = 0;

    while (true)
    {
        system("cls");
        a.Print();
        cout << endl;
        for (int i = 0; i < 15; i++)
        {
            cout << menuArr[i];
            if (i == positionArrow)
                cout << arrow;
            cout << endl;
        }

        int but = GetButton(positionArrow);

        if (but == 0)
            return;
        else if (but == 1)
        {
            int position;
            int value;
            cout << "\nEnter position: ";
            cin >> position;
            cout << "Enter value: ";
            cin >> value;
            a.Add(position, value);
        }
        else if (but == 2)
        {
            int value;
            cout << "\nEnter value: ";
            cin >> value;
            a.AddBack(value);
        }
        else if (but == 3)
        {
            int value;
            cout << "\nEnter value: ";
            cin >> value;
            a.AddFront(value);
        }
        else if (but == 4)
        {
            int position;
            cout << "\nEnter position: ";
            cin >> position;
            a.Delete(position);
        }
        else if (but == 5)
            a.DeleteBack();
        else if (but == 6)
            a.DeleteFront();
        else if (but == 7)
            a.SortTimsort();
        else if (but == 8)
            a.BubbleSort();
        else if (but == 9)
            a.RandomMix();
        else if (but == 10)
        {
            int number;
            cout << "\nEnter number: ";
            cin >> number;
            a.RandomFill(number);
        }
        else if (but == 11)
        {
            if (a.IsSort())
                cout << "\nSorted: True\n";
            else
                cout << "\nSorted: Flase\n";
            cout << "\nPress any key...";
            _getch();

        }
        else if (but == 12)
        {
            cout << endl << a.GetSizeVector();
            cout << "\nPress any key...";
            _getch();
        }
        else if (but == 13)
        {
            cout << endl << a.GetSizeMemory();
            cout << "\nPress any key...";
            _getch();
        }
        else if (but == 14)
            a.ClearVector();
    }
}


int main()
{
    testMyVector();
}
