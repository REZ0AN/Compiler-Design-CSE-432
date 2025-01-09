# Lexical Analyzer by Scanning and Tokenizing

This code is like the **"first step"** in building a compiler for a programming language. Imagine you're writing a program, and the compiler needs to understand what you've written so it can turn it into something a computer can execute. The compiler doesn't read your program as a whole—it breaks it down into smaller, understandable pieces. This process is called Lexical Analysis, and that's exactly what this code does.

## Purpose of Lexical Analysis in Compiler Design
The lexical analyzer performs the first phase of compilation. Its goals include:

- **Tokenization**: Breaking the source code into meaningful units (tokens), such as int, main, =, and +.
- **Syntax Simplification**: By converting the code into tokens, subsequent stages of compilation (e.g., parsing) become easier and more efficient.
- **Error Detection**: Identifying invalid tokens or characters early in the compilation process.
- **Classification**: Categorizing the tokens into meaningful types (e.g., keyword, operator, variable).
- **Preprocessing**: Handling low-level constructs such as special characters and whitespace.

## What Does This Program Do?
The program analyzes the contents of an `input.txt` file, classifies the components of the input program, and organizes them into categories using a map of sets. The steps include:

### Step-1 Reading the Input Code

It reads the file `input.txt` line by line and processes it character by character.

```cpp
FILE *ptr;
ptr = fopen("input.txt", "r");
```

### Step-2 Token Extraction

As it reads, it extracts "tokens" (e.g., int, main, +, etc.) by breaking the input at spaces, special characters, or operators.

```cpp
while (fgets(arr, MAX, ptr))
{
    for (i = 0; arr[i] != '\0'; i++)
    {
    char ch = arr[i];

    if (isSpecialCharacter(ch) || isspace(ch)) {
        // handles == operator
        if(ch == '='){
            if(arr[i+1] == '='){
                string specialToken(1, ch);
                specialToken += arr[i+1];
                categorizedTokens["operators"].insert(specialToken);
                i++;
            }
            else{
                string specialToken(1, ch);
                categorizedTokens["operators"].insert(specialToken);
            }
        }
        // handles >> operator
        if(ch == '>'){
                if(arr[i+1] == '>'){
                string specialToken(1, ch);
                specialToken += arr[i+1];
                categorizedTokens["operators"].insert(specialToken);
                i++;
            }
            else{
                string specialToken(1, ch);
                categorizedTokens["operators"].insert(specialToken);
            }
        }
        // handles << operator
        if(ch == '<'){
                if(arr[i+1] == '<'){
                string specialToken(1, ch);
                specialToken += arr[i+1];
                categorizedTokens["operators"].insert(specialToken);
                i++;
            }
            else{
                string specialToken(1, ch);
                categorizedTokens["operators"].insert(specialToken);
            }
        }

        // handles >= <= %= /= *= += -= != operators
        if(ch == '>' || ch == '<' || ch == '%' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '!') {
            if(arr[i+1] == '='){
                string specialToken(1, ch);
                specialToken += arr[i+1];
                categorizedTokens["operators"].insert(specialToken);
                i++;
            }
            else{
                string specialToken(1, ch);
                categorizedTokens["operators"].insert(specialToken);
            }
        }
        // handles && operator
        if(ch == '&'){
            if(arr[i+1] == '&'){
                string specialToken(1, ch);
                specialToken += arr[i+1];
                categorizedTokens["operators"].insert(specialToken);
                i++;
            }
        }
        // handles || operator
        if(ch == '|'){
            if(arr[i+1] == '|'){
                string specialToken(1, ch);
                specialToken += arr[i+1];
                categorizedTokens["operators"].insert(specialToken);
                i++;
            }
        }
        //  handles function
        if(ch == '(') {
            string function;
            for (size_t j = i - 1; j >= 0; --j) {
                if (isspace(arr[j]) || isSpecialCharacter(arr[j]) || arr[j] == '(') {
                    break;
                }
                function = arr[j] + function;
            }
            function = function + "(";
            if (isFunction(function)) {
                categorizedTokens["functions"].insert(function + ")");
            }
        }

        if (!currentToken.empty()) {
            if (isKeyword(currentToken)) {
                categorizedTokens["keywords"].insert(currentToken);
            } else if (isNumber(currentToken)) {
                categorizedTokens["numbers"].insert(currentToken);
            } else if (isIdentifier(currentToken)) {
                categorizedTokens["variables"].insert(currentToken);
            }
            currentToken.clear();
        }

        // Handle special character as a separate token
        if (isSpecialCharacter(ch) && ch != ' ') {
            string specialToken(1, ch);
            if (isOperator(specialToken)) {
                categorizedTokens["operators"].insert(specialToken);
            } else {
                categorizedTokens["others"].insert(specialToken);
            }
        }
    } else {
        currentToken += ch;
    }
}

// Check if the last token is valid
if (!currentToken.empty()) {
    if (isKeyword(currentToken)) {
        categorizedTokens["keywords"].insert(currentToken);
    } else if (isNumber(currentToken)) {
        categorizedTokens["numbers"].insert(currentToken);
    } else if (isIdentifier(currentToken)) {
        categorizedTokens["variables"].insert(currentToken);
    }
}

}
```
####  Step-2.x Token Categorization
For each token:
- **Keywords:** Checks if the token matches a predefined list of language keywords.

```cpp
bool isKeyword(const string &s) {
    set<string> keywords = {"int", "float", "double", "char", "string", "bool", "if", "else", "for", "while","elseif", "do", "return", "break", "continue", "switch", "case", "default", "void", "main"};
    return keywords.find(s) != keywords.end();
}
```
- **Operators:** Identifies operators (e.g., +, ==, &&) using predefined rules.

```cpp
bool isOperator(const string &s) {
    set<string> operators = {"+", "-", "*", "/", "%", "=","==","+=","-=","*=","/=","<",">","<=",">=","&&","||","!","!=","<<",">>", "|", "&"};
    return operators.find(s) != operators.end();
}
```
- **Numbers:** Validates if the token represents a number (integer or floating-point).

```cpp
bool isNumber(const string &s) {
    bool decimal = false;
    for (char ch : s) {
        if (!isdigit(ch)) {
            if (ch == '.' && !decimal) {
                decimal = true;
            } else {
                return false;
            }
        }
    }
    return true;
}
```
- **Identifiers:** Identifies valid variable names that follow the language rules.

```cpp
bool isIdentifier(const string &s) {
    if (isdigit(s[0])) return false;
    for (char ch : s) {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return true;
}
```
- **Functions:** Recognizes function calls (e.g., main()).

```cpp
bool isFunction(const string &s) {
    return s.back() == '(' && s.size() > 1;
}
```
- **Others:** Handles characters that don't fit into any of the above categories.

```cpp
bool isSpecialCharacter(char ch) {
    return !isalnum(ch) && ch != '.' && ch != '_';
}
```
### Step-3 Special Handling

It handles compound operators like ==, <=, &&, ||. Extracts function names and ensures they are not misclassified as variables or keywords.

```cpp
// handles == operator
if(ch == '='){
    if(arr[i+1] == '='){
        string specialToken(1, ch);
        specialToken += arr[i+1];
        categorizedTokens["operators"].insert(specialToken);
        i++;
    }
    else{
        string specialToken(1, ch);
        categorizedTokens["operators"].insert(specialToken);
    }
}
// handles >> operator
if(ch == '>'){
        if(arr[i+1] == '>'){
        string specialToken(1, ch);
        specialToken += arr[i+1];
        categorizedTokens["operators"].insert(specialToken);
        i++;
    }
    else{
        string specialToken(1, ch);
        categorizedTokens["operators"].insert(specialToken);
    }
}
// handles << operator
if(ch == '<'){
        if(arr[i+1] == '<'){
        string specialToken(1, ch);
        specialToken += arr[i+1];
        categorizedTokens["operators"].insert(specialToken);
        i++;
    }
    else{
        string specialToken(1, ch);
        categorizedTokens["operators"].insert(specialToken);
    }
}

// handles >= <= %= /= *= += -= != operators
if(ch == '>' || ch == '<' || ch == '%' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '!') {
    if(arr[i+1] == '='){
        string specialToken(1, ch);
        specialToken += arr[i+1];
        categorizedTokens["operators"].insert(specialToken);
        i++;
    }
    else{
        string specialToken(1, ch);
        categorizedTokens["operators"].insert(specialToken);
    }
}
// handles && operator
if(ch == '&'){
    if(arr[i+1] == '&'){
        string specialToken(1, ch);
        specialToken += arr[i+1];
        categorizedTokens["operators"].insert(specialToken);
        i++;
    }
}
// handles || operator
if(ch == '|'){
    if(arr[i+1] == '|'){
        string specialToken(1, ch);
        specialToken += arr[i+1];
        categorizedTokens["operators"].insert(specialToken);
        i++;
    }
}
//  handles function
if(ch == '(') {
    string function;
    for (size_t j = i - 1; j >= 0; --j) {
        if (isspace(arr[j]) || isSpecialCharacter(arr[j]) || arr[j] == '(') {
            break;
        }
        function = arr[j] + function;
    }
    function = function + "(";
    if (isFunction(function)) {
        categorizedTokens["functions"].insert(function + ")");
    }
}
```

At the end, it prints the categorized tokens, showing the classification of the input program.

```cpp

for (const auto &[category, items] : categorizedTokens) {
    cout << category << ": ";
    for (const string &item : items) {
        if(item == "\n")
            continue;
        cout << item << " ";
    }
    if (!items.empty()) {
        cout << "\b";
    }
    cout << endl;
}
```

## Why Is This Important?

When you write a program, a compiler needs to:
1. **Understand** what each part of your code means.
2. **Break it down** into manageable components.

This program performs the first step in this process. Think of it as separating a sentence into words and identifying which are **nouns**, **verbs**, or **punctuation marks**. Without this, the compiler cannot make sense of the code.

## Why Would You Write This Program?

- To **learn how compilers work**.
- To **create tools** for analyzing or checking code for errors.
- To build a foundation for developing **programming languages**, **compilers**, or **interpreters**.

## Conclusion

This program teaches a machine how to "read" and "understand" programming languages at a basic level. It’s an essential step in how computers process and execute code.

## Example Input and Output

### Input: `input.txt`
```cpp
int inc( int b) {
    return b<<10 + b>>10;
}

int add10( string ss, float i) {
    return ss + (i==0.01? "10" : "0.0");
}
int main() {
    int abc, ab10, carry = 0, under_score;
    int a = 10;
    bool OK = 1;
    int k = inc(a);
    a = a + 10;
    a = a - 10;
    a = a * 10;
    abc = OK | a;
    ab10 = OK & 10 | a;
    if ( ab10 >= abc && !OK || a > k) {
        a += 10;
    } elseif ( abc <= ab10 || OK != false && k < a) {
        ab10 -= 1;
    } else {
        under_score = carry * 10 + a;
    }
    return 0;
}
```
### Output

```bash
functions: add10() inc() main() 
keywords: bool else elseif float if int return string 
numbers: 0 0.0 0.01 1 10 
operators: ! != & && * + += - -= < << <= = == > >= >> | || 
others: " ( ) , : ; ? { } 
variables: OK a ab10 abc b carry false i k ss under_score 
```
