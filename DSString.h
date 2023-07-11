//
// Created by Mark Fontenot on 6/2/2021.
//

#ifndef PA01_SENTIMENT_DSSTRING_H
#define PA01_SENTIMENT_DSSTRING_H

#pragma once
#include <iostream>
#include <cstring>
#include "DSVector.h"

class DSString{

private:

    char* data = nullptr;
    size_t length=0;

    /**
     *  You will need to add some private data members here.
     *  This is up to your discretion.  However, we **strongly**
     *  encourage you to implement your string class as a wrapper
     *  for typical null-terminated c-strings.  In doing this, you
     *  may use c-sting functions in the methods in this class such
     *  as:
     *    * strlen(...)
     *    * strcpy(...)
     *    * strcmp(...)
     *    * strncpy(...)
     *    * strcat(...)
     *    * strncat(...)
     *
     *    A quick google search will return plenty of references on
     *    the c-string functions.
     **/

public:

    /**
     * Constructors and destructor
     *
     * Make sure you do proper memory management.
     **/
    DSString();
    DSString(const char* str);
    DSString(const DSString&);
    ~DSString();

    /**
     * Overloaded Assignment Operators
     */
    DSString& operator= (const char*);
    DSString& operator= (const DSString&);

    /**
     * Overloaded non-modifying string concat
     * @return
     */
    DSString operator+ (const DSString&) const;

    /**
     * Standard relational operators.  Feel free to add additional.
     *
     * Note that for each operator, there are two overloaded versions:
     *    one that takes a DSString object
     *    one that takes a null-terminated c-string
     *
     **/

    bool operator== (const char*) const;
    bool operator== (const DSString&) const;
    bool operator!= (const char*) const;
    bool operator!= (const DSString&) const;
    bool operator> (const DSString&) const;
    bool operator> (const char*) const;
    bool operator< (const DSString&) const;
    bool operator< (const char*) const;
    bool operator>= (const DSString&) const;
    bool operator>= (const char*) const;
    bool operator<= (const DSString&) const;
    bool operator<= (const char*) const;

    /**
     * Subscript operator to access a particular character of a DSString object
     * @return the character requested by reference
     */
    char& operator[] (const int);

    /**
     * getLength() returns the number (count) of characters in the string.
     **/
    [[nodiscard]] size_t getLength() const;

    /**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/
    DSString substring(int start, int numChars);

    /**
     * the c_str function returns a null-terminated c-string holding the
     * contents of this object.
     **/
    [[nodiscard]] char* c_str() const;

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument.
     **/
    friend std::ostream& operator<< (std::ostream&, const DSString&);
    friend std::istream& operator>> (const DSString&, std::istream&);

    size_t find(char* match) const;

    size_t findnth(char* match, size_t n) const;
    //You are free to add more functionality to the class.  For example,
    //you may want to add a find(...) function that will search for a
    //string within a string.  (just an example)
    //
    //Further - you will be able to update and modify this class as the
    //semester progresses.

    DSVector<DSString> tokenize();
    void formatString();
};

//Dr Fontenot gave me permission to look up a hash function to inject into the standard this is what I found on stack overflow

namespace std {
    template <>
    struct hash<DSString>
    {   // hash functor for CString
        size_t operator()(const DSString& _Keyval) const
        {   // hash _Keyval to size_t value by pseudorandomizing transform
            return std::hash<string>()(_Keyval.c_str());
        }
    };
}

#endif //PA01_SENTIMENT_DSSTRING_H
