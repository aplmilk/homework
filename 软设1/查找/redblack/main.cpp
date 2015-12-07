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

//一、左旋
static rnbode* rb_rotate_left(rnbode* node, rnbode* root)
{
    rnbode* right = node->right;    //指定指针指向 right<--node->right

    if ((node->right = right->left))
    {
        right->left->parent = node;  //好比上面的注释图，node成为b的父母
    }
    right->left = node;   //node成为right的左孩子

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
    node->parent = right;  //right成为node的父母

    return root;
}


//二、右旋
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


//三、红黑树查找结点
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

//返回上述rb_search_auxiliary查找结果
rnbode* rb_search(int key, rnbode* root)
{
    return rb_search_auxiliary(key, root, NULL);
}


//四、红黑树的插入
rnbode* rb_insert(int key, data_t data, rnbode* root)
{
    rnbode *parent = NULL, *node;

    parent = NULL;
    if ((node = rb_search_auxiliary(key, root, &parent)))  //调用rb_search_auxiliary找到插入结点的地方
    {
        return root;
    }

    node = rb_new_node(key, data);  //分配结点
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

    return rb_insert_rebalance(node, root);   //插入结点后，调用rb_insert_rebalance修复红黑树的性质
}


//红黑树3种插入情况
static rnbode*  rb_insert_rebalance(rnbode *node, rnbode *root)
{
    rnbode *parent, *gparent, *uncle, *tmp;  //父母p[z]、祖父p[p[z]]、叔叔y、临时结点*tmp

    while ((parent = node->parent) && parent->color == RED)
    {
        //parent 为node的父母，且当父母的颜色为红时
        gparent = parent->parent;   //gparent为祖父

        if (parent == gparent->left)  //当祖父的左孩子即为父母时。
            //其实上述几行语句，无非就是理顺孩子、父母、祖父的关系。:D。
        {
            uncle = gparent->right;  //定义叔叔的概念，叔叔y就是父母的右孩子。

            if (uncle && uncle->color == RED) //情况1：z的叔叔y是红色的
            {
                uncle->color = BLACK;   //将叔叔结点y着为黑色
                parent->color = BLACK;  //z的父母p[z]也着为黑色。解决z，p[z]都是红色的问题。
                gparent->color = RED;
                node = gparent;     //将祖父当做新增结点z，指针z上移俩层，且着为红色。
                //上述情况1中，只考虑了z作为父母的右孩子的情况。
            }
            else                     //情况2：z的叔叔y是黑色的，
            {
                if (parent->right == node)  //且z为右孩子
                {
                    root = rb_rotate_left(parent, root); //左旋[结点z，与父母结点]
                    tmp = parent;
                    parent = node;
                    node = tmp;     //parent与node 互换角色
                }
                //情况3：z的叔叔y是黑色的，此时z成为了左孩子。
                //注意，1：情况3是由上述情况2变化而来的。
                //......2：z的叔叔总是黑色的，否则就是情况1了。
                parent->color = BLACK;   //z的父母p[z]着为黑色
                gparent->color = RED;    //原祖父结点着为红色
                root = rb_rotate_right(gparent, root); //右旋[结点z，与祖父结点]
            }
        }

        else
        {
            //这部分是特别为情况1中，z作为左孩子情况，而写的。
            uncle = gparent->left;  //祖父的左孩子作为叔叔结点。[原理还是与上部分一样的]
            if (uncle && uncle->color == RED)  //情况1：z的叔叔y是红色的
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;           //同上。
            }
            else                               //情况2：z的叔叔y是黑色的，
            {
                if (parent->left == node)  //且z为左孩子
                {
                    root = rb_rotate_right(parent, root);  //以结点parent、root右旋
                    tmp = parent;
                    parent = node;
                    node = tmp;       //parent与node 互换角色
                }
                //经过情况2的变化，成为了情况3.
                parent->color = BLACK;
                gparent->color = RED;
                root = rb_rotate_left(gparent, root);   //以结点gparent和root左旋
            }
        }
    }

    root->color = BLACK; //根结点，不论怎样，都得置为黑色。
    return root;      //返回根结点。
}


//红黑树的删除结点
rnbode* rb_erase(int key, rnbode *root)
{
    rnbode *child, *parent, *old, *left, *node;
    rbcolor color;

    if (!(node = rb_search_auxiliary(key, root, NULL)))  //调用rb_search_auxiliary查找要删除的结点
    {
        //printf("%d不存在,");
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
        root = rb_erase_rebalance(child, parent, root); //调用rb_erase_rebalance来恢复红黑树性质
    }

    return root;
}




//红黑树修复删除的4种情况
static rnbode* rb_erase_rebalance(rnbode *node, rnbode *parent, rnbode *root)
{
    rnbode *other, *o_left, *o_right;   //x的兄弟*other，兄弟左孩子*o_left,*o_right

    while ((!node || node->color == BLACK) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (other->color == RED)   //情况1：x的兄弟w是红色的
            {
                other->color = BLACK;
                parent->color = RED;   //上俩行，改变颜色，w->黑、p[x]->红。
                root = rb_rotate_left(parent, root);  //再对p[x]做一次左旋
                other = parent->right;  //x的新兄弟new w 是旋转之前w的某个孩子。其实就是左旋后的效果。
            }
            if ((!other->left || other->left->color == BLACK) &&
                    (!other->right || other->right->color == BLACK))
                //情况2：x的兄弟w是黑色，且w的俩个孩子也 都是黑色的

            {
                //由于w和w的俩个孩子都是黑色的，则在x和w上得去掉一黑色，
                other->color = RED;   //于是，兄弟w变为红色。
                node = parent;    //p[x]为新结点x
                parent = node->parent;  //x<-p[x]
            }
            else                       //情况3：x的兄弟w是黑色的，
            {
                //且，w的左孩子是红色，右孩子为黑色。
                if (!other->right || other->right->color == BLACK)
                {
                    if ((o_left = other->left))   //w和其左孩子left[w]，颜色交换。
                    {
                        o_left->color = BLACK;    //w的左孩子变为由黑->红色
                    }
                    other->color = RED;           //w由黑->红
                    root = rb_rotate_right(other, root);  //再对w进行右旋，从而红黑性质恢复。
                    other = parent->right;        //变化后的，父结点的右孩子，作为新的兄弟结点w。
                }
                //情况4：x的兄弟w是黑色的

                other->color = parent->color;  //把兄弟节点染成当前节点父节点的颜色。
                parent->color = BLACK;  //把当前节点父节点染成黑色
                if (other->right)      //且w的右孩子是红
                {
                    other->right->color = BLACK;  //兄弟节点w右孩子染成黑色
                }
                root = rb_rotate_left(parent, root);  //并再做一次左旋
                node = root;   //并把x置为根。
                break;
            }
        }
        //下述情况与上述情况，原理一致。分析略。
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
        node->color = BLACK;  //最后将node[上述步骤置为了根结点]，改为黑色。
    }
    return root;  //返回root
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
        printf("1.插入节点\n");
        printf("2.搜索节点\n");
        printf("3.删除节点\n");
        printf("0.退出程序\n");
        scanf("%d",&choose);
        switch(choose)
        {
        case 1:
            scanf("%d",&key);

            if ((root = rb_insert(key, data, root)))
            {
                printf("插入关键字%d成功，颜色为%s！\n",key,rb_search(key,root)->color?"黑":"红");
            }
            else
            {
                printf("插入%d失败！\n",key);
            }
            break;
        case 2:
            printf("请输入查询关键字：\n");
            scanf("%d",&key);
            if ((node = rb_search(key, root)))
            {
                printf("查找关键字%d成功，颜色为%s！\n",key,rb_search(key,root)->color?"黑":"红");
            }
            else
            {
                printf("查找%d失败！\n",key);
            }
            break;
        case 3:
            printf("请输入删除关键字：\n");
            scanf("%d",&key);
            if ((root = rb_erase(key, root)))
            {
                printf("删除关键字%d成功\n",key);
            }
            else
            {
                printf("%d不存在，删除失败\n",key);
            }
            break;
        case 0:
            exit(-1);
        }
    }

    return 0;
}
