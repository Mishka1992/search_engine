#ifndef ANYERROR_H
#define ANYERROR_H
#include <exception>
using namespace std;
class NoFile:public exception
{
    const char* what() const noexcept override
    {
        return "config file is missing";
    }
};
class NoFileRequests:public exception
{
    const char* what() const noexcept override
    {
        return "requests file is missing";
    }
};
class NoCorrectJSON:public exception
{
    const char* what() const noexcept override
    {
        return "config file is empty";
    }
};
class FilesExist:public exception
{
    const char* what() const noexcept override
    {
        return "File does not exist";
    }
};
#endif // ANYERROR_H
