#include<iostream>
#include<vector>
using namespace std;

struct _TreeNode
{
    int left,right;
    int sum;
    _TreeNode* leftChild;
    _TreeNode* rightChild;
    _TreeNode(int l,int r) : left(l),right(r),leftChild(NULL),rightChild(NULL) { }
};

class NumArray
{
private:
    _TreeNode* build(int left,int right)
    {
        auto node = new _TreeNode(left,right);
        if(right - left == 1)
        {
            node->sum = nums[left];
            return node;
        }
        int mid = left + (right - left) / 2;
        node->leftChild = build(left,mid);
        node->rightChild = build(mid,right);
        node->sum = node->leftChild->sum + node->rightChild->sum;
        return node;
    }


    int query(int i,int j,_TreeNode* tree)
    {
        if(i == tree->left && j == tree->right)
            return tree->sum;
        int mid = tree->left + (tree->right - tree->left) / 2;
        if(j <= mid)
            return query(i,j,tree->leftChild);
        if(i >= mid)
            return query(i,j,tree->rightChild);
        return query(i,mid,tree->leftChild) + query(mid,j,tree->rightChild);
    }

    void updateVal(int i,int delta,_TreeNode* tree)
    {
        tree->sum += delta;
        if(tree->left + 1 == tree->right)
        {
            return;
        }
        int mid = tree->left + (tree->right - tree->left) / 2;
        if(i < mid)
        {
            updateVal(i,delta,tree->leftChild);
        }
        else if(i >= mid)
        {
            updateVal(i,delta,tree->rightChild);
        }
    }

    _TreeNode* root;
    vector<int> nums;
public:

    NumArray(vector<int> &_nums)
    {
        if(_nums.size() == 0)
            return;
        this->nums = _nums;
        root = build(0,nums.size());
    }

    void update(int i, int val)
    {
        int delta = val - nums[i];
        nums[i] = val;
        updateVal(i,delta,root);
    }

    int sumRange(int i, int j)
    {
        return query(i,j+1,root);
    }
};

int main()
{
    vector<int> nums = {1,3,5};
    NumArray na(nums);
    cout<<na.sumRange(1,2)<<endl;
    na.update(1,4);
    cout<<na.sumRange(1,2)<<endl;
    na.update(2,8);
    cout<<na.sumRange(0,2)<<endl;
    int a;
    cin>>a;
    return 0;
}
