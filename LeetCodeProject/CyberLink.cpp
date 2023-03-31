#include "CyberLink.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <stack>

#pragma region Missing Digit
class XInfo
{
public:
    XInfo() {
        
        x_idx = -1; // x index in sub vector ex. "1234x", x_idx = 0 || "x2345", x_idx = 4
        x_idx_group = 0; // x belongs to group
    }
public:
    int x_idx, x_idx_group;
};

class NumInfo {
public:

    NumInfo() {
        // num1_str operator_char num2_str '=' num3_str
        operator_char = ' ';
        num1_str = "";
        num2_str = "";
        num3_str = "";
    }

public:

    char operator_char;
    string num1_str, num2_str, num3_str;

    XInfo x_info;
};

class MissingDigitClass
{
public:

    // num1 * num2  = num3
    // 234 * 45 = 1053x
    string GetXStr(const string& str)
    {
        string out = "0";
        NumInfo num_info;
        
        // Split str & Get x position (зя)
        if (false == _SetNumInfo_2(str, num_info))
        {
            return out;
        }

        int nx = 0;
        if (false == _GetNxStr(num_info, nx))
        {
            return out;
        }

        // 234 * 45 = 105x0
        // x_idx = 1
        // 105x --> x
        return to_string(int(nx * pow(10.0, -num_info.x_info.x_idx)) % 10);
    }

private:

#pragma region Set Missing Digit Info
    // _SetNumInfo : 
    // 1. Split str
    // 2. Get x position
    bool _SetNumInfo(const string& str, NumInfo& num_info)
    {
        vector<string> vec;
        _SplitStr(vec, str, ' ');

        num_info.num1_str = vec[0];
        num_info.operator_char = vec[1][0];
        num_info.num2_str = vec[2];
        num_info.num3_str = vec[4];

        if (false == _Get_x_position(vec, num_info))
        {
            return false;
        }
        return true;
    }
    void _SplitStr(vector<string>& out, string const& str, const char& delim)
    {
        stringstream ss(str);

        string s;
        while (getline(ss, s, delim)) {
            out.push_back(s);
        }
    }
    bool _Get_x_position(const vector<string>& vec, NumInfo& num_info)
    {
        for (int i = 0; i < vec.size(); ++i)
        {
            if (i == 1 || i == 3)
                continue;

            if (vec[i].find('x') != std::string::npos)
            {
                num_info.x_info.x_idx_group = i;
                for (size_t j = 0; j < vec[i].size(); ++j)
                {
                    if (vec[i][j] == 'x')
                    {
                        num_info.x_info.x_idx = vec[i].size() - j - 1;
                        return true;
                    }

                }
            }
        }
        return false;
    }
#pragma endregion

    bool _SetNumInfo_2(const string& str, NumInfo& num_info)
    {
        // num1 * num2 = num3 -> "234 * 45 = 1053x"
        int initial_idx = str.size() - 1;

        // num3
        _GetNumStr(str, num_info.num3_str, num_info.operator_char, num_info.x_info.x_idx, initial_idx);
        num_info.x_info.x_idx_group = num_info.x_info.x_idx != -1 ? 2 : num_info.x_info.x_idx_group;

        // num2
        _GetNumStr(str, num_info.num2_str, num_info.operator_char, num_info.x_info.x_idx, initial_idx);
        num_info.x_info.x_idx_group = (num_info.x_info.x_idx_group == 0 && num_info.x_info.x_idx != -1) ? 1 : num_info.x_info.x_idx_group;

        // num1
        _GetNumStr(str, num_info.num1_str, num_info.operator_char, num_info.x_info.x_idx, initial_idx);
        if (num_info.x_info.x_idx == -1)
            return false;


        return true;
    }

    bool _GetNumStr(const string& str, string& num_str, char& operator_char, int& x_idx, int& initial_idx)
    {
        int j = 0;
        for (int i = initial_idx; i >= 0; --i)
        {
            if (str[i] == ' ')
            {
                continue;
            }
            else if (str[i] == '=')
            {
                initial_idx = i - 1;
                break;
            }
            else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
            {
                operator_char = str[i];
                initial_idx = i - 1;
                break;
            }

            num_str = str[i] + num_str;
            j++;
            if (str[i] == 'x')
            {
                if (x_idx != -1)
                    return false;
                x_idx = j - 1;
            }
        }
        return true;
    }
 

    bool _GetNxStr(const NumInfo& num_info, int& nx)
    {
        int n1 = 0, n2 = 0, n3 = 0;
        nx = 0;

        // n1 + n2 = ?
        if (num_info.x_info.x_idx_group == 2)
        {
            n1 = stoi(num_info.num1_str);
            n2 = stoi(num_info.num2_str);

            if (num_info.operator_char == '+')
                nx = n1 + n2;
            else if (num_info.operator_char == '-')
                nx = n1 - n2;
            else if (num_info.operator_char == '*')
                nx = n1 * n2;
            else if (num_info.operator_char == '/' && n2 != 0)
                nx = n1 / n2;
            else
                return false;
        }
        // n1 + ? = n3
        else if (num_info.x_info.x_idx_group == 1)
        {
            n1 = stoi(num_info.num1_str);
            n3 = stoi(num_info.num3_str);

            if (num_info.operator_char == '+')
                nx = n3 - n1;
            else if (num_info.operator_char == '-')
                nx = n1 - n3;
            else if (num_info.operator_char == '*' && n1 != 0)
                nx = n3 / n1;
            else if (num_info.operator_char == '/' && n3 != 0)
                nx = n1 / n3;
            else
                return false;
        }
        // ? + n2 = n3
        else
        {
            n2 = stoi(num_info.num2_str);
            n3 = stoi(num_info.num3_str);

            if (num_info.operator_char == '+')
                nx = n3 - n2;
            else if (num_info.operator_char == '-')
                nx = n3 + n2;
            else if (num_info.operator_char == '*' && n2 != 0)
                nx = n3 / n2;
            else if (num_info.operator_char == '/')
                nx = n3 * n2;
            else
                return false;
        }
        return true;
    }
};

string MissingDigit(string str)
{
    MissingDigitClass mdc = MissingDigitClass();
    return mdc.GetXStr(str);
}
#pragma endregion

#pragma region HTML Elements
string GetTag(const string& str, int& i)
{
    int left_idx = i;
    if ((i + 1) < str.size() && str[i+1] == '/')
    {
        left_idx = ++i;
    }
    while ((i + 1) < str.size() && str[++i] != '>')
    {
    }

    if (i <= 0)
        return "false";

    string left_tag = str.substr(left_idx+1, i - left_idx-1);

    return left_tag;
}
string HTMLElements(string str) 
{
    stack<string> left_tags;

    for (int i = 0; i < str.size(); ++i)
    {
        char tmpChar = str[i];
        char tmpChar1 = str[i+1];
        if ((i + 1) < str.size() && str[i] == '<' && str[i + 1] != '/')
        {
            string left_tag = GetTag(str, i);

            left_tags.push(left_tag);
        }
        else if ((i + 1) < str.size() && str[i] == '<' && str[i + 1] == '/')
        {
            if (left_tags.empty())
                return "false";

            string right_tag = GetTag(str, i);
            if (left_tags.top() == right_tag)
                left_tags.pop();
            else
                return left_tags.top();
        }
    }

    if (!left_tags.empty())
        return left_tags.top();


    return "true";
}
#pragma endregion

#pragma region Element Merger
int ElementMerger(int arr[], int arrLength)
{
    if (arrLength <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < arrLength; ++i)
    {
        for (size_t j = 0; j < arrLength-i-1; ++j)
        {
            int tmp = arr[j + 1] - arr[j];
            arr[j] = abs(arr[j+1] - arr[j]);
        }
    }

    return arr[0];
}
#pragma endregion
