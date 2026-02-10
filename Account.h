#ifndef SENECA_ACCOUNT_H_
#define SENECA_ACCOUNT_H_
#include <iostream>

namespace seneca {
   const int NameMaxLen = 30;
   class Account {
      double m_balance{};
      int m_number{};
      char m_holderName[NameMaxLen + 1]{};

      void cpyName(const char* src);
      bool isValidNumber(int number)const;
      void setInvalid();            

   public:
      Account(const char* holderName = nullptr);
      Account(const char* holderName, int number, double balance);
      std::ostream& display()const;

      operator bool() const;
      operator int() const;
      operator double() const;
      operator const char*() const;

      char& operator[](int index);
      const char operator[](int index) const;

      Account& operator=(int number);
      Account& operator=(double balance);

      Account& operator+=(double amount);
      Account& operator-=(double amount);
      Account& operator<<(Account& right);
      Account& operator>>(Account& right);

      bool operator~() const;
      Account& operator++();   Account operator++(int);
      Account& operator--();   Account operator--(int);
   };
}

#endif
