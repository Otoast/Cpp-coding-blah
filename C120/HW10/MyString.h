
# ifndef MYSTRING_H
# define MYSTRING_H

# include <iostream>
# define string MyString

class MyString{

    public:
        MyString();
        MyString(MyString& strToCopy);
        MyString(const char* c_ary);
        ~MyString();
        void resize(size_t n);
        size_t capacity() const noexcept;
        size_t size() const noexcept;
        size_t length() const noexcept;
        const char* data() const noexcept;
        bool empty() const noexcept;
        const char& front() const;
        const char& at(size_t n) const;
        void clear() noexcept;
        MyString& operator=(const MyString& objToCpy);
        MyString& operator+= (const MyString& objToAdd);
        size_t find (const MyString& strToLook, size_t st_indx = 0)const noexcept;
    private:
        char* str;
        size_t str_capacity;
        size_t str_size;
        


};

std::ostream& operator<<(std::ostream& os, const MyString& str);

#endif