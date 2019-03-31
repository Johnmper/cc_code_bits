#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
#include<chrono>
#include<vector>
#include<numeric>
#include<algorithm>
#include<functional>


size_t string2hash(std::string str){

    static int sz=str.size();
    size_t ret=0;
    
    for(int ii=0;ii<sz;++ii){
        ret+=str[ii];
    }
    return ret;

}

constexpr uint32_t HashStrRecur(uint32_t _hash, const char* _str)
{
  return (*_str == 0) ? _hash : HashStrRecur(((_hash << 5) + _hash) + *_str, _str + 1);
}

constexpr uint32_t HashStr(const char* _str)
{
  return (*_str == 0) ? 0 : HashStrRecur(5381, _str);
}

int main(int argc, char** argv){
    std::string line;
    std::vector<std::string> en3000;
    std::vector<std::size_t> hash_rep;
    std::vector<std::size_t> hashed;
    std::vector<std::size_t> timed;

    en3000.reserve(3100);
    hashed.reserve(3100);
    timed.reserve(3100);

    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;

    std::ifstream in("en-3000.txt",std::ifstream::in);
    if(in.is_open()){
        // Process english words
        while( getline(in,line) ){  // Read till End-of-file
            size_t hashed_tmp=0;
            const char* hash_str = line.c_str();
            t1 = std::chrono::high_resolution_clock::now();
            hashed_tmp = std::hash<std::string>{}(line);
            //hashed_tmp = string2hash(line);
            //hashed_tmp = HashStr(hash_str);
            t2 = std::chrono::high_resolution_clock::now();
            timed.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count());
            en3000.push_back(line);
            hashed.push_back(hashed_tmp);
        }
        // Close file
        in.close();
    }
    else{
        std::cout << "en-3000.txt" << " not found" << std::endl;
    }

    for(size_t kk=0; kk < hashed.size() ; ++kk){
        int found_n = 0;
        for(size_t ff=0; ff < hashed.size(); ++ff){
            if(hashed[kk] == hashed[ff]){
                found_n++;
            }
        }
        hash_rep.push_back(found_n);
        std::cout << std::setw(4) << found_n;
        std::cout << std::setw(16) << en3000[kk];
        std::cout <<" : " << hashed[kk] << std::endl;
    }

    int n_col=0;
    for(size_t kk=0;kk<hash_rep.size();++kk){
        if(hash_rep[kk]>1){
            ++n_col;
        }
    }
    std::cout <<"Mean: "<< std::accumulate(timed.begin(), timed.end(), 0)/timed.size() << std::endl;
    std::cout <<"Check collision: " << n_col << std::endl;

    return 0;
}
