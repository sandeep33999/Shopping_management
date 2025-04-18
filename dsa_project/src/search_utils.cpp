#include "search_utils.h"
#include "inventory.h" 
#include<iostream>
#include "search_utils.h"

vector<ItemInfo> getAllItems();


extern vector<ItemInfo> getAllItems();

vector<int> buildLPS(const string& pattern){

    int m = pattern.length();
    vector<int> lps(m, 0);
    int len=0,i=1;

    while(i<m){
        if(pattern[i]==pattern[len])
            lps[i++]= ++len;
        else if(len!= 0)
            len=lps[len-1];
        else
            lps[i++]=0;
    }
    return lps;
}



bool kmpSearch(const string& text,const string& pattern){


    int n = text.size(), m = pattern.size();
    vector<int> lps = buildLPS(pattern);
    int i =0,j=0;

    while(i <n){
        if(tolower(text[i])== tolower(pattern[j])){

            i++; j++;
        }
        if(j==m) return true;
        else if(i<n && tolower(text[i]) != tolower(pattern[j])){
            if(j !=0) j = lps[j - 1];
            else i++;
        }
    }
    return false;


}

vector<ItemInfo> searchItems(const string& keyword){

    vector<ItemInfo> all = getAllItems();
    vector<ItemInfo> results;

    for(auto& item :all){
            if(kmpSearch(item.name,keyword) ||kmpSearch(keyword, item.name)){ 
            results.push_back(item);
        }


    }

    return results;

    
}
