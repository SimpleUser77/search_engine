#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <map>
#include "converterJSON.h"

using namespace std;

struct Entry
  {
    size_t doc_id;
    size_t count = 0;
   bool operator ==(const Entry& other) const 
    {
      return (doc_id == other.doc_id && count == other.count);
    };
  };

class InvertedIndex
{
  private:
   vector<string> docs;
  public:
   InvertedIndex() = default;
   vector<thread> threads;
   map<string, vector<Entry>> freq_dictionary; 
   string GetText(int num)
   {
    string word;
    word = docs[num];
    return word;
   }
   int GetSizeVec()
   {
    return docs.size(); 
   }
   void UpdateDocumentBase(const vector<string>& input_docs) ;//Обновить или заполнить базу документов, по которой будем совершать поиск. "@param input_docs" содержимое документов
   vector<Entry> GetWordCount(const string& word); //*Метод определяет количество вхождений слова word в загруженной базе документов. @param word слово, частоту вхождений которого необходимо определить. @return возвращает подготовленный список с частотой слов*/
};