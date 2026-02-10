#include <iostream>
#include "Account.h"

using namespace std;
namespace seneca {
 

   void Account::cpyName(const char* src) {
      int i;
      for (i = 0; src && src[i] && i < NameMaxLen; i++) {
         m_holderName[i] = src[i];
      }
      m_holderName[i] = char(0);
   }
   bool Account::isValidNumber(int number) const {
      return number >= 10000 && number <= 99999;
   }
   Account::Account(const char* holderName) {  
      m_holderName[0] = char(0);
      m_number = -1;
      m_balance = 0.0;
      if (holderName && holderName[0]) {
         cpyName(holderName);
         m_number = 0;
      }
   }
   Account::Account(const char* holderName, int number, double balance ) {
      m_holderName[0] = char(0);
      m_number = -1;
      m_balance = 0.0;
      if (holderName && holderName[0] && isValidNumber(number)
         && balance > 0) {
         cpyName(holderName);
         m_number = number;
         m_balance = balance;
      }
   }
   std::ostream& Account::display() const{
      if (*this) {  
         cout << " ";
         cout.fill(' ');
         cout.width(NameMaxLen);
         cout.setf(ios::left);
         cout << m_holderName;
         cout.unsetf(ios::left);
         cout << " | ";
         cout << m_number;
         cout << " | ";
         cout.width(12);
         cout.precision(2);
         cout.setf(ios::right);
         cout.setf(ios::fixed);
         cout << m_balance;
         cout.unsetf(ios::right);
         cout << " ";
      }
      else if(~*this) {
         cout << " ";
         cout.fill(' ');
         cout.width(30);
         cout.setf(ios::left);
         cout << m_holderName;
         cout.unsetf(ios::left);
         cout << " |  NEW  |         0.00 ";
      }
      else {
         cout << " Bad Account                    | ----- | ------------ ";
      }
      return cout;
   }

   void Account::setInvalid() {
      m_number = -1;
      m_balance = 0.0;
      m_holderName[0] = char(0);
   }

   Account::operator bool() const {
      return m_holderName[0] && isValidNumber(m_number) && m_balance >= 0.0;
   }

   Account::operator int() const {
      return m_number;
   }

   Account::operator double() const {
      return m_balance;
   }

   Account::operator const char*() const {
      return m_holderName;
   }

  char& Account::operator[](int index) {
      int len = 0;
      while (m_holderName[len]) len++;
      if (index < 0) index = -index;
      return m_holderName[len ? index % len : 0];
   }

  const char Account::operator[](int index) const {
      int len = 0;
      while (m_holderName[len]) len++;
      if (index < 0) index = -index;
      return m_holderName[len ? index % len : 0];
   }

   Account& Account::operator=(int number) {
      if (~(*this))
         isValidNumber(number) ? m_number = number : setInvalid();
      return *this;
   }

   Account& Account::operator=(double balance) {
      return balance >= 0 ? (m_balance = balance, *this)
                          : (setInvalid(), *this);
   }

   Account& Account::operator+=(double amount) {
      if (*this && amount >= 0) m_balance += amount;
      return *this;
   }

   Account& Account::operator-=(double amount) {
      if (*this && amount >= 0 && m_balance >= amount)
         m_balance -= amount;
      return *this;
   }

   Account& Account::operator<<(Account& right) {
      if (this != &right && *this && right)
         m_balance += right.m_balance, right.m_balance = 0;
      return *this;
   }

   Account& Account::operator>>(Account& right) {
      if (this != &right && *this && right)
         right.m_balance += m_balance, m_balance = 0;
      return *this;
   }

   bool Account::operator~() const {
      return m_number == 0 && m_holderName[0];
   }

   Account& Account::operator++() {
      if (*this) m_balance += 1;
      return *this;
   }

   Account Account::operator++(int) {
      Account old = *this;
      ++(*this);
      return old;
   }

   Account& Account::operator--() {
      if (*this && m_balance >= 1) m_balance -= 1;
      return *this;
   }

   Account Account::operator--(int) {
      Account old = *this;
      --(*this);
      return old;
   }


   
}
