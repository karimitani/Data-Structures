class MyString {
  char * _s;
  
 protected:
  
  // My own implementation of strlen
  int slength(const char *s) const;

  // Initialize _s. Allocate memory for _s and copy s into _s
  void initialize(const char * s);
  
 public:
  // Create a MyString from a C string
  MyString(const char * s);
  
  // Create a MyString from a copy of another string
  MyString(const MyString &s);

  // Create a MyString with an empty string
  MyString();

  MyString & operator = (const MyString & other);

  MyString substring(int i, int n);

  // Remove at most n chars starting at location i
  void remove(int i, int n);

  // Return true if strings "this" and s are equal
  bool operator == (const MyString &s);

  // Return character at position i. Return '\0' if out of bounds.
  char operator [](int i);

  // Return C representation of string
  const char * cStr();

  // Get string length of this string.
  int length() const;
  
  // Destructor. Deallocate the space used by _s
  ~MyString();

  // Needed to allow the operator + to use the MyString member variables.
  friend MyString operator + (const MyString &s1, const MyString &s2);
};

// Concatanate two strings (non member method)
MyString operator + (const MyString &s1, const MyString &s2);
