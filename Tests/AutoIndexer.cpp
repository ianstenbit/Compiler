#include "vector.h"
#include "file.h"
#include <cstring>


using namespace std;

int main(int argc, char** argv){

    Vector< pair<String, Vector<int> > > words;
    IFile f(argv[1]);
    OFile o(argv[2]);
    String f_as_string;

    while(f.hasNext()){
        f_as_string = f_as_string + f.next() + " ";

    }
    Vector<String> tokens = f_as_string.split();

    int pageNum = -1;
    for(int i = 0; i < tokens.size(); i++){

        if(tokens[i][0] == '['){

            pageNum = atoi(tokens[i].substring(1,-1).c_str());
            if(pageNum == -1) break;

        }
        else{

            bool found = false;

            for(int j = 0; j < words.size(); j++){
                if(words[j].first == tokens[i]){
                    words[j].second += pageNum;
                    found = true;
                    break;

                }
            }
            if(!found){

                pair<String, Vector<int>> p;
                p.first = tokens[i];
                Vector<int> v;
                v.add(pageNum);
                p.second = v;
                words.add(p);

            }
        }
    }
    for(int i = 0; i < words.size(); i++){
        o.getStream() << words[i].first.substring(0,-1) << std::endl;
        o.getStream() << words[i].second << std::endl;
        ;
    }
    return 0;

}
