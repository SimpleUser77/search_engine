#pragma once
#include <iostream>
#include <vector>
#include <string>


using namespace std;

class ConverterJSON
{
  private:
   int maxResponses = 0; 
   vector<string> listOfRequests;
  public:
   ConverterJSON() = default;
   int check = 0;
   vector<string> GetTextDocuments(); 
   void SetResponsesLimit(int responses)
   {
      maxResponses = responses;
   };
   int GetResponsesLimit() const
   {
       return maxResponses;
   }
   vector<string> GetRequests();// Метод получения запросов из файла requests.json. @return возвращает список запросов из файла requests.json
   void putAnswers(vector<vector<pair<int, float>>>answers) const; //  положить в файл answers.json результаты поисковых запросов 
};