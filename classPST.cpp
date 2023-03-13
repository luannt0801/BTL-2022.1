#include <iostream>
using namespace std;

struct Point {
    int x, y;
};

struct Node {
    Point p;
    Node* left;
    Node* right;
    int maxY;
};

class PST {
private:
    Node* root;

    Node* buildSubtree(Point* points, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        int mid = (start + end) / 2;
        Node* node = new Node;
        node->p = points[mid];
        node->left = buildSubtree(points, start, mid - 1);
        node->right = buildSubtree(points, mid + 1, end);
        int maxYLeft = node->left ? node->left->maxY : node->p.y;
        int maxYRight = node->right ? node->right->maxY : node->p.y;
        node->maxY = max(node->p.y, max(maxYLeft, maxYRight));
        return node;
    }

    void searchSubtree(Node* node, int x1, int y1, int x2, int y2) {
        if (!node || node->p.y > y2 || node->maxY < y1) {
            return;
        }
        if (node->p.x >= x1 && node->p.x <= x2 && node->p.y >= y1 && node->p.y <= y2) {
            cout << "(" << node->p.y << ", " << node->p.x << ")" << endl;
        }
        searchSubtree(node->left, x1, y1, x2, y2);
        searchSubtree(node->right, x1, y1, x2, y2);
    }

public:
    PST(Point* points, int n) {
        root = buildSubtree(points, 0, n - 1);
    }

    void search(int x1, int y1, int x2, int y2) {
        searchSubtree(root, x1, y1, x2, y2);
    }
};

int main() {
    Point points[] = {
        {900, 2}, {1500, 2}, {1800, 3},
        {1200, 3}, {2100, 5}, {750, 6}, {2200, 7}
    };
    int n = sizeof(points) / sizeof(points[0]);

    PST pst(points, n);

    cout << "Searching for points in rectangle (x1, y1) = (1000, 2) and (x2, y2) = (2000, 5):" << endl;
    pst.search(1000, 2, 2000, 5);

    return 0;
}
