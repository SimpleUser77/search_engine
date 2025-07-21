#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <execution>
#include <cstdlib>
#include <sstream>
#include <filesystem>
#include "nlohmann/json.hpp"
#include "converterJSON.h"
#include "invertedIndex.h"
#include "searchServer.h"

using namespace std;
using json = nlohmann::json;

vector<string> ConverterJSON::GetTextDocuments()
{
  vector<string> listOfFiles; 
  vector<string> input_docs;
  int responses;
  json list;
  ifstream file ("config.json");
  if(file.fail())
   {
    throw runtime_error("The config file is missing");
   };
  file >> list;
  for(json::iterator it = list.begin(); it != list.end(); it++)
  {
    if(it.key() != "config")
     {
      this->check++;
     };
  }
  if(this->check > 1)
   {
    throw invalid_argument("The config file is empty!");
   };
  json name = list["config"]["name"];
  system ("cls");
  cout << name << endl;
  cout << "----------------------" << endl;
  cout << endl;
  json resp = list["config"]["max_responses"];
  responses = resp;
  this->SetResponsesLimit(responses);
  json name_engine = list["files"];
  listOfFiles.clear();
  for(auto &filename : name_engine) 
   {
     listOfFiles.push_back(filename.get<string>());
   }
  file.close();
  string temp;
  for(int i = 0; i < listOfFiles.size(); i++)
  {
    ifstream textfile(listOfFiles[i]);
    if(textfile.fail())
      {
        cerr << "Wrong open file on path: " << listOfFiles[i] << " !";
      };
      while (getline(textfile, temp)) 
       {  
         input_docs.push_back(temp);
       }
    textfile.close();
  }
  return input_docs;
}


vector<string> ConverterJSON::GetRequests()
{
  vector<string> queries_input;
  string text;
  json temp;
  ifstream file ("requests.json");
  if(file.fail())
   {
    throw runtime_error("The requests file is missing");
   };
  file >> temp;
  json req = temp["requests"];
  for(auto &fil:req)
  {
    queries_input.push_back(fil.get<string>());
  }
  file.close();
  return queries_input;
}

void ConverterJSON::putAnswers(vector<vector<pair<int, float>>> myAnswers) const
{
    ofstream file;
    file.open("answers.json");
    json relevance;
    json text;
    int limit = GetResponsesLimit();
    nlohmann::ordered_json result;
    nlohmann::ordered_json request;
    nlohmann::ordered_json answers;
    for (int i = 0; i < myAnswers.size(); i++)
    {
        request.clear();
        string requestName = "request00" + to_string(i + 1);
        if (!myAnswers[i].empty())
        {
            relevance = json::array();
            if (myAnswers[i].size() > limit)
            {
               myAnswers[i].resize(limit);
            }
            request[requestName]["result"] = "true";
            for (auto& element : myAnswers[i])
            {
                text["doc_id"] = element.first;
                text["rank"] = element.second;
                relevance.push_back(text);
                request[requestName]["relevance"] = relevance;
            }
        }
        else
        {
            request[requestName]["result"] = "false";
        }
        answers["answers"].emplace_back(request);
    }
  file << answers.dump(3);
  file.close();
}
