#ifndef CONTAINER_H
#define CONTAINER_H
template<typename T>
class Container
{
public:
    virtual ~Container();
    virtual void insert(const T& value);
    virtual bool exists(const T& value) const;
    virtual void remove(const T& value);
    //virtual void print();
};
template <typename T>
class Tree: public Container<T>
{
private:
    struct tree_element
    {
        T value;
        bool color;
        struct tree_element* left;
        struct tree_element* right;
        struct tree_element* parent;
    };
    struct tree_element* first;
    struct tree_element* create_tree_element(T a);
    struct tree_element* parent(struct tree_element *el);
struct tree_element* ded(struct tree_element *el);
struct tree_element* sibling(struct tree_element *el);
struct tree_element* uncle(struct tree_element *el);
void turn_left(struct tree_element* el);
void turn_right(struct tree_element *el);
void insert_case3(struct tree_element* el);//�������� �������,���� ������,�������� ������,������� ������ ��� ��������
void insert_case2(struct tree_element* el);//�������� �������,���� ������,�������� �����,������� ������ ��� ��������
void insert_case1(struct tree_element* el);//�������� �������,���� �������
void DoInsertion(struct tree_element* root,struct tree_element* el);
void Correction(struct tree_element* el);
struct tree_element* insertion(struct tree_element* root,struct tree_element* el);
void delete_case5(struct tree_element* el);//���� ������,����� ������� �������,������ ������, el ����� �������(��� ��������)>������ �����(�����) ������������ �����,������ ����� ����� � ��� ������ ��������
void delete_case4(struct tree_element*el);//���� ������,������ ������� �������,������ ������, el ����� �������(��� ��������)>������ �����(�����) ������������ ��������,������ ����� ����� � ��� ������ ��������
void delete_case3(struct tree_element* el);//����,���� ����� ������,�������� �������->������ ������� ����� �������� � �����
void delete_case2(struct tree_element* el);//��������,����,���� ����� ������->���������� ����� � �������
void delete_case1(struct tree_element* el);////���� �������->������ ����� �������� � �����,������������
struct tree_element* Min(struct tree_element* el);
void replace_el(struct tree_element* el,struct tree_element* child);
void Delete(struct tree_element* el);
struct tree_element* search_tree_element(struct tree_element* root,int a);
struct tree_element* search_root(struct tree_element* el);
void delete_tree(struct tree_element* root);
public:
    Tree();
    ~Tree();
    void insert(T value);
    bool exists(T value);
    void remove(T value);
};
#endif // CONTAINER_H
