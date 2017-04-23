//Joshua Pondrom
//1510 with Dr. Taylor
#include "abstractstringmap.h"

class HashNode<T>
{
  private:
    string Key;
    T value;
  public:
    HashNode(string K, T v)
    {
      Key = K;
      value = v;
    }
}

template<class T>
class MyStringMap<T>: public AbstractStringMap<T>
{
  private:
    int mapsize;


    int hash(const string &s) const
    {
      int total = 0;
      for(int i = 0; i < s.length(); i++)
      {
        total += s[i];
      }
      return (total % mapsize);
    }
  public:
    int size() const
    {
      return mapsize;
    }

    bool isEmpty() const
    {
      if(mapsize == 0)
        return true;
      return false;
    }
    
    const T& valueOf(const string& key) const throw ( Oops )
    {
    }
    
    void clear()
    {
    }

    void insert(const string& key, const T& val)
    {
    }

    void remove(const string& k)
    {
    }

    void print() const
    {
    }
};
