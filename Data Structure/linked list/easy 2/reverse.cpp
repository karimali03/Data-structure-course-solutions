#include <iostream>
#include <cassert>
#include <climits>
#include <vector>		// for debug
#include <algorithm>
#include <sstream>
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
			cout << cur->data << " ";
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

void delete_front(){
    if(!head){
        head=tail=nullptr;
    }
    else if(head==tail){
        delete_node(head);
        head=tail=nullptr;
    }
    else{
        Node* d=head;
        head=head->next;
        delete_node(d);
    }
}
void link_2(Node* one,Node* two){
	if(!one){
		head=two;
	}
	else{
		one->next=two;
	}
	if(!two) tail=one;
}
void reverse(){
    if(length<=1) return;
    Node* temp=tail; // swap tail and head 
    tail=head;
    head=temp;
    // invert every arrow 
    for(auto cur=tail->next,prev=tail;cur;){
		Node* next=cur->next;
        cur->next=prev;
        prev=cur;
        cur=next;
	}
    tail->next=nullptr;
}

};

void test1() {
	cout << "\n\ntest1\n";
	LinkedList list;
    list.insert_front(1);
    list.insert_front(2);
     list.insert_front(4);
    list.insert_front(7);
     list.insert_front(5);
    list.insert_front(6);
    list.reverse();
	list.print();
}

int main() {
	 test1();
	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}
