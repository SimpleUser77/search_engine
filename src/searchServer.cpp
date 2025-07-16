#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <filesystem>
#include "searchServer.h"
#include "invertedIndex.h"

using namespace std;

vector<vector<RelativeIndex>>SearchServer::search(const vector<string>& queries_input)
{
  vector<string> req_words;
  vector<float> relatives;
  vector<RelativeIndex> rel_in;
  vector<vector<RelativeIndex>>vec;
  string word;
  for (auto& request : queries_input)
   {
      float max = 0;
      req_words.clear();
      rel_in.clear();
      relatives.clear();
      RelativeIndex relative;
      istringstream req(request);
      while (!req.eof())
      {
        req >> word;
        req_words.push_back(word);
      }
      for (int i = 0; i < _index->GetSizeVec(); i++)
      {
        float abs = 0;
         for (auto& req_word : req_words)
         {
            for (auto& [key, value] : _index->freq_dictionary)
            {
               if (req_word == key)
               {
                  for (auto& vec : value)
                  {
                     if (vec.doc_id == i)
                      {
                        abs += vec.count;
                        if (abs > max)
                        {
                          max = abs;
                        }
                      }
                  }

               }
            }

         }
         relatives.push_back(abs);
      }
      for (int j = 0; j < relatives.size(); j++)
      {
          if (relatives[j] != 0)
          {
            relative.doc_id = j;
            relative.rank = relatives[j] / max;
            rel_in.push_back(relative);
          }
      }
      vec.push_back(rel_in);
   }
   return vec;
}