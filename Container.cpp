#include<iostream>
#include "Container.hpp"
template<typename T>
struct Tree<T>::tree_element* Tree<T>::create_tree_element(T a)
    {
        struct tree_element* el=new struct tree_element;
        el->color=1;
        el->value=a;
        el->left=NULL;
        el->right=NULL;
        el->parent=NULL;
        return el;
    }
template<typename T>
struct tree_element* first;
/*void print_tree(struct tree_element* root)
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
}*/
template<typename T>
struct Tree<T>::tree_element* Tree<T>::parent(struct tree_element*el)
{
    if(el->parent!=NULL)
        return el->parent;
    else
        return NULL;
}
template<typename T>
struct Tree<T>::tree_element* Tree<T>::ded(struct Tree<T>::tree_element *el)
{
    if(parent(parent(el))!=NULL)
       return parent(parent(el));
    else
        return NULL;
}
template<typename T>
struct Tree<T>::tree_element* Tree<T>::sibling(struct Tree<T>::tree_element *el)
{
    struct Tree<T>::tree_element* p=parent(el);
    if(p==NULL)
    {
        return NULL;
    }
    if(el==p->left)
        return p->right;
    else
        return p->left;
}
template<typename T>
struct Tree<T>::tree_element* Tree<T>::uncle(struct Tree<T>::tree_element *el)
{
    struct Tree<T>::tree_element* p=parent(el);
    return sibling(p);
}
template<typename T>
void Tree<T>::turn_left(struct Tree<T>::tree_element* el)
{
    struct Tree<T>::tree_element *r=el->right;
    struct Tree<T>::tree_element*p=parent(el);
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
template<typename T>
void Tree<T>::turn_right(struct Tree<T>::tree_element *el)
{
    struct Tree<T>::tree_element *l=el->left;
    struct Tree<T>::tree_element *p=parent(el);
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
template<typename T>
void Tree<T>::insert_case3(struct Tree<T>::tree_element* el)//родитель красный,дядя черный,родитель правый,элемент правый или наоборот
{
    struct Tree<T>::tree_element* p=parent(el);
    struct Tree<T>::tree_element* d=ded(el);
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
template<typename T>
void Tree<T>::insert_case2(struct Tree<T>::tree_element* el)//родитель красный,дядя черный,родитель левый,элемент правый или наоборот
{
    struct Tree<T>::tree_element* p=parent(el);
    struct Tree<T>::tree_element* d=ded(el);
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
template<typename T>
void Tree<T>::insert_case1(struct Tree<T>::tree_element* el)//родитель красный,дядя красный
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
template<typename T>
void Tree<T>::DoInsertion(struct Tree<T>::tree_element* root,struct Tree<T>::tree_element* el)
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
template<typename T>
void Tree<T>::Correction(struct Tree<T>::tree_element* el)
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
template<typename T>
struct Tree<T>::tree_element* insertion(struct Tree<T>::tree_element* root,struct Tree<T>::tree_element* el)
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
template<typename T>
void Tree<T>::delete_case5(struct Tree<T>::tree_element* el)//брат черный,левый ребенок красный,другой черный, el левый ребенок(или наоборот)>вертим право(влево) относительно брата,меняем цвета брата и его нового родителя
{
    struct Tree<T>::tree_element* s=sibling(el);
    struct Tree<T>::tree_element* p=parent(el);
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
template<typename T>
void Tree<T>::delete_case4(struct Tree<T>::tree_element*el)//брат черный,правый ребенок красный,другой черный, el левый ребенок(или наоборот)>вертим право(влево) относительно родителя,меняем цвета брата и его нового родителя
{
    struct Tree<T>::tree_element* s=sibling(el);
    struct Tree<T>::tree_element* p=parent(el);
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
template<typename T>
void Tree<T>::delete_case3(struct Tree<T>::tree_element* el)//брат,дети брата черные,родитель крансый->меняем местами цвета ролителя и брата
{
    struct Tree<T>::tree_element* s=sibling(el);
    struct Tree<T>::tree_element* p=parent(el);
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
template<typename T>
void Tree<T>::delete_case2(struct Tree<T>::tree_element* el)//родитель,брат,дети брата черные->перекрасим брата в красный
{
    struct Tree<T>::tree_element* s=sibling(el);
    struct Tree<T>::tree_element* p=parent(el);
    if(s!=NULL && s->color==0 && s->left!=NULL && s->right!=NULL && s->left->color==0 && s->right->color==0 && p->color==0)
    {
        s->color=1;
        if(p->parent!=NULL)
        {
            //т.к. компилятор не дает ссылаться на функцию,которая ниже в программе,копирую все сюда и грущу
            struct Tree<T>::tree_element* s=sibling(p);
            struct Tree<T>::tree_element* p1=parent(p);
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
template<typename T>
void Tree<T>::delete_case1(struct Tree<T>::tree_element* el)////брат красный->меняем цвета родителя и брата,поворачиваем
{
    struct Tree<T>::tree_element* s=sibling(el);
    struct Tree<T>::tree_element* p=parent(el);
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
template<typename T>
struct Tree<T>::tree_element* Min(struct Tree<T>::tree_element* el)
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
template<typename T>
void Tree<T>::replace_el(struct Tree<T>::tree_element* el,struct Tree<T>::tree_element* child)
{
    struct Tree<T>::tree_element* p=parent(el);
    child->parent=p;
    if(p->left==el)
        p->left=child;
    else
        p->right=child;
    return;
}
template<typename T>
void Tree<T>::Delete(struct Tree<T>::tree_element* el)
{
    if(el->right!=NULL && el->left!=NULL)
    {
        el->value=(Min(el->right))->value;
        Delete(Min(el->right));
        return;
    }
    struct Tree<T>::tree_element* child;
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
template<typename T>
struct Tree<T>::tree_element* Tree<T>::search_tree_element(struct Tree<T>::tree_element* root,int a)
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
template<typename T>
struct Tree<T>::tree_element* Tree<T>::search_root(struct Tree<T>::tree_element* el)
{
    if(el->parent!=NULL)
        return search_root(el->parent);
    else
        return el;
}
template<typename T>
void Tree<T>::delete_tree(struct Tree<T>::tree_element* root)
{
    if(root->right!=NULL)
        delete_tree(root->right);
    if(root->left!=NULL)
        delete_tree(root->left);
    delete root;
}
template<typename T>
    Tree<T>::Tree()
    {
        first=NULL;
    }
template<typename T>
    Tree<T>::~Tree()
    {
        delete_tree(first);
    }
template<typename T>
    void Tree<T>::insert(T value)
    {
        if(first!=NULL)
            first=insertion(first, create_tree_element(value));
        else
            first=create_tree_element(value);
    }
template<typename T>
    bool Tree<T>::exists(T value)
    {
        if(search_tree_element(first,value)!=NULL)
            return true;
        else return false;
    }
template<typename T>
    void Tree<T>::remove(T value)
    {
        Delete(search_tree_element(first,value));
        first=search_root(first);
    }

