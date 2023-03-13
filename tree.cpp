#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define null 0 
#define INFTY 100000

typedef struct point{
	int x;
	int y;
	int id; // the index of the data point in the original array
}point;

typedef struct node{
	point p;
	int ymid;
	struct node *left;
	struct node *right;
}node;

int comp_Y(const void *a, const void *b);
void print_array(point *A, int N);
// sắp xếp theo Y
void simple_pst_construction(point *A);
// tạo ra node
node *create_node(point p, int yv);
// tạo ra cây bằng đệ quy
node *recursive_pst_const(point *A, int l, int h);
//
void print_tree(node *root);
//
void print_node(node *u);
//
void report(node *root, point q);
//in ra các điểm
void print_point(point p);
//truy vấn cây
void query(node *root, point q);

point *A;
int N; // the number of points
node *root;// the root of the pst tree

int main(){
	N = 7;
	A = (point*)malloc(N*sizeof(point));
	A[0].x = 1; A[0].y = 5; A[0].id = 0;
	A[1].x = 3; A[1].y = 2; A[1].id = 1;
	A[2].x = 5; A[2].y = 6; A[2].id = 2;
	A[3].x = 1; A[3].y = 4; A[3].id = 3;
	A[4].x = 4; A[4].y = 3; A[4].id = 4;
	A[5].x = 7; A[5].y = 1; A[5].id = 5;
	A[6].x = 7; A[6].y = 7; A[6].id = 6;
	simple_pst_construction(A);
	print_tree(root);
	point q;
	q.x = 3; q.y = 5;
	printf("quering:(%d,%d)\n", q.x, q.y);
	query(root,q);
	return 0;
}
// sắp xếp các node theo chiều V tăng dần
void simple_pst_construction(point *A){
	qsort(A,N,sizeof(*A), comp_Y);
	print_array(A,N);
	root = recursive_pst_const(A,0, N-1);
}
// đệ quy để tạo ra tree
node *recursive_pst_const(point *A, int l, int h){
	if(h < l) return null;
	else if(h== l) return create_node(A[l], A[l].y);
	else if(h-l == 1){
		node *u = create_node(A[l], A[l].y);
		node *v = create_node(A[h], A[h].y);
		if(u->p.x < v->p.x){
			u->right = v; // remember here u->y < v->y
			return u;
		}else {
			v->left = u;
			return v;
		}		
	}else {
		int k = -1;
		int min  = INFTY;
		int i = l;
		// find the point of minimum x-coordinate
		for(; i <= h; i++){
			if(A[i].x < min){
				min = A[i].x;
				k = i;
			}
		}
		// put A[k] to the end of the array  
		point tmp = A[k];
		int j = k+1;
		for(; j <= h; j++){
			A[j-1] = A[j];
		}
		A[h] = tmp;
		// call recursive-pst-construction
		int m = (l + h-1) >>1;
		node *v = create_node(A[h], A[m].y);
		v->left = recursive_pst_const(A, l, m);
		v->right  = recursive_pst_const(A,m+1, h-1);
		return v;

	}
}

void query(node *root, point q){
	if(root == null) return;
	if(root->p.x <= q.x && root->p.y <= q.y){
		print_point(root->p);
	}
	if(root->ymid <= q.x){
		report(root->left, q);
		query(root->right, q);
	}else{
		query(root->left, q);
	}

}

void report(node *root, point q){
	if(root == null) return;
	if(root->p.x <= q.x){
		print_point(root->p);
		report(root->left, q);
		report(root->right, q);
	}
}
node *create_node(point p, int yv){
	node *v = (node *)malloc(sizeof(node));
	v->p = p;
	v->ymid = yv;
	v->left = null;
	v->right = null;
}
int comp_Y(const void *a, const void *b){
	point *pa = (point *)a;
	point *pb = (point *)b;
	return pa->y - pb->y;
}

void print_tree(node *root){
	if(root == null) return;
	print_node(root);
	printf("left ");
	print_node(root->left);
	printf("right ");
	print_node(root->right);
	printf("\n");
	print_tree(root->left);
	print_tree(root->right);     	
}

void print_node(node *u){
	if(u != null) printf("(%d,%d,%d)\t", u->p.x, u->p.y, u->ymid);
	else printf("null\t");
}

void print_point(point p){
		printf("(%d,%d)\n",p.x,p.y);
	}

void print_array(point *A, int N){
	int i = 0;
	for(i = 0; i < N; i++){
		printf("(%d,%d,%d) ", A[i].x, A[i].y, A[i].id);
	}
	printf("\n");
}