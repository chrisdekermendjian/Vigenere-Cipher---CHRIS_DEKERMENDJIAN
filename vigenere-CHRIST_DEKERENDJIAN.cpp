#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

string toUpperCase(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] = text[i] - 'a' + 'A';
        }
    }

    return text;
}

bool validKey(string key)
{
    if (key.empty())
    {
        return false;
    }

    for (int i = 0; i < key.length(); i++)
    {
        if (key[i] < 'A' || key[i] > 'Z')
        {
            return false;
        }
    }

    return true;
}

bool validText(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == '~')
        {
            return false;
        }
    }

    return true;
}

string encryptVigenere(string plaintext, string key)
{
    string ciphertext = "";
    int keyIndex = 0;

    for (int i = 0; i < plaintext.length(); i++)
    {
        char current = plaintext[i];

        if (current >= 'A' && current <= 'Z')
        {
            int p = current - 'A';
            int k = key[keyIndex % key.length()] - 'A';
            int c = (p + k) % 26;

            ciphertext += char('A' + c);
            keyIndex++;
        }
        else
        {
            ciphertext += current;
        }
    }

    return ciphertext;
}

string decryptVigenere(string ciphertext, string key)
{
    string plaintext = "";
    int keyIndex = 0;

    for (int i = 0; i < ciphertext.length(); i++)
    {
        char current = ciphertext[i];

        if (current >= 'A' && current <= 'Z')
        {
            int c = current - 'A';
            int k = key[keyIndex % key.length()] - 'A';
            int p = (c - k + 26) % 26;

            plaintext += char('A' + p);
            keyIndex++;
        }
        else
        {
            plaintext += current;
        }
    }

    return plaintext;
}

bool validPermutation(vector<int> key, int size)
{
    if (key.size() != size)
    {
        return false;
    }

    vector<bool> seen(size, false);

    for (int i = 0; i < key.size(); i++)
    {
        if (key[i] < 1 || key[i] > size)
        {
            return false;
        }

        if (seen[key[i] - 1])
        {
            return false;
        }

        seen[key[i] - 1] = true;
    }

    return true;
}

vector<int> readPermutation(int size, string name)
{
    vector<int> key;

    while (true)
    {
        cout << "Enter " << name << " permutation (" << size
             << " numbers from 1 to " << size << "): ";

        string line;
        getline(cin, line);

        stringstream ss(line);
        int value;

        key.clear();

        while (ss >> value)
        {
            key.push_back(value);
        }

        if (validPermutation(key, size))
        {
            return key;
        }

        cout << "Invalid permutation. Each number from 1 to "
             << size << " must appear exactly once.\n";
    }
}

string padText(string text, int cols)
{
    while (text.length() % cols != 0)
    {
        text += '~';
    }

    return text;
}

vector<vector<char>> createGrid(string text, int rows, int cols)
{
    vector<vector<char>> grid(rows, vector<char>(cols));
    int index = 0;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c] = text[index++];
        }
    }

    return grid;
}

string gridToString(vector<vector<char>> grid)
{
    string result = "";

    for (int r = 0; r < grid.size(); r++)
    {
        for (int c = 0; c < grid[r].size(); c++)
        {
            result += grid[r][c];
        }
    }

    return result;
}

string encryptColumnPermutation(string input, int cols, vector<int> key)
{
    int rows = input.length() / cols;

    vector<vector<char>> grid = createGrid(input, rows, cols);
    vector<vector<char>> result(rows, vector<char>(cols));

    for (int originalCol = 0; originalCol < cols; originalCol++)
    {
        int newCol = key[originalCol] - 1;

        for (int r = 0; r < rows; r++)
        {
            result[r][newCol] = grid[r][originalCol];
        }
    }

    return gridToString(result);
}

string decryptColumnPermutation(string input, int cols, vector<int> key)
{
    int rows = input.length() / cols;

    vector<vector<char>> grid = createGrid(input, rows, cols);
    vector<vector<char>> result(rows, vector<char>(cols));

    for (int originalCol = 0; originalCol < cols; originalCol++)
    {
        int newCol = key[originalCol] - 1;

        for (int r = 0; r < rows; r++)
        {
            result[r][originalCol] = grid[r][newCol];
        }
    }

    return gridToString(result);
}

string encryptRowPermutation(string input, int cols, vector<int> key)
{
    int rows = input.length() / cols;

    vector<vector<char>> grid = createGrid(input, rows, cols);
    vector<vector<char>> result(rows, vector<char>(cols));

    for (int originalRow = 0; originalRow < rows; originalRow++)
    {
        int newRow = key[originalRow] - 1;

        for (int c = 0; c < cols; c++)
        {
            result[newRow][c] = grid[originalRow][c];
        }
    }

    return gridToString(result);
}

string decryptRowPermutation(string input, int cols, vector<int> key)
{
    int rows = input.length() / cols;

    vector<vector<char>> grid = createGrid(input, rows, cols);
    vector<vector<char>> result(rows, vector<char>(cols));

    for (int originalRow = 0; originalRow < rows; originalRow++)
    {
        int newRow = key[originalRow] - 1;

        for (int c = 0; c < cols; c++)
        {
            result[originalRow][c] = grid[newRow][c];
        }
    }

    return gridToString(result);
}

int main()
{
    cout << "===== VIGENERE CIPHER SYSTEM =====\n\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";

    int mode;

    if (!(cin >> mode))
    {
        cout << "Invalid input.\n";
        return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (mode == 3)
    {
        cout << "Program ended.\n";
        return 0;
    }

    if (mode != 1 && mode != 2)
    {
        cout << "Invalid option.\n";
        return 1;
    }

    string input;
    string key;

    cout << "Enter text: ";
    getline(cin, input);

    input = toUpperCase(input);

    if (!validText(input))
    {
        cout << "The character '~' is reserved for padding.\n";
        return 1;
    }

    cout << "Enter Vigenere key: ";
    getline(cin, key);

    key = toUpperCase(key);

    if (!validKey(key))
    {
        cout << "Invalid key. Use letters A-Z only.\n";
        return 1;
    }

    cout << "\nChoose permutation mode:\n";
    cout << "0. Vigenere only\n";
    cout << "1. Vigenere + column permutation\n";
    cout << "2. Vigenere + row permutation\n";
    cout << "3. Vigenere + column + row permutations\n";
    cout << "4. Vigenere + row + column permutations\n";
    cout << "Enter choice: ";

    int permutationMode;

    if (!(cin >> permutationMode))
    {
        cout << "Invalid input.\n";
        return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (permutationMode < 0 || permutationMode > 4)
    {
        cout << "Invalid permutation mode.\n";
        return 1;
    }

    int cols = 1;
    int originalLength = 0;
    int rows = 0;

    vector<int> columnKey;
    vector<int> rowKey;

    if (permutationMode != 0)
    {
        if (mode == 2)
        {
            cout << "Enter the original Vigenere output length: ";

            if (!(cin >> originalLength) || originalLength < 1)
            {
                cout << "Invalid original length.\n";
                return 1;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (input.length() < originalLength)
            {
                cout << "Ciphertext is shorter than the original length.\n";
                return 1;
            }

            if (input.length() % 2 != 0)
            {
                cout << "Invalid padded ciphertext length.\n";
                return 1;
            }
        }
    }

    if (permutationMode != 0)
    {
        cout << "Enter number of columns: ";

        if (!(cin >> cols) || cols < 2)
        {
            cout << "Invalid number of columns. Use at least 2.\n";
            return 1;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (mode == 2 && input.length() % cols != 0)
        {
            cout << "Ciphertext length must be divisible by the number of columns.\n";
            return 1;
        }
    }

    if (mode == 1)
    {
        string result = encryptVigenere(input, key);

        cout << "\nAfter Vigenere: " << result << endl;

        if (permutationMode != 0)
        {
            originalLength = result.length();
            result = padText(result, cols);
            rows = result.length() / cols;

            if (permutationMode == 1 ||
                permutationMode == 3 ||
                permutationMode == 4)
            {
                columnKey = readPermutation(cols, "column");
            }

            if (permutationMode == 2 ||
                permutationMode == 3 ||
                permutationMode == 4)
            {
                rowKey = readPermutation(rows, "row");
            }

            if (permutationMode == 1)
            {
                result = encryptColumnPermutation(result, cols, columnKey);
                cout << "After column permutation: " << result << endl;
            }
            else if (permutationMode == 2)
            {
                result = encryptRowPermutation(result, cols, rowKey);
                cout << "After row permutation: " << result << endl;
            }
            else if (permutationMode == 3)
            {
                result = encryptColumnPermutation(result, cols, columnKey);
                cout << "After column permutation: " << result << endl;

                result = encryptRowPermutation(result, cols, rowKey);
                cout << "After row permutation: " << result << endl;
            }
            else if (permutationMode == 4)
            {
                result = encryptRowPermutation(result, cols, rowKey);
                cout << "After row permutation: " << result << endl;

                result = encryptColumnPermutation(result, cols, columnKey);
                cout << "After column permutation: " << result << endl;
            }

            cout << "Original Vigenere output length: "
                 << originalLength << endl;
        }

        cout << "\nFinal ciphertext: " << result << endl;
    }
    else
    {
        string result = input;

        if (permutationMode != 0)
        {
            if (originalLength < 1 || originalLength > result.length())
            {
                cout << "Invalid original length.\n";
                return 1;
            }

            if (result.length() % cols != 0)
            {
                cout << "Invalid ciphertext length for this grid.\n";
                return 1;
            }

            rows = result.length() / cols;

            if (permutationMode == 1 ||
                permutationMode == 3 ||
                permutationMode == 4)
            {
                columnKey = readPermutation(cols, "column");
            }

            if (permutationMode == 2 ||
                permutationMode == 3 ||
                permutationMode == 4)
            {
                rowKey = readPermutation(rows, "row");
            }

            if (permutationMode == 1)
            {
                result = decryptColumnPermutation(result, cols, columnKey);
            }
            else if (permutationMode == 2)
            {
                result = decryptRowPermutation(result, cols, rowKey);
            }
            else if (permutationMode == 3)
            {
                result = decryptRowPermutation(result, cols, rowKey);
                result = decryptColumnPermutation(result, cols, columnKey);
            }
            else if (permutationMode == 4)
            {
                result = decryptColumnPermutation(result, cols, columnKey);
                result = decryptRowPermutation(result, cols, rowKey);
            }

            result = result.substr(0, originalLength);
        }

        result = decryptVigenere(result, key);

        cout << "\nDecrypted plaintext: " << result << endl;
    }

    return 0;
}