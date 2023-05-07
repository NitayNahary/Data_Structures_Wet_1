//
// Created by nitay on 06/05/2023.
//
#ifndef PAIR_H
#define PAIR_H

template<class T, class K>
struct Pair{
private:
    T m_data;
    K m_key;
public:
    Pair(const T& data,const K& key):  m_data(data), m_key(key){}
    Pair(const Pair<T,K>& p):m_data(p.m_data), m_key(p.m_key){}
    Pair& operator= (const Pair& p) = default;
    ~Pair() = default;
    T& data(){
        return m_data;
    }
    const T& data() const{
        return m_data;
    }
    const K& key() const{
        return m_key;
    }
};
#endif //PAIR_H
