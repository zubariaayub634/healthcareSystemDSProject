// FinalProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

template <typename T>
class Vector
{
private:
	T* array;
	unsigned int size; //no of meaningful entries in array
	unsigned int capacity; //no of entries that can be made in the array
public:
	Vector(int capacity=10):array(new T[capacity]),size(0),capacity(capacity){}
	Vector(T* a,unsigned int size)
	{
		this->capacity=10;
		this->size=0;
		array=new T[this->capacity];
		for (unsigned int i=0; i<size; i++)
		{
			addAtEnd(a[i]);
		}
	}
	Vector(const Vector<T>& obj)
	{
		array=NULL;
		*this=obj;
	}
	const Vector<T>& operator = (const Vector<T>& obj)
	{
		if (this==&obj)
			return *this;
		capacity=obj.capacity;
		size=obj.size;
		if (array) delete []array;
		array=new T[capacity];
		for (unsigned int i=0; i<size; i++)
		{
			array[i]=obj.array[i];
		}
		return *this;
	}
	bool isEmpty()
	{
		return !size;
	}
	void addAtEnd(T element)
	{
		if (size>=capacity-1)
		{
			T* temp= new T[capacity*2];
			for (unsigned int i=0; i<size; i++)
			{
				temp[i]=array[i];
			}
			if (array) delete [] array;
			array=temp;
			capacity*=2;
		}
		array[size++]=element;
	}
	T& operator[] (unsigned int i)
	{
		if (i<size)
			return array[i];
		cout<<"out of bound error\n";
	}
	unsigned int getSize(){
		return size;
	}
	bool operator==(const Vector<T>& obj)
	{
		if (size!=obj.size)
			return false;
		for (unsigned int i=0; i<size; i++)
		{
			if (array[i]!=obj.array[i])
				return false;
		}
		return true;
	}
	const T& removeLast()
	{
		size--;
		return array[size];
	}
	void clear()
	{
		size=0;
	}
	bool operator<(const Vector<T>& obj)
	{
		for (unsigned int i=0; i<size && i<obj.size; i++)
		{
			if (array[i]>obj.array[i])
				return false;
			else if (array[i]<obj.array[i])
				return true;
		}
		if (size<obj.size)
			return true;
		return false;
	}
	bool operator>(const Vector<T>& obj)
	{
		for (unsigned int i=0; i<size && i<obj.size; i++)
		{
			if (array[i]<obj.array[i])
				return false;
			else if (array[i]>obj.array[i])
				return true;
		}
		if (size>obj.size)
			return true;
		return false;
	}
	bool remove(const T& obj)
	{
		unsigned int i=0;
		for (;i<size; i++)
		{
			if (array[i]==obj)
				break;
		}
		if (i==size)
			return false; //object not found in array
		for (unsigned int j=i; j<size-1; j++)
			array[j]=array[j+1];
		size--;
		return true;
	}
	bool removeByIndex(unsigned int i)
	{
		if(i > size)
			return false;
		int k = 0;
		for (unsigned int j=0; j<size; j++){
			if(j != i){
				array[k]=array[j];
				k++;
			}
		}
		size--;
		return true;
	}
	bool isPresent(const T& element) //gives the index at which element is present. if not present, returns -1
	{
		for (unsigned int i=0; i<size; i++)
		{
			if (array[i]==element)
			{
				return true;
			}
		}
		return false;
	}
	~Vector()
	{
		if (array) delete[] array;
	}
};

template <typename T>
class LinkedList {//set based on linked list, returns false on insertion if element is already present
	class Node {
	public:
		T data; // data
		Node* next; // pointer to next
		Node():next(NULL){}
		Node(T data):data(data),next(NULL){}
		Node(const Node& obj)
		{
			*this=obj;
		}
		const Node& operator=(const Node& obj)
		{
			if (this!=&obj)
			{
				data=obj.data;
				next=obj.next;
			}
			return *this;
		}
		~Node(){}
	};
	Node*head;
	Node*tail;
	int size;
public:
	LinkedList():head(NULL),size(0) {}
	~LinkedList()
	{
		Node* currNode = head;
		Node* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->next;
			delete currNode; // destroy the current node
			currNode = nextNode;
		}
	}
	LinkedList(const LinkedList& obj)
	{
		size=0;
		head=NULL;
		*this=obj;
	}
	const LinkedList& operator=(const LinkedList& obj)
	{
		if (this!=&obj)
		{
			clear();
			Node* curr=obj.head;
			while (curr)
			{
				insert(curr->data);
				curr=curr->next;
			}
		}
		return *this;
	}
	bool isEmpty()const {
		return (head == NULL);
	}
	bool removeElement(const T& data) {
		Node* prevNode = NULL;
		Node* currNode = head;
		while (currNode && !(currNode->data==data)) {
			prevNode = currNode;
			currNode = currNode->next;
		}
		if (currNode == NULL) {
			return false;
		}
		if (prevNode) {
			prevNode->next = currNode->next;
			delete currNode;
		}
		else {
			head = currNode->next;
			delete currNode;
		}
		size--;
		return true;
	}
	void display()const {
		if (isEmpty() == false) {
			Node* currNode = head;
			while (currNode != NULL) {
				(currNode->data).display();
				currNode = currNode->next;
			}
		}
	}
	void clear() {
		Node* currNode = head;
		Node *cl = NULL;
		while (currNode != NULL) {
			cl = currNode;
			currNode=currNode->next;
			delete cl;
		}
		head = NULL;
		size=0;
	}
	void replaceAt(const T& x, int index) {
		Node* node = head; int ind = 0;
		while (node != NULL) {
			node = node->next;
			ind++;
		}
		if (index <= 0 || index > ind) {
			cout << "Invalid Index" << endl;
			return;
		}
		int cIndex = 2;
		Node* currNode = head;
		while (currNode  && index > cIndex) {
			currNode = currNode->next;
			cIndex++;
		}
		if (index > 1 && currNode == NULL) {
			cout << "Invalid Index" << endl;
			return;
		}
		Node* newNode = new Node;
		newNode->data = x;
		if (index == 1) {
			head->data = x;
		}
		else {
			currNode->next->data = x;
		}
	}
	bool insert(const T& x) 
	{
		if (head)
		{
			tail->next=new Node(x);
			tail=tail->next;
		}
		else
		{
			head=new Node(x);
			tail=head;
		}
		size++;
		return true;
	}
	int getSize()
	{
		return size;
	}
	void fileWrite(ofstream& file)
	{
		Node* t=head;
		while(t)
		{
			file<<t->data<<endl;
			t=t->next;
		} 
	}
	Vector<T> getAll()
	{
		Vector<T> a;
		Node* currNode = head;
		while (currNode != NULL) {
			a.addAtEnd(currNode->data);
			currNode = currNode->next;
		}
		return a;
	}
};

template <typename T>
class Heap
{
    T*data;
	int size;
public:
	Heap(int s, T*Arr){
		size = s;
		data = new T[size];
		for(int i = 0; i < size;i++){
			data[i] = Arr[i];
		}
		buildHeap();
	}
	Heap(const Heap & obj)
	{
		size=obj.size;
		data=new T[size];
		for(int i=0;i<size;i++){
			data[i]=obj.data[i];
		}
	}
	~Heap(){
		delete [] data;
	}	
	bool isEmpty(){
		if(size == 0){
			return true;
		}
		return false;
	}
	void buildHeap(){
		int i = (size/2) - 1;
		while( i >= 0){
			Heapify(i);
			i--;
		}
	}
	void Heapify(int i){
		int l = 2*i + 1 ;
		int r  = (2*i) + 2;
		int smallest;
		T temp;
		if( r >= size){
			if( l >= size){
				return;
			}
			else
				smallest = l;
		}
		else{
			if(data[l] <= data[r]){
				smallest = l;
			}
			else{
				smallest = r;
			}
		}
		if(data[smallest] < data[i]){
			temp = data[i];
			data[i] = data[smallest];
			data[smallest] = temp;
			Heapify(smallest);
		}
	}
	T deleteMin(){
		if(!isEmpty()){
			T temp = data[0];
			data[0] = data[size - 1];
			size--;
			buildHeap();
			return temp;
		}
		else{
			cout << "Empty" << endl;
			return T();
		}
	}
	void display(){
		for(int i = 0; i < size;i++){
			cout << data[i] << " ";
		}
		cout << endl;
	}
	const Heap & operator = (const Heap & obj)
	{
		if (this==&obj)
			return *this;
		size=obj.size;
		delete [] data;
		data=new T[size];
		for(int i=0;i<size;i++){
		data[i]=obj.data[i];
		}
		return *this;
	}
};

ostream& operator<<(ostream& o, string array)
{
	for (unsigned int i=0; i<array.length(); i++)
	{
		o<<array[i];
	}
	return o;
}

template <typename T>
class FixedSortedSet
{
private:
	T* array;
	unsigned int size; //no of meaningful entries in array
	unsigned int capacity; //no of entries that can be made in the array
	const bool sortedEntry;
public:
	FixedSortedSet(int capacity,bool s):array(new T[capacity]),size(0),capacity(capacity),sortedEntry(s){}
	FixedSortedSet(const FixedSortedSet<T>& obj)
	{
		array=NULL;
		*this=obj;
	}
	const FixedSortedSet<T>& operator = (const FixedSortedSet<T>& obj)
	{
		if (this==&obj)
			return *this;
		capacity=obj.capacity;
		size=obj.size;
		if (array) delete []array;
		array=new T[capacity];
		for (unsigned int i=0; i<size; i++)
		{
			array[i]=obj.array[i];
		}
		return *this;
	}
	bool removeLast()
	{
		if (size > 0)
		{
			size--;
			return true;
		}
		return false;
	}
	bool addElement(const T& element)
	{
		if (isFull())
		{
			return false;
		}
		int index=presentAt(element);
		if (index+1)
		{//presentAt returns -1 if the element does not exist
			return false;
		}
		if (sortedEntry)
		{
			array[size++]=element;
			Heap <T> H(size,array);
			for(int i = 0; i < size;i++)
				array[i] = H.deleteMin();
		}
		else
		{
			array[size++]=element;
		}
		return true;
	}
	bool isFull()
	{
		return size>=capacity;
	}
	T& operator[] (int i)
	{
		if (i<size)
			return array[i];
		cout<<"out of bound error\n";
	}
	void incSize()
	{
		size++;
	}
	int getSize(){
		return size;
	}
	void clear()
	{
		size=0;
	}
	int presentAt(const T& element) //gives the index at which element is present. if not present, returns -1
	{
		for (unsigned int i=0; i<size; i++)
		{
			if (array[i]==element)
			{
				return i;
			}
		}
		return -1;
	}
	bool removeByIndex(unsigned int i)
	{
		if(i > size)
			return false;
		int k = 0;
		for (unsigned int j=0; j<size; j++){
			if(j != i){
				array[k]=array[j];
				k++;
			}
		}
		size--;
		return true;
	}
	~FixedSortedSet()
	{
		if (array) delete[] array;
	}
};

template <typename T,typename U>
T& operator<<(T& o, Vector<U> array)
{
	for (unsigned int i=0; i<array.getSize(); i++)
	{
		o<<array[i]<<" ";//<<endl;
	}
	o<<endl;
	return o;
}

int string2int(string a,int i)
{
	if (i==a.length())
		return 0;
	int b=(a[i]-'0');
	for (unsigned int j=0; j<a.length()-i-1;j++)
		b*=10;
	b+=string2int(a,i+1);
	return b;
}
bool strCmp(string a, string b)
{
	unsigned int s=b.length();
	if (a.length()!=s)
		return false;
	for (unsigned int i=0; i<s; i++)
	{
		if (a[i]!=b[i])
			return false;
	}
	return true;
}
bool operator==(string a,string b)
{
	return strCmp(a,b);
}
string int2str(int i)
{
	if (i<10)
	{
		string a="a";
		a[0]=static_cast<char>(i+'0');
		return a;
	}
	string a="";
	a+=int2str(i/10);
	a+=int2str(i%10);
	return a;
}
char* str2CharArray(string a)
{
	char* b=new char[a.length()+1];
	for (int i=0; i<a.length(); i++)
	{
		b[i]=a[i];
	}
	b[a.length()]=0;
	return b;
}
void split(char token, Vector<string>& tokens, string data) 
{
	tokens.clear();
	string temp; bool quotes = false;
	for (unsigned int i = 0; i < data.length(); i++) {
		if(data[i] == '"'){
			if(quotes == true)
				quotes = false;
			else
				quotes = true;
			i++;
		}
		if(quotes == true)
			temp += data[i];
		else{
			if (data[i] != token)
				temp+=data[i];
			else {
				string t="";
				if (!strCmp(temp,t))
					tokens.addAtEnd(temp);
				temp="";
			}
		}
	}
	tokens.addAtEnd(temp);
}
float string2float(string a)
{
	int i = 0;
	float num = 0,f = 0.1;
	for( i = 0; a[i] != '.';i++){
		num = num*10 + (a[i] - 48);
	}
	i++;
	for( int j = i; j < a.length();j++){
		num += (a[j] - 48)*f;
		f = f*0.1;
	}
	return num;
}
string charArray2String(char* a, unsigned int size)
{
	string b="";
	for (unsigned int i=0; i<size; i++)
	{
		if (a[i]==0)
			break;
		else
			b+=a[i];
	}
	return b;
}

template <typename T/*T is data type of key*/, typename S /*S is data type of data stored*/>
class BPlusTree
{
	const int m;
	char* path;
	struct Node
	{
		//static Vector<int> freeNodesStack()
		static int NAME;
		int name;
		FixedSortedSet<T> keys;
		FixedSortedSet<int> children; //array of numbers assigned to the child nodes node
		FixedSortedSet<LinkedList<S>*> data; //data[0] stores data with keys[0]
		bool leaf;
		int rightSibling;
		Node(int m,bool l=true):keys(FixedSortedSet<T>(m-1,0)),children(FixedSortedSet<int>(m,0)),data(FixedSortedSet<LinkedList<S>*>(m-1,0)),leaf(l),rightSibling(0) //we want this capacity to be fixed
		{//root is always 1
			name=NAME++;
		}
		Node(const Node& obj)
		{
			data=NULL;
			*this=obj;
		}
		const Node& operator=(const Node& obj)
		{
			if (this!=&obj)
			{
				name.obj.name;
				keys=obj.keys;
				children=obj.children;
				data=obj.data;
				leaf=obj.leaf;
				rightSibling=obj.rightSibling;
			}
			return *this;
		}
		void writeNodeData(const char* path)
		{
			int s=strlen(path);
			char* p=new char [s+10];
			for (int i=0; i<s; i++)
			{
				p[i]=path[i];
			}
			p[s]='\\';
			p[s+1]=0;
			strcat(p,str2CharArray(int2str(name)));
			strcat(p,".csv");
			ofstream file;
			file.open(p);
			if (!file)
			{
				cout<<"file opening failed\n";
				return;
			}
			file<<leaf;
			file<<","<<rightSibling;
			file<<endl;
			if (leaf)
			{//store data
				//format of storage:
				/*
				1,rightSibling
				no of keys
				key 0,no. of data items
				data item 1
				data item 2 and so on
				key 1,no. of data items
				*/
				int s=keys.getSize();
				file<<s<<endl;
				for (int i=0; i<s; i++)
				{
					file<<keys[i]<<","<<data[i]->getSize()<<endl;
					data[i]->fileWrite(file);
				}

			}
			else
			{
				for (unsigned int i=0; i<keys.getSize(); i++)
				{
					file<<keys[i];
					if (i==keys.getSize()-1)
						file<<endl;
					else
						file<<",";
				}
				for (unsigned int i=0; i<children.getSize(); i++)
				{
					file<<children[i];
					if (i==children.getSize()-1)
						file<<endl;
					else
						file<<",";
				}
			}
			file.close();
		}
		void readNodeData(const char* path,int n)
		{
			name=n;
			NAME--;
			if (name<=0)
				return;
			int s=strlen(path);
			char* p=new char [s+10];
			for (int i=0; i<s; i++)
			{
				p[i]=path[i];
			}
			p[s]='\\';
			p[s+1]=0;
			strcat(p,str2CharArray(int2str(name)));
			strcat(p,".csv");
			ifstream file;
			file.open(p);
			if (!file)
			{
				cout<<"file opening failed\n";
				return;
			}
			file>>leaf;
			file.ignore();
			file>>rightSibling;
			file.ignore();
			keys.clear();
			data.clear();
			children.clear();
			//get all keys
			Vector<string> t(1000);
			char* line=new char[1000];
			if (leaf)
			{//get all data
				//format of storage:
				/*
				1,rightSibling
				no of keys
				key 0,no. of data items
				data item 1
				data item 2 and so on
				key 1,no. of data items
				*/
				file.getline(line,1000);
				int s=string2int(charArray2String(line,strlen(line)),0);
				for (int i=0; i<s; i++)
				{
					file.getline(line,1000);
					split(',',t,line);
					T v=fromString<T>(str2CharArray(t[0]));
					int w=string2int(t[1],0);
					for (int j=0; j<w; j++)
					{
						file.getline(line,1000);
						S u=fromString<S>(line);
						addKey(v,u);
					}
				}
			}
			else
			{//get all keys and children
				file.getline(line,1000);
				split(',',t,line);
				for (unsigned int i=0; i<t.getSize(); i++)
				{
					keys.addElement(fromString<T>(str2CharArray(t[i])));
				}
				file.getline(line,1000);
				split(',',t,line);
				for (unsigned int i=0; i<t.getSize(); i++)
				{
					int x=string2int(t[i],0);
					if (x)
						children.addElement(x);
				}
			}
			delete []line;
			file.close();
		}
		T splitNode(const T& elementToAdd, const char* path,const S& d,int child=0)//returns the median
		{
			//get m for usage throughout function
			int m=keys.getSize()+1;
			//root or non root, both require creating a right child/sibling
			Node* right=new Node(m);
			//generates the same value for both odd and even m
			int medianIndex=(m-1)/2;
			T median=keys[medianIndex];
			//true if new element is to be inserted in right
			bool condition=elementToAdd>keys[medianIndex];
			//assign keys to right node from the original node and remove those keys from the original node
			for (int i=m-2; i>=medianIndex+condition; i--) //if condition is true, one less key is taken
			{
				right->addKey(keys[i],d);
				keys.removeLast();
			}
			if (leaf)
			{//transfer data
				//assign keys and data to right node from the original node and removal is done later
				right->data.clear();
				for (int i=medianIndex+condition; i<m-1; i++)//if condition is true, one less data item is taken
				{
					//right->keys.addElement(keys[i]);
					right->data.addElement(data[i]);
				}
				right->writeNodeData(path);
				if (condition)
				{
					right->insertData(elementToAdd,d);
				}
				if (name==1)
				{//root+leaf
					//both right and left are leaf by default 
					Node* left=new Node(m);
					for (int i=0; i<medianIndex+condition; i++)
					{
						//add keys and data to left child
						left->keys.addElement(keys[i]);
						left->data.addElement(data[i]);
					}
					if (!condition)
					{
						left->insertData(elementToAdd,d);
					}
					//clear all values from root
					keys.clear();
					data.clear();
					//change root to non leaf
					leaf=0;
					//insert median in root
					median=left->keys[left->keys.getSize()-1];
					keys.addElement(median);
					//assign children to root
					children.addElement(left->name);
					children.addElement(right->name);
					//assign rightSibling of left
					left->rightSibling=right->name;
					//writeNodeData of left child
					left->writeNodeData(path);
					//delete left child
					delete left;
					//writeNodeData of root, remove this later
					writeNodeData(path);
				}
				else
				{
					//remove the excess data and keys from original node
					for (int i=medianIndex+condition; i<m-1; i++)//if condition is true, one less data item is taken
					{
						//keys.removeLast();
						data.removeLast();
					}
					if (!condition)
					{
						insertData(elementToAdd,d);
					}
					//assign rightSibling to node
					right->rightSibling=rightSibling;
					rightSibling=right->name;
					writeNodeData(path);
					median=keys[keys.getSize()-1];
				}
			}
			else
			{//transfer children
				//assign children to right node from the original node and removal is done later
				for (int i=medianIndex+condition; i<m; i++)//if condition is true, one less child is taken
				{
					right->children.addElement(children[i]);
				}
				if (condition)
				{
					right->insertMedian(elementToAdd,child);
				}
				if (name==1)
				{
					//ensure both the new children have same value of leaf as the root
					Node* left=new Node(m,0);
					right->leaf=0;
					for (int i=0; i<medianIndex+condition; i++)
					{
						//add keys and children to left child
						left->keys.addElement(keys[i]);
						left->children.addElement(children[i]);
					}
					left->children.addElement(children[medianIndex+1]);
					if (!condition)
					{
						left->insertMedian(elementToAdd,child);
					}					
					//clear all values from root
					keys.clear();
					children.clear();
					//insert median in root
					keys.addElement(median);
					//assign children to root
					children.addElement(left->name);
					children.addElement(right->name);
					//assign rightSibling of left
					left->rightSibling=right->name;
					//writeNodeData of left child
					left->writeNodeData(path);
					median=left->keys[left->keys.getSize()-1];
					//delete left child
					delete left;
					//writeNodeData of root, remove this later
					writeNodeData(path);
				}
				else
				{
					right->leaf=0;
					if (condition)
					{//new child is in right node
						//retain medianIndex+1 children in original node, remove the rest
						for (int i=children.getSize()-1; i>medianIndex+1; i--)
							children.removeLast();
					}
					else
					{//new child is in original node					
						for (int i=children.getSize()-1; i>medianIndex; i--)
							children.removeLast();
						//use insertion sort method to place the new element and the new child at the appropriate place
						insertMedian(elementToAdd,child);
					}
					//assign value to rightSibling so that on return, the newly created node is not lost
					right->rightSibling=rightSibling;
					rightSibling=right->name;
					median=keys[keys.getSize()-1];
				}
			}
			right->writeNodeData(path);
			delete right;
			writeNodeData(path);
			return median;
		}
		void insertData(const T& element, const S& d)
		{//for leaf nodes only
			int i=keys.getSize();
			keys.incSize();
			data.incSize();
			keys[i]=element;
			LinkedList<S>* t=new LinkedList<S>;
			t->insert(d);
			this->data[i]=t;
			//writeNodeData("B+InID");
			if (i<0)
				return;
			for (; i>0; i--)
			{
				if (element<keys[i-1])
				{
					keys[i]=keys[i-1];
					data[i]=data[i-1];
				}
				else
				{
					break;
				}
			}
			keys[i]=element;
			data[i]=t;
		}
		void insertMedian(const T& element, const int& child)
		{//not called when keys is full
			int i=keys.getSize();
			keys.incSize();
			children.incSize();
			keys[i]=element;
			children[i+1]=child;
			if (i<0)
				return;
			for (; i>0; i--)
			{
				if (element<keys[i-1])
				{
					keys[i]=keys[i-1];
					children[i+1]=children[i];
				}
				else
				{
					break;
				}
			}
			keys[i]=element;
			children[i+1]=child;
		}
		bool addKey(const T& element,const S& data)
		{
			if (keys.addElement(element)) //key is inserted, now insert data
			{//when non leaf calls, donot assign data to anything, non leaf calls only when not full
				if (leaf)
				{
					/*LinkedList<S>* t=new LinkedList<S>;
					t->insert(data);
					this->data.addElement(t);*/
					keys.removeLast();
					insertData(element,data);
				}
				return true;
			}
			else 
			{//insertion failed
				int index=keys.presentAt(element);
				//although isFull would require lesser processing, we are not using it to check which condition triggerred the false in keys.addElement because a key can be repeated in a full node
				if (index+1)//element is not present so insertion failed due to being full
				{//insertion failed cuz no space, return false
					this->data[index]->insert(data);
					return true;
				}
				else
				{//insertion failed cuz key already exists
					return false;
				}
			}
			
		}
		~Node(){}
	};
	Node root;
	int getIndexOfKeyLesserOrEqualToDesired(Node& node, const T& element)
	{
		int s=node.keys.getSize();
		int index=-1;
		for (; index<s-1; index++)
		{
			if (element<=node.keys[index+1])
				break;
		}
		return index;
	}
	void getAppropriateChild(Node& parent, Node& child, const T& element)
	{
		//get index of children which stores name of the desired child
		int index=getIndexOfKeyLesserOrEqualToDesired(parent,element);
		child.readNodeData(path,parent.children[index+1]);
	}
	int recursiveInsert(Node& node, const T& element, T& median,const S& d) //returns right child for the key to be inserted, returns 0 if not to be inserted  
	{
		if (node.leaf)
		{//checks if leaf is encountered to break the recursive calls
			if (node.addKey(element,d))
			{//successful insertion so update data on file
				node.writeNodeData(path);
				return 0;
			}
			else
			{//keys is full so no insertion
				median=node.splitNode(element,path,d);
				return node.rightSibling;
			}
		}
		else
		{
			Node child(m);
			getAppropriateChild(node,child,element);
			int recursiveRightChild=recursiveInsert(child,element,median,d);
			if (recursiveRightChild)
			{//insert median on unrolling of function calling stack
				if (node.keys.isFull())
				{//if keys is full, call split node for a non leaf, non root node
					median=node.splitNode(median,path,d,recursiveRightChild);
					return node.rightSibling;
				}
				else
				{//if keys is not full, simply call insert median
					node.insertMedian(median,recursiveRightChild);
					if (node.name!=1)
						node.writeNodeData(path);
					return 0;
				}
			}
			else
			{//no insertion during unroll of function calling stack
				return 0;
			}
		}
	}
	void recursiveRangeSearch(Node& node, const T& start, const T& end, Vector<LinkedList<S>*>& lists)
	{
		//roll stack to reach the leaf node
		if (node.leaf)
		{//leaf is encountered, the leaf node has multiple keys so find the wanted key
			int index=getIndexOfKeyLesserOrEqualToDesired(node,start);
			if (index<0)
				index=0;
			/*if (node.keys[index]==start)
			{
				lists.addAtEnd(node.data[index]);
			}
			if (start==end)//vector will be empty if the key doesn't exist
				return;
			*/while (node.keys[index]<=end)
			{
				if (node.keys[index]>=start)
					lists.addAtEnd(node.data[index]);
				index++;
				if (index==node.keys.getSize()) //we have exceeded limit of keys
				{
					if (node.rightSibling)
					{
						node.readNodeData(path,node.rightSibling);
						Node::NAME++;
					}
					else 
						break;
					index=0;
					//if (!(node.keys[index]<=end))
					//	break;
					//continue; //ensure that first key of rightSibling is compared before adding it to lists
				}
			}
			//lists.removeLast();
			return;
		}
		//not leaf yet so get child
		Node child(m);
		getAppropriateChild(node,child,start);
		return recursiveRangeSearch(child,start,end,lists);
	}
	int recursiveDelete(Node& node, T& elementToDel, LinkedList<S>*& list)
	{
		const static int nothing=0;
		const static int replaceKey=1;
		const static int removeKey=2;
		const static int mergeWithLeft=3;
		if (node.leaf)
		{
			int index=node.keys.presentAt(elementToDel);
			if (index+1)
			{
				node.keys.removeByIndex(index);
				node.data.removeByIndex(index);
				int minAllowed=(m+1)/2-1;
				if (node.keys.getSize()<minAllowed)
				{
					if (node.rightSibling)
					{//rightSibling exists
						Node right(m);
						right.readNodeData(path,node.rightSibling);
						if (right.keys.getSize()>minAllowed)
						{//borrow from rightSibling
							node.keys.incSize();
							node.data.incSize();
							node.keys[node.keys.getSize()-1]=right.keys[0];
							node.data[node.data.getSize()-1]=right.data[0];
							right.keys.removeByIndex(0);
							right.data.removeByIndex(0);
							right.writeNodeData(path);
							//if (index==node.data.getSize()-1)
							//{//last key in leaf node has been removed so median changes so update parentNode
								elementToDel=node.keys[node.keys.getSize()-1];
								return replaceKey;
							//}
							//else
							//{//median is unchanged so no changes in parent nodes
								//return nothing;
							//}
						}
						else
						{//borrowing not allowed so merge with right
							for (int i=0; i<right.keys.getSize(); i++)
							{//shift keys and data of rightSibling to the original node
								node.keys.addElement(right.keys[i]);
								node.data.addElement(right.data[i]);
							}
							node.rightSibling=right.rightSibling;
							return removeKey;
						}
					}
					else
					{//rightSibling doesn't exist
						return 3;
					}
				}
				else
				{
					if (index==node.data.getSize()/*size has been reduced on removal of 1 element*/)
					{//last key in leaf node has been removed so median changes so update parentNode
						elementToDel=node.keys[node.keys.getSize()-1];
						return replaceKey;
					}
					else
					{//median is unchanged so no changes in parent nodes
						return nothing;
					}
				}
			}
			else
			{//element not found
				cout<<"Key not found\n";
				return nothing;
			}
		}
		//not leaf yet so get child
		Node child(m);
		//get index of children which stores name of the desired child
		int index=getIndexOfKeyLesserOrEqualToDesired(node,elementToDel);
		int childIndex=index+1;
		bool elementToDelExistsInParent=false;
		if (index >= 0)
		{
			if (elementToDel==node.keys[index])
			{
				childIndex--;
				elementToDelExistsInParent=true;
			}
		}
		cout<<"reading child of "<<node.name<<" : "<<node.children[childIndex]<<endl;
		child.readNodeData(path,node.children[childIndex]);
		int returnValue=recursiveDelete(child,elementToDel,list);
		child.writeNodeData(path);
		if (returnValue==nothing)
		{
			return nothing;
		}
		if (returnValue==replaceKey)
		{
			if (!elementToDelExistsInParent)
				index++;
			node.keys[index]=elementToDel;
			if (index==node.keys.getSize()-1)
			{//update key in parent as well
				return 1;
			}
			else
			{//no changes required in parent
				return 0;
			}
		}
		if (returnValue==removeKey)
		{
			node.keys.removeByIndex(index);
			node.children.removeByIndex(index+(index!=node.keys.getSize()-1)+1/*deleting the rightSibling of the accessed child*/);
			int minAllowed=(m+1)/2-1;
			if (node.keys.getSize()<minAllowed)
			{

			}
			else
			{//no underflow
				if (index==node.keys.getSize()-1)
				{//update the parent node
					elementToDel=node.keys[node.keys.getSize()-1];
					return replaceKey;
				}
				else
				{
					return nothing;
				}
			}
		}
		if (returnValue==mergeWithLeft)
		{
			//Node left(m);
			//left.readNodeData(path,node.children[index-1]);
			//remove last key and last child of node so as to portray that whole of the left most node has been deleted
			node.keys.removeLast();
			node.children.removeLast();
			node.writeNodeData(path);
			child.writeNodeData(path);
			//using recursiveInsert so that any overflow during merge can automatically result in splitting
			for (unsigned int i=0; i<child.keys.getSize(); i++)
			{
				Vector<S> temp=child.data[i]->getAll();
				for (int j=0; j<temp.getSize(); j++)
				{
					T m;
					recursiveInsert(node,child.keys[i],m,temp[j]);
				}
			}
			node.writeNodeData(path);
			child.writeNodeData(path);
		}
	}
public:
	BPlusTree(int m,const char* p/*the path to directory where all its data is stored*/):m(m),root(Node(m))
	{
		int s=strlen(p);
		path=new char[s+1];
		for (int i=0; i<=s; i++)
		{
			path[i]=p[i];
		}
		//creating directory for the B+ tree
		wchar_t* dirName=new wchar_t[strlen(p)+1];
		for (unsigned int i=0; i<strlen(p)+1; i++)
		{
			dirName[i]=static_cast<wchar_t>(p[i]);			
		}
		CreateDirectory(dirName, NULL);
		delete[] dirName;
		cout<<"bplus tree created\n";
		//root.readNodeData(path,1);
	}
	void insert(const T& element,const S& data)
	{
		T median;
		recursiveInsert(root,element,median,data);
	}
	Vector<S> rangeSearch(const T& start, const T& end)
	{
		//gets Vector<LinkedList<S>*> from recursive function
		//converts it to Vector<S>
		//returns the Vector<S>
		Vector<LinkedList<S>*> lists;
		recursiveRangeSearch(root,start,end,lists);
		Vector<S> elements;
		for (unsigned int i=0; i<lists.getSize(); i++)
		{
			Vector<S> a=lists[i]->getAll();
			//cout<<a<<endl;
			for (int j=0; j<a.getSize(); j++)
			{
				elements.addAtEnd(a[j]);
			}
		}
		//cout<<elements<<endl;
		return elements;
	}
	Vector<S> pointSearch(const T& element)
	{
		Vector<LinkedList<S>*> lists;
		recursiveRangeSearch(root,element,element,lists);
		Vector<S> elements;
		for (unsigned int i=0; i<lists.getSize(); i++)
		{
			Vector<S> a=lists[i]->getAll();
			for (int j=0; j<a.getSize(); j++)
			{
				elements.addAtEnd(a[j]);
			}
		}
		return elements;
	}
	Vector<S> deleteKey(const T& e)
	{
		T element=e;
		LinkedList<S>* list=NULL;
		recursiveDelete(root,element,list);
		Vector<S> temp;
		if (list)
			temp=list->getAll();
		delete list;
		return temp;
	}
	~BPlusTree()
	{
		root.writeNodeData(path);
	}
};

template <typename T,typename S>
int BPlusTree<T,S>::Node::NAME=1;

template<typename T, typename S> //T is data, S is key
class BTree {
	struct Key
	{
		T key;
		LinkedList<S>* data;
		int rightChild;
		Key(const T& k=T(), const S& d=S()):key(k),data(new LinkedList<S>),rightChild(0)
		{
			data->insert(d);
		}
		Key(const Key& obj)
		{
			data=NULL;
			*this=obj;
		}
		void addData(const S& data)
		{
			this->data->insert(data);
		}
		const Key& operator=(const Key& obj)
		{
			if (this!=& obj)
			{
				if (data)
					delete data;
				key=obj.key;
				data= new LinkedList<S>(*(obj.data));
				rightChild=obj.rightChild;
			}
			return *this;
		}
		bool operator<(const Key& obj)const
		{
			return key<obj.key;
		}
		bool operator==(const Key& obj)const
		{
			return key==obj.key;
		}
		bool operator<=(const Key& obj)const
		{
			return (*this<obj)||(*this==obj);
		}
		bool operator>=(const Key& obj)const
		{
			return (*this>obj)||(*this==obj);
		}
		bool operator>(const Key& obj)const
		{
			return key>obj.key;
		}
		~Key()
		{
			if (data)
				delete data;
		}
	};
	struct Node
	{
		static int NAME;
		int name;
		FixedSortedSet<Key> keys;
		bool leaf;
		int smallestChild;
		Node(int m,bool l=true):keys(FixedSortedSet<Key>(m-1,1)),leaf(l),smallestChild(0)//,rightSibling(0) //we want this capacity to be fixed
		{//root is always 1
			name=NAME++;
		}
		Node(const Node& obj)
		{
			*this=obj;
		}
		const Node& operator=(const Node& obj)
		{
			if (this!=&obj)
			{
				name.obj.name;
				keys=obj.keys;
				leaf=obj.leaf;
				smallestChild=oj.smallesChild;
			}
			return *this;
		}
		void writeNodeData(const char* path)
		{
			int s=strlen(path);
			char* p=new char [s+10];
			for (int i=0; i<s; i++)
			{
				p[i]=path[i];
			}
			p[s]='\\';
			p[s+1]=0;
			strcat(p,str2CharArray(int2str(name)));
			strcat(p,".csv");
			ofstream file;
			file.open(p);
			if (!file)
			{
				cout<<"file opening failed\n";
				return;
			}
			file<<leaf;
			file<<","<<smallestChild;
			file<<endl;
			//format of storage:
			/*
			leaf,smallestChild
			no of keys
			key 0,rightChild,no. of data items
			data item 1
			data item 2 and so on
			key 1,rightChild,no. of data items
			*/
			s=keys.getSize();
			file<<s<<endl;
			for (int i=0; i<s; i++)
			{
				file<<keys[i].key<<","<<keys[i].rightChild<<","<<keys[i].data->getSize()<<endl;
				keys[i].data->fileWrite(file);
			}
			file.close();
		}
		void readNodeData(const char* path,int n)
		{
			name=n;
			NAME--;
			if (name<=0)
				return;
			int s=strlen(path);
			char* p=new char [s+10];
			for (int i=0; i<s; i++)
			{
				p[i]=path[i];
			}
			p[s]='\\';
			p[s+1]=0;
			strcat(p,str2CharArray(int2str(name)));
			strcat(p,".csv");
			ifstream file;
			file.open(p);
			if (!file)
			{
				cout<<"file opening failed\n";
				return;
			}
			file>>leaf;
			file.ignore();
			file>>smallestChild;
			file.ignore();
			keys.clear();
			Vector<string> t(1000);
			char* line=new char[1000];
			//format of storage:
			/*
			leaf,smallestChild
			no of keys
			key 0,rightChild,no. of data items
			data item 1
			data item 2 and so on
			key 1,rightChild,no. of data items
			*/
			file.getline(line,1000);
			s=string2int(charArray2String(line,strlen(line)),0);
			for (int i=0; i<s; i++)
			{
				file.getline(line,1000);
				split(',',t,line);
				T v=fromString<T>(str2CharArray(t[0]));
				int x=string2int(t[1],0);
				int w=string2int(t[2],0);
				file.getline(line,1000);
				S u=fromString<S>(line);
				Key a(v,u);
				a.rightChild=x;
				addKey(a);
				for (int j=1; j<w; j++)
				{
					file.getline(line,1000);
					S u=fromString<S>(line);
					keys[i].addData(u);
				}
			}
			delete []line;
			file.close();
		}
		bool addKey(const Key& k)
		{
			if (keys.isFull())
			{//cannot insert key
				return false;
			}
			return keys.addElement(k);
		}
		Key splitNode(const Key& toAdd,const char* path,int& child)
		{
			Key returnValue;
			int m=keys.getSize()+1;
			int medianIndex=(m-1)/2;
			Node* right=new Node(m);
			if (name==1)
			{
				Node* left=new Node(m);
				Key inRootValue;
				if (toAdd<keys[medianIndex-1])
				{
					inRootValue=keys[medianIndex-1];
					for (int i=0; i<medianIndex-1; i++)
					{
						left->addKey(keys[i]);
					}
					left->addKey(toAdd);
					for (int i=medianIndex; i<keys.getSize(); i++)
					{
						right->addKey(keys[i]);
					}
				}
				else if (toAdd>keys[medianIndex])
				{
					inRootValue=keys[medianIndex];
					for (int i=0; i<medianIndex; i++)
					{
						left->addKey(keys[i]);
					}
					right->addKey(toAdd);
					for (int i=medianIndex+1; i<keys.getSize(); i++)
					{
						right->addKey(keys[i]);
					}
				}
				else 
				{
					inRootValue=toAdd;
					for (int i=0; i<medianIndex; i++)
					{
						left->addKey(keys[i]);
					}
					for (int i=medianIndex; i<keys.getSize(); i++)
					{
						right->addKey(keys[i]);
					}
				}
				child=0;
				keys.clear();
				addKey(inRootValue);
				left->leaf=leaf;
				right->leaf=leaf;
				leaf=false;
				left->smallestChild=smallestChild;
				right->smallestChild=inRootValue.rightChild;
				smallestChild=left->name;
				keys[0].rightChild=right->name;
				left->writeNodeData(path);
				delete left;
			}
			else
			{
				if (toAdd<keys[medianIndex-1])
				{
					returnValue=keys[medianIndex-1];
					int s=keys.getSize();
					for (int i=medianIndex; i<s; i++)
					{
						right->addKey(keys[i]);
					}
					for (int i=medianIndex; i<s; i++)
					{
						keys.removeLast();
					}
					keys.removeByIndex(medianIndex-1);
					addKey(toAdd);
				}
				else if (toAdd>keys[medianIndex])
				{
					returnValue=keys[medianIndex];
					right->addKey(toAdd);
					int s=keys.getSize();
					for (int i=medianIndex+1; i<s; i++)
					{
						right->addKey(keys[i]);
					}
					for (int i=medianIndex; i<s; i++)
					{
						keys.removeLast();
					}
				}
				else 
				{
					returnValue=toAdd;
					int s=keys.getSize();
					for (int i=medianIndex; i<s; i++)
					{
						right->addKey(keys[i]);
					}
					for (int i=medianIndex; i<s; i++)
					{
						keys.removeLast();
					}
				}
				child=right->name;
			}
			right->writeNodeData(path);
			delete right;
			if (name!=1)
				writeNodeData(path);
			return returnValue;
		}
		~Node(){}
	};
	Node root;
	char* path;
	int m; 
	int getIndexOfKeyLesserOrEqualToDesired(Node& node, const T& element)
	{
		int s=node.keys.getSize();
		int index=-1;
		for (; index<s-1; index++)
		{
			if (element<node.keys[index+1].key)
				break;
		}
		return index;
	}
	void getAppropriateChild(Node& parent, Node& child, const T& element)
	{
		//get index of children which stores name of the desired child
		int index=getIndexOfKeyLesserOrEqualToDesired(parent,element);
		if (index>=0)
			child.readNodeData(path,parent.keys[index].rightChild);
		else
			child.readNodeData(path,parent.smallestChild);
	}
	void recursiveRangeSearch(Node& node, const T& start, const T& end, Vector<S>& lists)
	{
		int index=getIndexOfKeyLesserOrEqualToDesired(node, start);
		Node child(m);
		for (; index<node.keys.getSize(); index++)
		{
			if (index<0)
			{//read smallestChild
				child.readNodeData(path,node.smallestChild);
			}
			else
			{
				if (node.keys[index]>end)
				{
					return;
				}
				else if (node.keys[index]>=start)
				{
					Vector<S> a=node.keys[index].data->getAll();
					for (int j=0; j<a.getSize(); j++)
					{
						lists.addAtEnd(a[j]);
					}
				}
				child.readNodeData(path,node.keys[index].rightChild);
			}
			if (child.name)
				recursiveRangeSearch(child, start, end, lists);
		}
	}
	int recursiveInsert(Node& node, const T& element, Key& median,const S& d) //returns right child for the key to be inserted, returns 0 if not to be inserted  
	{
		int index=node.keys.presentAt(Key(element,d));
		if (index+1)
		{//repeated entry so just add data
here:
			node.keys[index].addData(d);
			if (node.name!=1)
				node.writeNodeData(path);
			return 0;
		}
		if (node.leaf)
		{//checks if leaf is encountered to break the recursive calls
			if (node.addKey(Key(element,d)))
			{//successful insertion so update data on file
				if (node.name!=1)
					node.writeNodeData(path);
				return 0;
			}
			else
			{//keys is full so no insertion
				if (node.keys.isFull())
				{
					int newChild;
					median=node.splitNode(Key(element,d),path,newChild);
					return newChild;
				}
				else
					goto here;
			}
		}
		else
		{
			Node child(m);
			getAppropriateChild(node,child,element);
			int recursiveRightChild=recursiveInsert(child,element,median,d);
			if (recursiveRightChild)
			{
				median.rightChild=recursiveRightChild;
				if (node.addKey(median))
				{//successful insertion so update data on file
					if (node.name!=1)
						node.writeNodeData(path);
					return 0;
				}
				else
				{//keys is full so no insertion
					int newChild;
					median=node.splitNode(median,path,newChild);
					return newChild;
				}
			}
			return 0;
		}
	}
	int recursiveDelete(Node& node, T& elementToDel, Vector<S>& list)
	{
		int index=node.keys.presentAt(Key(elementToDel,S()));
		if (index+1)
		{//data is found
			int temp=0;
			temp=node.keys[index].rightChild;
			Vector<S> a=node.keys[index].data->getAll();
			for (int j=0; j<a.getSize(); j++)
			{
				list.addAtEnd(a[j]);
			}
			if (node.smallestChild)
			{//deletion from internal node
				Node rightChild(m);
				rightChild.readNodeData(path,node.keys[index].rightChild);
				if (rightChild.keys.getSize()>(m+1)/2-1)
				{
					//parent takes key from the rightChild
					node.keys[index].key=rightChild.keys[0].key;
					*(node.keys[index].data)=*(rightChild.keys[0].data);
					//remove key by val from rightChild
					T element=rightChild.keys[0].key;
					Vector<S> l;
					recursiveDelete(rightChild,element,l);
					rightChild.writeNodeData(path);
				}
				else
				{
					Node leftChild(m);
					if (index-1>=0)
						leftChild.readNodeData(path,node.keys[index-1].rightChild);
					else
						leftChild.readNodeData(path,node.smallestChild);
					//put keys of rightChild to leftChild
					for (int i=0; i<rightChild.keys.getSize(); i++)
					{
						leftChild.keys.incSize();
						leftChild.keys[leftChild.keys.getSize()-1]=rightChild.keys[i];
					}
					leftChild.writeNodeData(path);
					temp=0;//no lostChild
					//delete key from node
					node.keys.removeByIndex(index);
					//delete file of key's rightChild
				}
			}
			else
				node.keys.removeByIndex(index);
			return temp;
		}
		if (node.smallestChild)
		{
			Node child(m);
			index=getIndexOfKeyLesserOrEqualToDesired(node,elementToDel);
			if (index>=0)
				child.readNodeData(path,node.keys[index].rightChild);
			else
				child.readNodeData(path,node.smallestChild);
			int lostChild=recursiveDelete(child,elementToDel,list);
			int minAllowed=(m+1)/2-1;
			if (child.keys.getSize()<minAllowed)
			{
				if (index+1<node.keys.getSize())
				{//child is not leftmost node
					Node rightSibling(m);
					rightSibling.readNodeData(path,node.keys[index+1].rightChild);
					//check if u can borrow from rightSibling
					if (rightSibling.keys.getSize()>minAllowed)
					{//borrow from right sibling
						//parent gives its key to deficit child
						Vector<S> allData=node.keys[index+1].data->getAll();
						for (int i=0; i<allData.getSize(); i++)
						{
							if (!child.addKey(Key(node.keys[index+1].key,allData[i])))
								child.keys[child.keys.getSize()-1].addData(allData[i]);
						}
						if (lostChild)//borrowed key from rightChild
							child.keys[child.keys.getSize()-1].rightChild=lostChild;
						else
							child.keys[child.keys.getSize()-1].rightChild=rightSibling.smallestChild;
						//parent takes key from the rightSibling
						node.keys[index+1].key=rightSibling.keys[0].key;
						*(node.keys[index+1].data)=*(rightSibling.keys[0].data);
						rightSibling.smallestChild=rightSibling.keys[0].rightChild;
						//remove key by index from rightSibling
						rightSibling.keys.removeByIndex(0);
						rightSibling.writeNodeData(path);
					}
					else
					{//merge with rightSibling
						if (node.name==1)
						{
							//cout<<"here\n";
							if (index>=0)
								node.keys[index].rightChild=child.smallestChild;
							else
								node.smallestChild=child.smallestChild;
							node.keys[index+1].rightChild=rightSibling.smallestChild;
							for (int i=0; i<child.keys.getSize(); i++)
							{
								Vector<S> allData=child.keys[i].data->getAll();
								node.addKey(Key(child.keys[i].key,allData[0]));
								int k=node.keys.presentAt(child.keys[i]);
								node.keys[k].rightChild=child.keys[i].rightChild;
								for (int j=1; j<allData.getSize(); j++)
								{
									node.keys[k].addData(allData[j]);
								}
							}
							for (int i=0; i<rightSibling.keys.getSize(); i++)
							{
								Vector<S> allData=rightSibling.keys[i].data->getAll();
								node.addKey(Key(rightSibling.keys[i].key,allData[0]));
								int k=node.keys.presentAt(rightSibling.keys[i]);
								node.keys[k].rightChild=rightSibling.keys[i].rightChild;
								for (int j=1; j<allData.getSize(); j++)
								{
									node.keys[k].addData(allData[j]);
								}
							}
						}
						else
						{
							child.keys.incSize();
							child.keys[child.keys.getSize()-1]=node.keys[index+1];
							for (int i=0; i<rightSibling.keys.getSize(); i++)
							{
								child.keys.incSize();
								child.keys[child.keys.getSize()-1]=rightSibling.keys[i];
							}
							node.keys.removeByIndex(index+1);
							//delete rightChild's file
						}
					}
					child.writeNodeData(path);
				}
				else
				{//child is leftmost node
					Node leftSibling(m);
					if (index>0)
						leftSibling.readNodeData(path,node.keys[index-1].rightChild);
					else
						leftSibling.readNodeData(path,node.smallestChild);
					//check if u can borrow from leftSibling
					if (leftSibling.keys.getSize()>minAllowed)
					{//borrow from left sibling
						//parent gives its key to deficit child
						Vector<S> allData=node.keys[index].data->getAll();
						for (int i=0; i<allData.getSize(); i++)
						{
							if (!child.addKey(Key(node.keys[index].key,allData[i])))
								child.keys[0].addData(allData[i]);
						}
						if (lostChild)//borrowed key from leftChild
							child.keys[0].rightChild=lostChild;
						else
							child.keys[0].rightChild=leftSibling.smallestChild;
						//parent takes key from the leftSibling
						node.keys[index].key=leftSibling.keys[leftSibling.keys.getSize()-1].key;
						*(node.keys[index].data)=*(leftSibling.keys[leftSibling.keys.getSize()-1].data);
						leftSibling.smallestChild=leftSibling.keys[leftSibling.keys.getSize()-1].rightChild;
						//remove key by index from leftSibling
						leftSibling.keys.removeByIndex(leftSibling.keys.getSize()-1);
						leftSibling.writeNodeData(path);
					}
					else
					{//merge with leftSibling
						if (node.name==1)
						{
							//cout<<"here\n";
							if (index>0)
								node.keys[index-1].rightChild=leftSibling.smallestChild;
							else
								node.smallestChild=leftSibling.smallestChild;
							node.keys[index].rightChild=child.smallestChild;
							for (int i=0; i<leftSibling.keys.getSize(); i++)
							{
								Vector<S> allData=leftSibling.keys[i].data->getAll();
								node.addKey(Key(leftSibling.keys[i].key,allData[0]));
								int k=node.keys.presentAt(leftSibling.keys[i]);
								node.keys[k].rightChild=leftSibling.keys[i].rightChild;
								for (int j=1; j<allData.getSize(); j++)
								{
									node.keys[k].addData(allData[j]);
								}
							}
							for (int i=0; i<child.keys.getSize(); i++)
							{
								Vector<S> allData=child.keys[i].data->getAll();
								node.addKey(Key(child.keys[i].key,allData[0]));
								int k=node.keys.presentAt(child.keys[i]);
								node.keys[k].rightChild=child.keys[i].rightChild;
								for (int j=1; j<allData.getSize(); j++)
								{
									node.keys[k].addData(allData[j]);
								}
							}
							//delete files of right and left siblings
						}
						else
						{
							leftSibling.keys.incSize();
							leftSibling.keys[leftSibling.keys.getSize()-1]=node.keys[index];
							for (int i=0; i<child.keys.getSize(); i++)
							{
								leftSibling.keys.incSize();
								leftSibling.keys[leftSibling.keys.getSize()-1]=child.keys[i];
							}
							node.keys.removeByIndex(index);
							//delete child's file
							leftSibling.writeNodeData(path);
						}
					}
				}
			}
			child.writeNodeData(path);
		}
		else
		{//key is non existent
			return 0;
		}
	}
public:
	BTree(int m, const char* p/*the path to directory where all its data is stored*/) :m(m),root(Node(m))
	{
		int s = strlen(p);
		path = new char[s + 1];
		for (int i = 0; i <= s; i++)
		{
			path[i] = p[i];
		}
		//creating directory for the B+ tree
		wchar_t* dirName = new wchar_t[strlen(p) + 1];
		for (unsigned int i = 0; i<strlen(p) + 1; i++)
		{
			dirName[i] = static_cast<wchar_t>(p[i]);
		}
		CreateDirectory(dirName, NULL);
		delete[] dirName;
	}
	void insert(const T& element,const S& data)
	{
		Key median;
		recursiveInsert(root,element,median,data);
		//root.writeNodeData(path);
	}
	Vector<S> rangeSearch(const T& start, const T& end)
	{
		Vector<S> lists;
		recursiveRangeSearch(root,start,end,lists);
		return lists;
	}
	Vector<S> pointSearch(const T& element)
	{
		Vector<S> lists;
		recursiveRangeSearch(root,element,element,lists);
		return lists;
	}
	Vector<S> deleteKey(const T& e)
	{
		Vector<S> list;
		T element=e;
		recursiveDelete(root,element,list);
		return list;
	}
	~BTree()
	{
		root.writeNodeData(path);
	}
};

template <typename T,typename S>
int BTree<T,S>::Node::NAME=1;

class FileData
{
	int fileNo;
	int lineNo;
public:
	FileData():fileNo(-1),lineNo(-1){}
	FileData(int f,int l):fileNo(f),lineNo(l){}
	FileData(const FileData& obj)
	{
		*this=obj;
	}
	const FileData& operator=(const FileData& obj)
	{
		if (this!=&obj)
		{
			fileNo=obj.fileNo;
			lineNo=obj.lineNo;
		}
		return *this;
	}
	~FileData(){}
	template <typename T>
	friend T& operator<<(T& o, FileData a);
	bool operator<(const FileData& obj)const
	{
		if (fileNo<obj.fileNo)
		{
			return true;
		}
		else if (fileNo==obj.fileNo)
		{
			if (lineNo<obj.lineNo)
				return true;
			return false;
		}
		return false;
	}
	bool operator>(const FileData& obj)const
	{
		if (fileNo>obj.fileNo)
		{
			return true;
		}
		else if (fileNo==obj.fileNo)
		{
			if (lineNo>obj.lineNo)
				return true;
			return false;
		}
		return false;
	}
	int getFileNo()const
	{
		return fileNo;
	}
	int getLineNo()const
	{
		return lineNo;
	}
};

template <typename T>
T fromString(char* a)
{
	return T();
}
template <>
FileData fromString<FileData>(char* a)
{
	Vector<string> b;
	split(',',b,a);
	FileData c(string2int(b[0],0),string2int(b[1],0));
	return c;
}
template <>
int fromString<int>(char* a)
{
	return string2int(charArray2String(a,strlen(a)),0);
}
template <>
float fromString<float>(char* a)
{
	 int i = 0;
	 int num1=0;
	 float num2 = 0,f = 0.1;
	 for( i = 0; i<strlen(a);i++){
		if (a[i]=='.')
		{
			i++;
			 num2=num1;
			 for( int j = i; j < i+1/*strlen(a)*/;j++){
				num2 += (a[j] - 48)*f;
				f = f*0.1;
			 }
			 break;
		}
		else if (a[i]==' ')
		{
			//num2=num1;
			break;
		}
		num1 = num1*10 + (a[i] - 48);
	 }
	 if (!num2)
		 //cout<<"here\n";
		 num2=num1;
	 return num2;
}
template <>
string fromString<string>(char* a)
{
	return charArray2String(a,strlen(a));
}

template <typename T>
T& operator<<(T& o, FileData a)
{
	o<<a.fileNo<<','<<a.lineNo;
	return o;
}

class DSDB
{
	string fieldNames[7];
	Vector<string> fileNames;
	Vector<int> charsPerLine;
	enum TreeType
	{//tree type + t data type + s data type
		BIntFileData,
		BFloatFileData,
		BStringFileData,
		BPlusIntFileData,
		BPlusFloatFileData,
		BPlusStringFileData
	};
	TreeType treeType;
	int key;
	BTree<int,FileData>* tree0;
	BTree<float,FileData>* tree1;
	BTree<string,FileData>* tree2;
	BPlusTree<int,FileData>* tree3;
	BPlusTree<float,FileData>* tree4;
	BPlusTree<string,FileData>* tree5;
	void preProcessFiles()
	{
		cout<<"Pre-processing files\n";
		int lineLength;
		for(int i = 0; i < fileNames.getSize();i++)
		{
			fstream obj;
			obj.open(fileNames[i]);
			if (!obj)
			{
				cout<<"file opening failed\n";
				return;
			}
			Vector<char*> data(1310);
			lineLength = 0;
			while (!obj.eof())
			{
				char* temp=new char[250];
				obj.getline(temp,250);
				data.addAtEnd(temp);
				if(strlen(temp) > lineLength)
					lineLength = strlen(temp);
			}
			obj.close();
			obj.open(fileNames[i]);
			for(int j = 0; j < data.getSize() - 1;j++)
			{
				obj << data[j];
				for(int k = 0; k < lineLength - strlen(data[j]);k++)
					obj << " ";
				if( j != data.getSize() - 2)
					obj << endl;
			}
			obj.close();
			for (int i=0; i<data.getSize(); i++)
			{
				delete [] data[i];
			}
			charsPerLine.addAtEnd(lineLength);
			cout<<"File "<<i+1<<" completed\n";
		}
	}
	template <typename T>
	void feedData(BPlusTree<T,FileData>* tree)
	{
		cout<<"Feeding Data";
		for (int i=0; i<fileNames.getSize(); i++)
		{
			//read line wise and keep on feeding data line wise
			ifstream obj;
			obj.open(fileNames[i]);
			if (!obj)
			{
				cout<<"file opening failed\n";
				return;
			}
			Vector<string> fields;
			char* temp=new char[1000];
			obj.getline(temp,1000);
			while (temp[strlen(temp)-1]==' ')
				temp[strlen(temp)-1]=0;//remove the excess spaces
			int lineNo=1;
			while (!obj.eof())
			{
				obj.getline(temp,1000);
				//split line into fields
				split(',', fields, temp);
				tree->insert(fromString<T>(str2CharArray(fields[key])),FileData(i,lineNo));
				//cout<<lineNo<<" "<<temp<<endl;
				if (lineNo%50==0)
					cout<<".";
				lineNo++;
			}
			delete [] temp;
			obj.close();
		}
		cout<<endl;
	}
	template <typename T>
	void feedData(BTree<T,FileData>* tree)
	{
		cout<<"Feeding data";
		for (int i=0; i<fileNames.getSize(); i++)
		{
			//read line wise and keep on feeding data line wise
			ifstream obj;
			obj.open(fileNames[i]);
			if (!obj)
			{
				cout<<"file opening failed\n";
				return;
			}
			//Vector<char*> data(1310);
			//lineLength = 0;
			Vector<string> fields;
			char* temp=new char[1000];
			obj.getline(temp,1000);
			while (temp[strlen(temp)-1]==' ')
				temp[strlen(temp)-1]=0;//remove the excess spaces
			int lineNo=1;
			while (!obj.eof())
			{
				obj.getline(temp,1000);
				//split line into fields
				split(',', fields, temp);
				//cout<<fields<<endl;
				tree->insert(fromString<T>(str2CharArray(fields[key])),FileData(i,lineNo));
				//cout<<lineNo<<" "<<temp<<endl;
				lineNo++;
				if (lineNo%50==0)
					cout<<".";
			}
			delete [] temp;
			obj.close();
		}
		cout<<endl;
	}
	void createNewIndex()
	{
		cout<<"Which would you like to use?\n1. B Tree\n2. B+ Tree\n";
		int choice;
		do
		{
			cout<<"Enter your choice: ";
			cin>>choice;
		} while (choice!=1 && choice!=2);
		int treeType=choice-1; //0 for b, 1 for b+
		cout<< endl;
		do
		{
			cout<<"Enter value of m: ";
			cin>>choice;
		} while (choice<4); 
		int m = choice;
		cout<< endl;
		cout << "Enter your choice of key:\n"
			<<"1. ID\n"
			<<"2. Year\n"
			<<"3. 113 Cause Name\n"
			<<"4. Cause Name\n"
			<<"5. State\n"
			<<"6. Deaths\n"
			<<"7. Age-Adjusted Death Rate\n";
		bool valid = false;	
		do
		{
			cout<<"Enter your choice: ";
			cin>>choice;
			if(choice < 1 || choice > 7)
				cout << "Invalid choice, re-enter\n";
			else
				valid = true;
		} while (!valid);
		key=choice-1;
		cout << endl;
		string name;
		if(treeType == 0)
			name += "BIn";
		else
			name += "B+In";
		name += fieldNames[key];
		name += int2str(m);
		clearTrees();
		if (choice==1 || choice==2 || choice==6)
		{//T is int
			if (treeType)
			{
				this->treeType=BPlusIntFileData;
				tree3=new BPlusTree<int,FileData>(m,str2CharArray(name));
				feedData(tree3);
			}
			else
			{
				this->treeType=BIntFileData;
				tree0=new BTree<int,FileData>(m,str2CharArray(name));
				feedData(tree0);
			}
		}
		else if (choice==7)
		{//T is float
			if (treeType)
			{
				this->treeType=BPlusFloatFileData;
				tree4=new BPlusTree<float,FileData>(m,str2CharArray(name));
				feedData(tree4);
			}
			else
			{
				this->treeType=BFloatFileData;
				tree1=new BTree<float,FileData>(m,str2CharArray(name));
				feedData(tree1);
			}
		}
		else
		{//T is string
			if (treeType)
			{
				this->treeType=BPlusStringFileData;
				tree5=new BPlusTree<string,FileData>(m,str2CharArray(name));
				feedData(tree5);
			}
			else
			{
				this->treeType=BStringFileData;
				tree2=new BTree<string,FileData>(m,str2CharArray(name));
				feedData(tree2);
			}
		}
	}
	void pointSearch()
	{
		Vector<FileData> locations;
		getPointSearch(locations);
		displayRecords(locations);
	}
	void getPointSearch(Vector<FileData>& desiredLocations)
	{
		cout << "You are currently using " << fieldNames[key] << " as your key\n";
		cout<<"Enter the desired key: ";
		switch (treeType)
		{
		case BIntFileData:
			{
				int key;
				cin>>key;
				desiredLocations=tree0->pointSearch(key);
				break;
			}
		case BFloatFileData:
			{
				float key;
				cin>>key;
				desiredLocations=tree1->pointSearch(key);
				break;
			}
		case BStringFileData:
			{
				string key;
				cin>>key;
				desiredLocations=tree2->pointSearch(key);
				break;
			}
		case BPlusIntFileData:
			{
				int key;
				cin>>key;
				desiredLocations=tree3->pointSearch(key);
				break;
			}
		case BPlusFloatFileData:
			{
				float key1;
				cin>>key1;
				desiredLocations=tree4->pointSearch(key1);
				break;
			}
		case BPlusStringFileData:
			{
				string key1;
				cin.ignore();
				getline(cin,key1);
				desiredLocations=tree5->pointSearch(key1);
				break;
			}
		}
	}
	void displayRecords(Vector<FileData> locations)
	{
		if (!locations.getSize())
		{
			cout<<"No records match\n";
			return;
		}
		int openFile=locations[0].getFileNo();
		ifstream file(fileNames[openFile]);
		char* temp=new char[1000];
		for (int i=0; i<locations.getSize(); i++)
		{
			if (locations[i].getFileNo()!=openFile)
			{
				file.close();
				openFile=locations[i].getFileNo();
				file.open(fileNames[openFile]);
			}
here:
			file.seekg((charsPerLine[openFile]+2)*(locations[i].getLineNo()),ios::beg);
			file.getline(temp,1000);
			if (!file)
			{//reaches end of file so fstream needs to be renewed
				file.close();
				file.open(fileNames[openFile]);
				goto here;
			}
			cout<<temp<<endl;
		}
		delete[] temp;
		file.close();
	}
	void rangeSearch()
	{
		cout << "You are currently using " << fieldNames[key] << " as your key\n";
		cout<<"Enter the starting key: ";
		Vector<FileData> desiredLocations;
		switch (treeType)
		{
		case BIntFileData:
			{
				int key1,key2;
				cin>>key1;
				cout<<"Enter the ending key: ";
				cin>>key2;
				desiredLocations=tree0->rangeSearch(key1,key2);
				break;
			}
		case BFloatFileData:
			{
				float key1,key2;
				cin>>key1;
				cout<<"Enter the ending key: ";
				cin>>key2;
				desiredLocations=tree1->rangeSearch(key1,key2);
				break;
			}
		case BStringFileData:
			{
				string key1,key2;
				cin>>key1;
				cout<<"Enter the ending key: ";
				cin>>key2;
				desiredLocations=tree2->rangeSearch(key1,key2);
				break;
			}
		case BPlusIntFileData:
			{
				int key1,key2;
				cin>>key1;
				cout<<"Enter the ending key: ";
				cin>>key2;
				desiredLocations=tree3->rangeSearch(key1,key2);
				break;
			}
		case BPlusFloatFileData:
			{
				float key1,key2;
				cin>>key1;
				cout<<"Enter the ending key: ";
				cin>>key2;
				desiredLocations=tree4->rangeSearch(key1,key2);
				break;
			}
		case BPlusStringFileData:
			{
				string key1,key2;
				cin.ignore();
				getline(cin,key1);
				cout<<"Enter the ending key: ";
				getline(cin,key2);
				desiredLocations=tree5->rangeSearch(key1,key2);
				break;
			}
		}
		displayRecords(desiredLocations);
	}
	void updateField()
	{
		Vector<FileData> locations;
		getPointSearch(locations);
		if (!locations.getSize())
		{
			cout<<"Key doesnot exist\n";
			return;
		}
		cout<<"What field would you like to change?\n";
		for (int i=0; i<7; i++)
		{
			cout<<i+1<<". "<<fieldNames[i]<<endl;
		}
		int choice;
		do
		{
			cout<<"Enter your choice: ";
			cin>>choice;
		}while(choice<1 || choice>7);
		cout<<"Enter old value: ";
		if (choice==1 || choice==2 || choice==6)
		{//T is int
			int oldVal;
			cin>>oldVal;
			eliminateUnwanted(locations,choice-1,oldVal);
		}
		else if (choice==7)
		{//T is float
			float oldVal;
			cin>>oldVal;
			eliminateUnwanted(locations,choice-1,oldVal);
		}
		else
		{//T is string
			string oldVal;
			cin.ignore();
			getline(cin,oldVal);
			eliminateUnwanted(locations,choice-1,oldVal);
		}
		if (locations.getSize()==0)
		{
			cout<<"No records fulfill this criteria\n";
		}
		else if (locations.getSize()>1)
		{
			cout<<"Error! More than 1 records fulfill the given criteria\n";
		}
		else
		{
			cout<<"Enter new value: ";
			if (choice==1 || choice==2 || choice==6)
			{//T is int
				int newVal;
				cin>>newVal;
				Overwrite(locations[0],choice-1,newVal);
			}
			else if (choice==7)
			{//T is float
				float newVal;
				cin>>newVal;
				Overwrite(locations[0],choice-1,newVal);
			}
			else
			{//T is string
				string newVal;
				cin.ignore();
				getline(cin,newVal);
				Overwrite(locations[0],choice-1,newVal);
			}
			cout<<"Successfully updated\n";
		}
	}
	template <typename T>
	void Overwrite(const FileData& file,int fieldIndex,const T& newVal)
	{
		fstream obj,obj2;
		obj.open(fileNames[file.getFileNo()],ios::in); 
		obj2.open("Temp.csv",ios::out);
		int line_num = 0;
		string temp;
		while(!obj.eof()){
			if(line_num == file.getLineNo())
			{
				getline(obj,temp);
				line_num++;
				Vector<string> fields;
				split(',',fields,temp);
				for (int i=0; i<7; i++)
				{
					if (i==fieldIndex)
					{
						obj2<<newVal;
					}
					else
					{
						obj2<<fields[i];
					}
					if (i==6)
						cout<<endl;
					else
						cout<<',';
				}
			}
			getline(obj,temp);
			obj2 << temp << endl;
			line_num++;
		}
		obj.clear();
		obj.close();
		obj2.close();
		remove(str2CharArray(fileNames[file.getFileNo()]));
		rename("Temp.csv",str2CharArray(fileNames[file.getFileNo()]));
	}
	template <typename T>
	void eliminateUnwanted(Vector<FileData>& locations,int fieldIndex, const T& oldVal)
	{
		int openFile=locations[0].getFileNo();
		ifstream file(fileNames[openFile]);
		//char* temp=new char[1000];
		string temp;
		for (int i=0; i<locations.getSize(); )
		{
			if (locations[i].getFileNo()!=openFile)
			{
				file.close();
				openFile=locations[i].getFileNo();
				file.open(fileNames[openFile]);
			}
here:
			file.seekg((charsPerLine[openFile]+2)*(locations[i].getLineNo()),ios::beg);
			getline(file,temp);
			if (!file)
			{//reaches end of file so fstream needs to be renewed
				file.close();
				file.open(fileNames[openFile]);
				goto here;
			}
			//compare the specified field
			Vector<string> fields;
			split(',',fields,temp);
			if (fromString<T>(str2CharArray(fields[fieldIndex]))!=oldVal)
			{
				locations.removeByIndex(i);
			}
			else
			{
				i++;
			}
		}
		//delete[] temp;
		file.close();
	}
	/*void removeRecords(Vector<FileData> locations)
	{
		if (!locations.getSize())
		{
			cout<<"No records match\n";
			return;
		}
		for (int i=0; i<fileNames.getSize(); i++)
		{
			ifstream file(fileNames[i]);
			ofstream temp("Temp.csv");
			char* temp=new char[1000];
			int lineNo=0;
			delete[] temp;
			file.close();
			temp.close();
		}
	}*/
	void deleteTuples()
	{
		cout << "You are currently using " << fieldNames[key] << " as your key\n";
		cout<<"Enter the desired key: ";
		switch (treeType)
		{
		case BIntFileData:
			{
				int key;
				cin>>key;
				desiredLocations=tree0->deleteKey(key);
				break;
			}
		case BFloatFileData:
			{
				float key;
				cin>>key;
				desiredLocations=tree1->deleteKey(key);
				break;
			}
		case BStringFileData:
			{
				string key;
				cin>>key;
				desiredLocations=tree2->deleteKey(key);
				break;
			}
		case BPlusIntFileData:
			{
				cout<<"Sorry! Couldn't perfect deletion in time\n";
				//int key;
				//cin>>key;
				//desiredLocations=tree3->pointSearch(key);
				break;
			}
		case BPlusFloatFileData:
			{
				cout<<"Sorry! Couldn't perfect deletion in time\n";
				//float key1;
				//cin>>key1;
				//desiredLocations=tree4->pointSearch(key1);
				break;
			}
		case BPlusStringFileData:
			{
				cout<<"Sorry! Couldn't perfect deletion in time\n";
				//string key1;
				//cin.ignore();
				//getline(cin,key1);
				//desiredLocations=tree5->pointSearch(key1);
				break;
			}
		}
	}
	void queriesMenu()
	{
restart:
		cout<<"Enter the number corresponding to the required query:\n"
			<<"1. Create new index\n"
			<<"2. Point search using current key\n"
			<<"3. Range search using current key\n"
			<<"4. Update a field of a tuple (specified using current key)\n"
			<<"5. Delete tuples with specified key\n"
			<<"6. Delete tuples with specified key and specified value in a field\n"
			<<"7. Exit Program\n"
			<<"Enter your choice: ";
		int choice;
		cin>>choice;
		switch (choice)
		{
		case 1:
			{
				createNewIndex();
				break;
			}
		case 2:
			{
				pointSearch();
				break;
			}
		case 3:
			{
				rangeSearch();
				break;
			}
		case 4:
			{
				updateField();
				break;
			}
		case 5:
			{
				deleteTuples();
				break;
			}
		case 6:
			{
				//deleteTuplesIf();
				break;
			}
		case 7:
			{
				cout<<"You are now leaving DSDB\n";
				break;
			}
		default:
			{
				cout<<"Invalid Choice\n";
				break;
			}
		}
		if (choice!=7)
			goto restart;
	}
	void clearTrees()
	{
		if (tree0)
		{
			delete tree0;
			tree0=NULL;
		}
		if (tree1)
		{
			delete tree1;
			tree1=NULL;
		}
		if (tree2)
		{
			delete tree2;
			tree2=NULL;
		}
		if (tree3)
		{
			delete tree3;
			tree3=NULL;
		}
		if (tree4)
		{
			delete tree4;
			tree4=NULL;
		}
		if (tree5)
		{
			delete tree5;
			tree5=NULL;
		}
	}
public:
	DSDB(Vector<string> fileNames):tree0(NULL),tree1(NULL),tree2(NULL),tree3(NULL),tree4(NULL),tree5(NULL)//receives an array of names of all the files that we are to give user access to
	{
		this->fileNames=fileNames;
		fieldNames[0]="ID";
		fieldNames[1]="Year";
		fieldNames[2]="113 Cause Name";
		fieldNames[3]="Cause Name";
		fieldNames[4]="State";
		fieldNames[5]="Deaths";
		fieldNames[6]="Age-Adjusted Death Rate";
		preProcessFiles();
		cout<<"-----------------------------------WELCOME TO DSDB-----------------------------------\n"
			<<"Create your first tree now:\n";
		createNewIndex();
		queriesMenu();
	}
	~DSDB()
	{
		clearTrees();
	}
};

int main()
{
	/*BTree<int,int> a(5,"BInID");
	int array[26]={2,13,6,0,7,4,10,16,12,5,22,11,19,25,15,17,23,24,20,8,1,9,14,18,21,3};
	for (int i=0; i<26; i++)
	{
		int element=array[i];
		if (i==5)
			cout<<"here\n";
		a.insert(array[i],array[i]);
		a.insert(array[i],array[i]);
	}
	a.insert(2,2);
	a.deleteKey(14);
	//a.deleteKey(5);
	a.deleteKey(19);
	a.deleteKey(7);
	a.deleteKey(6);
	//a.deleteKey(2);
	a.deleteKey(24);
	a.deleteKey(9);
	a.deleteKey(10);
	a.deleteKey(13);*/
	//Vector<int> b=a.pointSearch(2);
	//cout<<b<<endl;
	/*BPlusTree<int,int> a(5,"B+InID");
	int array[26]={'C','N','G','A','H','E','K','Q','M','F','W','L','T','Z','P','R','X','Y','U','I','B','J','O','S','V','D'};
	for (int i=0; i<26; i++)
	{
		array[i]-='A';
		a.insert(array[i],array[i]);
	}
	Vector<int> b=a.deleteKey(12);
	b=a.deleteKey(3);
	b=a.deleteKey(25);
	b=a.deleteKey(10);
	b=a.deleteKey(11);
	b=a.deleteKey(2);*/
	Vector<string> names;
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_2.csv");
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_3.csv");
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_4.csv");
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_5.csv");
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_6.csv");
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_7.csv");
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_8.csv");
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_9.csv");
	names.addAtEnd("NCHS_-_Leading_Causes_of_Death__United_States_10.csv");
	DSDB a(names);
	return 0;
}

