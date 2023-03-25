// ConsoleApplication.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class XInfo
{
public:
    XInfo() {
        x_idx = -1; // x index in sub vector
        x_idx_group = 0; // x belongs to group
    }
public:
    int x_idx, x_idx_group;
};

class NumInfo {
public:

    NumInfo() {
        operator_char = ' ';
        skip_char = '-';
        vec_len = 7;
    }

public:
    char operator_char, skip_char;
    int vec_len;
    XInfo x_info;
};

char GetOperator(char* str, int& initial_idx)
{
    char operator_char = ' ';

    for (int i = initial_idx; i >= 0; --i)
    {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
            operator_char = str[i];

        if (operator_char != ' ' && str[i] == ' ')
        {
            initial_idx = i - 1;
            break;
        }
    }
    return operator_char;
}

void GetNumVec(char* str, int& idx, vector<char>& num, int& x_idx)
{
    int length = strlen(str);
    int j = 0;
    for (int i = idx; i >= 0; --i)
    {
        if (str[i] == ' ')
        {
            idx = i-1;
            break;
        }
        num[j++] = str[i];
        if (str[i] == 'x')
        {
            x_idx = j-1;
        }
    }
}

void GetNum(const vector<char>& num, const char& skip_char, int& val)
{
    int digit = 1;
    for (size_t i = 0; i < num.size(); ++i)
    {
        if (num[i] == skip_char)
            break;

        val += (num[i]-'0') * digit;
        digit *= 10;

    }
}

string GetXNum(int x_idx, int n)
{
    return to_string(int(n * pow(10.0, x_idx)) % 10);
}

bool GetNumVecs(char* str, vector<char>& num1_vec, vector<char>& num2_vec, vector<char>& num3_vec, NumInfo& num_info)
{
    int initial_idx = strlen(str) - 1;

    GetNumVec(str, initial_idx, num3_vec, num_info.x_info.x_idx);
    num_info.x_info.x_idx_group = num_info.x_info.x_idx != -1 ? 2 : num_info.x_info.x_idx_group;
    initial_idx -= 2; // =

    GetNumVec(str, initial_idx, num2_vec, num_info.x_info.x_idx);
    num_info.x_info.x_idx_group = (num_info.x_info.x_idx_group == 0 && num_info.x_info.x_idx != -1) ? 1 : num_info.x_info.x_idx_group;

    num_info.operator_char = GetOperator(str, initial_idx);

    GetNumVec(str, initial_idx, num1_vec, num_info.x_info.x_idx);

    if (num_info.x_info.x_idx == -1)
        return false;

    return true;
}

string GetX(vector<char>& num1_vec, const vector<char>& num2_vec, const vector<char>& num3_vec, const NumInfo& num_info)
{
    string out = "";
    int n1 = 0, n2 = 0, n3 = 0;
    if (num_info.x_info.x_idx_group == 2)
    {
        GetNum(num1_vec, num_info.skip_char, n1);
        GetNum(num2_vec, num_info.skip_char, n2);

        if (num_info.operator_char == '+')
            n3 = n1 + n2;
        else if (num_info.operator_char == '-')
            n3 = n1 - n2;
        else if (num_info.operator_char == '*')
            n3 = n1 * n2;
        else if (num_info.operator_char == '/' && n2 != 0)
            n3 = n1 / n2;
        else
            return out;

        out = GetXNum(num_info.x_info.x_idx, n3);
    }
    else if (num_info.x_info.x_idx_group == 1)
    {
        GetNum(num1_vec, num_info.skip_char, n1);
        GetNum(num3_vec, num_info.skip_char, n3);

        if (num_info.operator_char == '+')
            n2 = n3 - n1;
        else if (num_info.operator_char == '-')
            n2 = n3 + n1;
        else if (num_info.operator_char == '*' && n1 != 0)
            n2 = n3 / n1;
        else if (num_info.operator_char == '/')
            n2 = n1 / n3;
        else
            return out;

        out = GetXNum(num_info.x_info.x_idx, n2);
    }
    else
    {
        GetNum(num2_vec, num_info.skip_char, n2);
        GetNum(num3_vec, num_info.skip_char, n3);

        if (num_info.operator_char == '+')
            n1 = n3 - n2;
        else if (num_info.operator_char == '-')
            n1 = n3 + n2;
        else if (num_info.operator_char == '*' && n2 != 0)
            n1 = n3 / n2;
        else if (num_info.operator_char == '/')
            n1 = n3 * n2;
        else
            return out;

        out = GetXNum(num_info.x_info.x_idx, n1);
    }

    return out;

}

void MissingDigit(char* str)
{
    // n1 + n2 = n3
    printf("%s, x = ", str);

    string out = "";

    NumInfo num_info;
    vector<char> num1_vec(num_info.vec_len, num_info.skip_char);
    vector<char> num2_vec(num_info.vec_len, num_info.skip_char);
    vector<char> num3_vec(num_info.vec_len, num_info.skip_char);
    
    if (false == GetNumVecs(str, num1_vec, num2_vec, num3_vec, num_info))
    {
        return;
    }

    out = GetX(num1_vec, num2_vec, num3_vec, num_info);

    cout << out << endl;
    return;
}

int main()
{
    string str = "4 - 2 = x";
    MissingDigit(&str[0]);

    str = "40 - 2x = 15";
    MissingDigit(&str[0]);

    str = "1x0 * 12 = 1200";
    MissingDigit(&str[0]);
}

