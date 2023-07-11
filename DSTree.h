//
// Created by johnk on 6/20/2021.
//

#ifndef INC_21SU_PA02_DSTREE_H
#define INC_21SU_PA02_DSTREE_H

template<typename T>
class DSTree{
public:
    struct Node{
        T data;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(T val,Node* l = nullptr,Node* r= nullptr, int h = 0): data(val), left(l), right(r),height(h){};
        ~Node();
    };

    DSTree() = default;
    DSTree(const DSTree&) = delete;
    ~DSTree();

    DSTree& operator=(const DSTree&) = delete;

    int size();

    void insert(const T& val);
    void insert(const T& val,std::function<bool(const T&,const T&)> lessThan);
    void clear();

    Node* find(std::function<int(T&)> ternComp);
    Node* find(const T& key);

    void preOrder(std::function<void(Node*)>);
    void inOrder(std::function<void(Node*)>);
    void postOrder(std::function<void(Node*)>);
private:

    Node* root = nullptr;
    int Size = 0;
    int height(Node* node);
    Node* leftRot(Node* node);
    Node* rightRot(Node* node);
    Node* insert(Node*& node,const  T& val);
    Node* insert(Node*& node,const T& val,std::function<bool(const T&,const T&)> lessThan);

    Node* find(Node* node, std::function<int(T&)> ternComp);
    Node* find(Node* node, const T& key);

    void preOrder(Node* node, std::function<void(Node*)>);
    void inOrder(Node* node, std::function<void(Node*)>);
    void postOrder(Node* node, std::function<void(Node*)>);
};

template<typename T>
DSTree<T>::Node::~Node() {
    delete left;
    delete right;
}

template<typename T>
DSTree<T>::~DSTree<T>() {
    delete root;
}

template<typename T>
int DSTree<T>::size() {
    return Size;
}

template<typename T>
int DSTree<T>::height(Node *node) {
    if(node == nullptr){return 0;}
    return node->height;
}

template<typename T>
typename DSTree<T>::Node* DSTree<T>::leftRot(Node* node){
    Node* r = node->right;
    Node* Tre = r->left;
    r->left = node;
    node->right = Tre;
    node->height = 1 + std::max(height(node->right),height(node->left));
    r->height = 1 + std::max(height(r->right),height(r->left));
    return r;
}

template<typename T>
typename DSTree<T>::Node* DSTree<T>::rightRot(Node* node){
    Node* l = node->left;
    Node* Tre = l->right;
    l->right = node;
    node->left = Tre;
    node->height = 1 + std::max(height(node->right),height(node->left));
    l->height = 1 + std::max(height(l->right),height(l->left));
    return l;
}

template<typename T>
typename DSTree<T>::Node* DSTree<T>::insert(Node*& node,const T& val,std::function<bool(const T&,const T&)> lessThan) {
    if(node == nullptr){
        Node* temp = new Node(val);
        temp->height=1;
        return temp;
    }else if(lessThan(val,node->data)){
        node->left = insert(node->left,val,lessThan);
    }else if(lessThan(node->data,val)){
        node->right = insert(node->right, val,lessThan);
    }else{
        return node;
    }

    node-> height = 1 + std::max(height(node->left),height(node->right));
    int balance = 0;
    if(node!=nullptr){
        balance =  height(node->left) - height(node->right);
    }

    if( balance > 1 && lessThan(val,node->left->data)){
        return rightRot(node);
    }
    if( balance < -1 && lessThan(node->right->data,val)){
        return leftRot(node);
    }
    if( balance < -1 && lessThan(val,node->right->data)){
        node->right = rightRot(node->right);
        return leftRot(node);
    }
    if( balance > 1 && lessThan(node->left->data,val)){
        node->left = leftRot(node->left);
        return rightRot(node);
    }

    return node;
}

template<typename T>
typename DSTree<T>::Node* DSTree<T>::insert(Node*& node,const T& val) {
    if(node == nullptr){
        Node* temp = new Node(val);
        temp->height=1;
        return temp;
    }else if(val < node->data){
        node->left = insert(node->left,val);
    }else if(node->data < val){
        node->right = insert(node->right, val);
    }else{
        return node;
    }

    node-> height = 1 + std::max(height(node->left),height(node->right));
    int balance = 0;
    if(node!=nullptr){
        balance =  height(node->left) - height(node->right);
    }

    if( balance > 1 && val < node->left->data){
        return rightRot(node);
    }
    if( balance < -1 && node->right->data < val){
        return leftRot(node);
    }
    if( balance < -1 && val < node->right->data){
        node->right = rightRot(node->right);
        return leftRot(node);
    }
    if( balance > 1 && node->left->data < val){
        node->left = leftRot(node->left);
        return rightRot(node);
    }

    return node;
}
template<typename T>
void DSTree<T>::insert(const T& val) {
    Size++;
    root = insert(root,val);
}

template<typename T>
void DSTree<T>::insert(const T& val,std::function<bool(const T&,const T&)> lessThan){
    Size++;
    root = insert(root,val,lessThan);
}

template<typename T>
void DSTree<T>::clear(){
    delete root;
    root = nullptr;
}

template<typename T>
typename DSTree<T>::Node* DSTree<T>::find(const T &key) {
    return find(root,key);
}

template<typename T>
typename DSTree<T>::Node* DSTree<T>::find(std::function<int(T&)> ternComp) {
    return find(root,ternComp);
}

template<typename T>
typename DSTree<T>::Node* DSTree<T>::find(Node* node, const T &key) {
    if(node == nullptr){
        return nullptr;
    }else if(key < node->data){
        return find(node->left, key);
    }else if(node->data < key){
        return find(node->right, key);
    }else{
        return node;
    }
}

template<typename T>
typename DSTree<T>::Node* DSTree<T>::find(Node* node, std::function<int(T&)> ternComp) {
    if(node == nullptr){
        return nullptr;
    }else if(ternComp(node->data) < 0){
        return find(node->left, ternComp);
    }else if(ternComp(node->data) > 0){
        return find(node->right, ternComp);
    }else{
        return node;
    }
}

template<typename T>
void DSTree<T>::preOrder(Node* node, std::function<void(Node*)> pred){
    if(node != nullptr){
        pred(node);
        preOrder(node->left,pred);
        preOrder(node->right,pred);
    }
}

template<typename T>
void DSTree<T>::preOrder(std::function<void(Node*)> pred) {
    preOrder(root,pred);
}

template<typename T>
void DSTree<T>::inOrder(Node* node, std::function<void(Node*)> pred){
    if(node != nullptr){
        inOrder(node->left,pred);
        pred(node);
        inOrder(node->right,pred);
    }
}

template<typename T>
void DSTree<T>::inOrder(std::function<void(Node*)> pred) {
    inOrder(root,pred);
}

template<typename T>
void DSTree<T>::postOrder(Node* node, std::function<void(Node*)> pred){
    if(node != nullptr){
        postOrder(node->left,pred);
        postOrder(node->right,pred);
        pred(node);
    }
}

template<typename T>
void DSTree<T>::postOrder(std::function<void(Node*)> pred) {
    postOrder(root,pred);
}

#endif //INC_21SU_PA02_DSTREE_H