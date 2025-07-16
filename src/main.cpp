#include <iostream>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
#include "converterJSON.h"
#include "searchServer.h"

using namespace std;

 int main() 
{
  setlocale(LC_ALL, "ru");
  ConverterJSON conv;
  InvertedIndex idx;
  SearchServer srv(idx);
  Entry ent;
  vector <pair<int, float>> myPair;
  vector<vector<RelativeIndex>>vec;
  vector<vector<pair<int, float>>> answers;
  try
  {
    idx.UpdateDocumentBase(conv.GetTextDocuments());
  }
  catch(const runtime_error& e)
  {
    cerr << e.what() << endl;
  }
  catch(const invalid_argument& e)
      {
        cerr << ""<< e.what() << endl;
      }
  try
  {
    conv.GetRequests();
  }
  catch(const runtime_error& e)
  {
    cerr << e.what() << endl;
  }
  
  vec = srv.search(conv.GetRequests());
  for (int i = 0; i < vec.size(); i++)
  {
      myPair.clear();
      for (auto& element : vec[i])
      { 
        pair<int, float> pair = make_pair(static_cast<int>(element.doc_id), element.rank);
        myPair.push_back(pair); 
      }
      answers.push_back(myPair);
  }
  conv.putAnswers(answers);
}