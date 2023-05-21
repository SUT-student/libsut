#include <iostream>
#include <sstream>

using namespace std;

typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

// 建立二叉树
void Creatree(BiTree& BT, char* a) {
    BiTree s[30], p;
    BT = nullptr;
    char ch;
    int top = -1, k;
    // 把字符串 a 定义为输入字符串流对象 ins
    istringstream ins(a);
    ins >> ch;
    while (ch != '@') {
        switch (ch) {
            case '(':
                top++;
                s[top] = p;
                k = 1;
                break;
            case ')':
                top--;
                break;
            case ',':
                k = 2;
                break;
            default:
                p = new BiTNode;
                p->data = ch;
                p->lchild = p->rchild = nullptr;
                if (BT == nullptr)
                    BT = p;
                else {
                    if (k == 1) s[top]->lchild = p;
                    if (k == 2) s[top]->rchild = p;
                }
        }
        ins >> ch;
    }
}

void InOrder (BiTree BT) {
    if (BT != nullptr) {
        InOrder(BT->lchild);
        cout << BT->data;
        InOrder(BT->rchild);
    }
}

// 按二叉树广义表方式输出
void PrintBtree (BiTree BT) {
    if (BT != nullptr) {
        cout << BT->data;
        if (BT->lchild || BT->rchild) {
            cout << '(';
            PrintBtree(BT->lchild);
            if (BT->rchild)
                cout << ',';
            PrintBtree(BT->rchild);
            cout << ')';
        }
    }
}

// 先序遍历非递归
void PreOrderTrav(BiTree BT) {
    BiTree S[40], p;
    int top = -1;
    if (BT) {
        top++;
        S[top] = BT;
    }
    while (top != -1) {
        p = S[top--];
        cout << p->data << ",";
        if (p->rchild) {
            top++;
            S[top] = p->rchild;
        }
        if (p->lchild) {
            top++;
            S[top] = p->lchild;
        }
    }
}

// 中序遍历非递归
void InOrderTrav(BiTree BT) {
    BiTree S[40], p = BT;
    int top = -1;
    while (p != nullptr || top != -1) {
        while (p != nullptr) {
            top++;
            S[top] = p;
            p = p->lchild;
        }
        if (top != -1) {
            p = S[top];
            top--;
            cout << p->data << ",";
            p = p->rchild;
        }
    }
}

// 按层遍历二叉树
void Levelorder(BiTree BT) {
    BiTree q[50], p;
    int front = 0, rear = 0;
    if (BT) {
        q[rear] = BT;
        rear = (rear + 1) % 50;
    }
    while (front != rear) {
        p = q[front];
        front = (front + 1) % 50;
        cout << p->data << " ";
        if (p->lchild) {
            q[rear] = p->lchild;
            rear = (rear + 1) % 50;
        }
        if (p->rchild) {
            q[rear] = p->rchild;
            rear = (rear + 1) % 50;
        }
    }
}

int getHeight(BiTree BT, int s) {
    static int ans = 0;
    if (BT == nullptr && s > ans) ans = s;
    if (BT != nullptr) {
        getHeight(BT->lchild, s + 1);
        getHeight(BT->rchild, s + 1);
    }
    return ans;
}

int getLeafNum(BiTree BT) {
    static int leaf_count = 0;
    if (BT != nullptr) {
        getLeafNum(BT->lchild);
        getLeafNum(BT->rchild);
        if (!BT->lchild && !BT->rchild) leaf_count++;
    }
    return leaf_count;
}

int main() {
    char b[30];
    BiTree bt;
    cin.getline(b, sizeof b);

    cout << "建树ing..." << endl;
    Creatree(bt, b);

    cout << "中序遍历（递归）：" << endl;
    InOrder(bt);
    cout << endl;

    cout << "中序遍历（非递归）：" << endl;
    InOrderTrav(bt);
    cout << endl;

    PrintBtree(bt);
    cout << endl;

    // 打印树的高度
    cout << "树的高度：" << endl;
    cout << getHeight(bt, 0) << endl;

    // 打印叶子节点数
    cout << "叶子节点数：" << endl;
    cout << getLeafNum(bt) << endl;
}
