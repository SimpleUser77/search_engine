#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <sstream>
#include <filesystem>
#include "nlohmann/json.hpp"
#include "invertedIndex.h"

using namespace std;

mutex mtx;
ConverterJSON conv;
InvertedIndex idx;
void InvertedIndex::UpdateDocumentBase(const vector<string>& input_docs)
{
  string word;
  this->docs = input_docs;
  this->freq_dictionary.clear();
  for (auto& text : docs)
  {
    istringstream req(text);
    while (!req.eof()) 
    {
      req >> word;
      threads.emplace_back(&InvertedIndex::GetWordCount, ref(idx), word);
      freq_dictionary.insert(make_pair(word,GetWordCount(word)));
    }
  }
  for (int j = 0; j < threads.size(); j++)
  {
      threads[j].join();
  };
  
}

vector<Entry> InvertedIndex::GetWordCount(const string& word)
{ 
  mtx.lock();
  vector<Entry> entry;
  string text;
  for(size_t i = 0; i < docs.size(); i++)
  {
    int count = 0;
    Entry myEntry;
    istringstream req(docs[i]);
    while (!req.eof()) 
    {
      req >> text;
      if (word == text)
      {
        count++;
      }
    }
    if (count > 0)
    {
      myEntry.doc_id = i;
      myEntry.count = count;
      entry.push_back(myEntry);
    }  
  }
  mtx.unlock();
  return entry;
}
