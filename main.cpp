#include <iostream>
using namespace std;
class Container
{
public:
    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;

    virtual void print() = 0;

    virtual ~Container() { };
};
class Tree: public Container {
private:
    struct tree_element
    {
        int value;
        bool color;
        struct tree_element* left;
        struct tree_element* right;
        struct tree_element* parent;
    };
    struct tree_element* first;
    struct tree_element* create_tree_element(int a)
    {
        struct tree_element* el=new struct tree_element;
        el->color=1;
        el->value=a;
        el->left=NULL;
        el->right=NULL;
        el->parent=NULL;
        return el;
    }
void print_tree(struct tree_element* root)
{
    if(root->left!=NULL)
        print_tree(root->left);
    cout<<"Value= "<<root->value<<" Color- "<<root->color<<" Parent- ";
    if(root->parent!=NULL)
        cout<<root->parent->value;
    else
        cout<<"Does not exist";
    if(root->right!=NULL)
    {
        cout<<" Right- "<<root->right->value;
    }
    else
    {
        cout<<" Right- NULL";
    }
    if(root->left!=NULL)
    {
        cout<<" Left- "<<root->left->value<<endl;
    }
    else
    {
        cout<<" Left- NULL"<<endl;
    }
    if(root->parent==NULL) cout<<" # The number upper is the root #"<<endl;
    if(root->right!=NULL)
        print_tree(root->right);
}
struct tree_element* parent(struct tree_element *el)
{
    if(el->parent!=NULL)
        return el->parent;
    else
        return NULL;
}
struct tree_element* ded(struct tree_element *el)
{
    if(parent(parent(el))!=NULL)
       return parent(parent(el));
    else
        return NULL;
}
struct tree_element* sibling(struct tree_element *el)
{
    struct tree_element* p=parent(el);
    if(p==NULL)
    {
        return NULL;
    }
    if(el==p->left)
        return p->right;
    else
        return p->left;
}
struct tree_element* uncle(struct tree_element *el)
{
    struct tree_element* p=parent(el);
    return sibling(p);
}
void turn_left(struct tree_element* el)
{
    struct tree_element *r=el->right;
    struct tree_element *p=parent(el);
    el->right=r->left;
    r->left=el;
    el->parent=r;
    if(el->right!=NULL)
    {
       el->right->parent=el;
    }
    if(p!=NULL)
    {
        if(el==p->left)
        {
            p->left=r;
        }
        else
        {
            p->right=r;
        }
    }
    r->parent=p;
}
void turn_right(struct tree_element *el)
{
    struct tree_element *l=el->left;
    struct tree_element *p=parent(el);
    el->left=l->right;
    l->right=el;
    el->parent=l;
    if(el->left!=NULL)
    {
       el->left->parent=el;
    }
    if(p!=NULL)
    {
        if(el==p->left)
        {
            p->left=l;
        }
        else
        {
            p->right=l;
        }
    }
    l->parent=p;
}
void insert_case3(struct tree_element* el)//родитель красный,дядя черный,родитель правый,элемент правый или наоборот
{
    struct tree_element* p=parent(el);
    struct tree_element* d=ded(el);
    if(d!=NULL && el==p->left)
    {
        turn_right(d);
    }
    else if(d!=NULL)
    {
        turn_left(d);
    }
    p->color=0;
    if(d!=NULL)
        d->color=1;
}
void insert_case2(struct tree_element* el)//родитель красный,дядя черный,родитель левый,элемент правый или наоборот
{
    struct tree_element* p=parent(el);
    struct tree_element* d=ded(el);
    if(d!=NULL && el==p->right && p==d->left)
    {
        turn_left(p);
        el=el->left;
    }
    if(d!=NULL && el==p->left && p==d->right)
    {
        turn_right(p);
        el=el->right;
    }
    insert_case3(el);
}
void insert_case1(struct tree_element* el)//родитель красный,дядя красный
{
    parent(el)->color=0;
    uncle(el)->color=0;
    ded(el)->color=1;
    //повторятется коррекшон, потому что компилятор не дает функциям ссылаться друг на друга
    if(parent(ded(el))==NULL)
    {
        ded(el)->color=0;
    }
    else if(uncle(ded(el))!=NULL && uncle(ded(el))->color==1 && parent(ded(el))->color!=0)
    {
        insert_case1(ded(el));
    }
    else if(parent(ded(el))->color!=0)
    {
        insert_case2(ded(el));
    }
}
void DoInsertion(struct tree_element* root,struct tree_element* el)
{
    if(el->value>=root->value)
        {
            if(root->right==NULL)
            {
                root->right=el;
                el->parent=root;
            }
            else
            {
                DoInsertion(root->right,el);
            }
        }
    else
        {
            if(root->left==NULL)
            {
                root->left=el;
                el->parent=root;
            }
            else
            {
                DoInsertion(root->left,el);
            }
        }
}
void Correction(struct tree_element* el)
{
    if(parent(el)==NULL)
    {
        el->color=0;
    }
    else if(uncle(el)!=NULL && uncle(el)->color==1 && parent(el)->color!=0)
    {
        insert_case1(el);
    }
    else if(parent(el)->color!=0)
    {
        insert_case2(el);
    }
}
struct tree_element* insertion(struct tree_element* root,struct tree_element* el)
{
    if(el!=root)
    {
        DoInsertion(root,el);
    }
    Correction(el);
    while(parent(root)!=NULL)
    {
        root=parent(root);
    }
    return root;
}
void delete_case5(struct tree_element* el)//брат черный,левый ребенок красный,другой черный, el левый ребенок(или наоборот)>вертим право(влево) относительно брата,меняем цвета брата и его нового родителя
{
    struct tree_element* s=sibling(el);
    struct tree_element* p=parent(el);
    if(s!=NULL)
        s->color=p->color;
    else
        return;
    p->color=0;
    if(el==p->left)
    {
        if(s!=NULL && s->right!=NULL)
            s->right->color=0;
        turn_left(p);
    }
    else if(el==p->right)
    {
        if(s!=NULL && s->left!=NULL)
            s->left->color=0;
        turn_right(p);
    }
}
void delete_case4(struct tree_element*el)//брат черный,правый ребенок красный,другой черный, el левый ребенок(или наоборот)>вертим право(влево) относительно родителя,меняем цвета брата и его нового родителя
{
    struct tree_element* s=sibling(el);
    struct tree_element* p=parent(el);
    if(s!=NULL && s->color==0)
    {
        if(el==p->left && s->right!=NULL && s->left!=NULL && s->right->color==0 && s->left->color==1)
        {
            s->color=1;
            s->left->color=0;
            turn_right(s);
        }
        else if(el==p->left && s->right!=NULL && s->left!=NULL && s->right->color==1 && s->left->color==0)
        {
            s->color=1;
            s->left->color=0;
            turn_left(s);
        }
    }
    else
    {
        delete_case5(el);
    }
}
void delete_case3(struct tree_element* el)//брат,дети брата черные,родитель крансый->меняем местами цвета ролителя и брата
{
    struct tree_element* s=sibling(el);
    struct tree_element* p=parent(el);
    if(s!=NULL && s->color==0 && s->right!=NULL && s->left!=NULL && s->right->color==0 && s->left->color==0 && p->color==1)
    {
        s->color=1;
        p->color=0;
    }
    else
    {
        delete_case4(el);
    }
}
void delete_case2(struct tree_element* el)//родитель,брат,дети брата черные->перекрасим брата в красный
{
    struct tree_element* s=sibling(el);
    struct tree_element* p=parent(el);
    if(s!=NULL && s->color==0 && s->left!=NULL && s->right!=NULL && s->left->color==0 && s->right->color==0 && p->color==0)
    {
        s->color=1;
        if(p->parent!=NULL)
        {
            //т.к. компилятор не дает ссылаться на функцию,которая ниже в программе,копирую все сюда и грущу
            struct tree_element* s=sibling(p);
            struct tree_element* p1=parent(p);
            if(s->color==1)
            {
                (p1)->color=1;
                s->color=0;
                if(p==p1->left)
                {
                turn_left(p1);
                }
                else
                {
                turn_right(p1);
                }
            }
            delete_case2(p);
        }
    }
    else
    {
    delete_case3(el);
    }
}
void delete_case1(struct tree_element* el)////брат красный->меняем цвета родителя и брата,поворачиваем
{
    struct tree_element* s=sibling(el);
    struct tree_element* p=parent(el);
    if(s!=NULL && s->color==1)
    {
        p->color=1;
        s->color=0;
        if(el==p->left)
        {
            turn_left(p);
        }
        else
        {
            turn_right(p);
        }
    }
    delete_case2(el);
}
struct tree_element* Min(struct tree_element* el)
{
    if(el->left!=NULL)
    {
        return Min(el->left);
    }
    else
    {
        return el;
    }
}
void replace_el(struct tree_element* el,struct tree_element* child)
{
    struct tree_element* p=parent(el);
    child->parent=p;
    if(p->left==el)
        p->left=child;
    else
        p->right=child;
    return;
}
void Delete(struct tree_element* el)
{
    if(el->right!=NULL && el->left!=NULL)
    {
        el->value=(Min(el->right))->value;
        Delete(Min(el->right));
        return;
    }
    struct tree_element* child;
    if(el->right==NULL && el->left==NULL)
        child=NULL;
    else if(el->right==NULL)
        child=el->left;
    else
        child=el->right;
    if(child!=NULL)
        replace_el(el,child);
    if(child==NULL)
    {
        delete_case1(el);
        if(el->parent->right==el)
            el->parent->right=NULL;
        else
            el->parent->left=NULL;
    }
    if(el->color==0 && child!=NULL)
    {
        if(child->color==1)
        {
            child->color=0;
        }
        else
        {
            if(child->parent!=NULL)
                delete_case1(child);
        }
    }
    delete el;
}
struct tree_element* search_tree_element(struct tree_element* root,int a)
{
    if((root->value==a))
    {
        return root;
    }
    if((root->value)>a && root->left!=NULL)
        return search_tree_element(root->left,a);
    if(root->value<a && root->right!=NULL)
        return search_tree_element(root->right,a);
    return NULL;
}
struct tree_element* search_root(struct tree_element* el)
{
    if(el->parent!=NULL)
        return search_root(el->parent);
    else
        return el;
}
void delete_tree(struct tree_element* root)
{
    if(root->right!=NULL)
        delete_tree(root->right);
    if(root->left!=NULL)
        delete_tree(root->left);
    delete root;
}
public:
    Tree()
    {
        first=NULL;
    }
    ~Tree()
    {
        delete_tree(first);
    }
    void insert(int value)
    {
        if(first!=NULL)
            first=insertion(first, create_tree_element(value));
        else
            first=create_tree_element(value);
    }
    bool exists(int value)
    {
        if(search_tree_element(first,value)!=NULL)
            return true;
        else return false;
    }
    void remove(int value)
    {
        Delete(search_tree_element(first,value));
        first=search_root(first);
    }
    void print()
    {
        print_tree(first);
    }
};
int main()
{
    Container* c=new Tree();
    for(int i = 1; i < 10; i++)
        c->insert(i*i);
    cout << "Container after creation:" << endl;
    c->print();

    if(c->exists(25))
        cout << "Search for value 25: found" << endl;

    if(!c->exists(111))
        cout << "Search for value 111: not found" << endl;

    c->remove(25);
    cout << "Container after deletion of the element:" << endl;
    c->print();

    delete c;
    return 0;
}

