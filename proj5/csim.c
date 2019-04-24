//Minxuan Song 
//7618212030

#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
int newinlru = 9999999; // the lru number given when a new element comes into the cache
int misses, hits, evictions, isL = 0;
typedef struct CacheLine CacheLine;
typedef struct Cache Cache;
typedef struct Set Set;
struct Set{
    CacheLine* clines;
};
struct Cache{
    Set* sets; // all of the sets
    int snum; // number of sets in the cache
    int lnum; // number of lines in the cache
};
struct CacheLine{
    int lruscore; // evaluation for lru
    int fifoscore; // evaluation for fifo
    int isvalid; 
    int tag;
};
int retrieveSetBit(int ad,int s,int b){
    int mask =(1<<s)-1;
    ad = ad >> b;
    int key = ad&mask;
    return key; // getting the set bits
}
int retrieveTagBit(int ad,int s,int b){
    int mask =b+s;
    int key = ad>>mask;
    return key; //getting the tag bits
}
int minlru(Cache *cache,int setBits){
    int minI=0;
    int minLru = newinlru;
    for(int s=0;s<cache->lnum;s++){
        if(!(cache->sets[setBits].clines[s].lruscore < minLru)){
            continue;
        }
        else{
            minLru = cache->sets[setBits].clines[s].lruscore; // equals to the implementation of the min/max function
            minI = s;
        }
    }
    return minI; // find the index of the lowest lru in the whole cache
}
void updatelru(Cache *cache,int setBits,int hitI){
        for(int j=0;j<cache->lnum;j++) cache->sets[setBits].clines[j].lruscore--; // for all elements except for the new-in, lru scores go down
        cache->sets[setBits].clines[hitI].lruscore = newinlru;
}
int minfifo(Cache *cache,int setBits){
    int minI=0;
    int minFIFO = 500000000;
    for(int i=0;i<cache->lnum;i++){
        if(!(cache->sets[setBits].clines[i].fifoscore < minFIFO)){
            continue;}
            else
            {
            minFIFO = cache->sets[setBits].clines[i].fifoscore;
            minI = i; // the same as finding the lowest lru score
        }
    }
    return minI;
}
void updatefifo(Cache *cache,int setBits,int hitI){
        int hitfifonum = 0;
        for(int i=0;i<cache->lnum;i++){
            if(cache->sets[setBits].clines[i].fifoscore > hitfifonum){
                hitfifonum = cache->sets[setBits].clines[i].fifoscore;
            }
        }
        for(int j=0;j<cache->lnum;j++) cache->sets[setBits].clines[j].fifoscore--;
        cache->sets[setBits].clines[hitI].fifoscore = hitfifonum+1; // for all element (no exception except for the new in), all scores go down
}
int missed(Cache *cache,int setBits,int tagBits){
    int i;
    int missed = 1;
    for(i=0;i<cache->lnum;i++){
        if(cache->sets[setBits].clines[i].isvalid == 1 && cache->sets[setBits].clines[i].tag == tagBits){
            // method: check if the tag bit equals, and then check if that line is valid
            //if valid, we hit, and lru score goes up, no eviction & miss happening
            missed = 0;
            updatelru(cache,setBits,i); // only lru value is changed
        }
    }
    return missed; //determine if we missed
}
int updateCache(Cache *cache,int setBits,int tagBits){
    int i;
    int isfull = 1;
    for(i=0;i<cache->lnum;i++){
        if(cache->sets[setBits].clines[i].isvalid == 0){
            isfull = 0; 
            break;
        } // first check if it's full, if there's invalid, it's not full (cache)
    }
    if(isfull){ // if it's full, we gotta evict. by min fifo or min lru, we evict the element
        int evictionIndex = 0;
        if (isL){
        evictionIndex = minlru(cache,setBits);}
        else{ evictionIndex = minfifo(cache,setBits);}
        cache->sets[setBits].clines[evictionIndex].isvalid = 1;
        cache->sets[setBits].clines[evictionIndex].tag = tagBits;
        updatelru(cache,setBits,evictionIndex);
        updatefifo(cache,setBits,evictionIndex);
    }else{ // if not full, we just reset the element in the cache to 1, and keep going
        //this here, nothing is evicted. FIFO only changes when eviction happens. so we only update lru.
        cache->sets[setBits].clines[i].isvalid = 1;
        cache->sets[setBits].clines[i].tag = tagBits;
        updatelru(cache,setBits,i);
    }
    return isfull;
}
void load(Cache *cache,int setBits,int tagBits){
    if(!missed(cache,setBits,tagBits)){  // if doesn't miss, we hit, so adding
        ++hits;
    }else{ 
        ++misses; // if we miss, and updatecache returns 1, which means it is full, we ++evictions, because it's already evicted,
        // in the update function. However, whether that happens or not, we ++ miss.
        if(updateCache(cache,setBits,tagBits)){
            ++evictions;
        }
    }
}
void store(Cache *cache,int setBits,int tagBits){
    load(cache,setBits,tagBits);
}
void modify(Cache *cache,int setBits,int tagBits){
    load(cache,setBits,tagBits);
    store(cache,setBits,tagBits);
}
void cacheInit(int s,int E,int b,Cache *cache){
    cache->lnum = E; 
    cache->snum = 2 << s; 
    cache->sets = (Set*)malloc(cache->snum*sizeof(Set));
    int i ,j;
    int count = 0;
    for(i=0; i< cache->snum; i++)
    {
        cache->sets[i].clines =(CacheLine*)malloc(sizeof(CacheLine)*E);
        for(j=0; j < E; j++){
            cache->sets[i].clines[j].isvalid = 0; // initialization
            cache->sets[i].clines[j].lruscore = 0; // all not used, so 0 at the beginning
            cache->sets[i].clines[j].fifoscore = count; // the fundamental idea of fifo, ++ by order
            count++; 
        }
    }
    return;
}
void readInput(int argc,char **argv,int *s,int *E,int *b,char *tfname){
    int in;
    while((in = getopt(argc,argv,"LFhvs:E:b:t:"))!=-1)
    {
        switch(in)
        {
        case 's': // Number of set index bits 
            *s = atoi(optarg);
            break;
        case 'E': // Associativity (number of lines per set)
            *E = atoi(optarg);
            break;
        case 'b': //num of block bits
            *b = atoi(optarg);
            break;
        case 'L': // if it's lru alg
            isL = 1;
            break;
        case 'F': // if it's fifo alg
            isL = 0;
            break;
        case 't': // Name of the valgrind trace to replay
            strcpy(tfname,optarg); 
            break;
        case '?':
        default:
            break;
        }
    }
}
int main(int argc,char **argv){
    int s,E,b,ad,size,setBits,tagBits=0;
    char tfname[500],opt[50];
    Cache cache;
    readInput(argc,argv,&s,&E,&b,tfname); //reading the input, filling the params
    cacheInit(s,E,b,&cache); // now the cache is in our hand
    FILE *tf = fopen(tfname,"r"); //open the trace file
    while(fscanf(tf,"%s%x,%d",opt,&ad,&size)!=EOF){ //getting the traces
        if(!strcmp(opt,"I"))continue;
        setBits = retrieveSetBit(ad,s,b);
        tagBits = retrieveTagBit(ad,s,b);
        if(!strcmp(opt,"L")) {
            load(&cache,setBits,tagBits);
        }
        else if(!strcmp(opt,"S")) { //first character comparison
            store(&cache,setBits,tagBits);
        }
        else{ // if M
            modify(&cache,setBits,tagBits);
        }
    }
    printSummary(hits,misses,evictions);
    return 0;
}