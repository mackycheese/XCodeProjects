//
//  pt_list.cpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "pt_list.hpp"

namespace pt{
    
    list::list(){

    }
    
    list::~list(){

    }
    
    void list::clear(){
        inner.clear();
    }
    
    void list::add(obj *o){
        inner.push_back(std::unique_ptr<obj>(o));
    }
    
    int list::size()const{
        return (int)inner.size();
    }
    
    bool list::intersect(ray ray,float &t,surface_data&sd,obj*o) const{
        
        t=10000000;
        bool found=false;
        obj*dummy_o;
        float dummy_t;
        surface_data dummy_sd;
        for(int i=0;i<size();i++){
            if(inner[i].get()->intersect(ray,dummy_t,dummy_sd,dummy_o)){
                if(dummy_t<t){
                    t=dummy_t;
                    o=dummy_o;
                    sd=dummy_sd;
                    found=true;
                }
            }
        }
        
        return found;
        
    }
    
}
