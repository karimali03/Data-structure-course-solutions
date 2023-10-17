#include <iostream>
#include <cassert>
#include <climits>
#include <vector>		// for debug
#include <algorithm>
#include <sstream>
#include <unordered_set>
using namespace std;

struct Node {
	int data { };
	Node* next { };
	Node(int data) : data(data) {}
	~Node() {
		cout << "Destroy value: " << data <<" at address "<< this<< "\n";
	}
};

class LinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;	// let's maintain how many nodes

	vector<Node*> debug_data;	// add/remove nodes you use

	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it =find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

public:

	// Below 2 deletes prevent copy and assign to avoid this mistake
	LinkedList() {
	}
	LinkedList(const LinkedList&) = delete;
	LinkedList &operator=(const LinkedList &another) = delete;

	void debug_print_address() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}

	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int) debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n"<<flush;
	}


	void debug_verify_data_integrity() {
		if (length == 0) {
			assert(head == nullptr);
			assert(tail == nullptr);
		} else {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?
		assert(length == len);
		assert(length == (int)debug_data.size());
	}

	////////////////////////////////////////////////////////////

	void print() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << "address: "<<cur<<" Data: "<<cur->data << "\n";
		cout << "\n";
	}

	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}

	void add_node(Node* node) {
		debug_add_node(node);
		++length;
	}

	void insert_end(int value) {
		Node* item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else
			tail->next = item, tail = item;
	}
	void insert_front(int value) {		
		Node* item = new Node(value);
		add_node(item);

		item->next = head;
		head = item;

		if(length == 1)
			tail = head;

		debug_verify_data_integrity();
	}
	void deleteNext(Node* prv,Node *cur){
		Node* nxt=cur->next;
		delete cur; length--;
		if(!nxt) tail=prv;
		if(!prv) head=nxt;
		else prv->next=nxt;
	}
    

   Node* reverseChain(Node* st,Node *end){
    Node* prv=nullptr;
    Node* cur=st;
    Node* nxt=nullptr;
    if(!end->next) tail=st;
    while(prv!=end){
		nxt=cur->next;
        cur->next=prv;
        prv=cur;
        cur=nxt;
    }
    return nxt;
   }

   void Reverse(int k){
    if(!head || head==tail || k==1) return;
    int cnt=0;
    for(Node *cur=head,*prv=nullptr;cur;){
        Node* st=cur;
		Node* end=cur;
       for(Node* node=st;node && cnt<k ;node=node->next){
		   cnt++;
		   end=node;
	   }
        cur=reverseChain(st,end);
	    if(prv) prv->next=end;
		else head=end;
		prv=st;
        cnt=0;
    }
   }
};


void test2() {
	cout << "\n\ntest2\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);
	list.Reverse(3);
	// some actions
	list.print();

	string expected = "3 2 1 6 5 4";
	
}

void test3() {
	cout << "\n\ntest3\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);
	list.insert_end(6);
	list.insert_end(7);
	list.Reverse(3);
	// some actions
	list.print();

	string expected = "2 1 4 3 6 5 7";
	
}

int main() {
	 test2();
	 test3();
	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}
