#ifndef EMP_STRING_FUNCS_H
#define EMP_STRING_FUNCS_H
#endif

#include <stdint.h>

// returns true if given char is a lowercase.
int EMP_islwr(const char ch)
{ return (unsigned)(ch - 'a') < 26; }

// returns true if given char is a uppercase.
int EMP_isupr(const char ch)
{ return (unsigned)(ch - 'A') < 26; }

// returns true if given char is an alphabet.
int EMP_isalpha(const char ch)
{ return EMP_islwr(ch) | EMP_isupr(ch); }

// returns true if given char is a number.
int EMP_isnum(const char ch)
{ return (unsigned)(ch - '0') < 10; }

// returns true if given char is a space.
int EMP_isspace(const char ch)
{ return ch == ' ' || ch == '\n' || ch == '\t'; }

// returns the uppercase of given char if it is an alphabet.
char EMP_tolwr(const char ch)
{ return EMP_isupr(ch)? ch + 32: ch; }

// returns the lowercase of given char if it is an alphabet.
char EMP_toupr(const char ch)
{ return EMP_islwr(ch)? ch - 32: ch; }

// NOTE: String must be a c string which ends with '\0'(null) terminate.
//          and given address must not be NULL or 0.

// converts given string to lowercase
char* EMP_strlwr(char* str)
{
    char* iter = str;
    while(*iter != 0){
        if(EMP_isupr(*iter))
            *iter += 32;
        ++iter;    
    }        
    return str;    
}

// converts given string to uppercase.
char* EMP_strupr(char* str)
{
    char* iter = str;
    while(*iter != '\0'){
        if(EMP_islwr(*iter))
            *iter -= 32;
        ++iter;    
    }    
    return str;    
}

// converts given string to capitalize e.g. heLlo -> Hello.
char* EMP_strcapitalize(char* str)
{
    if(EMP_islwr(*str)) *str -= 32;
    EMP_strlwr(str+1);
    return str;    
}

// returns number of characters in given string.
size_t EMP_strlen(const char const* str)
{
    size_t i = 0u;
    while(str[i] != '\0') ++i;
    return i;
}

// returns true if strings are equal.
int EMP_streql(const char* s1, const char* s2)
{
    while(*s1 && *s1 == *s2)
        ++s1, ++s2;
    return *s1 == *s2;
}

// same as EMP_streql but ignores case-sensitivity.
int EMP_strceql(const char* s1, const char* s2)
{
    while(*s1 && EMP_tolwr(*s1) == EMP_tolwr(*s2))
        ++s1, ++s2;
    return *s1 == *s2;
}

// campare equaliy of strings with specified number of chars.
int EMP_strneql(const char* s1, const char* s2, size_t n)
{
    while(n && *s1 && *s1 == *s2){
        ++s1;
        ++s2;
        --n;
    }
    return n == 0;
}

// same as EMP_strneql buts ignores case-sensitivity.
int EMP_strcneql(const char* s1, const char* s2, size_t n)
{
    while(n && *s1 && EMP_tolwr(*s1) == EMP_tolwr(*s2)){
        ++s1;
        ++s2;
        --n;
    }
    return n == 0;
}

// search given sub str in given str.
// if sub str found, returns address of first char else NULL(0)
char* EMP_strstr(const char* str, const char* substr)
{
    size_t slen = EMP_strlen(substr);
    while(*str != '\0'){
        if(*str == *substr){
            if(EMP_strneql(str, substr, slen))
                return str;
        }        
        ++str;
    }
    return 0;
}

// same as EMP_strnceql buts ignores case-sensitivity.
char* EMP_strcstr(const char* str, const char* substr)
{
    size_t slen = EMP_strlen(substr);
    while(*str != '\0'){
        if(*str == *substr){
            if(EMP_strcneql(str, substr, slen))
                return str;
        }        
        ++str;
    }
    return 0;
}

// move the pointer to the first char which is not space.
char* EMP_strlstrip(char* str)
{
    while(EMP_isspace(*str)) ++str;
    return str;
}

// moves the '\0'(null) next to the last char which is not space.
char* EMP_strrstrip(char* str)
{
    char* end = str + EMP_strlen(str) - 1;
    while(EMP_isspace(*end)) --end;
    *(end+1) = '\0';
    
    return str;
}

// do both left and right strip and returns the pointer \
//   which is pointing to the first visible char.
char* EMP_strstrip(char* str)
{
    EMP_strrstrip(str);
    return EMP_strlstrip(str);
} 

// converts given string as number to long int
long EMP_stol(const char* str)
{
    long num = 0l;
    int isplus = 1;
    
    str = EMP_strlstrip(str);
    if(*str == '-' || *str == '+'){
        isplus = *str == '+';
        ++str;
    }
    while(EMP_isnum(*str)){
        num = num * 10l + (*str - '0');
        ++str;
    }
    
    return isplus? num: -num;
}

// converts given string as number to double 
double EMP_stod(const char* str)
{
    double num = 0.0;
    double div;
    
    str = EMP_strlstrip(str);
    if(*str == '-' || *str == '+'){
        div = *str == '-'? -1.0: 1.0;
        ++str;
    }
    while(EMP_isnum(*str)){
        num = num * 10.0 + (*str - '0');
        ++str;
    }
    if(*str == '.'){
        ++str;
        while(EMP_isnum(*str)){
            num = num * 10.0 + (*str - '0');
            div *= 10.0;
            ++str;
        }
    }
    
    return num/div;
}