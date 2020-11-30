#include "bintree_impl.h"
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <bitset>
#include <memory>

using namespace std;
struct huffchar {
    char c;     // since utf-8 也是用8位8位這樣存的，ascii還是不ascii沒差
    int frequency;
    huffchar(char cc, int f): c(cc), frequency(f) {}
};
struct huffcode {
    unsigned code;
    size_t len;
    huffcode(unsigned _code, size_t _len): code(_code), len(_len){}
    huffcode() = delete; // debug
};
typedef BinNode<huffchar> huffnode;
typedef BinTree<huffchar> hufftree;
typedef vector<unique_ptr<hufftree>> huffmanforest;
typedef map<char, huffcode> hufftable;
class Huffman {
private:
    unique_ptr<huffmanforest>forest;
    //hufftable* table;
    unique_ptr<hufftable> table;
    // the one true tree (XD
    hufftree* tree;
    const char* filename;
    static const int LETTERNUM = 256;
    int statistics[LETTERNUM]{0};
    long filesize = 0;
    // learn c++ file manipulation!
    // return an array of frequency, size LETTERNUM
    void stat ( const char* );
    // generate huffman tree (from huffman forest)
    hufftree* gentree ();
    // get and remove the tree with its root the lowest frequency
    unique_ptr<hufftree> mintree ();
    // from the code, get encodings of each character
    void gencode ();
    void gencode_helper(hufftable*, huffnode*, huffcode);
    void encode (char* zip, long& zip_length);
public:
    Huffman ();             // do nothing la
    void zip (const char*);
    void unzip (const char*);
};

void Huffman::stat (const char* filename) {
    this->filename = filename;
    ifstream in (filename, ios::in);
    if (!in) {
        cerr << "file not loaded: " << filename << endl;
        exit (EXIT_FAILURE);
    }
    int c;
    while ((c = in.get()) != EOF) {
        statistics[c]++;
        filesize++;
    }
    in.close();
}

Huffman::Huffman () { }
hufftree* Huffman::gentree () {
    unique_ptr<huffmanforest> temp (new huffmanforest);
    forest = move(temp);
    for (size_t i = 0; i < LETTERNUM; i++) {
        if (!statistics[i]) continue; // if no such character, continue
        forest->push_back (unique_ptr<hufftree>(new hufftree));   //statistics
        forest->back()->insertAsRoot(huffchar ((int) i, statistics[i]));
    }
    while (forest->size() > 1) {            //while there is not only one tree
        //hufftree* smaller = mintree();
        //hufftree* larger = mintree();
        // get two smallest (frequency) trees
        unique_ptr<hufftree> smaller = mintree(); // need to transfer ownership
        unique_ptr<hufftree> larger = mintree();
        //hufftree* merge = new hufftree();   // ready to merge
        unique_ptr<hufftree> merge(new hufftree);
        merge->insertAsRoot(huffchar (0, smaller->root()->data.frequency+larger->root()->data.frequency));                                  //insert root with the two fs combined
        merge->root()->attachAsLC(smaller->root()); //attach
        merge->root()->attachAsRC(larger->root());  //attach
        forest->push_back(move(merge));                   //push back
    }
    //好麻煩！(but anything for no memory leaks!
    return forest->at(0).get();
}

unique_ptr<hufftree> Huffman::mintree() {
    int min = forest->at(0)->root()->data.frequency;
    huffmanforest::iterator tree = forest->begin();// to remove
    hufftree* temp = forest->at(0).get();
    for (auto it = forest->begin(); it != forest->end(); it++) {    //traverse
        if (min > (*it)->root()->data.frequency) {                  //store the info about min char
            min = (*it)->root()->data.frequency;
            tree = it;
            temp = it->get();
        }
    }
    unique_ptr<hufftree> saveya {move(*tree)};
    forest->erase(tree);        //remove it, so we can get the next minimum one//我猜這裡有一個core dump，因為unique_ptr從forest裡面移除之後就被釋放了（救命啊！）
    //感覺這樣還是不太行...
    // looks like it works but don't know how
    return move(saveya);
}

void Huffman::gencode () {
    tree = gentree();
    unique_ptr<hufftable>temp{new hufftable()};
    table = move(temp);
    gencode_helper (table.get(), tree->root(), huffcode(0, 0));
}

void Huffman::gencode_helper (hufftable* table, huffnode* node, huffcode encoding) {
    if (!node->lc && !node->rc) { // leaf
        //(*table)[node->data.c] = encoding;
        table->insert(make_pair(node->data.c, encoding));
        return;
    }
    huffcode encodingl(encoding.code << 1, encoding.len + 1); // left child, shift left, 0
    huffcode encodingr((encoding.code << 1)+1, encoding.len + 1);   // right child, shift left, 1

    if (node->lc) gencode_helper (table, node->lc, encodingl);
    if (node->rc) gencode_helper (table, node->rc, encodingr);
}

void Huffman::zip (const char* filename) {
    stat(filename);
    gencode();
    char* myzip = nullptr;
    myzip = new char[filesize+10000];      //压缩后的文件可能更大，考虑将fsize扩大一点
	// damn...
	if (!myzip) { // are you idiot?
		printf("文件太大，内存不够，读入错误!\n");
		exit(0);
	}
    long zip_length;
    encode (myzip, zip_length); //编码后返回长度zip_length的内容myzip

	FILE *outfp = fopen("whatever.myzip","wb");
	if(!outfp){
        printf("无法打开写入文件!\n");
        exit(0);
    }
    fwrite(tree, sizeof(hufftree), 1, outfp);       //保存哈夫曼树 ，解码要用到
    fwrite(myzip, sizeof(char), zip_length, outfp);//保存编码后的内容
	fclose(outfp);

	free(myzip);	//释放文件内容
	printf("compressed file %s generated!\n", "whatever.myzip");

}
void Huffman::encode (char* myzip, long& zip_length) {
	size_t j=0; //myzip的下标
	size_t code;
	int len, c;
	int usedbits = 0; //myzip[j]中被占用的bits数
    //....................................
    ifstream in (filename, ios::in);
    if (!in) {
        cerr << "file not loaded: " << filename << endl;
        exit (EXIT_FAILURE);
    }
    while ((c = in.get()) != EOF) {
        auto it = table->find(c);
        if (it == table->end()) {
            cerr << "char c" << c << " not found" << endl;
            exit (EXIT_FAILURE);
        } else {
            code = it->second.code;
            len = it->second.len;
        }
		while (len + usedbits>=8){  //code需要左移usedbits长的一段，然后和myzip[j]位或操作
			size_t code1 = code >> len + usedbits - 8;
			myzip[j] = myzip[j] | code1; //填满前一个编码字符
			len = len + usedbits - 8;      //code现在有效长度
			usedbits = 0;
			myzip[++j]=0;
			//printf("\n编码的第 %d 个字符为：#%2x\n",j - 1, myzip[j-1]);
		}//循环，使得len+usedbits <8
		//将code的前面各位清0,因为有效位是len
		code = code & ((1<<len)-1); //code和后面k个1，其它全为0的数据进行与，保留后面len位
		code = code << 8 - len - usedbits;//向前移动若干位
		myzip[j] = myzip[j] | code;
		usedbits = len+usedbits;
    }
    in.close();
	zip_length = j+1;
}

void Huffman::unzip(const char* filename) {
    ifstream in (filename, ios::in);
    ofstream out ("unzip.txt", ios::out);
    if (!in || !out) {
        cerr << "file " << filename << " not found" << endl;
        cerr << "or 'unzip.txt' won't open" << endl;
        exit(EXIT_FAILURE);
    }
    int c;
    in.read((char*)tree, sizeof(hufftree));
    huffnode* node = tree->root();
    size_t i = 0;
    while ((c = in.get()) != EOF) {
        bitset<8> bits{c}; // init bits with c
        while (i < 8) {
            if (!node->lc && !node->rc) {
                out.put(node->data.c);
                node = tree->root();
            }
            if (bits.test(7-i)) node = node->rc;//坑！
            else node = node->lc;
            i++;
        }
        i = 0;
    }
    in.close();
    out.close();
}
int main(void) {
    Huffman hfm;
    hfm.zip("test");
    hfm.unzip("whatever.myzip");
    return 0;
}