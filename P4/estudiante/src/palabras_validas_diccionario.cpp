//#include <csignal>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "dictionary.h"

using namespace std;

int main(int argc, char *argv[])
{
 srand(time(NULL));

  ifstream dict_file(argv[1]);
  vector <char> available_letters;
  for (int i = 2; i < argc; ++i) {
    available_letters.push_back(std::tolower(argv[i][0]));
  }

  if(!dict_file){
    cerr << "No puedo abrir el fichero " << argv[1] << endl;
    return 0;
  }

  Dictionary dictionary;
  dict_file >> dictionary;
  dict_file.close();



  for (auto it = dictionary.possible_words_begin(available_letters); it != dictionary.possible_words_end(); ++it) {
	cout << *it << endl;
  }





  return 0;
}
