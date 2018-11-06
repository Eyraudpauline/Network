#include "network.h"
#include "random.h"
#include "iostream"

using namespace std;

    void Network::resize(const size_t& n){
		values.resize(n);
		RNG.normal(values,0,1);} // Rempli le tableau de valeurs aleatoires suivant la loi normal
    

    bool Network::add_link(const size_t& indiceA, const size_t& indiceB){
		//A ne peut pas faire de lien avec lui meme / que les valeurs A et B soient dans values et que le lien n'existe pas deja
		if (indiceA==indiceB) {return false;}
		else if (indiceA>=values.size() or indiceB>=values.size()){return false;}
		
		auto range=links.equal_range(indiceA); 
		for(auto i=range.first;i!=range.second;++i){  
		if(i->second==indiceB){return true;}
		
		}
			links.insert(pair<const size_t,const size_t>(indiceA, indiceB));
			links.insert(pair<const size_t,const size_t>(indiceB, indiceA));
			return true;
		
	}


   size_t Network::random_connect(const double& mean_deg){
	 links.clear();
	  
	 for(size_t i(0); i<size() ; ++i){                                         
	int nb_liensouhaites(RNG.poisson(mean_deg)); 
    while(nb_liensouhaites>=size()-1){ nb_liensouhaites=RNG.poisson(mean_deg);}

	int nbeffectif(0);  
	                       
	while(nbeffectif<nb_liensouhaites){   
	int indice=RNG.uniform_double(0, size()-1);       
	if(add_link(i, indice)){++nbeffectif;}
	}		 
	}
	return links.size()/2;
 }

    size_t Network::set_values(const std::vector<double>& newvalues){
		
		size_t size_to_add(std::min(newvalues.size(), size()));
		
		for(size_t i(0); i < size_to_add; ++i){
			values[i] = newvalues[i];
		}
		return size_to_add;	
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

	
