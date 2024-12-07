#include "MyString.h"
using namespace std;

std::ostream& operator<<(std::ostream& os, const MyString& str){
        for (unsigned int i = 0; i < str.length(); ++i){
            os << str.at(i);
        }
        if (cin.fail()) throw std::runtime_error("Reading failed.");
        return os;

    }
MyString::MyString() : str(new char[1]), str_capacity(1), str_size(0) {this->str[0] = '\0';}
MyString::MyString(MyString& strToCopy) : str(nullptr), str_capacity(strToCopy.str_capacity), str_size(strToCopy.str_size){
    // if (str_capacity < 0 || str_size < 0) throw std::runtime_error("Bad input.");
    this->str = new char[str_capacity];
    for (unsigned int i = 0; i < strToCopy.str_size; ++i){
        this->str[i] = (strToCopy.str)[i];
    }
}
MyString::MyString(const char* c_ary) : str(), str_capacity(), str_size(){ // Check for memory leaks
    if (c_ary == nullptr) throw std::runtime_error("C_array is a nullptr.");
    this->str_capacity = 1;
    for (int cap = 0; c_ary[cap] != '\0'; ++cap) this->str_capacity += 1;
    char* newString = new char[this->str_capacity];
    unsigned int i;
    // Potential bug: null terminator in middle of string
    for (i = 0; c_ary[i] != '\0'; ++i){
        newString[i] = c_ary[i];
    }
    newString[i] = '\0';
    this->str_size = i;
    this->str = newString;
}
MyString::~MyString(){
    delete[] this->str;
}
void MyString::resize(size_t n){
    // if (n < 0) throw runtime_error("Resizing to negative value");
    if (n >= this->str_capacity) this->str_capacity = n * 2;
    char* newStr = new char[this->str_capacity + 1];
    for (unsigned int j = this->str_size; j < this->str_capacity; ++j){
        newStr[j] = '\0';
    }
    if (n >= this->str_size){
        for (unsigned int i = 0; i < this->str_size; ++i){
            newStr[i] = (this->str)[i];
        }
    }

    else {
        for (unsigned int i = 0; i < n; ++i){
            newStr[i] = (this->str)[i];
        }
    }
    delete[] this->str;
    this->str = newStr;
    this->str_size = n;
}

size_t MyString::capacity() const noexcept{
    return this->str_capacity;
}
size_t MyString::size() const noexcept{
    return this->str_size;
}
size_t MyString::length() const noexcept{
    return this->str_size;
}
const char* MyString::data() const noexcept{
    return this->str;
}
bool MyString::empty() const noexcept{
    if (str_size == 0) return true;
    return false;
}
const char& MyString::front() const{
    if(empty()) throw runtime_error("Cannot call front on empty strings");
    return this->str[0];
}
const char& MyString::at(size_t n) const{
    if (n >= this->str_size /*|| n < 0*/) throw out_of_range("Accessing an invalid index");
    return this->str[n];
}
void MyString::clear() noexcept{
    for (unsigned int i = 0; i < this->str_capacity; ++i){
        this->str[i] = '\0';
    }
    this->str_size = 0;
}
MyString& MyString::operator=(const MyString& objToCpy) {
    if (this == &objToCpy) return *this;
    this->resize(objToCpy.str_size);
    for (unsigned int i = 0; i < objToCpy.str_size; ++i){
        this->str[i] = objToCpy.str[i];
    }
    return *this;

}
MyString& MyString::operator+=(const MyString& objToAdd){
    if (this->str_size + objToAdd.str_size >= this->str_capacity){
        this->str_capacity = this->str_size + objToAdd.str_size;
        this->str_capacity *= 2;
    }

    char* newStr = new char[this->str_capacity];
    unsigned int i;
    size_t newSize = 0;
    for (i = 0; this->str[i] != '\0'; ++i){
        newStr[i] = this->str[i];
        newSize += 1;

    }
    for (unsigned int j = 0; j < objToAdd.str_size; ++j){
        newStr[i++] = objToAdd.str[j];
        newSize += 1;
    }
    newStr[i] = '\0';
    delete [] this->str;
    this->str = newStr;
    this->str_size = newSize;
    return *this;
}
size_t MyString::find(const MyString& strToLook, size_t st_indx) const noexcept {
    unsigned int length = strToLook.str_size;
    int indexFound = -1;
    if ((int)this->str_size - (int)length < 0) return -1;
    for (unsigned int i = st_indx; i < this->str_size - length; ++i){
        bool foundFlag = true;
        for (unsigned int j = 0; j < length; ++j){
            if (strToLook.str[j] != this->str[i + j]) {foundFlag = false;   break;}
        }
        if (foundFlag){
            indexFound = i;
            break;
            }
    }
    return indexFound;
}
