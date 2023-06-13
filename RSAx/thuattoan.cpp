#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

// Hàm kiểm tra tính nguyên tố của một số
bool isPrime(long long n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Hàm tạo số nguyên tố ngẫu nhiên trong khoảng [min, max]
long long generateRandomPrime(long long min, long long max) {
    long long num;
    do {
        num = min + rand() % (max - min + 1);
    } while (!isPrime(num));

    return num;
}

// Hàm tính gcd của hai số a và b
long long gcd(long long a, long long b) {

    if (b == 0) {
        return a;
    }
    else
        return gcd(b, a % b);
}

// Hàm tính phần tử nghịch đảo modulo
long ModInverse(long a, long m)
{
    long m0 = m;
    long y = 0;
    long x = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
        long q = a / m;
        long t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}
long CalculatePrivateKey(long publicKey, long phi)
{
    long privateKey = ModInverse(publicKey, phi);
    return privateKey;
}

// Hàm chuyển đổi chuỗi kí tự thành byte code
vector<long long> stringToByteCode(const string str)
{
    vector<long long> byteCode;
    for (char c : str)
    {
        for (int i = 0; i < sizeof(c); i++)
        {
            byteCode.push_back(static_cast<long long>((c >> (8 * i)) & 0xFF));
        }
    }
    return byteCode;
}

// Hàm tính công thức bình phương và nhân modulo
long long power_modulo(long long x, long long b, long long n)
{
    if (b == 0)
    {
        return 1;
    }
    if (b == 1)
    {
        return x % n;
    }
    long long t = power_modulo(x, b / 2, n);
    t = (t * t) % n;
    if (b % 2 == 0)
        return t;
    else
        return ((x % n) * t) % n;
}

// Hàm mã hóa RSA
vector<long long> encryptRSA(const vector<long long>& byteCode, long long b, long long n)
{
    vector<long long> banma;
    for (int i = 0; i <= byteCode.size() - 1; i++)
    {
        long long encryptedValue = power_modulo(byteCode[i], b, n);
        banma.emplace_back(encryptedValue);
    }

    return banma;
}
// Hàm giai ma RSA
vector<long long> decryptRSA(const vector<long long>& banma, long long a, long long n)
{
    vector<long long> banro;
    for (int i = 0; i <= banma.size() - 1; i++)
    {
        long long decryptedValue = power_modulo(banma[i], a, n);
        banro.emplace_back(decryptedValue);
    }

    return banro;
}



int main() {
    srand(time(0));
    long long p = generateRandomPrime(10000, 100000); // tao p ngau nhien
    long long q = generateRandomPrime(10000, 100000); // tao q ngau nhien
    cout << p << endl;
    cout << q << endl;

    string str;
    cout << "nhap chuoi can ma hoa: ";
    getline(cin, str);  //chuoi can ma hoa 

    vector<long long> byteCode = stringToByteCode(str);
    cout << "do dai bytecode= " << byteCode.size() << endl;
    cout << "gia tri bytecode: ";
    for (long long byte : byteCode)
    {
        cout << static_cast<int>(byte) << " ";
    }
    cout << endl;

    long long  n = p * q;       // tinh n
    cout << "n= " << n << endl;

    long long phiN = (p - 1) * (q - 1);   // tinh phiN 
    cout << "phiN= " << phiN << endl;

    long long b;
    do {
        b = generateRandomPrime(2, phiN);     // chon b 
    } while (gcd(b, phiN) != 1);
    cout << "b= " << b << endl;

    long long a = CalculatePrivateKey(b, phiN);  // tinh a
    cout << "a= " << a << endl;

    // chuoi sau khi duoc ma hoa	
    vector<long long> banma = encryptRSA(byteCode, b, n);
    for (long long byte : banma)
    {
        cout << static_cast<long long>(byte) << " ";
    }
    cout << endl;
    // chuoi sau khi duoc giai ma
    vector<long long> banro = decryptRSA(banma, a, n);
    for (long long byte : banro)
    {
        cout << static_cast<char>(byte);
    }



    return 0;

}