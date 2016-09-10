#include "io.h"
#include "vector.h"
#include "avltree.h"
#include "file.h"
#include "hashtable.h"
#include "linkedlist.h"
#include "class.h"
#include <algorithm>

int getNum(){

    return 5;

}
void printStuff(){

    std::cout << "Test stuff" << std::endl;

}
void printFile(){

    IFile f("line.cpp");
    OFile out("test.txt");
    out.getStream() << f << std::endl;

}
void testAVL(){

    AVLtree<int> tree;
    for(int i = 10; i > 0; i--){
        tree += i;
    }
    std::cout << tree << std::endl;

}
void testVector(){

    Vector<int> nums;
    nums += 5;
    nums += 2;
    std::cout << nums << std::endl;
    nums += 7;
    std::cout << nums[2] << std::endl;

    nums.sort();
    std::cout << nums << std::endl;

}
void testHash(){

    HashTable<int, String> hash;

    hash.insert(5, String("swag"));
    hash.insert(6, String("no swag"));

    std::cout << hash[6] << std::endl;

    std::cout << hash << std::endl;

}
void testList(){

    LinkedList<int> l;
    l.add(5);
    l.add(2);
    l.add(3);

    OFile("list.txt").getStream() << l << std::endl;


}
int main(){

    std::cout << "Hello, World!" << std::endl;
    std::cout << "The DS Language!" << std::endl;
    printStuff();
    printFile();
    testAVL();
    testVector();
    testHash();
    testList();
    Test t;
    std::cout << t.getNum() << std::endl;

}
