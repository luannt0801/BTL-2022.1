#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#define INFTY 100000

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

int sosanhvido(const void *a, const void *b);
void sapxeptheovido(Restaurant *A);

Node* CreateNode(Restaurant p, int d );
Node *recursive_pst_const(Restaurant *A, int l, int h);

void print_array(Restaurant *A, int N);
void print_tree(Node *root);
void print_node(Node *u);
void report(Node *root, Restaurant q);
void print_point(Restaurant p);

void query(Node *root, Restaurant q);
void findRestaurant();

int main()
{
	/*
    int kinhdo, vido;
    cout << "Nhap vao toa do cua nha hang: "<<endl;
    cin >> kinhdo >> vido;*/
    N = 7;
	A = (Restaurant*)malloc(N*sizeof(Restaurant));
	A[0].k = 1; A[0].v = 5;
	A[1].k = 3; A[1].v = 2;
	A[2].k = 5; A[2].v = 6;
	A[3].k = 1; A[3].v = 4;
	A[4].k = 4; A[4].v = 3;
	A[5].k = 7; A[5].v = 1;
	A[6].k = 7; A[6].v = 7;
	/*
	for (int i = 0; i<=N; i++)
	{
		int tmp1 = 0;
		tmp1 = (sqrt( ( (A[i].k - kinhdo) * (A[i].k - kinhdo) ) + ( (A[i].v - vido) * (A[i].v - vido) )));
		A[i].distance = tmp1/1;
	}
	*/
	//print_array(A,7);
	//cout << endl;
	sapxeptheovido(A);
	cout << endl;
	print_tree(root);
	//Restaurant q;
	//q.k = 3; q.v = 5;
	//cout << q.k << q.v << endl;
	//query(root,q);
	//return 0;
}

// sắp xếp các node theo chiều Y tăng dần
void sapxeptheovido(Restaurant *A){
	qsort(A,N,sizeof(*A), sosanhvido);
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
    // neu co it hon 1 nut thi tra ve NULL
	if(h < l) 
        {
        return NULL;
        }
    // nếu có 1 nút
	else if(h == l)
        {
            return CreateNode(A[l], A[l].v);
        }
    // nếu có 2 nút
	else if(h-l == 1){
		Node *a = CreateNode(A[l], A[l].v);
		Node *b = CreateNode(A[h], A[h].v);
        // nếu kinh do của nut a nhỏ hơn kinh độ của nút b thì nút b nằm bên phải nút a
		if(a->R.k < b->R.k){
			a->right = b;
			return a;
        // ngược lại
		}else {
			b->left = a;
			return b;
		}
    // nếu có nhiều hơn 2 nút	
	}else {
		int c = -1;
		int min  = INFTY;
		// tim node có tọa độ x nhỏ nhất
		for(int i =1; i <= h; i++)
        {
			if(A[i].k < min){
				min = A[i].k;
				c = i; // c la toa do x nho nhat
			}
		}
		// them A[k] vao mang
		Restaurant tmp = A[c];
		for(int j = c+1; j <= h; j++){
			A[j-1] = A[j];
		}
		A[h] = tmp;
		// sử dụng đệ quy
		int m = (l + h-1) >>1;
		Node *s = CreateNode(A[h], A[m].v);
		s->left = recursive_pst_const(A, l, m);
		s->right  = recursive_pst_const(A,m+1, h-1);
		return s;

	}
}

void query(Node *root, Restaurant q){
	if(root == NULL) return;
	if(root->R.k <= q.k && root->R.v <= q.v){
		print_point(root->R);
	}
	if(root->dmid <= q.k){
		report(root->left, q);
		query(root->right, q);
	}else{
		query(root->left, q);
	}
}

void print_node(Node *u){
	if(u != NULL) cout << u->R.k << u->R.v << endl;
	else cout << "NULL ";
}

void print_array(Restaurant *A, int N){
	for(int i = 0; i < N; i++){
		cout << A[i].k << ", " << A[i].v << endl;
	}
}

void print_point(Restaurant p){
		cout << p.k << p.v << endl;
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
	if(root->R.k <= q.k){
		print_point(root->R);
		report(root->left, q);
		report(root->right, q);
	}
}

int sosanhvido(const void* a, const void* b)
{
	Restaurant *Pa = (Restaurant *)a;
	Restaurant *Pb = (Restaurant *)b;
	return Pa->v - Pb->v;
}