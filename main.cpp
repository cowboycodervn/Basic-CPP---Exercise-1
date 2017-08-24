#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

struct Student
{
    string name, inClass, address;
    double math, literature, english;
};

Student allStudent[100000];
int number;

char currentFile[100];
bool isEditing = false;

string decode(string s)
{
    for(int i = 0; i < s.size(); i ++)
        if (s[i] == '$')
            s[i] = ' ';
    return s;
}

string encode(string s)
{
    for(int i = 0; i < s.size(); i ++)
        if (s[i] == ' ')
            s[i] = '$';
    return s;
}

int getIntRange(int low, int high)
{
    int input;
    while(true)
    {
        cin >> input;
        if (input < low || input > high)
            cout << "Gia tri khong hop le, xin hay nhap lai!\n";
        else
            break;
    }
    return input;
}

void newFile()
{
    // Chưa có học sinh nào trong danh sách
    number = 0;
    // File chưa được lưu, do đó không có tên file
    strcpy(currentFile, "");
    // Thông báo đã có file đang được chỉnh sửa
    isEditing = true;
}

void openFile()
{
    // Lưu tên file lại để dùng về sau
    cout << "Hay nhap vao ten file: ";
    cin >> currentFile;

    // Mở file
    ifstream input;
    input.open(currentFile);

    // Đọc dữ liệu
    input >> number;
    for (int i = 1; i <= number; i ++)
    {
        input >> allStudent[i].name;
        allStudent[i].name = decode(allStudent[i].name);
        input >> allStudent[i].inClass;
        allStudent[i].inClass = decode(allStudent[i].inClass);
        input >> allStudent[i].address;
        allStudent[i].address = decode(allStudent[i].address);

        input >> allStudent[i].math;
        input >> allStudent[i].literature;
        input >> allStudent[i].english;
    }

    // Đóng file
    input.close();

    // Thông báo đã có file đang được chỉnh sửa
    isEditing = true;
}

void inputStudentInfo(int id)
{
    string temp; getline(cin, temp);
    cout << "Ten cua hoc sinh?\n";
    getline(cin, allStudent[id].name);
    cout << "Lop?\n";
    getline(cin, allStudent[id].inClass);
    cout << "Dia chi?\n";
    getline(cin, allStudent[id].address);
    cout << "Diem mon Toan?\n"; cin >> allStudent[id].math;
    cout << "Diem mon Van?\n"; cin >> allStudent[id].literature;
    cout << "Diem mon Anh?\n"; cin >> allStudent[id].english;
}

void addStudent()
{
    number ++;
    inputStudentInfo(number);
}

void editStudent()
{
    int id;
    cout << "Hay nhap ma so hoc sinh: ";
    cin >> id;
    if (id < 1 || id > number)
    {
        cout << "Ma so hoc sinh khong hop le!\n";
        return;
    }

    inputStudentInfo(id);
}

void deleteStudent()
{
    int id;
    cout << "Hay nhap ma so hoc sinh: ";
    cin >> id;
    if (id < 1 || id > number)
    {
        cout << "Ma so hoc sinh khong hop le!\n";
        return;
    }
    // Đẩy các học sinh phía sau về đúng chỗ
    for (int i = id + 1; i <= number; i ++)
        allStudent[i - 1] = allStudent[i];
    number --; // Bớt đi một học sinh
}

void printStudentInfo(int id)
{
    cout
    << "Ma so hoc sinh: " << id << '\n'
    << allStudent[id].name << ", hoc sinh lop " << allStudent[id].inClass << ", song tai " << allStudent[id].address
    << '\n'
    << "Diem mon Toan: " << allStudent[id].math
    << '\n'
    << "Diem mon Van: " << allStudent[id].literature
    << '\n'
    << "Diem mon Anh: " << allStudent[id].english
    << '\n';
}

void printAllStudent()
{
    for (int i = 1; i <= number; i ++)
        printStudentInfo(i);
}

void searchStudentByString(int byWhat, string value)
{
    for (int i = 1; i <= number; i ++)
    {
        // Lấy dữ liệu phù hợp
        string data;
        switch(byWhat)
        {
            case 1: // Tìm theo tên
                data = allStudent[i].name;
                break;
            case 2: // Tìm theo lớp
                data = allStudent[i].inClass;
                break;
            case 3: // Tìm theo địa chỉ
                data = allStudent[i].address;
                break;
        }

        // So sánh với yêu cầu
        if (data == value)
            printStudentInfo(i);
    }
}

void searchStudentByScore(int byWhat, double value, int compare)
{
    for (int i = 1; i <= number; i ++)
    {
        // Lấy dữ liệu phù hợp
        double data;
        switch(byWhat)
        {
            case 4: // Tìm theo điểm môn Toán
                data = allStudent[i].math;
                break;
            case 5: // Tìm theo điểm môn Văn
                data = allStudent[i].literature;
                break;
            case 6: // Tìm theo điểm môn Anh
                data = allStudent[i].english;
                break;
        }

        bool check;

        // So sánh phù hợp với phép toán
        switch (compare)
        {
            case 1: // =
                check = (data == value);
                break;
            case 2: // >
                check = (data > value);
                break;
            case 3: // <
                check = (data < value);
                break;
            case 4: // >=
                check = (data >= value);
                break;
            case 5: // <=
                check = (data <= value);
                break;
        }

        // Kiểm tra kết quả
        if (check)
            printStudentInfo(i);
    }
}

void searchStudent()
{
    cout << "Ban muon tim kiem hoc sinh theo thong tin nao?\n";
    cout << "1: Ten\n";
    cout << "2: Lop\n";
    cout << "3: Dia chi\n";
    cout << "4: Diem Toan\n";
    cout << "5: Diem Van\n";
    cout << "6: Diem Anh\n";
    int byWhat = getIntRange(1, 6);

    if (byWhat <= 3) // Ba thông tin kiểu string
    {
        cout << "Nhap gia tri can tim: ";
        string data; getline(cin, data); getline(cin, data);
        searchStudentByString(byWhat, data);
    }
    else // Ba thông tin kiểu số
    {
        cout << "Nhap gia tri can tim: ";
        double data; cin >> data;

        cout << "Ban muon so sanh nhu the nao?\n";
        cout << "1: =\n";
        cout << "2: >\n";
        cout << "3: <\n";
        cout << "4: >=\n";
        cout << "5: <=\n";
        int compare = getIntRange(1, 5);

        searchStudentByScore(byWhat, data, compare);
    }
}

void saveFile()
{
    if (strcmp(currentFile, "") != 0) // Nếu như có file hiện tại đang được mở
    {
        cout << "Ban muon luu vao file cu, hay tao file moi?\n";
        cout << "1: File cu\n";
        cout << "2: File moi\n";
        int input = getIntRange(1, 2);
        if (input == 2)
        {
            cout << "Hay nhap ten file ban muon tao moi: ";
            cin >> currentFile;
        }
    }
    else
    {
        cout << "Hay nhap ten file ban muon tao moi: ";
        cin >> currentFile;
    }

    // Mở file
    ofstream output;
    output.open(currentFile);

    // Viết ra file phù hợp với tiêu chuẩn
    output << number << '\n';

    for (int i = 1; i <= number; i ++)
    {
        output << encode(allStudent[i].name) << '\n';
        output << encode(allStudent[i].inClass) << '\n';
        output << encode(allStudent[i].address) << '\n';
        output << allStudent[i].math << '\n';
        output << allStudent[i].literature << '\n';
        output << allStudent[i].english << '\n';
    }

    // Đóng file
    output.close();
}

void exitFile()
{
    cout << "Ban co muon luu file hien tai?\n";
    cout << "1: Yes\n";
    cout << "0: No\n";
    int input = getIntRange(0, 1);
    if (input == 1)
        saveFile();

    isEditing = false;
}

int main()
{
    int input;
    while (true)
    {
        if (!isEditing) // Nếu như chưa có file nào được mở
        {
            cout << "Hien chua co file nao duoc mo, ban muon lam gi?\n";
            cout << "1: Tao file moi\n";
            cout << "2: Mo file cu\n";
            cout << "0: Ket thuc chuong trinh\n";

            input = getIntRange(0, 2);

            switch(input)
            {
                case 1: // Tạo file mới
                    newFile();
                    break;

                case 2: // Mở file cũ
                    openFile();
                    break;

                case 0: // Kết thúc chương trình
                    return 0;
            }
        }
        else
        {
            cout << "Ban muon lam gi voi file?\n";
            cout << "1: In ra tat ca hoc sinh\n";
            cout << "2: Loc hoc sinh theo thong tin\n";
            cout << "3: Them hoc sinh moi\n";
            cout << "4: Chinh sua thong tin hoc sinh\n";
            cout << "5: Xoa thong tin hoc sinh\n";
            cout << "6: Luu\n";
            cout << "7: Dong file hien tai\n";

            input = getIntRange(1, 7);

            switch(input)
            {
                case 1: // In ra tất cả học sinh
                    printAllStudent();
                    break;

                case 2: // Lọc học sinh theo thông tin
                    searchStudent();
                    break;

                case 3: // Thêm học sinh mới
                    addStudent();
                    break;

                case 4: // Chỉnh sửa thông tin học sinh
                    editStudent();
                    break;

                case 5: // Xóa thông tin học sinh
                    deleteStudent();
                    break;

                case 6: // Lưu
                    saveFile();
                    break;

                case 7:
                    exitFile();
                    break;
            }
        }
    }
    return 0;
}
