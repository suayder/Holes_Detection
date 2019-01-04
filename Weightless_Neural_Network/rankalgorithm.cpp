#include "rankalgorithm.h"

void RankAlgorithm::setN(const n_Tuple_size &value)
{
    n = value;
}

RankAlgorithm::RankAlgorithm()
{
    this->shortestElement = 0;
}

//Used when training
int RankAlgorithm::encode(multimap<u_char, u_char>& tupple)
{

    string key;

    for(auto& element:tupple){
        try{
            key.push_back(element.second);
        }
        catch (std::exception& e){
            cout<<"Function encode wrong: " << e.what();
        }
    }
    unordered_map<string, unsigned int>::const_iterator it = this->rankTable.find(key);
    if(it != this->rankTable.end()){
        return it->second;
    }
    else{
        this->rankTable.insert({key, ++(this->shortestElement)});
        return this->shortestElement;
    }
}

//Used when testing
int RankAlgorithm::decode(multimap<u_char, u_char> &tupple)
{
    string key;

    for(auto& element:tupple){
        try{
            key.push_back(element.second);
        }
        catch(exception& e){
            cout<<"Function decode wrong: " << e.what();
        }
    }
    unordered_map<string, uint>::const_iterator it = this->rankTable.find(key);

    if(it != this->rankTable.end())
        return it->second;
    else
        return 0;
}
