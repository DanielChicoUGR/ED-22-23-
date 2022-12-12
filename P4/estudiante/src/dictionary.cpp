//
// Created by fluque1995 on 8/9/21.
//

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
  node prev_child, curr_child = current.left_child();

  for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
    prev_child = curr_child;
    if ((*curr_child).character == character) {
      return curr_child;
    }
  }
  if (!prev_child.is_null()) {
    return prev_child;
  }
  return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
  node insertion_position = findLowerBoundChildNode(character, current);
  if (insertion_position == current){
    this->words.insert_left_child(current, char_info(character));
    return insertion_position.left_child();
  } else if ((*insertion_position).character != character){
    this->words.insert_right_sibling(insertion_position, char_info(character));
    return insertion_position.right_sibling();
  } else {
    return insertion_position;
  }
}

int Dictionary::getOccurrences(node curr_node, char c){
  //Si se llega a un nodo nulo se devuelve 0
  if(curr_node.is_null()) return 0;


  int ret=0;
   if((*curr_node).character==c) ret+=1;

   ret+= getOccurrences(curr_node.left_child(),c);
   ret+= getOccurrences(curr_node.right_sibling(),c);

  return ret;

}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){
  if(curr_node.is_null())
    return {0,0};

  auto hijo_i = getTotalUsages(curr_node.left_child(), c);

  auto herm_d=getTotalUsages(curr_node.right_sibling(), c);

  std::pair<int, int> ret;
  ret.first=hijo_i.first+herm_d.first;
  ret.second=hijo_i.second+herm_d.second;

  if((*curr_node).character==c) {
    ret.first+=hijo_i.second;
  }

  if((*curr_node).valid_word) {
    ret.second+=1;
    if ((*curr_node).character == c)
      ret.first+=1;
  }

  return ret;


}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
  this->words.set_root(char_info());
  this->total_words = 0;
}

Dictionary::Dictionary(const Dictionary &other) {
  this->words = other.words;
  this->total_words = other.total_words;
}

Dictionary::~Dictionary() {
  this->words.clear();
}

bool Dictionary::exists(const std::string & word) {
  node current = this->words.get_root();
  for (char i : word){
    current = this->findLowerBoundChildNode(i, current);
    if ((*current).character != i) {
      return false;
    }
  }

  return (*current).valid_word;
}

bool Dictionary::insert(const std::string &word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->insertCharacter(word[i], current);
  }

  if (!(*current).valid_word) {
    (*current).valid_word = true;
    this->total_words++;
    return true;
  }

  return false;
}

bool Dictionary::erase(const std::string & val){
  node current = this->words.get_root();
  for (char i : val){
    current = this->findLowerBoundChildNode(i, current);
    if ((*current).character != i) {
      return false;
    }
  }
  if ((*current).valid_word){
    (*current).valid_word = false;
    this->total_words--;
    return true;
  }
  return false;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
  if (this != &dic){
    this->words.clear();
    this->words = dic.words;
    this->total_words = dic.total_words;
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

/*std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << std::endl;
  }
  return os;
}*/

std::istream& operator>>(std::istream &is, Dictionary &dict){
  std::string curr_word;
  while (getline(is, curr_word)){
    dict.insert(curr_word);
  }
  return is;
}

///////////////////////////////////////////////////////////////////////////////
//                            Recursive counters                             //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){
  auto nodo=this->words.get_root();
  return getOccurrences(nodo,c);
}

int Dictionary::getTotalUsages(const char c){
  auto nodo=this->words.get_root();
  return getTotalUsages(nodo,c).first;
}

///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////

Dictionary::iterator::iterator() {
  iter=tree<char_info>::const_preorder_iterator();
  curr_word="";
}

Dictionary::iterator::iterator( tree<char_info>::const_preorder_iterator &iter): iter(iter),curr_word("") {}

Dictionary::iterator::iterator(const Dictionary::iterator &other){

  this->curr_word=other.curr_word;
  this->iter=other.iter;
}

std::string Dictionary::iterator::operator*() {
  return curr_word;
}

Dictionary::iterator &Dictionary::iterator::operator++() {

  bool c_lvl;
  do{
    auto nivel=iter.get_level();
    ++iter;

  //Hemos descendido a un hijo, se añade esa letra a la palabra
    c_lvl=iter.get_level()!=0;

    if(nivel<iter.get_level())
      curr_word.push_back((*iter).character);

    else if(nivel==iter.get_level())
     curr_word.back()=(*iter).character;

    else if(nivel>iter.get_level()) {
      while (curr_word.size() > iter.get_level())
        curr_word.pop_back();

      if (c_lvl) curr_word.back()=(*iter).character;


    }


  }while(  c_lvl && !(*iter).valid_word );
  return *this;
}

bool Dictionary::iterator::operator==(const iterator &other) {
  return  (iter)==(other.iter);
}


bool Dictionary::iterator::operator!=(const iterator &other) {
    return !(*this==other);
}

Dictionary::iterator Dictionary::iterator::operator=(const Dictionary::iterator &other) {
  this->iter=other.iter;
  this->curr_word=other.curr_word;

  return *this;
}

Dictionary::iterator Dictionary::begin() const {
  auto it=Dictionary::iterator();
  it.iter=words.cbegin_preorder();
  it.curr_word="";
  return it;
}

Dictionary::iterator Dictionary::end() const {
  Dictionary::iterator it;
  it.iter=words.cend_preorder();
  it.curr_word="";
  return it;
}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////


Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {
    possible_words_iterator it;
    it.current_node=words.get_root();
    it.available_letters=std::multiset<char>{*(available_characters.data())};
    it.level=0;
    return it;
}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {
    possible_words_iterator it;
    it.current_node=node();
    it.level=-1;
    it.current_word="";

    return it;
}

Dictionary::possible_words_iterator::possible_words_iterator() {
    current_node=node();
    level=0;
    available_letters=multiset<char>();
    current_word="";
}

Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters){
    this->current_node=current_node;
    this->current_word="";
    this->available_letters= {*available_letters.data()};
    level=0;
}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other){
    *this=other;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other) {
    this->current_node=other.current_node;
    this->current_word=other.current_word;
    this->available_letters=other.available_letters;
    this->level=other.level;

    return *this;

}

bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {
    return current_node==other.current_node;
}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {
    return !(*this==other);
}

bool Dictionary::possible_words_iterator::existe_hi(node current){
    return !current.left_child().is_null();
}

bool Dictionary::possible_words_iterator::existe_herm(node current){
    return !current.right_sibling().is_null();
}

bool Dictionary::possible_words_iterator::existe_padre(node current) {
    return !current.parent().is_null();

}

    Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {
    //Si el nodo es nulo no hacemos nada, no podemos avanzar. Seguramente estemos en una hoja en el la raiz.
    bool c_parada;

        do {

            if (!current_node.is_null()) {
                //Si tiene hijos a la izquierda (nuevas letras a la palabra, se avanza

                char letra;
                if (existe_hi(current_node)
                    and available_letters.find((*current_node.left_child()).character) != available_letters.end()) {
                    letra = (*current_node.left_child()).character;
                    available_letters.erase(available_letters.lower_bound(letra));
                    current_node = current_node.left_child();
                    level++;
                    current_word.push_back(letra);
                    //Si no tiene hijos a la izquierda, se pregunta si existen hermanos. en ese caso, se accede al hermano. mismo nivel en el arbol.
                } else if (existe_herm(current_node)
                           and
                           available_letters.find((*current_node.right_sibling()).character) !=
                           available_letters.end()) {
                    letra = (*current_node.right_sibling()).character;
                    available_letters.erase(available_letters.lower_bound(letra));
                    available_letters.insert(current_word.back());

                    current_word.back() = letra;
                    current_node = current_node.right_sibling();

                    //Has llegado a una hoja. Gestion de hojas y recorrido regresivo en busca de nodos no explorados.
                } else {
                    //Se sube por el arbol"
                    while (existe_padre(current_node) && //Mientras que exista un padre *Y*
                           (!existe_herm(current_node.parent()) ||
                            current_node.parent().right_sibling() == current_node))
                        //El nodo padre tenga hermanos *O* rl nodo actual sea hermano del nodo padre
                    {
                        available_letters.insert(current_word.back());
                        current_word.pop_back();
                        current_node = current_node.parent();
                        level--;
                    }
                    //Hemos llegado a la raiz, devolvemos el nodo vacio
                    if (current_node.parent().is_null()) {
                        current_node = node();
                        current_word = "";


                    } else {
                        //Sino avanzamos hacia un nodo hermano del nodo padre.
                        this->current_node = this->current_node.parent().right_sibling();
                        available_letters.insert(current_word.back());
                        current_word.pop_back();

                        //Sube un nivel (elimina letra) y altera la ultima letra. Hay dos alteraciones a avalibe_lettersnt_node = current_node.parent().right_sibling();
                        level--;
                    }
                }
            }
            else   c_parada=false;

            c_parada=level!=0;

        } while (c_parada && !(*current_node).valid_word);
    return *this;
}

std::string Dictionary::possible_words_iterator::operator*() const {
    return this->current_word;
}