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
    
    string getkey()
    {
      return Key;
    }
    
    T& getval()
    {
      return value;
    }

    void setval(T val)
    {
      value = val;
    }
};

template<typename T>
class MyStringMap: public AbstractStringMap<T>
{
  private:
    int mapsize;
    HashNode<T>** map;
    int contents;

    int hash(const string &s) const
    {
      int total = 0;
      for(unsigned int i = 0; i < s.length(); i++)
      {
        total += s[i];
      }
      return (total % mapsize);
    }

    void grow()
    {
      HashNode<T>** newmap;
      mapsize *= 2;
      newmap = new HashNode<T>*[mapsize];
      for(int i = 0; i < mapsize; i++)
      {
        newmap[i] = NULL;
      }
      for(int i = 0; i < mapsize/2; i++)
      {
        if(map[i] != NULL)
	{
	  newmap[hash(map[i]->getkey())] = new HashNode<T>(map[i]->getkey(),map[i]->getval());
	  delete map[i];
	  map[i] = NULL;
	}
      }
      mapsize /= 2;
      clear();
      mapsize *= 2;
      delete[] map;
      map = newmap;
    }

  public:
    MyStringMap()
    {
      mapsize = 4096;
      contents = 0;
      map = new HashNode<T>*[mapsize];
      for(int i = 0; i < mapsize; i++)
      {
        map[i] = NULL;
      }
    }

    ~MyStringMap()
    {
      for(int i = 0; i < mapsize; i++)
      {
        if(map[i] != NULL)
	{
	  delete map[i];
	  map[i] = NULL;
	}
      }
      delete[] map;
    }

    int size() const
    {
      return contents;
    }

    bool isEmpty() const
    {
      if(contents)
	return false;
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
        throw(Oops("Key Not Found!!"));
      }
      else
      {
        return map[hashval]->getval();
      }
    }
    
    void clear()
    {
      for(int i = 0; i < mapsize; i++)
      {
        if(map[i] != NULL)
	{
	  delete map[i];
	  map[i] = NULL;
        }
      }
      contents = 0;
    }

    void insert(const string& key, const T& val)
    {
      if(contents > (mapsize * .5))
      {
        grow();
      }
      int hashval = hash(key);
      while(map[hashval] != NULL && map[hashval]->getkey() != key)
      {
        hashval++;
	hashval %= mapsize;
      }
      if(map[hashval] != NULL && map[hashval]->getkey() == key)
      {
        delete map[hashval];
	map[hashval] = new HashNode<T>(key,val);
      }
      else
      {
        map[hashval] = new HashNode<T>(key,val);
        contents++;
      }
    }

    void remove(const string& k)
    {
      int hashval = hash(k);
      while(map[hashval] != NULL && map[hashval]->getkey() != k)
      {
        hashval++;
	hashval %= mapsize;
      }
      delete map[hashval];
      map[hashval] = NULL;
      contents--;
    }

    void print() const
    {
      for(int i = 0; i < mapsize; i++)
      {
        if(map[i] != NULL)
	{
          cout << "< ";
	  cout << map[i]->getkey() << ", ";
          cout << map[i]->getval();
          cout << " >" << endl;
	}
      }
    }
};
