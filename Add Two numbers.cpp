#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;
#include <iostream>
#include <string>
#include <math.h>
#include <vector>

//题目描述：给两个非空的链表，表示两个非负的整数。它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字
//请你将两个数相加，并以相同形式返回一个表示和的链表
//你可以假设除了数字0之外，这两个数都不会以0开头。

//解题思路一：
//因为链表是逆序存储的，所以举个例子2->3->4->0,即2340这个数在链表中存储方式为0->4->3->2;
//而9->5->8,即958这个数在链表中存储方式为8->5->9;
//显然2340+958=3298，由于也要以相同形式返回这个和（即同样以逆序方式存储），则输出的值为8923，可以看到，这个输出第一个值就是链表1第一个值和链表2第一个值按照数学加法得到的进位的数。
//可以设置一个头指针，指向结构体ListNode,即类型为* ListNode，同时赋初值为空指针，设置一个尾指针，同样指向结构体ListNode,即类型为* ListNode,也同样赋初值为空指针。
//若头指针不存在，即刚开始的时候，令head=tail=new ListNode(sum%10); 其中sum=n1+n2+carry,n1=L1->val,n2=L2->val,carry的初始值为0，为进位，以后可能会变成1的。
//若头指针存在，即第一次创建(new)ListNode之后，令tail->next= new ListNode(sum%10),tail=tail->next
//最后一步，若进位不为0，即为1呗，还需要在将tail->next=new ListNode(carry) ,返回head即可


//这是自定义的链表节点结构体
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* L1, ListNode* L2)
    {
        ListNode* head = nullptr, *tail = head;
        int carry = 0;
        while (L1 || L2)
        {
            int n1 = L1 ? L1->val : 0;
            int n2 = L2 ? L2->val : 0;
            int sum = n1 + n2 + carry;
            if (!head)
            {
                head = tail = new ListNode(sum % 10);
            }
            else
            {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;

            }
            carry = sum / 10;
            if (L1)
            {
                L1 = L1->next;
            }
            if (L2)
            {
                L2 = L2->next;
            }
            
        }
        if (carry > 0)
        {
            tail->next = new ListNode(carry);
        }
        return head;
    }
};

void test01()
{
    ListNode L1_4 = ListNode(2);
    ListNode L1_3 = ListNode(3, &L1_4);
    ListNode L1_2 = ListNode(4, &L1_3);
    ListNode L1 = ListNode(0, &L1_2);
    ListNode* L1temp = &L1;
    cout << "L1= ";
    for (int i = 0; i < 4; i++)
    {
        cout << L1temp->val;
        L1temp = L1temp->next;
    }
    cout << endl;
    ListNode L2_3 = ListNode(9);
    ListNode L2_2 = ListNode(5,&L2_3);
    ListNode L2 = ListNode(8, &L2_2);
    ListNode* L2temp = &L2;
    cout << "L2= ";
    for (int i = 0; i < 3; i++)
    {
        cout << L2temp->val;
        L2temp = L2temp->next;
    }
    cout << endl;
    Solution solution;
    ListNode *ret=solution.addTwoNumbers(&L1, &L2);
    cout << "ret=";
    for (int i = 0; i < 4; i++)
    {
        cout << ret->val;
        ret = ret->next;
    }
    cout << endl;
    cout << "如果结果是8923则正确！" << endl;
}


//解题思路二：
////链表是逆序存储的，举个例子8->3->7,即837这个数在链表中存储方式为7->3->8;
//而5->6->4,即564这个数在链表中存储方式为4->6->5;
//显然837+564=1401，由于也要以相同形式返回这个和（即同样以逆序方式存储），则输出的值为1041，可以看到，这个输出第一个值就是链表1第一个值和链表2第一个值按照数学加法得到的进位的数。
//可以设置一个L3指针，指向结构体ListNode,即类型为* ListNode，同时赋初值为ListNode(0),即值为0，next为空指针，设置一个L4指针，同样指向结构体ListNode,即类型为* ListNode,也同样赋初值为ListNode(0)。
//灵魂的地方是设计了一个缓存和sumtemp,其可以表示每一位加法之后的和
//若L3或L4或sumtemp存在，则L4->next 指向new ListNode(sumtemp%10),否则退出
//最后返回L3->next即可,以为L3的val为0,从next开始生效，即L3存储的第二个数字生效。

class Solution2
{
public:
    ListNode* addTwoNumbers(ListNode* L1, ListNode* L2)
    {
        ListNode* L3 = new ListNode(0), * L4 = L3;
        int sumtemp = 0;
        while (L1 || L2 || sumtemp)
        {
            if (L1)
            {
                sumtemp += L1->val;
                L1 = L1->next;
            }
            if (L2)
            {
                sumtemp += L2->val;
                L2 = L2->next;
            }
            L4->next = new ListNode(sumtemp % 10);
            L4 = L4->next;
            sumtemp /= 10;
        }
        return L3->next;

    }
};

void test02()
{

    ListNode L1_3= ListNode(8);
    ListNode L1_2 = ListNode(3, &L1_3);
    ListNode L1 = ListNode(7, &L1_2);
    ListNode* L1temp = &L1;
    cout << "L1= ";
    for (int i = 0; i < 3; i++)
    {
        cout << L1temp->val;
        L1temp = L1temp->next;
    }
    cout << endl;
    ListNode L2_3 = ListNode(5);
    ListNode L2_2 = ListNode(6, &L2_3);
    ListNode L2 = ListNode(4, &L2_2);
    ListNode* L2temp = &L2;
    cout << "L2= ";
    for (int i = 0; i < 3; i++)
    {
        cout << L2temp->val;
        L2temp = L2temp->next;
    }
    cout << endl;
    Solution solution2;
    ListNode* ret = solution2.addTwoNumbers(&L1, &L2);
    cout << "ret=";
    for (int i = 0; i < 4; i++)
    {
        cout << ret->val;
        ret = ret->next;
    }
    cout << endl;
    cout << "如果结果是1041则正确！" << endl;
}









int main() {

    test01();
    cout << "---------这是两种解法的华丽分割线--------------" << endl;
    test02();
	system("pause");
	return 0;
}
