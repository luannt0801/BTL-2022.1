#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<climits>

using namespace std;

struct Restaurant
{
    int k,v; // nha ha co thuoc tinh la kinh do va vi do
	float distance;
	int money;
};

struct Node
{
    Restaurant R; 
    int dmid; 
    Node* left;
    Node* right;
};

Restaurant *A;
int N; // so luong nha hang
Node *root;// nut goc

int sosanhkhoangcach(const void *a, const void *b);
void sapxeptheokc(Restaurant *A);

Node* CreateNode(Restaurant p, int d );
Node *recursive_pst_const(Restaurant *A, int l, int h);

void print_array(Restaurant *A, int N);
void print_tree(Node *root);
void print_node(Node *u);
void print_point(Restaurant p);

void report(Node *root, Restaurant q);
void find(Node *root, Restaurant q);

int main()
{
    int kinhdo, vido;
	kinhdo = 1;
	vido = 2;
    N = 7;
	A = (Restaurant*)malloc(N*sizeof(Restaurant));
	A[0].k = 192; A[0].v = 121;A[0].money = 1200;
	A[1].k = 20; A[1].v = 13;A[1].money = 900;
	A[2].k = 70; A[2].v = 102;A[2].money = 2100;
	A[3].k = 127; A[3].v = 45;A[3].money = 1500;
	A[4].k = 34; A[4].v = 60;A[4].money = 1800;
	A[5].k = 291; A[5].v = 70;A[5].money = 750;
	A[6].k = 139; A[6].v = 172;A[6].money = 2200;
	for (int i = 0; i<N; i++)
	{
		int tmp1 = 0;
		tmp1 = (sqrt( ( (A[i].k - kinhdo) * (A[i].k - kinhdo) ) + ( (A[i].v - vido) * (A[i].v - vido) )));
		A[i].distance = tmp1/1;
	}
	print_array(A,7);
	cout << endl;
	cout <<"Sap xep thu tu cac nha hang theo khoang cach: " << endl;
	sapxeptheokc(A);
	cout << endl;
	cout <<"In ra PST: "<< endl;
	print_tree(root);
	cout <<"Nha hang gan nhat la: "<< endl;
	print_point(A[0]);
	Restaurant q;
	q.k = 3; q.v = 5;q.money = 1100;
	int tmp2 = 0;
	tmp2 = (sqrt( ( (q.k - kinhdo) * (q.k - kinhdo) ) + ( (q.v - vido) * (q.v - vido) )));
	q.distance = tmp2/1;
	cout << q.k << q.v << endl;
	find(root,q);
	return 0;
}

// sắp xếp các node theo khoang cach tăng dần
void sapxeptheokc(Restaurant *A){
	qsort(A,N,sizeof(*A), sosanhkhoangcach);
	print_array(A,N);
	root = recursive_pst_const(A,0, N-1);
}

Node* CreateNode(Restaurant p, int d )
{
    Node *v = (Node *)malloc(sizeof(Node));
    v->R = p;
    v->dmid = d;
    v->left = NULL;
    v->right = NULL;
}

// đệ quy để tạo ra tree

Node *recursive_pst_const(Restaurant *A, int l, int h){

	if(h < l) 
        {
        return NULL;
        }
	else if(h == l)
        {
            return CreateNode(A[l], A[l].distance);
        }
	else if(h-l == 1){
		Node *a = CreateNode(A[l], A[l].distance);
		Node *b = CreateNode(A[h], A[h].distance);
		if(a->R.money > b->R.money){
			a->right = b;
			return a;
		}else {
			b->left = a;
			return b;
		}
	}else {
		int c;
		int min;
		// tim node có distance nho nhat
		for(int i =1; i <= h; i++)
        {
			if(A[i].distance <= min){
				min = A[i].distance;
				c = i; // c la khoang cach nho nhat
			}
		}
		// them A[k] vao cay
		Restaurant tmp = A[c];
		for(int j = c+1; j <= h; j++){
			A[j-1] = A[j];
		}
		A[h] = tmp;
		// sử dụng đệ quy
		int m = (l + h-1) >>1;
		Node *s = CreateNode(A[h], A[m].distance);
		s->left = recursive_pst_const(A, l, m);
		s->right  = recursive_pst_const(A,m+1, h-1);
		return s;

	}
}

void print_node(Node *u){
	if(u != NULL) cout << u->R.distance <<", "  << u->R.money << endl;
	else cout << "NULL ";
}

void print_array(Restaurant *A, int N){
	for(int i = 0; i < N; i++){
		cout << A[i].distance <<", "  << A[i].money << endl;
	}
}

void print_point(Restaurant p){
		cout << p.distance <<", "  << p.money << endl;
	}

void print_tree(Node *root){
	if(root == NULL) return;
	print_node(root);
	printf("left ");
	print_node(root->left);
	printf("right ");
	print_node(root->right);
	printf("\n");
	print_tree(root->left);
	print_tree(root->right); 	
}

void report(Node *root, Restaurant q){
	if(root == NULL) return;
	if(root->R.money <= q.money){
		print_point(root->R);
		report(root->left, q);
		report(root->right, q);
	}
}

void find(Node *root, Restaurant q)
{
	if(root == NULL) return;
	if(root->R.money <= q.money && root->R.distance <= q.distance){
		print_point(root->R);
	}
	if(root->dmid <= q.money){
		report(root->left, q);
		find(root->right, q);
	}else{
		find(root->left, q);
	}
}

int sosanhkhoangcach(const void* a, const void* b)
{
	Restaurant *Pa = (Restaurant *)a;
	Restaurant *Pb = (Restaurant *)b;
	return Pa->distance - Pb->distance;
}