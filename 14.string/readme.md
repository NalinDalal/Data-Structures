# Strings
A collection of characters

use `cin` for input
`cout` for output

```cpp
string s;
cin>>s;
```

```cpp
string s="hello";
cout<<s;
```

# String Operations

## Concatenation:
```cpp
String a="Hello",b="World";
string c=a+" "+b;
cout<<c<<endl;
```

```bin
Hello World
```

## Length:
```cpp
String s="Hi";
s.len();
//or
s.size();
//or
s.length();
```

## Copying the String
to copy over the string into other string
```cpp
string b=a;
```

## Traversal
Traversal means to go over the string:
```cpp
for(int i=0;i<s.length();i++){
    cout<<s[i]<<" ";
}
```

# Common String Functions

## `substr()`
**Usage:** `str.substr(a, b)`

Returns a substring starting from index `a` of the original string with a length of `b` characters.  
> **Example:**  
> ```cpp
> std::string s = "hello world";
> std::string sub = s.substr(0, 5); // returns "hello"
> ```

Note: If you want to extract up to a certain index `b`, use `str.substr(a, b - a)`.

---

## `find()`
**Usage:** `str.find(substring)` or `str.find(substring, start_pos)`

Searches the string for the first occurrence of the specified substring.  
Returns the index of the first character of the found substring or `std::string::npos` if not found.  
> **Example:**  
> ```cpp
> std::string s = "hello world";
> size_t pos = s.find("world"); // returns 6
> ```

---

## `replace()`
**Usage:** `str.replace(start_pos, length, new_substring)`

Replaces a portion of the string starting at `start_pos` and spanning `length` characters with `new_substring`.  
> **Example:**  
> ```cpp
> std::string s = "hello world";
> s.replace(6, 5, "there"); // s becomes "hello there"
> ```

---

## `erase()`
**Usage:** `str.erase(pos, len)`

Erases `len` characters from the string starting at position `pos`.  
If `len` is not provided, all characters from `pos` to the end are removed.  
> **Example:**  
> ```cpp
> std::string s = "hello world";
> s.erase(5, 1);  // removes the space, s becomes "helloworld"
> s.erase(5);     // removes all characters from index 5 onwards
> ```

---

## `stringstream`
splits the string into words.

`reverse(word.begin(), word.end())` reverses each word separately.

Print each reversed word with a space.
> ```cpp
>     string s = "hello world";
>     stringstream ss(s);
>     string word;
> 
>     while (ss >> word) {
>         reverse(word.begin(), word.end());
>         cout << word << " ";
>     }
> ```


