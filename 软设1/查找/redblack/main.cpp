#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int data_t;

typedef enum rbcolor
{
    RED = 0,
    BLACK = 1
} rbcolor;

typedef struct rnbode
{
    struct rnbode *left, *right, *parent;
    int key;
    data_t data;
    rbcolor color;
} rnbode;

/* forward declaration */
static rnbode* rb_new_node(int key, data_t data);
static rnbode*  rb_insert_rebalance(rnbode *node, rnbode *root);
static rnbode* rb_erase_rebalance(rnbode *node, rnbode *parent, rnbode *root);
rnbode* rb_insert(int key, data_t data, rnbode* root);
rnbode* rb_search(int key, rnbode* root);
rnbode* rb_erase(int key, rnbode* root);

static rnbode* rb_new_node(int key, data_t data)
{
    rnbode *node = (rnbode*)malloc(sizeof(struct rnbode));
    if (!node)
    {
        printf("malloc error!\n");
        exit(-1);
    }
    node->key = key, node->data = data;
    return node;
}

//һ������
static rnbode* rb_rotate_left(rnbode* node, rnbode* root)
{
    rnbode* right = node->right;    //ָ��ָ��ָ�� right<--node->right

    if ((node->right = right->left))
    {
        right->left->parent = node;  //�ñ������ע��ͼ��node��Ϊb�ĸ�ĸ
    }
    right->left = node;   //node��Ϊright������

    if ((right->parent = node->parent))
    {
        if (node == node->parent->right)
        {
            node->parent->right = right;
        }
        else
        {
            node->parent->left = right;
        }
    }
    else
    {
        root = right;
    }
    node->parent = right;  //right��Ϊnode�ĸ�ĸ

    return root;
}


//��������
static rnbode* rb_rotate_right(rnbode* node, rnbode* root)
{
    rnbode* left = node->left;

    if ((node->left = left->right))
    {
        left->right->parent = node;
    }
    left->right = node;

    if ((left->parent = node->parent))
    {
        if (node == node->parent->right)
        {
            node->parent->right = left;
        }
        else
        {
            node->parent->left = left;
        }
    }
    else
    {
        root = left;
    }
    node->parent = left;

    return root;
}


//������������ҽ��
static rnbode* rb_search_auxiliary(int key, rnbode* root, rnbode** save)
{
    rnbode *node = root, *parent = NULL;
    int ret;

    while (node)
    {
        parent = node;
        ret = node->key - key;
        if (0 < ret)
        {
            node = node->left;
        }
        else if (0 > ret)
        {
            node = node->right;
        }
        else
        {
            return node;
        }
    }

    if (save)
    {
        *save = parent;
    }

    return NULL;
}

//��������rb_search_auxiliary���ҽ��
rnbode* rb_search(int key, rnbode* root)
{
    return rb_search_auxiliary(key, root, NULL);
}


//�ġ�������Ĳ���
rnbode* rb_insert(int key, data_t data, rnbode* root)
{
    rnbode *parent = NULL, *node;

    parent = NULL;
    if ((node = rb_search_auxiliary(key, root, &parent)))  //����rb_search_auxiliary�ҵ�������ĵط�
    {
        return root;
    }

    node = rb_new_node(key, data);  //������
    node->parent = parent;
    node->left = node->right = NULL;
    node->color = RED;

    if (parent)
    {
        if (parent->key > key)
        {
            parent->left = node;
        }
        else
        {
            parent->right = node;
        }
    }
    else
    {
        root = node;
    }

    return rb_insert_rebalance(node, root);   //������󣬵���rb_insert_rebalance�޸������������
}


//�����3�ֲ������
static rnbode*  rb_insert_rebalance(rnbode *node, rnbode *root)
{
    rnbode *parent, *gparent, *uncle, *tmp;  //��ĸp[z]���游p[p[z]]������y����ʱ���*tmp

    while ((parent = node->parent) && parent->color == RED)
    {
        //parent Ϊnode�ĸ�ĸ���ҵ���ĸ����ɫΪ��ʱ
        gparent = parent->parent;   //gparentΪ�游

        if (parent == gparent->left)  //���游�����Ӽ�Ϊ��ĸʱ��
            //��ʵ����������䣬�޷Ǿ�����˳���ӡ���ĸ���游�Ĺ�ϵ��:D��
        {
            uncle = gparent->right;  //��������ĸ������y���Ǹ�ĸ���Һ��ӡ�

            if (uncle && uncle->color == RED) //���1��z������y�Ǻ�ɫ��
            {
                uncle->color = BLACK;   //��������y��Ϊ��ɫ
                parent->color = BLACK;  //z�ĸ�ĸp[z]Ҳ��Ϊ��ɫ�����z��p[z]���Ǻ�ɫ�����⡣
                gparent->color = RED;
                node = gparent;     //���游�����������z��ָ��z�������㣬����Ϊ��ɫ��
                //�������1�У�ֻ������z��Ϊ��ĸ���Һ��ӵ������
            }
            else                     //���2��z������y�Ǻ�ɫ�ģ�
            {
                if (parent->right == node)  //��zΪ�Һ���
                {
                    root = rb_rotate_left(parent, root); //����[���z���븸ĸ���]
                    tmp = parent;
                    parent = node;
                    node = tmp;     //parent��node ������ɫ
                }
                //���3��z������y�Ǻ�ɫ�ģ���ʱz��Ϊ�����ӡ�
                //ע�⣬1�����3�����������2�仯�����ġ�
                //......2��z���������Ǻ�ɫ�ģ�����������1�ˡ�
                parent->color = BLACK;   //z�ĸ�ĸp[z]��Ϊ��ɫ
                gparent->color = RED;    //ԭ�游�����Ϊ��ɫ
                root = rb_rotate_right(gparent, root); //����[���z�����游���]
            }
        }

        else
        {
            //�ⲿ�����ر�Ϊ���1�У�z��Ϊ�����������д�ġ�
            uncle = gparent->left;  //�游��������Ϊ�����㡣[ԭ�������ϲ���һ����]
            if (uncle && uncle->color == RED)  //���1��z������y�Ǻ�ɫ��
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;           //ͬ�ϡ�
            }
            else                               //���2��z������y�Ǻ�ɫ�ģ�
            {
                if (parent->left == node)  //��zΪ����
                {
                    root = rb_rotate_right(parent, root);  //�Խ��parent��root����
                    tmp = parent;
                    parent = node;
                    node = tmp;       //parent��node ������ɫ
                }
                //�������2�ı仯����Ϊ�����3.
                parent->color = BLACK;
                gparent->color = RED;
                root = rb_rotate_left(gparent, root);   //�Խ��gparent��root����
            }
        }
    }

    root->color = BLACK; //����㣬����������������Ϊ��ɫ��
    return root;      //���ظ���㡣
}


//�������ɾ�����
rnbode* rb_erase(int key, rnbode *root)
{
    rnbode *child, *parent, *old, *left, *node;
    rbcolor color;

    if (!(node = rb_search_auxiliary(key, root, NULL)))  //����rb_search_auxiliary����Ҫɾ���Ľ��
    {
        //printf("%d������,");
        return NULL;
    }

    old = node;

    if (node->left && node->right)
    {
        node = node->right;
        while ((left = node->left) != NULL)
        {
            node = left;
        }
        child = node->right;
        parent = node->parent;
        color = node->color;

        if (child)
        {
            child->parent = parent;
        }
        if (parent)
        {
            if (parent->left == node)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
        else
        {
            root = child;
        }

        if (node->parent == old)
        {
            parent = node;
        }

        node->parent = old->parent;
        node->color = old->color;
        node->right = old->right;
        node->left = old->left;

        if (old->parent)
        {
            if (old->parent->left == old)
            {
                old->parent->left = node;
            }
            else
            {
                old->parent->right = node;
            }
        }
        else
        {
            root = node;
        }

        old->left->parent = node;
        if (old->right)
        {
            old->right->parent = node;
        }
    }
    else
    {
        if (!node->left)
        {
            child = node->right;
        }
        else if (!node->right)
        {
            child = node->left;
        }
        parent = node->parent;
        color = node->color;

        if (child)
        {
            child->parent = parent;
        }
        if (parent)
        {
            if (parent->left == node)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
        else
        {
            root = child;
        }
    }

    free(old);

    if (color == BLACK)
    {
        root = rb_erase_rebalance(child, parent, root); //����rb_erase_rebalance���ָ����������
    }

    return root;
}




//������޸�ɾ����4�����
static rnbode* rb_erase_rebalance(rnbode *node, rnbode *parent, rnbode *root)
{
    rnbode *other, *o_left, *o_right;   //x���ֵ�*other���ֵ�����*o_left,*o_right

    while ((!node || node->color == BLACK) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (other->color == RED)   //���1��x���ֵ�w�Ǻ�ɫ��
            {
                other->color = BLACK;
                parent->color = RED;   //�����У��ı���ɫ��w->�ڡ�p[x]->�졣
                root = rb_rotate_left(parent, root);  //�ٶ�p[x]��һ������
                other = parent->right;  //x�����ֵ�new w ����ת֮ǰw��ĳ�����ӡ���ʵ�����������Ч����
            }
            if ((!other->left || other->left->color == BLACK) &&
                    (!other->right || other->right->color == BLACK))
                //���2��x���ֵ�w�Ǻ�ɫ����w����������Ҳ ���Ǻ�ɫ��

            {
                //����w��w���������Ӷ��Ǻ�ɫ�ģ�����x��w�ϵ�ȥ��һ��ɫ��
                other->color = RED;   //���ǣ��ֵ�w��Ϊ��ɫ��
                node = parent;    //p[x]Ϊ�½��x
                parent = node->parent;  //x<-p[x]
            }
            else                       //���3��x���ֵ�w�Ǻ�ɫ�ģ�
            {
                //�ң�w�������Ǻ�ɫ���Һ���Ϊ��ɫ��
                if (!other->right || other->right->color == BLACK)
                {
                    if ((o_left = other->left))   //w��������left[w]����ɫ������
                    {
                        o_left->color = BLACK;    //w�����ӱ�Ϊ�ɺ�->��ɫ
                    }
                    other->color = RED;           //w�ɺ�->��
                    root = rb_rotate_right(other, root);  //�ٶ�w�����������Ӷ�������ʻָ���
                    other = parent->right;        //�仯��ģ��������Һ��ӣ���Ϊ�µ��ֵܽ��w��
                }
                //���4��x���ֵ�w�Ǻ�ɫ��

                other->color = parent->color;  //���ֵܽڵ�Ⱦ�ɵ�ǰ�ڵ㸸�ڵ����ɫ��
                parent->color = BLACK;  //�ѵ�ǰ�ڵ㸸�ڵ�Ⱦ�ɺ�ɫ
                if (other->right)      //��w���Һ����Ǻ�
                {
                    other->right->color = BLACK;  //�ֵܽڵ�w�Һ���Ⱦ�ɺ�ɫ
                }
                root = rb_rotate_left(parent, root);  //������һ������
                node = root;   //����x��Ϊ����
                break;
            }
        }
        //������������������ԭ��һ�¡������ԡ�
        else
        {
            other = parent->left;
            if (other->color == RED)
            {
                other->color = BLACK;
                parent->color = RED;
                root = rb_rotate_right(parent, root);
                other = parent->left;
            }
            if ((!other->left || other->left->color == BLACK) &&
                    (!other->right || other->right->color == BLACK))
            {
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->left || other->left->color == BLACK)
                {
                    if ((o_right = other->right))
                    {
                        o_right->color = BLACK;
                    }
                    other->color = RED;
                    root = rb_rotate_left(other, root);
                    other = parent->left;
                }
                other->color = parent->color;
                parent->color = BLACK;
                if (other->left)
                {
                    other->left->color = BLACK;
                }
                root = rb_rotate_right(parent, root);
                node = root;
                break;
            }
        }
    }

    if (node)
    {
        node->color = BLACK;  //���node[����������Ϊ�˸����]����Ϊ��ɫ��
    }
    return root;  //����root
}


int main()
{
    int i, count = 100;
    int key;
    data_t data;
    int choose;
    rnbode* root = NULL, *node = NULL;
    while(1)
    {
        printf("1.����ڵ�\n");
        printf("2.�����ڵ�\n");
        printf("3.ɾ���ڵ�\n");
        printf("0.�˳�����\n");
        scanf("%d",&choose);
        switch(choose)
        {
        case 1:
            scanf("%d",&key);

            if ((root = rb_insert(key, data, root)))
            {
                printf("����ؼ���%d�ɹ�����ɫΪ%s��\n",key,rb_search(key,root)->color?"��":"��");
            }
            else
            {
                printf("����%dʧ�ܣ�\n",key);
            }
            break;
        case 2:
            printf("�������ѯ�ؼ��֣�\n");
            scanf("%d",&key);
            if ((node = rb_search(key, root)))
            {
                printf("���ҹؼ���%d�ɹ�����ɫΪ%s��\n",key,rb_search(key,root)->color?"��":"��");
            }
            else
            {
                printf("����%dʧ�ܣ�\n",key);
            }
            break;
        case 3:
            printf("������ɾ���ؼ��֣�\n");
            scanf("%d",&key);
            if ((root = rb_erase(key, root)))
            {
                printf("ɾ���ؼ���%d�ɹ�\n",key);
            }
            else
            {
                printf("%d�����ڣ�ɾ��ʧ��\n",key);
            }
            break;
        case 0:
            exit(-1);
        }
    }

    return 0;
}
