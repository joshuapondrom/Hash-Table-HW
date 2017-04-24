//Joshua Pondrom
//1510 with Dr. Taylor
#include "abstractstringmap.h"


template<typename T>
class HashNode
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
    
    string getkey() const
    {
      return Key;
    }
    
    T getval() const
    {
      return value;
    }
};

template<typename T>
class MyStringMap: public AbstractStringMap<T>
{
  private:
    int mapsize;
    HashNode<T>** map;

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
    MyStringMap()
    {
      mapsize = 65536;
      map = new HashNode<T>*[mapsize];
      for(int i = 0; i < mapsize; i++)
      {
        map[i] = NULL;
      }
    }

    int size() const
    {
      return mapsize;
    }

    bool isEmpty() const
    {
      for(int i = 0; i < mapsize; i++)
      {
        if(map[i] != NULL)
	{
	  return false;
	}
      }
      return true;
    }
    
    const T& valueOf(const string& key) const throw ( Oops )
    {
      int hashval = hash(key);
      while(map[hashval] != NULL && map[hashval]->getkey() != key)
      {
        hashval++;
	hashval %= mapsize;
      }
      if(map[hashval] == NULL)
      {
        throw(Oops(""));
      }
      else
      {
        cout << "testing seg fault 1" << endl;
        return map[hashval]->getval();
        cout << "testing seg fault 2" << endl;
      }
    }
    
    void clear()
    {
      for(int i = 0; i < mapsize; i++)
      {
        map[i] = NULL;
      }
    }

    void insert(const string& key, const T& val)
    {
      int hashval = hash(key);
      while(map[hashval] != NULL && map[hashval]->getkey() != key)
      {
        hashval++;
	hashval %= mapsize;
      }
      map[hashval] = new HashNode<T>(key,val);
      mapsize++;
    }

    void remove(const string& k)
    {
    }

    void print() const
    {
    }
};
