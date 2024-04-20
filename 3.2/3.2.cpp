#include <iostream>
#include <fstream>

using namespace std;
void write_file(fstream& file);
void read_file(fstream& file);
void fill_time_file(fstream& file_1, fstream& file_2, fstream& file_main);
void create_file(fstream& file, fstream& file_1, fstream& file_2);


int main()
{
    fstream outfile;
    outfile.open("f.bin", ios::in | ios::out | ios::app | ios::binary);
    if (!outfile.is_open())
    {
        cout << "Error 1";
        return 1;
    }

    write_file(outfile);
    cout << "Your sequense: ";
    read_file(outfile);

    fstream time_file_1;
    time_file_1.open("even_number.bin", ios::in | ios::out | ios::app | ios::binary);
    if (!time_file_1.is_open())
    {
        cout << "Error 2";
        return 2;
    }

    fstream time_file_2;
    time_file_2.open("not_even_number.bin", ios::in | ios::out | ios::app | ios::binary);
    if (!time_file_2.is_open())
    {
        cout << "Error 3";
        return 3;
    }

    outfile.clear();
    fill_time_file(time_file_1, time_file_2, outfile);
    cout << "File even_number.bin: ";
    read_file(time_file_1);
    cout << "File not_even_number.bin: ";
    read_file(time_file_2);

    fstream infile;
    infile.open("g.bin", ios::in | ios::out | ios::app  | ios::binary);
    if (!infile.is_open())
    {
        cout << "Error 4";
        return 4;
    }

    time_file_1.clear();
    time_file_2.clear();
    create_file(infile, time_file_1, time_file_2);
    infile.clear();
    cout << "Your result sequense: ";
    read_file(infile);

    infile.close();
    time_file_1.close();
    time_file_2.close();
    outfile.close();
    remove("even_number.bin");
    remove("not_even_number.bin");
    remove("f.bin");
    remove("g.bin");
    return 0;
}

void write_file(fstream& file)
{
    cout << "Enter number(-1-end): ";
    int value;
    do
    {
        cin >> value;
        file.write(reinterpret_cast<char*>(&value), sizeof(int));
    } while (value != (-1));

    file.flush();
}

void read_file(fstream& file)
{
    int value;
    file.seekg(0);
    while (file.read(reinterpret_cast<char*>(&value), sizeof(int)))
    {
        cout << value<<" ";
    }

    cout << endl;
}

void fill_time_file(fstream& file_1, fstream& file_2, fstream& file_main)
{
    int value;
    file_main.seekg(0);
    while (file_main.read(reinterpret_cast<char*>(&value), sizeof(int)))
    {
        if (value % 2 == 0)
            file_1.write(reinterpret_cast<char*>(&value), sizeof(int));
        if (value % 2 != 0)
            file_2.write(reinterpret_cast<char*>(&value), sizeof(int));
    }

    file_1.flush();
    file_2.flush();
}

void create_file(fstream& file, fstream& file_1, fstream& file_2)
{
    int value;
    bool bit = 1;
    int counter = 0;
    file_1.seekg(0);
    file_2.seekg(0);

    while ((!file_1.eof()) || (!file_2.eof()))
    {
        if (bit == true)
        {
            if (file_1.read(reinterpret_cast<char*>(&value), sizeof(int)))
            {
                file.write(reinterpret_cast<char*>(&value), sizeof(int));
                counter++;
            }
            else
            {
                bit = false;
                counter = 0;
            }

            if (counter == 2)
            {
                bit = false;
                counter = 0;
            }
        }
        
        if (bit == false)
        {
            if (file_2.read(reinterpret_cast<char*>(&value), sizeof(int)))
            {
                file.write(reinterpret_cast<char*>(&value), sizeof(int));
                counter++;
            }
            else
            {
                bit = true;
                counter = 0;
            }

            if (counter == 2)
            {
                bit = true;
                counter = 0;
            }
        }
    }

    file.flush();
}


//outfile.write(reinterpret_cast<char*>(&v), sizeof(int) <<
//infile.read(reinterpret_cast<char*>(&v), sizeof(int)) >>