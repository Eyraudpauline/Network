#include "network.h"
#include "random.h"
#include <algorithm>

using namespace std;

    void Network::resize(const size_t& n){
		links.clear();
		values.resize(n);
		RandomNumbers aleatoires;
		aleatoires.normal(values);} // Rempli le tableau de valeurs aleatoires suivant la loi normal
    

    bool Network::add_link(const size_t& indiceA, const size_t& indiceB){
		//A ne peut pas faire de lien avec lui meme / que les valeurs A et B soient dans values et que le lien n'existe pas deja
		if (indiceA==indiceB) {return false;}
		else if (indiceA>=values.size() or indiceB>=values.size()){return false;}//PK>=
		
		auto range=links.equal_range(indiceA); // je cherche tous les liens commencant par A
		for(auto i=range.first;i!=range.second;++i){  //je parcours tous les liens commencant par A
		if(i->second==indiceB){return true;}
		
		}
			links.insert(pair<const size_t,const size_t>(indiceA, indiceB));
			links.insert(pair<const size_t,const size_t>(indiceB, indiceA));
			return true;
		
	}


    size_t Network::random_connect(const double& mean_deg){ //TYPE DE retour correspond à quoi ?????
		
		links.clear();
		size_t nblienstot(0);
		
		
		for (unsigned int i(0);i<values.size();++i){
		size_t nbliens(RNG.poisson(mean_deg));
		
		while(nbliens>=values.size()){nbliens= RNG.poisson(mean_deg);} //Pour ne pas avoir plus de liens que de nombres 
			
		vector<int> indices(nbliens);//tableau de la taille nb de lien
		RNG.uniform_int(indices,0,values.size());//rempli le tableau en lui donnant des nb aleatoires
		
		for(auto j: indices){	
		if(!add_link(j,i)){add_link(j,i+1);}
		else{add_link(j,i);}
		}
		
		nblienstot+=nbliens;	
		}
	return nblienstot;
	} 
	


    size_t Network::set_values(const std::vector<double>& newvalues){
		
		values.clear();
		links.clear();//Averifier!!
		for(auto i: newvalues){
			values.push_back(i);
		}
		return (values.size());	
	}
	
    size_t Network::size() const{
		return values.size();}
    
    
    size_t Network::degree(const size_t & n) const{
		int degree(0);
		if(n>=values.size()){throw std::invalid_argument("Out of range !");}
		auto range=links.equal_range(n);
		for(auto i=range.first;i!=range.second;++i){
			degree+=1;
		}
		return degree;
		}

    double Network::value(const size_t& n) const{
		
		if(n>=values.size()){throw std::invalid_argument("Out of range !");}
		return values[n];
		}


    vector<double> Network::sorted_values() const{
		
		vector<double> sortedvalues;
		for(auto i: values){
			sortedvalues.push_back(i);
		}
		
		sort(sortedvalues.begin(), sortedvalues.end(), std::greater<double>());
		return sortedvalues;
		}
		
    vector<size_t> Network::neighbors(const size_t& n) const{
		if(n>=values.size()){throw std::invalid_argument("Out of range !");}
		vector<size_t> neighbors;
		auto range=links.equal_range(n);
		for(auto i=range.first;i!=range.second;++i){
			neighbors.push_back(i->second);
		}
		return neighbors;
		}

	
