#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "invertedIndex.h"

using namespace std;

struct RelativeIndex
  {
   size_t doc_id = 0;
   float rank = 0;
   bool operator == (const RelativeIndex& other) const 
    {
     return (doc_id == other.doc_id && rank == other.rank);
    };
  };

class SearchServer
{
 private:
 InvertedIndex* _index;
 public:
 SearchServer(InvertedIndex& idx) :_index(&idx){};// @param idx в конструктор класса передаётся ссылка на класс InvertedIndex, чтобы SearchServer мог узнать частоту слов встречаемых в запросе
 vector<vector<RelativeIndex>> search(const vector<string>& queries_input);// Метод обработки поисковых запросов. @param queries_input поисковые запросы взятые из файла requests.json. @return возвращает отсортированный список релевантных ответов для заданных запросов
};